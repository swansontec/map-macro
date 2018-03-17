/*
 * Compile with `gcc -E example.c` to see the preprocessor output.
 */
#include "map.h"

/* Basic `MAP` usage: */
#define STRING(x) char const *x##_string = #x;
MAP(STRING, foo, bar, baz)

/* Basic `MAP_LIST` usage: */
#define PARAM(x) int x
void function(MAP_LIST(PARAM, foo, bar, baz));

/* Test `MAP` with parentheses in the arguments: */
#define CALL(x) putchar x;
MAP(CALL, ('a'), ('b'), ('c'))

/* Test `MAP_LIST` with parentheses in the arguments: */
#define CALL_LIST(x) putchar x
MAP_LIST(CALL_LIST, ('a'), ('b'), ('c'));

/* Pass user-defined data to each invocation */
#define PRINT_STREAM(x, stream) fprintf (stream, "%d\n", x);
MAP_UD(PRINT_STREAM, stderr, 1, 2, 3, 4, 5)

/* Pass user-defined data to each list invocation */
#define INVOKE(x, fun) fun(x)
int arr [] = { MAP_LIST_UD(INVOKE, map, 1, 2, 3, 4, 5) };

/* Pass user-defined data and an index to each invocation */
#define PRINT_STREAM_I(x, stream, index) fprintf (stream, "%d: %d\n", index, x);
MAP_UD_I(PRINT_STREAM_I, stderr, 1, 2, 3, 4, 5)

/* Pass user-defined data and an index to each list invocation */
#define INVOKE_I(x, fun, index) fun(index, x)
int arr2 [] = { MAP_LIST_UD_I(INVOKE_I, map2, 1, 2, 3, 4, 5) };
