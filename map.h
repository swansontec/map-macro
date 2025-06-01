/*
 * map-macro by William R Swanson is marked with CC0 1.0 Universal.
 *
 * To view a copy of this license,
 * visit https://creativecommons.org/publicdomain/zero/1.0/
 */

#ifndef MAP_H_INCLUDED
#define MAP_H_INCLUDED

#define EVAL0(...) __VA_ARGS__
#define EVAL1(...) EVAL0(EVAL0(EVAL0(__VA_ARGS__)))
#define EVAL2(...) EVAL1(EVAL1(EVAL1(__VA_ARGS__)))
#define EVAL3(...) EVAL2(EVAL2(EVAL2(__VA_ARGS__)))
#define EVAL4(...) EVAL3(EVAL3(EVAL3(__VA_ARGS__)))
#define EVAL5(...) EVAL4(EVAL4(EVAL4(__VA_ARGS__)))

#ifdef _MSC_VER
// MSVC needs more evaluations
#define EVAL6(...) EVAL5(EVAL5(EVAL5(__VA_ARGS__)))
#define EVAL(...)  EVAL6(EVAL6(__VA_ARGS__))
#else
#define EVAL(...)  EVAL5(__VA_ARGS__)
#endif

#define MAP_END(...)
#define MAP_OUT

#define EMPTY() 
#define DEFER(id) id EMPTY()

#define MAP_GET_END2() 0, MAP_END
#define MAP_GET_END1(...) MAP_GET_END2
#define MAP_GET_END(...) MAP_GET_END1
#define MAP_NEXT0(test, next, ...) next MAP_OUT
#define MAP_NEXT1(test, next) DEFER ( MAP_NEXT0 ) ( test, next, 0)
#define MAP_NEXT(test, next)  MAP_NEXT1(MAP_GET_END test, next)

#define MAP0(f, x, peek, ...) f(x) DEFER ( MAP_NEXT(peek, MAP1) ) ( f, peek, __VA_ARGS__ ) 
#define MAP1(f, x, peek, ...) f(x) DEFER ( MAP_NEXT(peek, MAP0) ) ( f, peek, __VA_ARGS__ )

#define MAP0_UD(f, userdata, x, peek, ...) f(x,userdata) DEFER ( MAP_NEXT(peek, MAP1_UD) ) ( f, userdata, peek, __VA_ARGS__ ) 
#define MAP1_UD(f, userdata, x, peek, ...) f(x,userdata) DEFER ( MAP_NEXT(peek, MAP0_UD) ) ( f, userdata, peek, __VA_ARGS__ ) 

#define MAP0_UD_I(f, userdata, index, x, peek, ...) f(x,userdata, SEQ_TO_INT index ) DEFER ( MAP_NEXT(peek, MAP1_UD_I) ) ( f, userdata, (MAP_INC index), peek, __VA_ARGS__ )
#define MAP1_UD_I(f, userdata, index, x, peek, ...) f(x,userdata, SEQ_TO_INT index ) DEFER ( MAP_NEXT(peek, MAP0_UD_I) ) ( f, userdata, (MAP_INC index), peek, __VA_ARGS__ )

#define MAP_LIST0(f, x, peek, ...) , f(x) DEFER ( MAP_NEXT(peek, MAP_LIST1) ) ( f, peek, __VA_ARGS__ ) 
#define MAP_LIST1(f, x, peek, ...) , f(x) DEFER ( MAP_NEXT(peek, MAP_LIST0) ) ( f, peek, __VA_ARGS__ ) 
#define MAP_LIST2(f, x, peek, ...)   f(x) DEFER ( MAP_NEXT(peek, MAP_LIST1) ) ( f, peek, __VA_ARGS__ ) 

#define MAP_LIST0_UD(f, userdata, x, peek, ...) , f(x, userdata) DEFER ( MAP_NEXT(peek, MAP_LIST1_UD) ) ( f, userdata, peek, __VA_ARGS__ ) 
#define MAP_LIST1_UD(f, userdata, x, peek, ...) , f(x, userdata) DEFER ( MAP_NEXT(peek, MAP_LIST0_UD) ) ( f, userdata, peek, __VA_ARGS__ ) 
#define MAP_LIST2_UD(f, userdata, x, peek, ...)   f(x, userdata) DEFER ( MAP_NEXT(peek, MAP_LIST1_UD) ) ( f, userdata, peek, __VA_ARGS__ ) 

#define MAP_LIST0_UD_I(f, userdata, index, x, peek, ...) , f(x, userdata, SEQ_TO_INT index) DEFER ( MAP_NEXT(peek, MAP_LIST1_UD_I) ) ( f, userdata, (MAP_INC index), peek, __VA_ARGS__ ) 
#define MAP_LIST1_UD_I(f, userdata, index, x, peek, ...) , f(x, userdata, SEQ_TO_INT index) DEFER ( MAP_NEXT(peek, MAP_LIST0_UD_I) ) ( f, userdata, (MAP_INC index), peek, __VA_ARGS__ ) 
#define MAP_LIST2_UD_I(f, userdata, index, x, peek, ...)   f(x, userdata, SEQ_TO_INT index) DEFER ( MAP_NEXT(peek, MAP_LIST0_UD_I) ) ( f, userdata, (MAP_INC index), peek, __VA_ARGS__ ) 

