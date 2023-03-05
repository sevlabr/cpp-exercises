#include <string>
#include <vector>

using namespace std;

#define MAKE_UNIQ_ID(line) UNIQ_ID##line
#define UNIQ_ID_MAKER(line) MAKE_UNIQ_ID(line)
#define UNIQ_ID UNIQ_ID_MAKER(__LINE__)

int main() {
  int UNIQ_ID = 0;
  string UNIQ_ID = "hello";
  vector<string> UNIQ_ID = {"hello", "world"};
  vector<int> UNIQ_ID = {1, 2, 3, 4};
}

/*
#define UNIQ_ID_IMPL_2(lineno) _a_local_var_##lineno
#define UNIQ_ID_IMPL(lineno) UNIQ_ID_IMPL_2(lineno)
#define UNIQ_ID UNIQ_ID_IMPL(__LINE__) */
