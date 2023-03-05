#include <iostream>
#include <cstdint>
using namespace std;

int main() {
	unsigned n = 0;
	unsigned r = 0;
	cin >> n >> r;
	uint64_t mass = 0;
	for (unsigned i = 0; i < n; ++i) {
		unsigned w = 0;
		unsigned h = 0;
		unsigned d = 0;
		cin >> w >> h >> d;
		mass += static_cast<uint64_t>(r)*w*h*d;
	}
	cout << mass << endl;
	return 0;
}

/* #include <cstdint>
#include <iostream>

using namespace std;

int main() {
  int N, R;
  cin >> N >> R;
  uint64_t answer = 0;
  for (int i = 0; i < N; ++i) {
    int W, H, D;
    cin >> W >> H >> D;
    answer += static_cast<uint64_t>(W) * H * D;
  }
  answer *= R;
  cout << answer << endl;
  return 0;
} */
