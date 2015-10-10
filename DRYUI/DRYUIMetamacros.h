//
//  DRYUIMetamacros.h
//  Pods
//
//  Created by Griffin Schneider on 10/7/15.
//
//

#ifndef DRYUIMetamacros_h
#define DRYUIMetamacros_h

#import <libextobjc/metamacros.h>


// Expands to a comma (,) if there are any arguments. Otherwise, expands to nothing.
#define metamacro_comma_if_any_args(...) metamacro_if_eq(1, metamacro_argcount(bogus , ##__VA_ARGS__))()(,)

#define metamacro_comma_sep(idx) ,

////////////////////////////////////////////////////////////////////////////////////////////////////
#define metamacro_20_minus(N) \
    metamacro_at(N, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0)


////////////////////////////////////////////////////////////////////////////////////////////////////
#define metamacro_foreach_sep_macro(MACRO, SEP, ...) \
    metamacro_foreach_sep_macro_cxt(metamacro_foreach_iter, SEP, MACRO, __VA_ARGS__)

#define metamacro_foreach_sep_macro_cxt(MACRO, SEP, CONTEXT, ...) \
    metamacro_concat(metamacro_foreach_sep_macro_cxt, metamacro_argcount(__VA_ARGS__))(MACRO, SEP, CONTEXT, __VA_ARGS__)


#define metamacro_foreach_sep_macro_recursive(MACRO, SEP, ...) \
    metamacro_foreach_sep_macro_recursive_cxt(metamacro_foreach_recursive_iter, SEP, MACRO, __VA_ARGS__)

#define metamacro_foreach_sep_macro_recursive_cxt(MACRO, SEP, CONTEXT, ...) \
    metamacro_concat(metamacro_foreach_sep_macro_recursive_cxt, metamacro_argcount(__VA_ARGS__))(MACRO, SEP, CONTEXT, __VA_ARGS__)


#define metamacro_for_sep_macro(COUNT, MACRO, SEP) \
    metamacro_for_sep_macro_cxt(COUNT, metamacro_for_iter, SEP, MACRO)

#define metamacro_for_sep_macro_cxt(COUNT, MACRO, SEP, CONTEXT) \
    metamacro_concat(metamacro_for_sep_macro_cxt, COUNT)(MACRO, SEP, CONTEXT)


////////////////////////////////////////////////////////////////////////////////////////////////////
// Iterators to transform the foreach_cxt macros into macros without the cxt.
#define metamacro_for_iter(INDEX, MACRO, ARG) MACRO(INDEX, ARG)
#define metamacro_foreach_iter(INDEX, MACRO, ARG) MACRO(INDEX, ARG)
#define metamacro_foreach_recursive_iter(INDEX, MACRO, ARG) MACRO(INDEX, ARG)


////////////////////////////////////////////////////////////////////////////////////////////////////
#define metamacro_for_sep_macro_cxt0(MACRO, SEP, CONTEXT)
#define metamacro_for_sep_macro_cxt1(MACRO, SEP, CONTEXT) MACRO(0, CONTEXT)

#define metamacro_for_sep_macro_cxt2(MACRO, SEP, CONTEXT) \
    metamacro_for_sep_macro_cxt1(MACRO, SEP, CONTEXT) \
    SEP(0) \
    MACRO(1, CONTEXT)

#define metamacro_for_sep_macro_cxt3(MACRO, SEP, CONTEXT) \
    metamacro_for_sep_macro_cxt2(MACRO, SEP, CONTEXT) \
    SEP(1) \
    MACRO(2, CONTEXT)

#define metamacro_for_sep_macro_cxt4(MACRO, SEP, CONTEXT) \
    metamacro_for_sep_macro_cxt3(MACRO, SEP, CONTEXT) \
    SEP(2) \
    MACRO(3, CONTEXT)

#define metamacro_for_sep_macro_cxt5(MACRO, SEP, CONTEXT) \
    metamacro_for_sep_macro_cxt4(MACRO, SEP, CONTEXT) \
    SEP(3) \
    MACRO(4, CONTEXT)

#define metamacro_for_sep_macro_cxt6(MACRO, SEP, CONTEXT) \
    metamacro_for_sep_macro_cxt5(MACRO, SEP, CONTEXT) \
    SEP(4) \
    MACRO(5, CONTEXT)

