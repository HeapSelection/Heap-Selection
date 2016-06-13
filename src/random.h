#pragma once

#include <random>

using namespace std;

static mt19937 r(42);
static uniform_int_distribution<int> dist(1, 100);
static uniform_int_distribution<int> distEasy(0, 10);
static uniform_int_distribution<int> distStrong(0, 1000);
//uniform_int_distribution<int> dist(0, 10);
