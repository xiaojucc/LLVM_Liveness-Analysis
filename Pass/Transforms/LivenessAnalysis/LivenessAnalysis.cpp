#include "llvm/Pass.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/Instruction.h"
#include <string>
#include <map>
#include <typeinfo>
#include "llvm/IR/CFG.h"
#include <list>
#include <iterator>
#include<fstream>
#include<iomanip>
#include <iostream>

using namespace llvm;
using namespace std;

#define DEBUG_TYPE "Liveness"

using namespace llvm;

namespace lva{
struct Liveness : public FunctionPass {
  string func_name = "test";
  static char ID;
  Liveness() : FunctionPass(ID) {
  }
    // LIVEOUT(b) = Union_(succ(b) as x) (LIVEOUT (x) - VARKILL (x) + UEEXPR (x)) 
    std::map<BasicBlock*, std::vector<std::string>*> killSet;
    std::map<BasicBlock*, std::vector<std::string>*> UEE;
    std::map<BasicBlock*, std::vector<std::string>*> liveOut;
    std::list<BasicBlock*> worklist;

    // Parse the block from top to down, Add operands not existed in the KillSet and Add destination to the kill set
    // FOR i = 1 to k
    // assume oi is “x = y op z”
    // IF y not in VARKILL(n)
    // UEVar(n) = UEVAR(n) + y
    // IF z not in VARKILL(n)
    // UEVar(n) = UEVAR(n) + z
    // VARKILL(n) = VARKILL(n) + x
    void UEVar(BasicBlock* bb){
        std::pair<BasicBlock*,std::vector<std::string>*> *temp = new std::pair<BasicBlock*,std::vector<std::string>*>;
        auto killSet = new std::vector<std::string>;
        auto tempLiveB = new std::vector<std::string>;
        auto UEE = new std::vector<std::string>;
        std::vector<std::string>::iterator killSetIt;
        std::vector<std::string>::iterator UEEIt;
        for (auto& inst : *bb)
        {
          if(inst.getOpcode() == Instruction::Load){
            if(LoadInst *load = dyn_cast<LoadInst>(&inst)){
              Value* v = load->getPointerOperand();
              if(AllocaInst *allocInst = dyn_cast<AllocaInst>(&*v)){
                StringRef varname= allocInst->getName();
                if(std::find(killSet->begin(), killSet->end(), varname) == killSet->end()) {
                  UEEIt = UEE->begin();
                  if (std::find(UEE->begin(),UEE->end(),varname)==UEE->end()){
                      UEE->insert(UEEIt, varname);
                  }
                }
              } 
            } 
          }
          if(inst.getOpcode() == Instruction::Store){
            if (StoreInst *store = dyn_cast<StoreInst>(&inst))
            {
              StringRef vstore = store->getOperand(1)->getName();
              if(std::find(killSet->begin(), killSet->end(), vstore) == killSet->end()){
                killSetIt = killSet->begin();
                killSet->insert(killSetIt, vstore);
              }
            }
          }
        }

        temp->first = bb;
        temp->second = killSet;
        this->killSet.insert(*temp);
        temp->first = bb;
        temp->second = UEE;
        this->UEE.insert(*temp);
    }

    //compute LIVEOUT for each BB 
    bool LiveoutBlock(BasicBlock* basic_block) {
        std::vector<std::string> *liveB;
        auto search = liveOut.find(basic_block);
        if ( search != liveOut.end()){
            // if liveout is already stored
            liveB = search->second;
        }
        else {
            // it is a new BB that haven't store in Liveout
            liveB = new std::vector<std::string>;
        }
        // Update the Liveout of this block based on its successors
        // Union(successors) like Liveout(successor) - Killset(successor) + UEE(successor)
        auto tempLiveB = new std::vector<std::string>;
        for (BasicBlock *Succ : successors(basic_block)) {
            std::vector<std::string> *lSucc;
            std::vector<std::string> *kSucc;
            std::vector<std::string> *uSucc;
            std::vector<std::string> diff;
            std::map<BasicBlock*, std::vector<std::string>*>::iterator searchS;

            // find the killset of this BB
            searchS = killSet.find(Succ);
            kSucc = searchS->second;
            // find the UUE of this BB
            searchS = UEE.find(Succ);
            uSucc = searchS->second;
            // find the liveOut of this BB
            searchS = liveOut.find(Succ);

            // do the formula: Liveout(successor) - Killset(successor)
            if (searchS != liveOut.end()){
                lSucc = searchS->second;
                setDiff(lSucc,kSucc,&diff);
            }

            auto tmp2 = new std::vector<std::string>;
            setUnion(&diff,uSucc,tmp2);

            auto tmp3 = new std::vector<std::string>;
            // union this successor with liveB and store in tmp3
            setUnion(tmp2,tempLiveB,tmp3);
            tempLiveB = tmp3;
        } // end of successor iteration
        // check for liveout change: basic iteration algorithm
        bool changed = false;
        if (tempLiveB->size()!=liveB->size() || search==liveOut.end()){
            changed =true;
        }
        else {
            std::vector<std::string>::iterator it;
            for (it = liveB->begin();it != liveB->end();it++){
                if(std::find(tempLiveB->begin(),tempLiveB->end(),*it)==tempLiveB->end()){ 
                    changed = true;
                    break;
                }
            }
        }
        if (changed){
            if(search!=liveOut.end()){
                search->second = tempLiveB;
            }
            else{
                auto temp = new std::pair<BasicBlock*,std::vector<std::string>*>;
                temp->first = basic_block;
                temp->second = tempLiveB;
                this->liveOut.insert(*temp);
            }
        }
        return changed;
    }

