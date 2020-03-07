void test() {
  int a, b, c, d, e, f;
  a = 0;
  c = 1;
  do
  {
      c = a + 1;
      c = c * b;
      if (b > 9) {
          f = d * c;
          c = f - 3;
      } else {
          a = e + 1;
          e = d / 2;
      }
      a = b;
  } while (a < 9);
  a = a + 1;
}

int main(int argc, char** argv) {
	test();
    return 0;
}