/**
 * Applies the function macro `f` to each of the remaining parameters.
 */
#define MAP(f, ...) EVAL(MAP1(f, __VA_ARGS__, ()()(), ()()(), ()()(), 0))

/**
 * Applies the function macro `f` to each of the remaining parameters and
 * inserts commas between the results.
 */
#define MAP_LIST(f, ...) EVAL(MAP_LIST2(f, __VA_ARGS__, ()()(), ()()(), ()()(), 0))

/**
 * Applies the function macro `f` to each of the remaining parameters and passes userdata as the second parameter to each invocation,
 * e.g. MAP_UD(f, x, a, b, c) evaluates to f(a, x) f(b, x) f(c, x)
 */
#define MAP_UD(f, userdata, ...) EVAL(MAP1_UD(f, userdata, __VA_ARGS__, ()()(), ()()(), ()()(), 0))

/**
 * Applies the function macro `f` to each of the remaining parameters, inserts commas between the results,
 * and passes userdata as the second parameter to each invocation,
 * e.g. MAP_LIST_UD(f, x, a, b, c) evaluates to f(a, x), f(b, x), f(c, x)
 */
#define MAP_LIST_UD(f, userdata, ...) EVAL(MAP_LIST2_UD(f, userdata, __VA_ARGS__, ()()(), ()()(), ()()(), 0))

/**
 * Applies the function macro `f` to each of the remaining parameters, passes userdata as the second parameter to each invocation,
 * and the index of the invocation as the third parameter,
 * e.g. MAP_UD_I(f, x, a, b, c) evaluates to f(a, x, 0) f(b, x, 1) f(c, x, 2)
 */
#define MAP_UD_I(f, userdata, ...) EVAL(MAP1_UD_I(f, userdata, (0,0,0,0), __VA_ARGS__, ()()(), ()()(), ()()(), 0))

/**
 * Applies the function macro `f` to each of the remaining parameters, inserts commas between the results,
 * passes userdata as the second parameter to each invocation, and the index of the invocation as the third parameter,
 * e.g. MAP_LIST_UD_I(f, x, a, b, c) evaluates to f(a, x, 0), f(b, x, 1), f(c, x, 2)
 */
#define MAP_LIST_UD_I(f, userdata, ...) EVAL(MAP_LIST2_UD_I(f, userdata, (0,0,0,0), __VA_ARGS__, ()()(), ()()(), ()()(), 0))

// Who said the preprocessor can't do arithmetic :)
#define _ADD_TABLE00 0,0
#define _ADD_TABLE01 0,1
#define _ADD_TABLE02 0,2
#define _ADD_TABLE03 0,3
#define _ADD_TABLE04 0,4
#define _ADD_TABLE05 0,5
#define _ADD_TABLE06 0,6
#define _ADD_TABLE07 0,7
#define _ADD_TABLE08 0,8
#define _ADD_TABLE09 0,9
#define _ADD_TABLE10 0,1
#define _ADD_TABLE11 0,2
#define _ADD_TABLE12 0,3
#define _ADD_TABLE13 0,4
#define _ADD_TABLE14 0,5
#define _ADD_TABLE15 0,6
#define _ADD_TABLE16 0,7
#define _ADD_TABLE17 0,8
#define _ADD_TABLE18 0,9
#define _ADD_TABLE19 1,0
#define _ADD_TABLE20 0,2
#define _ADD_TABLE21 0,3
#define _ADD_TABLE22 0,4
#define _ADD_TABLE23 0,5
#define _ADD_TABLE24 0,6
#define _ADD_TABLE25 0,7
#define _ADD_TABLE26 0,8
#define _ADD_TABLE27 0,9
#define _ADD_TABLE28 1,0
#define _ADD_TABLE29 1,1
#define _ADD_TABLE30 0,3
#define _ADD_TABLE31 0,4
#define _ADD_TABLE32 0,5
#define _ADD_TABLE33 0,6
#define _ADD_TABLE34 0,7
#define _ADD_TABLE35 0,8
#define _ADD_TABLE36 0,9
#define _ADD_TABLE37 1,0
#define _ADD_TABLE38 1,1
#define _ADD_TABLE39 1,2
#define _ADD_TABLE40 0,4
#define _ADD_TABLE41 0,5
#define _ADD_TABLE42 0,6
#define _ADD_TABLE43 0,7
#define _ADD_TABLE44 0,8
#define _ADD_TABLE45 0,9
#define _ADD_TABLE46 1,0
#define _ADD_TABLE47 1,1
#define _ADD_TABLE48 1,2
#define _ADD_TABLE49 1,3
#define _ADD_TABLE50 0,5
#define _ADD_TABLE51 0,6
#define _ADD_TABLE52 0,7
#define _ADD_TABLE53 0,8
#define _ADD_TABLE54 0,9
#define _ADD_TABLE55 1,0
#define _ADD_TABLE56 1,1
#define _ADD_TABLE57 1,2
#define _ADD_TABLE58 1,3
#define _ADD_TABLE59 1,4
#define _ADD_TABLE60 0,6
#define _ADD_TABLE61 0,7
#define _ADD_TABLE62 0,8
#define _ADD_TABLE63 0,9
#define _ADD_TABLE64 1,0
#define _ADD_TABLE65 1,1
#define _ADD_TABLE66 1,2
#define _ADD_TABLE67 1,3
#define _ADD_TABLE68 1,4
#define _ADD_TABLE69 1,5
#define _ADD_TABLE70 0,7
#define _ADD_TABLE71 0,8
#define _ADD_TABLE72 0,9
#define _ADD_TABLE73 1,0
#define _ADD_TABLE74 1,1
#define _ADD_TABLE75 1,2
#define _ADD_TABLE76 1,3
#define _ADD_TABLE77 1,4
#define _ADD_TABLE78 1,5
#define _ADD_TABLE79 1,6
#define _ADD_TABLE80 0,8
#define _ADD_TABLE81 0,9
#define _ADD_TABLE82 1,0
#define _ADD_TABLE83 1,1
#define _ADD_TABLE84 1,2
#define _ADD_TABLE85 1,3
#define _ADD_TABLE86 1,4
#define _ADD_TABLE87 1,5
#define _ADD_TABLE88 1,6
#define _ADD_TABLE89 1,7
#define _ADD_TABLE90 0,9
#define _ADD_TABLE91 1,0
#define _ADD_TABLE92 1,1
#define _ADD_TABLE93 1,2
#define _ADD_TABLE94 1,3
#define _ADD_TABLE95 1,4
#define _ADD_TABLE96 1,5
#define _ADD_TABLE97 1,6
#define _ADD_TABLE98 1,7
#define _ADD_TABLE99 1,8

