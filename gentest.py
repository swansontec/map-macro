#!/usr/bin/python3

import sys

max = 365

file = open(sys.argv[1], "w")

file.write("""#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stddef.h>
#include "map.h"

#define M0(x) "[" #x "]",
#define M1(x) "[" #x "]"
#define M2(x) x
#define M3(x,y) "[" #x "," #y "]",
#define M4(x,y) "[" #x "," #y "]"
#define M5(x,y,z) "[" #x "," #y "," #z "]" ,
#define M6(x,y,z) "[" #x "," #y "," #z "]"


void testArray (const char* got [], const char* expected []){
	for (size_t i = 0; expected [i] != NULL; ++i) {
		assert (strcmp (got [i], expected [i]) == 0);
	}
}

int main () {
""")

def testcase(macro,cb,append,mkelem):
	file.write('\t{\n\t\tconst char* got [] = { '+ macro + ' (' + cb + ',')
	file.write(','.join(str(x) for x in range(0,max)))
	file.write(') ' + append + ' };\n\t\tconst char* expected [] = {')
	file.write(', '.join('"' + mkelem(x) + '"' for x in range(0,max)))
	file.write(', NULL};\n\t\ttestArray(got,expected);\n\t}\n')

testcase('MAP','M0', 'NULL', lambda x : '[' + str(x) + ']')

testcase('MAP_LIST','M1', '', lambda x : '[' + str(x) + ']')

testcase('MAP_UD','M3, ud', 'NULL', lambda x : '[' + str(x) + ',ud]')

testcase('MAP_LIST_UD','M4, ud', '', lambda x : '[' + str(x) + ',ud]')

testcase('MAP_UD_I','M5, ud', 'NULL', lambda x : '[' + str(x) + ',ud,' + str(x) + ']')

testcase('MAP_LIST_UD_I','M6, ud', '', lambda x : '[' + str(x) + ',ud,' + str(x) + ']')


file.write('\tputs("All tests succeeded.");\n\treturn 0;\n}\n')