#define metamacro_for_sep_macro_cxt7(MACRO, SEP, CONTEXT) \
    metamacro_for_sep_macro_cxt6(MACRO, SEP, CONTEXT) \
    SEP(5) \
    MACRO(6, CONTEXT)

#define metamacro_for_sep_macro_cxt8(MACRO, SEP, CONTEXT) \
    metamacro_for_sep_macro_cxt7(MACRO, SEP, CONTEXT) \
    SEP(6) \
    MACRO(7, CONTEXT)

#define metamacro_for_sep_macro_cxt9(MACRO, SEP, CONTEXT) \
    metamacro_for_sep_macro_cxt8(MACRO, SEP, CONTEXT) \
    SEP(7) \
    MACRO(8, CONTEXT)

#define metamacro_for_sep_macro_cxt10(MACRO, SEP, CONTEXT) \
    metamacro_for_sep_macro_cxt9(MACRO, SEP, CONTEXT) \
    SEP(8) \
    MACRO(9, CONTEXT)

#define metamacro_for_sep_macro_cxt11(MACRO, SEP, CONTEXT) \
    metamacro_for_sep_macro_cxt10(MACRO, SEP, CONTEXT) \
    SEP(9) \
    MACRO(10, CONTEXT)

#define metamacro_for_sep_macro_cxt12(MACRO, SEP, CONTEXT) \
    metamacro_for_sep_macro_cxt11(MACRO, SEP, CONTEXT) \
    SEP(10) \
    MACRO(11, CONTEXT)

#define metamacro_for_sep_macro_cxt13(MACRO, SEP, CONTEXT) \
    metamacro_for_sep_macro_cxt12(MACRO, SEP, CONTEXT) \
    SEP(11) \
    MACRO(12, CONTEXT)

#define metamacro_for_sep_macro_cxt14(MACRO, SEP, CONTEXT) \
    metamacro_for_sep_macro_cxt13(MACRO, SEP, CONTEXT) \
    SEP(12) \
    MACRO(13, CONTEXT)

#define metamacro_for_sep_macro_cxt15(MACRO, SEP, CONTEXT) \
    metamacro_for_sep_macro_cxt14(MACRO, SEP, CONTEXT) \
    SEP(13) \
    MACRO(14, CONTEXT)

#define metamacro_for_sep_macro_cxt16(MACRO, SEP, CONTEXT) \
    metamacro_for_sep_macro_cxt15(MACRO, SEP, CONTEXT) \
    SEP(14) \
    MACRO(15, CONTEXT)

#define metamacro_for_sep_macro_cxt17(MACRO, SEP, CONTEXT) \
    metamacro_for_sep_macro_cxt16(MACRO, SEP, CONTEXT) \
    SEP(15) \
    MACRO(16, CONTEXT)

#define metamacro_for_sep_macro_cxt18(MACRO, SEP, CONTEXT) \
    metamacro_for_sep_macro_cxt17(MACRO, SEP, CONTEXT) \
    SEP(16) \
    MACRO(17, CONTEXT)

#define metamacro_for_sep_macro_cxt19(MACRO, SEP, CONTEXT) \
    metamacro_for_sep_macro_cxt18(MACRO, SEP, CONTEXT) \
    SEP(17) \
    MACRO(18, CONTEXT)

#define metamacro_for_sep_macro_cxt20(MACRO, SEP, CONTEXT) \
    metamacro_for_sep_macro_cxt19(MACRO, SEP, CONTEXT) \
    SEP(18) \
    MACRO(19, CONTEXT)


////////////////////////////////////////////////////////////////////////////////////////////////////
#define metamacro_foreach_sep_macro_cxt0(MACRO, SEP, CONTEXT)
#define metamacro_foreach_sep_macro_cxt1(MACRO, SEP, CONTEXT, _0) MACRO(0, CONTEXT, _0)

#define metamacro_foreach_sep_macro_cxt2(MACRO, SEP, CONTEXT, _0, _1) \
    metamacro_foreach_sep_macro_cxt1(MACRO, SEP, CONTEXT, _0) \
    SEP (0) \
    MACRO(1, CONTEXT, _1)

#define metamacro_foreach_sep_macro_cxt3(MACRO, SEP, CONTEXT, _0, _1, _2) \
    metamacro_foreach_sep_macro_cxt2(MACRO, SEP, CONTEXT, _0, _1) \
    SEP (1) \
    MACRO(2, CONTEXT, _2)

