#include "./preproc.h"

#ifndef PL_IOTA_FOR
 #error incorrect usage
#else
 #ifndef PL_IOTA
  #define DETAIL_PL_IOTA (PL_CALL(PL_AT_0, PL_IOTA_FOR))
 #endif
 #ifndef DETAIL_PL_IOTA0
  #if DETAIL_PL_IOTA & (1ull << 0)
   #define DETAIL_PL_IOTA0 1
  #else
   #define DETAIL_PL_IOTA0 0
  #endif
  #if DETAIL_PL_IOTA & (1ull << 1)
   #define DETAIL_PL_IOTA1 1
  #else
   #define DETAIL_PL_IOTA1 0
  #endif
  #if DETAIL_PL_IOTA & (1ull << 2)
   #define DETAIL_PL_IOTA2 1
  #else
   #define DETAIL_PL_IOTA2 0
  #endif
  #if DETAIL_PL_IOTA & (1ull << 3)
   #define DETAIL_PL_IOTA3 1
  #else
   #define DETAIL_PL_IOTA3 0
  #endif
  #if DETAIL_PL_IOTA & (1ull << 4)
   #define DETAIL_PL_IOTA4 1
  #else
   #define DETAIL_PL_IOTA4 0
  #endif
  #if DETAIL_PL_IOTA & (1ull << 5)
   #define DETAIL_PL_IOTA5 1
  #else
   #define DETAIL_PL_IOTA5 0
  #endif
  #if DETAIL_PL_IOTA & (1ull << 6)
   #define DETAIL_PL_IOTA6 1
  #else
   #define DETAIL_PL_IOTA6 0
  #endif
  #if DETAIL_PL_IOTA & (1ull << 7)
   #define DETAIL_PL_IOTA7 1
  #else
   #define DETAIL_PL_IOTA7 0
  #endif
  #if DETAIL_PL_IOTA & (1ull << 8)
   #define DETAIL_PL_IOTA8 1
  #else
   #define DETAIL_PL_IOTA8 0
  #endif
  #if DETAIL_PL_IOTA & (1ull << 9)
   #define DETAIL_PL_IOTA9 1
  #else
   #define DETAIL_PL_IOTA9 0
  #endif
  #if DETAIL_PL_IOTA & (1ull << 10)
   #define DETAIL_PL_IOTA10 1
  #else
   #define DETAIL_PL_IOTA10 0
  #endif
  #if DETAIL_PL_IOTA & (1ull << 11)
   #define DETAIL_PL_IOTA11 1
  #else
   #define DETAIL_PL_IOTA11 0
  #endif
  #if DETAIL_PL_IOTA & (1ull << 12)
   #define DETAIL_PL_IOTA12 1
  #else
   #define DETAIL_PL_IOTA12 0
  #endif
  #if DETAIL_PL_IOTA & (1ull << 13)
   #define DETAIL_PL_IOTA13 1
  #else
   #define DETAIL_PL_IOTA13 0
  #endif
  #if DETAIL_PL_IOTA & (1ull << 14)
   #define DETAIL_PL_IOTA14 1
  #else
   #define DETAIL_PL_IOTA14 0
  #endif
  #if DETAIL_PL_IOTA & (1ull << 15)
   #define DETAIL_PL_IOTA15 1
  #else
   #define DETAIL_PL_IOTA15 0
  #endif
  #if DETAIL_PL_IOTA & (1ull << 16)
   #define DETAIL_PL_IOTA16 1
  #else
   #define DETAIL_PL_IOTA16 0
  #endif
  #if DETAIL_PL_IOTA & (1ull << 17)
   #define DETAIL_PL_IOTA17 1
  #else
   #define DETAIL_PL_IOTA17 0
  #endif
  #if DETAIL_PL_IOTA & (1ull << 18)
   #define DETAIL_PL_IOTA18 1
  #else
   #define DETAIL_PL_IOTA18 0
  #endif
  #if DETAIL_PL_IOTA & (1ull << 19)
   #define DETAIL_PL_IOTA19 1
  #else
   #define DETAIL_PL_IOTA19 0
  #endif
  #if DETAIL_PL_IOTA & (1ull << 20)
   #define DETAIL_PL_IOTA20 1
  #else
   #define DETAIL_PL_IOTA20 0
  #endif
  #if DETAIL_PL_IOTA & (1ull << 21)
   #define DETAIL_PL_IOTA21 1
  #else
   #define DETAIL_PL_IOTA21 0
  #endif
  #if DETAIL_PL_IOTA & (1ull << 22)
   #define DETAIL_PL_IOTA22 1
  #else
   #define DETAIL_PL_IOTA22 0
  #endif
  #if DETAIL_PL_IOTA & (1ull << 23)
   #define DETAIL_PL_IOTA23 1
  #else
   #define DETAIL_PL_IOTA23 0
  #endif
  #if DETAIL_PL_IOTA & (1ull << 24)
   #define DETAIL_PL_IOTA24 1
  #else
   #define DETAIL_PL_IOTA24 0
  #endif
  #if DETAIL_PL_IOTA & (1ull << 25)
   #define DETAIL_PL_IOTA25 1
  #else
   #define DETAIL_PL_IOTA25 0
  #endif
  #if DETAIL_PL_IOTA & (1ull << 26)
   #define DETAIL_PL_IOTA26 1
  #else
   #define DETAIL_PL_IOTA26 0
  #endif
  #if DETAIL_PL_IOTA & (1ull << 27)
   #define DETAIL_PL_IOTA27 1
  #else
   #define DETAIL_PL_IOTA27 0
  #endif
  #if DETAIL_PL_IOTA & (1ull << 28)
   #define DETAIL_PL_IOTA28 1
  #else
   #define DETAIL_PL_IOTA28 0
  #endif
  #if DETAIL_PL_IOTA & (1ull << 29)
   #define DETAIL_PL_IOTA29 1
  #else
   #define DETAIL_PL_IOTA29 0
  #endif
  #if DETAIL_PL_IOTA & (1ull << 30)
   #define DETAIL_PL_IOTA30 1
  #else
   #define DETAIL_PL_IOTA30 0
  #endif
  #if DETAIL_PL_IOTA & (1ull << 31)
   #define DETAIL_PL_IOTA31 1
  #else
   #define DETAIL_PL_IOTA31 0
  #endif
  #if DETAIL_PL_IOTA & (1ull << 32)
   #define DETAIL_PL_IOTA32 1
  #else
   #define DETAIL_PL_IOTA32 0
  #endif
  #if DETAIL_PL_IOTA & (1ull << 33)
   #define DETAIL_PL_IOTA33 1
  #else
   #define DETAIL_PL_IOTA33 0
  #endif
  #if DETAIL_PL_IOTA & (1ull << 34)
   #define DETAIL_PL_IOTA34 1
  #else
   #define DETAIL_PL_IOTA34 0
  #endif
  #if DETAIL_PL_IOTA & (1ull << 35)
   #define DETAIL_PL_IOTA35 1
  #else
   #define DETAIL_PL_IOTA35 0
  #endif
  #if DETAIL_PL_IOTA & (1ull << 36)
   #define DETAIL_PL_IOTA36 1
  #else
   #define DETAIL_PL_IOTA36 0
  #endif
  #if DETAIL_PL_IOTA & (1ull << 37)
   #define DETAIL_PL_IOTA37 1
  #else
   #define DETAIL_PL_IOTA37 0
  #endif
  #if DETAIL_PL_IOTA & (1ull << 38)
   #define DETAIL_PL_IOTA38 1
  #else
   #define DETAIL_PL_IOTA38 0
  #endif
  #if DETAIL_PL_IOTA & (1ull << 39)
   #define DETAIL_PL_IOTA39 1
  #else
   #define DETAIL_PL_IOTA39 0
  #endif
  #if DETAIL_PL_IOTA & (1ull << 40)
   #define DETAIL_PL_IOTA40 1
  #else
   #define DETAIL_PL_IOTA40 0
  #endif
  #if DETAIL_PL_IOTA & (1ull << 41)
   #define DETAIL_PL_IOTA41 1
  #else
   #define DETAIL_PL_IOTA41 0
  #endif
  #if DETAIL_PL_IOTA & (1ull << 42)
   #define DETAIL_PL_IOTA42 1
  #else
   #define DETAIL_PL_IOTA42 0
  #endif
  #if DETAIL_PL_IOTA & (1ull << 43)
   #define DETAIL_PL_IOTA43 1
  #else
   #define DETAIL_PL_IOTA43 0
  #endif
  #if DETAIL_PL_IOTA & (1ull << 44)
   #define DETAIL_PL_IOTA44 1
  #else
   #define DETAIL_PL_IOTA44 0
  #endif
  #if DETAIL_PL_IOTA & (1ull << 45)
   #define DETAIL_PL_IOTA45 1
  #else
   #define DETAIL_PL_IOTA45 0
  #endif
  #if DETAIL_PL_IOTA & (1ull << 46)
   #define DETAIL_PL_IOTA46 1
  #else
   #define DETAIL_PL_IOTA46 0
  #endif
  #if DETAIL_PL_IOTA & (1ull << 47)
   #define DETAIL_PL_IOTA47 1
  #else
   #define DETAIL_PL_IOTA47 0
  #endif
  #if DETAIL_PL_IOTA & (1ull << 48)
   #define DETAIL_PL_IOTA48 1
  #else
   #define DETAIL_PL_IOTA48 0
  #endif
  #if DETAIL_PL_IOTA & (1ull << 49)
   #define DETAIL_PL_IOTA49 1
  #else
   #define DETAIL_PL_IOTA49 0
  #endif
  #if DETAIL_PL_IOTA & (1ull << 50)
   #define DETAIL_PL_IOTA50 1
  #else
   #define DETAIL_PL_IOTA50 0
  #endif
  #if DETAIL_PL_IOTA & (1ull << 51)
   #define DETAIL_PL_IOTA51 1
  #else
   #define DETAIL_PL_IOTA51 0
  #endif
  #if DETAIL_PL_IOTA & (1ull << 52)
   #define DETAIL_PL_IOTA52 1
  #else
   #define DETAIL_PL_IOTA52 0
  #endif
  #if DETAIL_PL_IOTA & (1ull << 53)
   #define DETAIL_PL_IOTA53 1
  #else
   #define DETAIL_PL_IOTA53 0
  #endif
  #if DETAIL_PL_IOTA & (1ull << 54)
   #define DETAIL_PL_IOTA54 1
  #else
   #define DETAIL_PL_IOTA54 0
  #endif
  #if DETAIL_PL_IOTA & (1ull << 55)
   #define DETAIL_PL_IOTA55 1
  #else
   #define DETAIL_PL_IOTA55 0
  #endif
  #if DETAIL_PL_IOTA & (1ull << 56)
   #define DETAIL_PL_IOTA56 1
  #else
   #define DETAIL_PL_IOTA56 0
  #endif
  #if DETAIL_PL_IOTA & (1ull << 57)
   #define DETAIL_PL_IOTA57 1
  #else
   #define DETAIL_PL_IOTA57 0
  #endif
  #if DETAIL_PL_IOTA & (1ull << 58)
   #define DETAIL_PL_IOTA58 1
  #else
   #define DETAIL_PL_IOTA58 0
  #endif
  #if DETAIL_PL_IOTA & (1ull << 59)
   #define DETAIL_PL_IOTA59 1
  #else
   #define DETAIL_PL_IOTA59 0
  #endif
  #if DETAIL_PL_IOTA & (1ull << 60)
   #define DETAIL_PL_IOTA60 1
  #else
   #define DETAIL_PL_IOTA60 0
  #endif
  #if DETAIL_PL_IOTA & (1ull << 61)
   #define DETAIL_PL_IOTA61 1
  #else
   #define DETAIL_PL_IOTA61 0
  #endif
  #if DETAIL_PL_IOTA & (1ull << 62)
   #define DETAIL_PL_IOTA62 1
  #else
   #define DETAIL_PL_IOTA62 0
  #endif
  #if DETAIL_PL_IOTA & (1ull << 63)
   #define DETAIL_PL_IOTA63 1
  #else
   #define DETAIL_PL_IOTA63 0
  #endif
  #undef DETAIL_PL_IOTA0_
  #undef DETAIL_PL_IOTA1_
  #undef DETAIL_PL_IOTA2_
  #undef DETAIL_PL_IOTA3_
  #undef DETAIL_PL_IOTA4_
  #undef DETAIL_PL_IOTA5_
  #undef DETAIL_PL_IOTA6_
  #undef DETAIL_PL_IOTA7_
  #undef DETAIL_PL_IOTA8_
  #undef DETAIL_PL_IOTA9_
  #undef DETAIL_PL_IOTA10_
  #undef DETAIL_PL_IOTA11_
  #undef DETAIL_PL_IOTA12_
  #undef DETAIL_PL_IOTA13_
  #undef DETAIL_PL_IOTA14_
  #undef DETAIL_PL_IOTA15_
  #undef DETAIL_PL_IOTA16_
  #undef DETAIL_PL_IOTA17_
  #undef DETAIL_PL_IOTA18_
  #undef DETAIL_PL_IOTA19_
  #undef DETAIL_PL_IOTA20_
  #undef DETAIL_PL_IOTA21_
  #undef DETAIL_PL_IOTA22_
  #undef DETAIL_PL_IOTA23_
  #undef DETAIL_PL_IOTA24_
  #undef DETAIL_PL_IOTA25_
  #undef DETAIL_PL_IOTA26_
  #undef DETAIL_PL_IOTA27_
  #undef DETAIL_PL_IOTA28_
  #undef DETAIL_PL_IOTA29_
  #undef DETAIL_PL_IOTA30_
  #undef DETAIL_PL_IOTA31_
  #undef DETAIL_PL_IOTA32_
  #undef DETAIL_PL_IOTA33_
  #undef DETAIL_PL_IOTA34_
  #undef DETAIL_PL_IOTA35_
  #undef DETAIL_PL_IOTA36_
  #undef DETAIL_PL_IOTA37_
  #undef DETAIL_PL_IOTA38_
  #undef DETAIL_PL_IOTA39_
  #undef DETAIL_PL_IOTA40_
  #undef DETAIL_PL_IOTA41_
  #undef DETAIL_PL_IOTA42_
  #undef DETAIL_PL_IOTA43_
  #undef DETAIL_PL_IOTA44_
  #undef DETAIL_PL_IOTA45_
  #undef DETAIL_PL_IOTA46_
  #undef DETAIL_PL_IOTA47_
  #undef DETAIL_PL_IOTA48_
  #undef DETAIL_PL_IOTA49_
  #undef DETAIL_PL_IOTA50_
  #undef DETAIL_PL_IOTA51_
  #undef DETAIL_PL_IOTA52_
  #undef DETAIL_PL_IOTA53_
  #undef DETAIL_PL_IOTA54_
  #undef DETAIL_PL_IOTA55_
  #undef DETAIL_PL_IOTA56_
  #undef DETAIL_PL_IOTA57_
  #undef DETAIL_PL_IOTA58_
  #undef DETAIL_PL_IOTA59_
  #undef DETAIL_PL_IOTA60_
  #undef DETAIL_PL_IOTA61_
  #undef DETAIL_PL_IOTA62_
  #undef DETAIL_PL_IOTA63_
  #undef PL_IOTA
  #define PL_IOTA PL_BITCAT64(DETAIL_PL_IOTA63, DETAIL_PL_IOTA62, DETAIL_PL_IOTA61, DETAIL_PL_IOTA60, DETAIL_PL_IOTA59, DETAIL_PL_IOTA58, DETAIL_PL_IOTA57, DETAIL_PL_IOTA56, DETAIL_PL_IOTA55, DETAIL_PL_IOTA54, DETAIL_PL_IOTA53, DETAIL_PL_IOTA52, DETAIL_PL_IOTA51, DETAIL_PL_IOTA50, DETAIL_PL_IOTA49, DETAIL_PL_IOTA48, DETAIL_PL_IOTA47, DETAIL_PL_IOTA46, DETAIL_PL_IOTA45, DETAIL_PL_IOTA44, DETAIL_PL_IOTA43, DETAIL_PL_IOTA42, DETAIL_PL_IOTA41, DETAIL_PL_IOTA40, DETAIL_PL_IOTA39, DETAIL_PL_IOTA38, DETAIL_PL_IOTA37, DETAIL_PL_IOTA36, DETAIL_PL_IOTA35, DETAIL_PL_IOTA34, DETAIL_PL_IOTA33, DETAIL_PL_IOTA32, DETAIL_PL_IOTA31, DETAIL_PL_IOTA30, DETAIL_PL_IOTA29, DETAIL_PL_IOTA28, DETAIL_PL_IOTA27, DETAIL_PL_IOTA26, DETAIL_PL_IOTA25, DETAIL_PL_IOTA24, DETAIL_PL_IOTA23, DETAIL_PL_IOTA22, DETAIL_PL_IOTA21, DETAIL_PL_IOTA20, DETAIL_PL_IOTA19, DETAIL_PL_IOTA18, DETAIL_PL_IOTA17, DETAIL_PL_IOTA16, DETAIL_PL_IOTA15, DETAIL_PL_IOTA14, DETAIL_PL_IOTA13, DETAIL_PL_IOTA12, DETAIL_PL_IOTA11, DETAIL_PL_IOTA10, DETAIL_PL_IOTA9, DETAIL_PL_IOTA8, DETAIL_PL_IOTA7, DETAIL_PL_IOTA6, DETAIL_PL_IOTA5, DETAIL_PL_IOTA4, DETAIL_PL_IOTA3, DETAIL_PL_IOTA2, DETAIL_PL_IOTA1, DETAIL_PL_IOTA0)
 #else
  #if DETAIL_PL_IOTA & (1ull << 0)
   #define DETAIL_PL_IOTA0_ 1
  #else
   #define DETAIL_PL_IOTA0_ 0
  #endif
  #if DETAIL_PL_IOTA & (1ull << 1)
   #define DETAIL_PL_IOTA1_ 1
  #else
   #define DETAIL_PL_IOTA1_ 0
  #endif
  #if DETAIL_PL_IOTA & (1ull << 2)
   #define DETAIL_PL_IOTA2_ 1
  #else
   #define DETAIL_PL_IOTA2_ 0
  #endif
  #if DETAIL_PL_IOTA & (1ull << 3)
   #define DETAIL_PL_IOTA3_ 1
  #else
   #define DETAIL_PL_IOTA3_ 0
  #endif
  #if DETAIL_PL_IOTA & (1ull << 4)
   #define DETAIL_PL_IOTA4_ 1
  #else
   #define DETAIL_PL_IOTA4_ 0
  #endif
  #if DETAIL_PL_IOTA & (1ull << 5)
   #define DETAIL_PL_IOTA5_ 1
  #else
   #define DETAIL_PL_IOTA5_ 0
  #endif
  #if DETAIL_PL_IOTA & (1ull << 6)
   #define DETAIL_PL_IOTA6_ 1
  #else
   #define DETAIL_PL_IOTA6_ 0
  #endif
  #if DETAIL_PL_IOTA & (1ull << 7)
   #define DETAIL_PL_IOTA7_ 1
  #else
   #define DETAIL_PL_IOTA7_ 0
  #endif
  #if DETAIL_PL_IOTA & (1ull << 8)
   #define DETAIL_PL_IOTA8_ 1
  #else
   #define DETAIL_PL_IOTA8_ 0
  #endif
  #if DETAIL_PL_IOTA & (1ull << 9)
   #define DETAIL_PL_IOTA9_ 1
  #else
   #define DETAIL_PL_IOTA9_ 0
  #endif
  #if DETAIL_PL_IOTA & (1ull << 10)
   #define DETAIL_PL_IOTA10_ 1
  #else
   #define DETAIL_PL_IOTA10_ 0
  #endif
  #if DETAIL_PL_IOTA & (1ull << 11)
   #define DETAIL_PL_IOTA11_ 1
  #else
   #define DETAIL_PL_IOTA11_ 0
  #endif
  #if DETAIL_PL_IOTA & (1ull << 12)
   #define DETAIL_PL_IOTA12_ 1
  #else
   #define DETAIL_PL_IOTA12_ 0
  #endif
  #if DETAIL_PL_IOTA & (1ull << 13)
   #define DETAIL_PL_IOTA13_ 1
  #else
   #define DETAIL_PL_IOTA13_ 0
  #endif
  #if DETAIL_PL_IOTA & (1ull << 14)
   #define DETAIL_PL_IOTA14_ 1
  #else
   #define DETAIL_PL_IOTA14_ 0
  #endif
  #if DETAIL_PL_IOTA & (1ull << 15)
   #define DETAIL_PL_IOTA15_ 1
  #else
   #define DETAIL_PL_IOTA15_ 0
  #endif
  #if DETAIL_PL_IOTA & (1ull << 16)
   #define DETAIL_PL_IOTA16_ 1
  #else
   #define DETAIL_PL_IOTA16_ 0
  #endif
  #if DETAIL_PL_IOTA & (1ull << 17)
   #define DETAIL_PL_IOTA17_ 1
  #else
   #define DETAIL_PL_IOTA17_ 0
  #endif
  #if DETAIL_PL_IOTA & (1ull << 18)
   #define DETAIL_PL_IOTA18_ 1
  #else
   #define DETAIL_PL_IOTA18_ 0
  #endif
  #if DETAIL_PL_IOTA & (1ull << 19)
   #define DETAIL_PL_IOTA19_ 1
  #else
   #define DETAIL_PL_IOTA19_ 0
  #endif
  #if DETAIL_PL_IOTA & (1ull << 20)
   #define DETAIL_PL_IOTA20_ 1
  #else
   #define DETAIL_PL_IOTA20_ 0
  #endif
  #if DETAIL_PL_IOTA & (1ull << 21)
   #define DETAIL_PL_IOTA21_ 1
  #else
   #define DETAIL_PL_IOTA21_ 0
  #endif
  #if DETAIL_PL_IOTA & (1ull << 22)
   #define DETAIL_PL_IOTA22_ 1
  #else
   #define DETAIL_PL_IOTA22_ 0
  #endif
  #if DETAIL_PL_IOTA & (1ull << 23)
   #define DETAIL_PL_IOTA23_ 1
  #else
   #define DETAIL_PL_IOTA23_ 0
  #endif
  #if DETAIL_PL_IOTA & (1ull << 24)
   #define DETAIL_PL_IOTA24_ 1
  #else
   #define DETAIL_PL_IOTA24_ 0
  #endif
  #if DETAIL_PL_IOTA & (1ull << 25)
   #define DETAIL_PL_IOTA25_ 1
  #else
   #define DETAIL_PL_IOTA25_ 0
  #endif
  #if DETAIL_PL_IOTA & (1ull << 26)
   #define DETAIL_PL_IOTA26_ 1
  #else
   #define DETAIL_PL_IOTA26_ 0
  #endif
  #if DETAIL_PL_IOTA & (1ull << 27)
   #define DETAIL_PL_IOTA27_ 1
  #else
   #define DETAIL_PL_IOTA27_ 0
  #endif
  #if DETAIL_PL_IOTA & (1ull << 28)
   #define DETAIL_PL_IOTA28_ 1
  #else
   #define DETAIL_PL_IOTA28_ 0
  #endif
  #if DETAIL_PL_IOTA & (1ull << 29)
   #define DETAIL_PL_IOTA29_ 1
  #else
   #define DETAIL_PL_IOTA29_ 0
  #endif
  #if DETAIL_PL_IOTA & (1ull << 30)
   #define DETAIL_PL_IOTA30_ 1
  #else
   #define DETAIL_PL_IOTA30_ 0
  #endif
  #if DETAIL_PL_IOTA & (1ull << 31)
   #define DETAIL_PL_IOTA31_ 1
  #else
   #define DETAIL_PL_IOTA31_ 0
  #endif
  #if DETAIL_PL_IOTA & (1ull << 32)
   #define DETAIL_PL_IOTA32_ 1
  #else
   #define DETAIL_PL_IOTA32_ 0
  #endif
  #if DETAIL_PL_IOTA & (1ull << 33)
   #define DETAIL_PL_IOTA33_ 1
  #else
   #define DETAIL_PL_IOTA33_ 0
  #endif
  #if DETAIL_PL_IOTA & (1ull << 34)
   #define DETAIL_PL_IOTA34_ 1
  #else
   #define DETAIL_PL_IOTA34_ 0
  #endif
  #if DETAIL_PL_IOTA & (1ull << 35)
   #define DETAIL_PL_IOTA35_ 1
  #else
   #define DETAIL_PL_IOTA35_ 0
  #endif
  #if DETAIL_PL_IOTA & (1ull << 36)
   #define DETAIL_PL_IOTA36_ 1
  #else
   #define DETAIL_PL_IOTA36_ 0
  #endif
  #if DETAIL_PL_IOTA & (1ull << 37)
   #define DETAIL_PL_IOTA37_ 1
  #else
   #define DETAIL_PL_IOTA37_ 0
  #endif
  #if DETAIL_PL_IOTA & (1ull << 38)
   #define DETAIL_PL_IOTA38_ 1
  #else
   #define DETAIL_PL_IOTA38_ 0
  #endif
  #if DETAIL_PL_IOTA & (1ull << 39)
   #define DETAIL_PL_IOTA39_ 1
  #else
   #define DETAIL_PL_IOTA39_ 0
  #endif
  #if DETAIL_PL_IOTA & (1ull << 40)
   #define DETAIL_PL_IOTA40_ 1
  #else
   #define DETAIL_PL_IOTA40_ 0
  #endif
  #if DETAIL_PL_IOTA & (1ull << 41)
   #define DETAIL_PL_IOTA41_ 1
  #else
   #define DETAIL_PL_IOTA41_ 0
  #endif
  #if DETAIL_PL_IOTA & (1ull << 42)
   #define DETAIL_PL_IOTA42_ 1
  #else
   #define DETAIL_PL_IOTA42_ 0
  #endif
  #if DETAIL_PL_IOTA & (1ull << 43)
   #define DETAIL_PL_IOTA43_ 1
  #else
   #define DETAIL_PL_IOTA43_ 0
  #endif
  #if DETAIL_PL_IOTA & (1ull << 44)
   #define DETAIL_PL_IOTA44_ 1
  #else
   #define DETAIL_PL_IOTA44_ 0
  #endif
  #if DETAIL_PL_IOTA & (1ull << 45)
   #define DETAIL_PL_IOTA45_ 1
  #else
   #define DETAIL_PL_IOTA45_ 0
  #endif
  #if DETAIL_PL_IOTA & (1ull << 46)
   #define DETAIL_PL_IOTA46_ 1
  #else
   #define DETAIL_PL_IOTA46_ 0
  #endif
  #if DETAIL_PL_IOTA & (1ull << 47)
   #define DETAIL_PL_IOTA47_ 1
  #else
   #define DETAIL_PL_IOTA47_ 0
  #endif
  #if DETAIL_PL_IOTA & (1ull << 48)
   #define DETAIL_PL_IOTA48_ 1
  #else
   #define DETAIL_PL_IOTA48_ 0
  #endif
  #if DETAIL_PL_IOTA & (1ull << 49)
   #define DETAIL_PL_IOTA49_ 1
  #else
   #define DETAIL_PL_IOTA49_ 0
  #endif
  #if DETAIL_PL_IOTA & (1ull << 50)
   #define DETAIL_PL_IOTA50_ 1
  #else
   #define DETAIL_PL_IOTA50_ 0
  #endif
  #if DETAIL_PL_IOTA & (1ull << 51)
   #define DETAIL_PL_IOTA51_ 1
  #else
   #define DETAIL_PL_IOTA51_ 0
  #endif
  #if DETAIL_PL_IOTA & (1ull << 52)
   #define DETAIL_PL_IOTA52_ 1
  #else
   #define DETAIL_PL_IOTA52_ 0
  #endif
  #if DETAIL_PL_IOTA & (1ull << 53)
   #define DETAIL_PL_IOTA53_ 1
  #else
   #define DETAIL_PL_IOTA53_ 0
  #endif
  #if DETAIL_PL_IOTA & (1ull << 54)
   #define DETAIL_PL_IOTA54_ 1
  #else
   #define DETAIL_PL_IOTA54_ 0
  #endif
  #if DETAIL_PL_IOTA & (1ull << 55)
   #define DETAIL_PL_IOTA55_ 1
  #else
   #define DETAIL_PL_IOTA55_ 0
  #endif
  #if DETAIL_PL_IOTA & (1ull << 56)
   #define DETAIL_PL_IOTA56_ 1
  #else
   #define DETAIL_PL_IOTA56_ 0
  #endif
  #if DETAIL_PL_IOTA & (1ull << 57)
   #define DETAIL_PL_IOTA57_ 1
  #else
   #define DETAIL_PL_IOTA57_ 0
  #endif
  #if DETAIL_PL_IOTA & (1ull << 58)
   #define DETAIL_PL_IOTA58_ 1
  #else
   #define DETAIL_PL_IOTA58_ 0
  #endif
  #if DETAIL_PL_IOTA & (1ull << 59)
   #define DETAIL_PL_IOTA59_ 1
  #else
   #define DETAIL_PL_IOTA59_ 0
  #endif
  #if DETAIL_PL_IOTA & (1ull << 60)
   #define DETAIL_PL_IOTA60_ 1
  #else
   #define DETAIL_PL_IOTA60_ 0
  #endif
  #if DETAIL_PL_IOTA & (1ull << 61)
   #define DETAIL_PL_IOTA61_ 1
  #else
   #define DETAIL_PL_IOTA61_ 0
  #endif
  #if DETAIL_PL_IOTA & (1ull << 62)
   #define DETAIL_PL_IOTA62_ 1
  #else
   #define DETAIL_PL_IOTA62_ 0
  #endif
  #if DETAIL_PL_IOTA & (1ull << 63)
   #define DETAIL_PL_IOTA63_ 1
  #else
   #define DETAIL_PL_IOTA63_ 0
  #endif
  #undef DETAIL_PL_IOTA0
  #undef DETAIL_PL_IOTA1
  #undef DETAIL_PL_IOTA2
  #undef DETAIL_PL_IOTA3
  #undef DETAIL_PL_IOTA4
  #undef DETAIL_PL_IOTA5
  #undef DETAIL_PL_IOTA6
  #undef DETAIL_PL_IOTA7
  #undef DETAIL_PL_IOTA8
  #undef DETAIL_PL_IOTA9
  #undef DETAIL_PL_IOTA10
  #undef DETAIL_PL_IOTA11
  #undef DETAIL_PL_IOTA12
  #undef DETAIL_PL_IOTA13
  #undef DETAIL_PL_IOTA14
  #undef DETAIL_PL_IOTA15
  #undef DETAIL_PL_IOTA16
  #undef DETAIL_PL_IOTA17
  #undef DETAIL_PL_IOTA18
  #undef DETAIL_PL_IOTA19
  #undef DETAIL_PL_IOTA20
  #undef DETAIL_PL_IOTA21
  #undef DETAIL_PL_IOTA22
  #undef DETAIL_PL_IOTA23
  #undef DETAIL_PL_IOTA24
  #undef DETAIL_PL_IOTA25
  #undef DETAIL_PL_IOTA26
  #undef DETAIL_PL_IOTA27
  #undef DETAIL_PL_IOTA28
  #undef DETAIL_PL_IOTA29
  #undef DETAIL_PL_IOTA30
  #undef DETAIL_PL_IOTA31
  #undef DETAIL_PL_IOTA32
  #undef DETAIL_PL_IOTA33
  #undef DETAIL_PL_IOTA34
  #undef DETAIL_PL_IOTA35
  #undef DETAIL_PL_IOTA36
  #undef DETAIL_PL_IOTA37
  #undef DETAIL_PL_IOTA38
  #undef DETAIL_PL_IOTA39
  #undef DETAIL_PL_IOTA40
  #undef DETAIL_PL_IOTA41
  #undef DETAIL_PL_IOTA42
  #undef DETAIL_PL_IOTA43
  #undef DETAIL_PL_IOTA44
  #undef DETAIL_PL_IOTA45
  #undef DETAIL_PL_IOTA46
  #undef DETAIL_PL_IOTA47
  #undef DETAIL_PL_IOTA48
  #undef DETAIL_PL_IOTA49
  #undef DETAIL_PL_IOTA50
  #undef DETAIL_PL_IOTA51
  #undef DETAIL_PL_IOTA52
  #undef DETAIL_PL_IOTA53
  #undef DETAIL_PL_IOTA54
  #undef DETAIL_PL_IOTA55
  #undef DETAIL_PL_IOTA56
  #undef DETAIL_PL_IOTA57
  #undef DETAIL_PL_IOTA58
  #undef DETAIL_PL_IOTA59
  #undef DETAIL_PL_IOTA60
  #undef DETAIL_PL_IOTA61
  #undef DETAIL_PL_IOTA62
  #undef DETAIL_PL_IOTA63
  #undef PL_IOTA
  #define PL_IOTA PL_BITCAT64(DETAIL_PL_IOTA63_, DETAIL_PL_IOTA62_, DETAIL_PL_IOTA61_, DETAIL_PL_IOTA60_, DETAIL_PL_IOTA59_, DETAIL_PL_IOTA58_, DETAIL_PL_IOTA57_, DETAIL_PL_IOTA56_, DETAIL_PL_IOTA55_, DETAIL_PL_IOTA54_, DETAIL_PL_IOTA53_, DETAIL_PL_IOTA52_, DETAIL_PL_IOTA51_, DETAIL_PL_IOTA50_, DETAIL_PL_IOTA49_, DETAIL_PL_IOTA48_, DETAIL_PL_IOTA47_, DETAIL_PL_IOTA46_, DETAIL_PL_IOTA45_, DETAIL_PL_IOTA44_, DETAIL_PL_IOTA43_, DETAIL_PL_IOTA42_, DETAIL_PL_IOTA41_, DETAIL_PL_IOTA40_, DETAIL_PL_IOTA39_, DETAIL_PL_IOTA38_, DETAIL_PL_IOTA37_, DETAIL_PL_IOTA36_, DETAIL_PL_IOTA35_, DETAIL_PL_IOTA34_, DETAIL_PL_IOTA33_, DETAIL_PL_IOTA32_, DETAIL_PL_IOTA31_, DETAIL_PL_IOTA30_, DETAIL_PL_IOTA29_, DETAIL_PL_IOTA28_, DETAIL_PL_IOTA27_, DETAIL_PL_IOTA26_, DETAIL_PL_IOTA25_, DETAIL_PL_IOTA24_, DETAIL_PL_IOTA23_, DETAIL_PL_IOTA22_, DETAIL_PL_IOTA21_, DETAIL_PL_IOTA20_, DETAIL_PL_IOTA19_, DETAIL_PL_IOTA18_, DETAIL_PL_IOTA17_, DETAIL_PL_IOTA16_, DETAIL_PL_IOTA15_, DETAIL_PL_IOTA14_, DETAIL_PL_IOTA13_, DETAIL_PL_IOTA12_, DETAIL_PL_IOTA11_, DETAIL_PL_IOTA10_, DETAIL_PL_IOTA9_, DETAIL_PL_IOTA8_, DETAIL_PL_IOTA7_, DETAIL_PL_IOTA6_, DETAIL_PL_IOTA5_, DETAIL_PL_IOTA4_, DETAIL_PL_IOTA3_, DETAIL_PL_IOTA2_, DETAIL_PL_IOTA1_, DETAIL_PL_IOTA0_)
 #endif
 #undef DETAIL_PL_IOTA
 #define DETAIL_PL_IOTA (PL_CALL(PL_AT_2, PL_IOTA_FOR))
 #if PL_CALL(PL_AT_1, PL_IOTA_FOR)
  PL_CALL(PL_FROM_3, PL_IOTA_FOR)
  #include __FILE__
 #else
  #undef PL_IOTA_FOR
  #undef PL_IOTA
  #undef DETAIL_PL_IOTA
 #endif
#endif
