#include "profile.h"

#include <iostream>
#include <chrono>
#include <string>

using namespace std;
using namespace std::chrono;

LogDuration::~LogDuration() {
    auto finish = steady_clock::now();
    auto dur = finish - start;
    cerr << message
        << duration_cast<milliseconds>(dur).count()
        << " ms" << endl;
}
