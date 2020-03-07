Move to directory using cd command on your local system. Next, execute the following command. If it executes successfully, proceed to next step.
```bash
cmake -DCMAKE_BUILD_TYPE=Release ../Transforms/LivenessAnalysis
```
Next execute make and it will generate *.so files under build directory. 
```bash
make -j4
```
Move to **test**/ directory and generate ***Test.ll*** file for Test.c using following command. 
```c++
clang -Xclang -disable-O0-optnone Test.c -O0 -S -emit-llvm -o Test.ll
```
Next generate ***Test.bc*** file for Test.ll using following command. 
```c++
opt Test.ll -mem2reg -S -o Test.bc
```
After generating test.bc, execute following command it execute the LLVM Pass. 
```bash
opt -load ../Pass/build/libLLVMLivenessAnalysisPass.so  -Liveness Test.ll
```