#define metamacro_foreach_sep_macro_cxt4(MACRO, SEP, CONTEXT, _0, _1, _2, _3) \
    metamacro_foreach_sep_macro_cxt3(MACRO, SEP, CONTEXT, _0, _1, _2) \
    SEP (2) \
    MACRO(3, CONTEXT, _3)

#define metamacro_foreach_sep_macro_cxt5(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4) \
    metamacro_foreach_sep_macro_cxt4(MACRO, SEP, CONTEXT, _0, _1, _2, _3) \
    SEP (3) \
    MACRO(4, CONTEXT, _4)

#define metamacro_foreach_sep_macro_cxt6(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5) \
    metamacro_foreach_sep_macro_cxt5(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4) \
    SEP (4) \
    MACRO(5, CONTEXT, _5)

#define metamacro_foreach_sep_macro_cxt7(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6) \
    metamacro_foreach_sep_macro_cxt6(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5) \
    SEP (5) \
    MACRO(6, CONTEXT, _6)

#define metamacro_foreach_sep_macro_cxt8(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7) \
    metamacro_foreach_sep_macro_cxt7(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6) \
    SEP (6) \
    MACRO(7, CONTEXT, _7)

#define metamacro_foreach_sep_macro_cxt9(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8) \
    metamacro_foreach_sep_macro_cxt8(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7) \
    SEP (7) \
    MACRO(8, CONTEXT, _8)

#define metamacro_foreach_sep_macro_cxt10(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9) \
    metamacro_foreach_sep_macro_cxt9(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8) \
    SEP (8) \
    MACRO(9, CONTEXT, _9)

#define metamacro_foreach_sep_macro_cxt11(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10) \
    metamacro_foreach_sep_macro_cxt10(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9) \
    SEP (9) \
    MACRO(10, CONTEXT, _10)

#define metamacro_foreach_sep_macro_cxt12(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11) \
    metamacro_foreach_sep_macro_cxt11(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10) \
    SEP (10) \
    MACRO(11, CONTEXT, _11)

#define metamacro_foreach_sep_macro_cxt13(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12) \
    metamacro_foreach_sep_macro_cxt12(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11) \
    SEP (11) \
    MACRO(12, CONTEXT, _12)

#define metamacro_foreach_sep_macro_cxt14(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13) \
    metamacro_foreach_sep_macro_cxt13(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12) \
    SEP (12) \
    MACRO(13, CONTEXT, _13)

#define metamacro_foreach_sep_macro_cxt15(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14) \
    metamacro_foreach_sep_macro_cxt14(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13) \
    SEP (13) \
    MACRO(14, CONTEXT, _14)

#define metamacro_foreach_sep_macro_cxt16(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15) \
    metamacro_foreach_sep_macro_cxt15(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14) \
    SEP (14) \
    MACRO(15, CONTEXT, _15)

#define metamacro_foreach_sep_macro_cxt17(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16) \
    metamacro_foreach_sep_macro_cxt16(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15) \
    SEP (15) \
    MACRO(16, CONTEXT, _16)

#define metamacro_foreach_sep_macro_cxt18(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17) \
    metamacro_foreach_sep_macro_cxt17(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16) \
    SEP (16) \
    MACRO(17, CONTEXT, _17)

#define metamacro_foreach_sep_macro_cxt19(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18) \
    metamacro_foreach_sep_macro_cxt18(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17) \
    SEP (17) \
    MACRO(18, CONTEXT, _18)

#define metamacro_foreach_sep_macro_cxt20(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19) \
    metamacro_foreach_sep_macro_cxt19(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18) \
    SEP (18) \
    MACRO(19, CONTEXT, _19)


////////////////////////////////////////////////////////////////////////////////////////////////////
#define metamacro_foreach_sep_macro_recursive_cxt0(MACRO, SEP, CONTEXT)
#define metamacro_foreach_sep_macro_recursive_cxt1(MACRO, SEP, CONTEXT, _0) MACRO(0, CONTEXT, _0)

#define metamacro_foreach_sep_macro_recursive_cxt2(MACRO, SEP, CONTEXT, _0, _1) \
    metamacro_foreach_sep_macro_recursive_cxt1(MACRO, SEP, CONTEXT, _0) \
    SEP (0) \
    MACRO(1, CONTEXT, _1)

