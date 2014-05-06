/*
 * Compile with `gcc -E example.c` to see the preprocessor output.
 */
#include "map.h"

#define STRING(x) char const *x##_string = #x;
MAP(STRING, foo, bar, baz)

#define PARAM(x) int x
void function(MAP_LIST(PARAM, foo, bar, baz));