#define MAP_INC0(_,a) a
#define MAP_INC0_(a) MAP_INC0(a)
#define MAP_INC1(a,_,b) MAP_INC0_(_ADD_TABLE##a##_),b
#define MAP_INC1_(a,b) MAP_INC1(a,b)
#define MAP_INC2(a,b,_,c) MAP_INC1_(a,_ADD_TABLE##b##_),c
#define MAP_INC2_(a,b,c) MAP_INC2(a,b,c)
#define MAP_INC3(a,b,c,_,d) MAP_INC2_(a,b,_ADD_TABLE##c##_),d
#define MAP_INC3_(a,b,c,d) MAP_INC3(a,b,c,d)
#define MAP_INC4(a,b,c,d) MAP_INC3_(a,b,c,_ADD_TABLE1##d)
#define MAP_INC(...) MAP_INC4(__VA_ARGS__)

#define SEQ2_TO_INT0(a,b) b
#define SEQ2_TO_INT1(a,b) a##b
#define SEQ2_TO_INT2(a,b) a##b
#define SEQ2_TO_INT3(a,b) a##b
#define SEQ2_TO_INT4(a,b) a##b
#define SEQ2_TO_INT5(a,b) a##b
#define SEQ2_TO_INT6(a,b) a##b
#define SEQ2_TO_INT7(a,b) a##b
#define SEQ2_TO_INT8(a,b) a##b
#define SEQ2_TO_INT9(a,b) a##b
#define SEQ3_TO_INT0(a,b,c) SEQ2_TO_INT##b(b,c)
#define SEQ3_TO_INT1(a,b,c) a##b##c
#define SEQ3_TO_INT2(a,b,c) a##b##c
#define SEQ3_TO_INT3(a,b,c) a##b##c
#define SEQ3_TO_INT4(a,b,c) a##b##c
#define SEQ3_TO_INT5(a,b,c) a##b##c
#define SEQ3_TO_INT6(a,b,c) a##b##c
#define SEQ3_TO_INT7(a,b,c) a##b##c
#define SEQ3_TO_INT8(a,b,c) a##b##c
#define SEQ3_TO_INT9(a,b,c) a##b##c
#define SEQ4_TO_INT0(a,b,c,d) SEQ3_TO_INT##b(b,c,d)
#define SEQ4_TO_INT1(a,b,c,d) a##b##c##d
#define SEQ4_TO_INT2(a,b,c,d) a##b##c##d
#define SEQ4_TO_INT3(a,b,c,d) a##b##c##d
#define SEQ4_TO_INT4(a,b,c,d) a##b##c##d
#define SEQ4_TO_INT5(a,b,c,d) a##b##c##d
#define SEQ4_TO_INT6(a,b,c,d) a##b##c##d
#define SEQ4_TO_INT7(a,b,c,d) a##b##c##d
#define SEQ4_TO_INT8(a,b,c,d) a##b##c##d
#define SEQ4_TO_INT9(a,b,c,d) a##b##c##d
#define SEQ_TO_INT(a,b,c,d) SEQ4_TO_INT##a(a,b,c,d)

#endif