#define metamacro_foreach_sep_macro_recursive_cxt3(MACRO, SEP, CONTEXT, _0, _1, _2) \
    metamacro_foreach_sep_macro_recursive_cxt2(MACRO, SEP, CONTEXT, _0, _1) \
    SEP (1) \
    MACRO(2, CONTEXT, _2)

#define metamacro_foreach_sep_macro_recursive_cxt4(MACRO, SEP, CONTEXT, _0, _1, _2, _3) \
    metamacro_foreach_sep_macro_recursive_cxt3(MACRO, SEP, CONTEXT, _0, _1, _2) \
    SEP (2) \
    MACRO(3, CONTEXT, _3)

#define metamacro_foreach_sep_macro_recursive_cxt5(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4) \
    metamacro_foreach_sep_macro_recursive_cxt4(MACRO, SEP, CONTEXT, _0, _1, _2, _3) \
    SEP (3) \
    MACRO(4, CONTEXT, _4)

#define metamacro_foreach_sep_macro_recursive_cxt6(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5) \
    metamacro_foreach_sep_macro_recursive_cxt5(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4) \
    SEP (4) \
    MACRO(5, CONTEXT, _5)

#define metamacro_foreach_sep_macro_recursive_cxt7(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6) \
    metamacro_foreach_sep_macro_recursive_cxt6(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5) \
    SEP (5) \
    MACRO(6, CONTEXT, _6)

#define metamacro_foreach_sep_macro_recursive_cxt8(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7) \
    metamacro_foreach_sep_macro_recursive_cxt7(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6) \
    SEP (6) \
    MACRO(7, CONTEXT, _7)

#define metamacro_foreach_sep_macro_recursive_cxt9(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8) \
    metamacro_foreach_sep_macro_recursive_cxt8(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7) \
    SEP (7) \
    MACRO(8, CONTEXT, _8)

#define metamacro_foreach_sep_macro_recursive_cxt10(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9) \
    metamacro_foreach_sep_macro_recursive_cxt9(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8) \
    SEP (8) \
    MACRO(9, CONTEXT, _9)

#define metamacro_foreach_sep_macro_recursive_cxt11(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10) \
    metamacro_foreach_sep_macro_recursive_cxt10(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9) \
    SEP (9) \
    MACRO(10, CONTEXT, _10)

#define metamacro_foreach_sep_macro_recursive_cxt12(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11) \
    metamacro_foreach_sep_macro_recursive_cxt11(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10) \
    SEP (10) \
    MACRO(11, CONTEXT, _11)

#define metamacro_foreach_sep_macro_recursive_cxt13(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12) \
    metamacro_foreach_sep_macro_recursive_cxt12(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11) \
    SEP (11) \
    MACRO(12, CONTEXT, _12)

#define metamacro_foreach_sep_macro_recursive_cxt14(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13) \
    metamacro_foreach_sep_macro_recursive_cxt13(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12) \
    SEP (12) \
    MACRO(13, CONTEXT, _13)

#define metamacro_foreach_sep_macro_recursive_cxt15(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14) \
    metamacro_foreach_sep_macro_recursive_cxt14(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13) \
    SEP (13) \
    MACRO(14, CONTEXT, _14)

#define metamacro_foreach_sep_macro_recursive_cxt16(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15) \
    metamacro_foreach_sep_macro_recursive_cxt15(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14) \
    SEP (14) \
    MACRO(15, CONTEXT, _15)

#define metamacro_foreach_sep_macro_recursive_cxt17(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16) \
    metamacro_foreach_sep_macro_recursive_cxt16(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15) \
    SEP (15) \
    MACRO(16, CONTEXT, _16)

#define metamacro_foreach_sep_macro_recursive_cxt18(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17) \
    metamacro_foreach_sep_macro_recursive_cxt17(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16) \
    SEP (16) \
    MACRO(17, CONTEXT, _17)

#define metamacro_foreach_sep_macro_recursive_cxt19(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18) \
    metamacro_foreach_sep_macro_recursive_cxt18(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17) \
    SEP (17) \
    MACRO(18, CONTEXT, _18)

#define metamacro_foreach_sep_macro_recursive_cxt20(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19) \
    metamacro_foreach_sep_macro_recursive_cxt19(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18) \
    SEP (18) \
    MACRO(19, CONTEXT, _19)


#endif