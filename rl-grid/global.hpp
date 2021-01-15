#ifndef GLOBAL_H_
#define GLOBAL_H_

// C++ headers
#include <iostream>
#include <cstring>
#include <set>

// Engine headers
#include <network.hpp>

#include <std/activations.hpp>
#include <std/erfs.hpp>
#include <std/optimizers.hpp>

// Constants
#define SIZE	20
#define CHOICES	4
#define R	100.0
#define P	-200.0
#define EPS	1.0

// Namespaces
using namespace std;
using namespace zhetapi;

// Typedefs
typedef pair <int, int> pi;
typedef set <pair <int, int>> spi;

// Global variables
extern char **grid;

extern int ix;
extern int iy;

extern int rx;
extern int ry;

extern int dx[];
extern int dy[];

extern spi path;

// Functions
void print();
void generate();

bool valid(int, int);

#endif