    // back to front traverse, return the order how bb should be visited
    std::list<BasicBlock*>* PostTraverse(BasicBlock* bb, std::list<BasicBlock*> *visited, std::list<BasicBlock*> *order) {
        visited->push_back(bb);
        for (BasicBlock *succ : successors(bb)) { // Parse the left tree and, then the right tree. Technically, it would be recursive call on every successor
            if (std::find(visited->begin(), visited->end(), succ)==visited->end()){
                //if the successor hasn't been visited before, keep on searching on its successors
                visited = PostTraverse(succ,visited,order);
            }
        }
        // when it come the bb which has no successor, put in the order list and return to is ancestoer saying I was visited,is your turn now !
        order->push_back(bb);
        return visited;
    }

    //compute LIVEOUT and add changed basicblock's pred to worklist 
    void LivenessAnalysis(BasicBlock* bb) {
        bool changed = LiveoutBlock(bb);
        if(changed){
            for (BasicBlock *pred : predecessors(bb)) {
                auto el = std::find(worklist.begin(), worklist.end(), pred);
                if(el==worklist.end()){
                    worklist.push_back(pred);
                }
            }
        }
    }

    //print out result
    string printAnalysis(BasicBlock* bb,std::map<BasicBlock*, std::vector<std::string>*> *up_exposed,std::map<BasicBlock*, std::vector<std::string>*> *kill_set,std::map<BasicBlock*, std::vector<std::string>*> *live_out){
      std::string _instr;
      std::string temp;
      temp = bb->getName() ;
      _instr  = _instr+"----- " + temp + " ----- \n" ;
      for (std::map<BasicBlock*, std::vector<std::string>*>::iterator block = up_exposed->begin();block != up_exposed->end();block++){
        if(block->first->getName()==bb->getName()){
           _instr =_instr + "UEVAR: " ;
          for(auto var = block->second->begin(); var!=block->second->end();var++){
            _instr =_instr + *var +" ";
          }
          _instr =_instr+ "\n" ;
        }
      }
      for (std::map<BasicBlock*, std::vector<std::string>*>::iterator block1 = kill_set->begin();block1 != kill_set->end();block1++){
        if(block1->first->getName()==bb->getName()){
          _instr = _instr+ "VARKILL: " ;
          for(auto var = block1->second->begin(); var!=block1->second->end();var++){
             _instr = _instr+ *var+ " ";
          }
          _instr = _instr+ "\n" ;
        }
      }
      for (std::map<BasicBlock*, std::vector<std::string>*>::iterator block2 = live_out->begin();block2 != live_out->end();block2++){
        if(block2->first->getName()==bb->getName()){
          _instr =_instr + "LIVEOUT: " ;
          for(auto var = block2->second->begin(); var!=block2->second->end();var++){
            _instr =_instr + *var+ " ";
          }
           _instr =_instr + "\n" ;
        }
      }
      return _instr;
    }

    void setDiff(std::vector<std::string> *s1,std::vector<std::string> *s2,std::vector<std::string> *s3){
        for (auto it=s1->begin();it!=s1->end();it++){
            if(std::find(s2->begin(),s2->end(),*it)==s2->end()){
                s3->insert(s3->end(),*it);
            }
        }
    }

    void setUnion(std::vector<std::string> *s1,std::vector<std::string> *s2,std::vector<std::string> *s3){
        *s3 = *s1;
        for (auto it=s2->begin();it!=s2->end();it++){
            if(std::find(s1->begin(),s1->end(),*it)==s1->end()){
                s3->insert(s3->end(),*it);
            }
        }
    }

  bool runOnFunction(Function &F) override {
        if (F.getName().compare("main")==0){
            return false;
        }
      killSet.clear();
      UEE.clear();
      liveOut.clear();
      worklist.clear();
      std::string *outputstr = new std::string;
      // initialize UEVar and the Killset on all blocks
      for (auto& basic_block : F)
      {
          UEVar(&basic_block);
      }
      BasicBlock &basicBlock = F.getEntryBlock();
      std::list<BasicBlock*> *visited = new std::list<BasicBlock*>;
      // get the traverse function
      auto visitedBlocks = PostTraverse(&basicBlock,visited,&worklist);
      // initialize the worklist to the entry block, then all others will be automatically added from there
      int i = 0;
      while (!worklist.empty()) // Call Liveness on the entry block until worklist is empty
      {
          auto block = worklist.front();
          LivenessAnalysis(block);
          worklist.pop_front();
          i++;
      }
      //make output file
      for (BasicBlock &BB : F)
      {
        *outputstr = *outputstr + printAnalysis(&BB,&UEE,&killSet,&liveOut);
      }
      errs() << *outputstr;
      std::string filename = F.getParent()->getSourceFileName();
      if(filename == "Test.c"){
        filename = "1.out";
      }else if(filename == "Test2.c"){
        filename = "2.out";
      }else{
        filename.replace(filename.find("c"),string("c").length(),"out");
      }
      ofstream file; 
      file.open(filename);
      file << *outputstr;
      file.close();
      return false;
  }

}; // end of struct Liveness
}  // end of anonymous namespace

char lva::Liveness::ID = 0;
static RegisterPass<lva::Liveness> X("Liveness", "Liveness Pass",
                             false /* Only looks at CFG */,
                             false /* Analysis Pass */);