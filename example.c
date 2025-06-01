/* Compile with `gcc -E example.c` to see the preprocessor output.
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
MAP_INC(1,2,3,4)
MAP_INC(MAP_INC(1,2,3,4))
/* Pass user-defined data and an index to each invocation */
#define PRINT_STREAM_I(x, stream, index) fprintf (stream, "%d: %d\n", index, x);
MAP_UD_I(PRINT_STREAM_I, stderr,
	1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
	11, 12, 13, 14, 15, 16, 17, 18, 19, 20,
	21, 22, 23, 24, 25, 26, 27, 28, 29, 30,
	31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
	41, 42, 43, 44, 45, 46, 47, 48, 49, 50,
	51, 52, 53, 54, 55, 56, 57, 58, 59, 60,
	61, 62, 63, 64, 65, 66, 67, 68, 69, 70,
	71, 72, 73, 74, 75, 76, 77, 78, 79, 80,
	81, 82, 83, 84, 85, 86, 87, 88, 89, 90,
	91, 92, 93, 94, 95, 96, 97, 98, 99, 100,
	101, 102, 103, 104, 105, 106, 107, 108, 109
)

/* Pass user-defined data and an index to each list invocation */
#define INVOKE_I(x, fun, index) fun(index, x)
int arr2 [] = { MAP_LIST_UD_I(INVOKE_I, map2, 1, 2, 3, 4, 5) };
