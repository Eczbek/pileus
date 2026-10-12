#include "./preproc.h"

#ifndef PL_LOOP
 #error incorrect usage
#else
 #ifndef PL_I
  #define DETAIL_PL_I (PL_APPLY(PL_AT_0, PL_LOOP))
 #endif
 #ifndef DETAIL_PL_I0
  #if DETAIL_PL_I & (1ull << 0)
   #define DETAIL_PL_I0 1
  #else
   #define DETAIL_PL_I0 0
  #endif
  #if DETAIL_PL_I & (1ull << 1)
   #define DETAIL_PL_I1 1
  #else
   #define DETAIL_PL_I1 0
  #endif
  #if DETAIL_PL_I & (1ull << 2)
   #define DETAIL_PL_I2 1
  #else
   #define DETAIL_PL_I2 0
  #endif
  #if DETAIL_PL_I & (1ull << 3)
   #define DETAIL_PL_I3 1
  #else
   #define DETAIL_PL_I3 0
  #endif
  #if DETAIL_PL_I & (1ull << 4)
   #define DETAIL_PL_I4 1
  #else
   #define DETAIL_PL_I4 0
  #endif
  #if DETAIL_PL_I & (1ull << 5)
   #define DETAIL_PL_I5 1
  #else
   #define DETAIL_PL_I5 0
  #endif
  #if DETAIL_PL_I & (1ull << 6)
   #define DETAIL_PL_I6 1
  #else
   #define DETAIL_PL_I6 0
  #endif
  #if DETAIL_PL_I & (1ull << 7)
   #define DETAIL_PL_I7 1
  #else
   #define DETAIL_PL_I7 0
  #endif
  #if DETAIL_PL_I & (1ull << 8)
   #define DETAIL_PL_I8 1
  #else
   #define DETAIL_PL_I8 0
  #endif
  #if DETAIL_PL_I & (1ull << 9)
   #define DETAIL_PL_I9 1
  #else
   #define DETAIL_PL_I9 0
  #endif
  #if DETAIL_PL_I & (1ull << 10)
   #define DETAIL_PL_I10 1
  #else
   #define DETAIL_PL_I10 0
  #endif
  #if DETAIL_PL_I & (1ull << 11)
   #define DETAIL_PL_I11 1
  #else
   #define DETAIL_PL_I11 0
  #endif
  #if DETAIL_PL_I & (1ull << 12)
   #define DETAIL_PL_I12 1
  #else
   #define DETAIL_PL_I12 0
  #endif
  #if DETAIL_PL_I & (1ull << 13)
   #define DETAIL_PL_I13 1
  #else
   #define DETAIL_PL_I13 0
  #endif
  #if DETAIL_PL_I & (1ull << 14)
   #define DETAIL_PL_I14 1
  #else
   #define DETAIL_PL_I14 0
  #endif
  #if DETAIL_PL_I & (1ull << 15)
   #define DETAIL_PL_I15 1
  #else
   #define DETAIL_PL_I15 0
  #endif
  #if DETAIL_PL_I & (1ull << 16)
   #define DETAIL_PL_I16 1
  #else
   #define DETAIL_PL_I16 0
  #endif
  #if DETAIL_PL_I & (1ull << 17)
   #define DETAIL_PL_I17 1
  #else
   #define DETAIL_PL_I17 0
  #endif
  #if DETAIL_PL_I & (1ull << 18)
   #define DETAIL_PL_I18 1
  #else
   #define DETAIL_PL_I18 0
  #endif
  #if DETAIL_PL_I & (1ull << 19)
   #define DETAIL_PL_I19 1
  #else
   #define DETAIL_PL_I19 0
  #endif
  #if DETAIL_PL_I & (1ull << 20)
   #define DETAIL_PL_I20 1
  #else
   #define DETAIL_PL_I20 0
  #endif
  #if DETAIL_PL_I & (1ull << 21)
   #define DETAIL_PL_I21 1
  #else
   #define DETAIL_PL_I21 0
  #endif
  #if DETAIL_PL_I & (1ull << 22)
   #define DETAIL_PL_I22 1
  #else
   #define DETAIL_PL_I22 0
  #endif
  #if DETAIL_PL_I & (1ull << 23)
   #define DETAIL_PL_I23 1
  #else
   #define DETAIL_PL_I23 0
  #endif
  #if DETAIL_PL_I & (1ull << 24)
   #define DETAIL_PL_I24 1
  #else
   #define DETAIL_PL_I24 0
  #endif
  #if DETAIL_PL_I & (1ull << 25)
   #define DETAIL_PL_I25 1
  #else
   #define DETAIL_PL_I25 0
  #endif
  #if DETAIL_PL_I & (1ull << 26)
   #define DETAIL_PL_I26 1
  #else
   #define DETAIL_PL_I26 0
  #endif
  #if DETAIL_PL_I & (1ull << 27)
   #define DETAIL_PL_I27 1
  #else
   #define DETAIL_PL_I27 0
  #endif
  #if DETAIL_PL_I & (1ull << 28)
   #define DETAIL_PL_I28 1
  #else
   #define DETAIL_PL_I28 0
  #endif
  #if DETAIL_PL_I & (1ull << 29)
   #define DETAIL_PL_I29 1
  #else
   #define DETAIL_PL_I29 0
  #endif
  #if DETAIL_PL_I & (1ull << 30)
   #define DETAIL_PL_I30 1
  #else
   #define DETAIL_PL_I30 0
  #endif
  #if DETAIL_PL_I & (1ull << 31)
   #define DETAIL_PL_I31 1
  #else
   #define DETAIL_PL_I31 0
  #endif
  #if DETAIL_PL_I & (1ull << 32)
   #define DETAIL_PL_I32 1
  #else
   #define DETAIL_PL_I32 0
  #endif
  #if DETAIL_PL_I & (1ull << 33)
   #define DETAIL_PL_I33 1
  #else
   #define DETAIL_PL_I33 0
  #endif
  #if DETAIL_PL_I & (1ull << 34)
   #define DETAIL_PL_I34 1
  #else
   #define DETAIL_PL_I34 0
  #endif
  #if DETAIL_PL_I & (1ull << 35)
   #define DETAIL_PL_I35 1
  #else
   #define DETAIL_PL_I35 0
  #endif
  #if DETAIL_PL_I & (1ull << 36)
   #define DETAIL_PL_I36 1
  #else
   #define DETAIL_PL_I36 0
  #endif
  #if DETAIL_PL_I & (1ull << 37)
   #define DETAIL_PL_I37 1
  #else
   #define DETAIL_PL_I37 0
  #endif
  #if DETAIL_PL_I & (1ull << 38)
   #define DETAIL_PL_I38 1
  #else
   #define DETAIL_PL_I38 0
  #endif
  #if DETAIL_PL_I & (1ull << 39)
   #define DETAIL_PL_I39 1
  #else
   #define DETAIL_PL_I39 0
  #endif
  #if DETAIL_PL_I & (1ull << 40)
   #define DETAIL_PL_I40 1
  #else
   #define DETAIL_PL_I40 0
  #endif
  #if DETAIL_PL_I & (1ull << 41)
   #define DETAIL_PL_I41 1
  #else
   #define DETAIL_PL_I41 0
  #endif
  #if DETAIL_PL_I & (1ull << 42)
   #define DETAIL_PL_I42 1
  #else
   #define DETAIL_PL_I42 0
  #endif
  #if DETAIL_PL_I & (1ull << 43)
   #define DETAIL_PL_I43 1
  #else
   #define DETAIL_PL_I43 0
  #endif
  #if DETAIL_PL_I & (1ull << 44)
   #define DETAIL_PL_I44 1
  #else
   #define DETAIL_PL_I44 0
  #endif
  #if DETAIL_PL_I & (1ull << 45)
   #define DETAIL_PL_I45 1
  #else
   #define DETAIL_PL_I45 0
  #endif
  #if DETAIL_PL_I & (1ull << 46)
   #define DETAIL_PL_I46 1
  #else
   #define DETAIL_PL_I46 0
  #endif
  #if DETAIL_PL_I & (1ull << 47)
   #define DETAIL_PL_I47 1
  #else
   #define DETAIL_PL_I47 0
  #endif
  #if DETAIL_PL_I & (1ull << 48)
   #define DETAIL_PL_I48 1
  #else
   #define DETAIL_PL_I48 0
  #endif
  #if DETAIL_PL_I & (1ull << 49)
   #define DETAIL_PL_I49 1
  #else
   #define DETAIL_PL_I49 0
  #endif
  #if DETAIL_PL_I & (1ull << 50)
   #define DETAIL_PL_I50 1
  #else
   #define DETAIL_PL_I50 0
  #endif
  #if DETAIL_PL_I & (1ull << 51)
   #define DETAIL_PL_I51 1
  #else
   #define DETAIL_PL_I51 0
  #endif
  #if DETAIL_PL_I & (1ull << 52)
   #define DETAIL_PL_I52 1
  #else
   #define DETAIL_PL_I52 0
  #endif
  #if DETAIL_PL_I & (1ull << 53)
   #define DETAIL_PL_I53 1
  #else
   #define DETAIL_PL_I53 0
  #endif
  #if DETAIL_PL_I & (1ull << 54)
   #define DETAIL_PL_I54 1
  #else
   #define DETAIL_PL_I54 0
  #endif
  #if DETAIL_PL_I & (1ull << 55)
   #define DETAIL_PL_I55 1
  #else
   #define DETAIL_PL_I55 0
  #endif
  #if DETAIL_PL_I & (1ull << 56)
   #define DETAIL_PL_I56 1
  #else
   #define DETAIL_PL_I56 0
  #endif
  #if DETAIL_PL_I & (1ull << 57)
   #define DETAIL_PL_I57 1
  #else
   #define DETAIL_PL_I57 0
  #endif
  #if DETAIL_PL_I & (1ull << 58)
   #define DETAIL_PL_I58 1
  #else
   #define DETAIL_PL_I58 0
  #endif
  #if DETAIL_PL_I & (1ull << 59)
   #define DETAIL_PL_I59 1
  #else
   #define DETAIL_PL_I59 0
  #endif
  #if DETAIL_PL_I & (1ull << 60)
   #define DETAIL_PL_I60 1
  #else
   #define DETAIL_PL_I60 0
  #endif
  #if DETAIL_PL_I & (1ull << 61)
   #define DETAIL_PL_I61 1
  #else
   #define DETAIL_PL_I61 0
  #endif
  #if DETAIL_PL_I & (1ull << 62)
   #define DETAIL_PL_I62 1
  #else
   #define DETAIL_PL_I62 0
  #endif
  #if DETAIL_PL_I & (1ull << 63)
   #define DETAIL_PL_I63 1
  #else
   #define DETAIL_PL_I63 0
  #endif
  #undef DETAIL_PL_I0_
  #undef DETAIL_PL_I1_
  #undef DETAIL_PL_I2_
  #undef DETAIL_PL_I3_
  #undef DETAIL_PL_I4_
  #undef DETAIL_PL_I5_
  #undef DETAIL_PL_I6_
  #undef DETAIL_PL_I7_
  #undef DETAIL_PL_I8_
  #undef DETAIL_PL_I9_
  #undef DETAIL_PL_I10_
  #undef DETAIL_PL_I11_
  #undef DETAIL_PL_I12_
  #undef DETAIL_PL_I13_
  #undef DETAIL_PL_I14_
  #undef DETAIL_PL_I15_
  #undef DETAIL_PL_I16_
  #undef DETAIL_PL_I17_
  #undef DETAIL_PL_I18_
  #undef DETAIL_PL_I19_
  #undef DETAIL_PL_I20_
  #undef DETAIL_PL_I21_
  #undef DETAIL_PL_I22_
  #undef DETAIL_PL_I23_
  #undef DETAIL_PL_I24_
  #undef DETAIL_PL_I25_
  #undef DETAIL_PL_I26_
  #undef DETAIL_PL_I27_
  #undef DETAIL_PL_I28_
  #undef DETAIL_PL_I29_
  #undef DETAIL_PL_I30_
  #undef DETAIL_PL_I31_
  #undef DETAIL_PL_I32_
  #undef DETAIL_PL_I33_
  #undef DETAIL_PL_I34_
  #undef DETAIL_PL_I35_
  #undef DETAIL_PL_I36_
  #undef DETAIL_PL_I37_
  #undef DETAIL_PL_I38_
  #undef DETAIL_PL_I39_
  #undef DETAIL_PL_I40_
  #undef DETAIL_PL_I41_
  #undef DETAIL_PL_I42_
  #undef DETAIL_PL_I43_
  #undef DETAIL_PL_I44_
  #undef DETAIL_PL_I45_
  #undef DETAIL_PL_I46_
  #undef DETAIL_PL_I47_
  #undef DETAIL_PL_I48_
  #undef DETAIL_PL_I49_
  #undef DETAIL_PL_I50_
  #undef DETAIL_PL_I51_
  #undef DETAIL_PL_I52_
  #undef DETAIL_PL_I53_
  #undef DETAIL_PL_I54_
  #undef DETAIL_PL_I55_
  #undef DETAIL_PL_I56_
  #undef DETAIL_PL_I57_
  #undef DETAIL_PL_I58_
  #undef DETAIL_PL_I59_
  #undef DETAIL_PL_I60_
  #undef DETAIL_PL_I61_
  #undef DETAIL_PL_I62_
  #undef DETAIL_PL_I63_
  #undef PL_I
  #define PL_I PL_BITCAT64(DETAIL_PL_I63, DETAIL_PL_I62, DETAIL_PL_I61, DETAIL_PL_I60, DETAIL_PL_I59, DETAIL_PL_I58, DETAIL_PL_I57, DETAIL_PL_I56, DETAIL_PL_I55, DETAIL_PL_I54, DETAIL_PL_I53, DETAIL_PL_I52, DETAIL_PL_I51, DETAIL_PL_I50, DETAIL_PL_I49, DETAIL_PL_I48, DETAIL_PL_I47, DETAIL_PL_I46, DETAIL_PL_I45, DETAIL_PL_I44, DETAIL_PL_I43, DETAIL_PL_I42, DETAIL_PL_I41, DETAIL_PL_I40, DETAIL_PL_I39, DETAIL_PL_I38, DETAIL_PL_I37, DETAIL_PL_I36, DETAIL_PL_I35, DETAIL_PL_I34, DETAIL_PL_I33, DETAIL_PL_I32, DETAIL_PL_I31, DETAIL_PL_I30, DETAIL_PL_I29, DETAIL_PL_I28, DETAIL_PL_I27, DETAIL_PL_I26, DETAIL_PL_I25, DETAIL_PL_I24, DETAIL_PL_I23, DETAIL_PL_I22, DETAIL_PL_I21, DETAIL_PL_I20, DETAIL_PL_I19, DETAIL_PL_I18, DETAIL_PL_I17, DETAIL_PL_I16, DETAIL_PL_I15, DETAIL_PL_I14, DETAIL_PL_I13, DETAIL_PL_I12, DETAIL_PL_I11, DETAIL_PL_I10, DETAIL_PL_I9, DETAIL_PL_I8, DETAIL_PL_I7, DETAIL_PL_I6, DETAIL_PL_I5, DETAIL_PL_I4, DETAIL_PL_I3, DETAIL_PL_I2, DETAIL_PL_I1, DETAIL_PL_I0)
 #else
  #if DETAIL_PL_I & (1ull << 0)
   #define DETAIL_PL_I0_ 1
  #else
   #define DETAIL_PL_I0_ 0
  #endif
  #if DETAIL_PL_I & (1ull << 1)
   #define DETAIL_PL_I1_ 1
  #else
   #define DETAIL_PL_I1_ 0
  #endif
  #if DETAIL_PL_I & (1ull << 2)
   #define DETAIL_PL_I2_ 1
  #else
   #define DETAIL_PL_I2_ 0
  #endif
  #if DETAIL_PL_I & (1ull << 3)
   #define DETAIL_PL_I3_ 1
  #else
   #define DETAIL_PL_I3_ 0
  #endif
  #if DETAIL_PL_I & (1ull << 4)
   #define DETAIL_PL_I4_ 1
  #else
   #define DETAIL_PL_I4_ 0
  #endif
  #if DETAIL_PL_I & (1ull << 5)
   #define DETAIL_PL_I5_ 1
  #else
   #define DETAIL_PL_I5_ 0
  #endif
  #if DETAIL_PL_I & (1ull << 6)
   #define DETAIL_PL_I6_ 1
  #else
   #define DETAIL_PL_I6_ 0
  #endif
  #if DETAIL_PL_I & (1ull << 7)
   #define DETAIL_PL_I7_ 1
  #else
   #define DETAIL_PL_I7_ 0
  #endif
  #if DETAIL_PL_I & (1ull << 8)
   #define DETAIL_PL_I8_ 1
  #else
   #define DETAIL_PL_I8_ 0
  #endif
  #if DETAIL_PL_I & (1ull << 9)
   #define DETAIL_PL_I9_ 1
  #else
   #define DETAIL_PL_I9_ 0
  #endif
  #if DETAIL_PL_I & (1ull << 10)
   #define DETAIL_PL_I10_ 1
  #else
   #define DETAIL_PL_I10_ 0
  #endif
  #if DETAIL_PL_I & (1ull << 11)
   #define DETAIL_PL_I11_ 1
  #else
   #define DETAIL_PL_I11_ 0
  #endif
  #if DETAIL_PL_I & (1ull << 12)
   #define DETAIL_PL_I12_ 1
  #else
   #define DETAIL_PL_I12_ 0
  #endif
  #if DETAIL_PL_I & (1ull << 13)
   #define DETAIL_PL_I13_ 1
  #else
   #define DETAIL_PL_I13_ 0
  #endif
  #if DETAIL_PL_I & (1ull << 14)
   #define DETAIL_PL_I14_ 1
  #else
   #define DETAIL_PL_I14_ 0
  #endif
  #if DETAIL_PL_I & (1ull << 15)
   #define DETAIL_PL_I15_ 1
  #else
   #define DETAIL_PL_I15_ 0
  #endif
  #if DETAIL_PL_I & (1ull << 16)
   #define DETAIL_PL_I16_ 1
  #else
   #define DETAIL_PL_I16_ 0
  #endif
  #if DETAIL_PL_I & (1ull << 17)
   #define DETAIL_PL_I17_ 1
  #else
   #define DETAIL_PL_I17_ 0
  #endif
  #if DETAIL_PL_I & (1ull << 18)
   #define DETAIL_PL_I18_ 1
  #else
   #define DETAIL_PL_I18_ 0
  #endif
  #if DETAIL_PL_I & (1ull << 19)
   #define DETAIL_PL_I19_ 1
  #else
   #define DETAIL_PL_I19_ 0
  #endif
  #if DETAIL_PL_I & (1ull << 20)
   #define DETAIL_PL_I20_ 1
  #else
   #define DETAIL_PL_I20_ 0
  #endif
  #if DETAIL_PL_I & (1ull << 21)
   #define DETAIL_PL_I21_ 1
  #else
   #define DETAIL_PL_I21_ 0
  #endif
  #if DETAIL_PL_I & (1ull << 22)
   #define DETAIL_PL_I22_ 1
  #else
   #define DETAIL_PL_I22_ 0
  #endif
  #if DETAIL_PL_I & (1ull << 23)
   #define DETAIL_PL_I23_ 1
  #else
   #define DETAIL_PL_I23_ 0
  #endif
  #if DETAIL_PL_I & (1ull << 24)
   #define DETAIL_PL_I24_ 1
  #else
   #define DETAIL_PL_I24_ 0
  #endif
  #if DETAIL_PL_I & (1ull << 25)
   #define DETAIL_PL_I25_ 1
  #else
   #define DETAIL_PL_I25_ 0
  #endif
  #if DETAIL_PL_I & (1ull << 26)
   #define DETAIL_PL_I26_ 1
  #else
   #define DETAIL_PL_I26_ 0
  #endif
  #if DETAIL_PL_I & (1ull << 27)
   #define DETAIL_PL_I27_ 1
  #else
   #define DETAIL_PL_I27_ 0
  #endif
  #if DETAIL_PL_I & (1ull << 28)
   #define DETAIL_PL_I28_ 1
  #else
   #define DETAIL_PL_I28_ 0
  #endif
  #if DETAIL_PL_I & (1ull << 29)
   #define DETAIL_PL_I29_ 1
  #else
   #define DETAIL_PL_I29_ 0
  #endif
  #if DETAIL_PL_I & (1ull << 30)
   #define DETAIL_PL_I30_ 1
  #else
   #define DETAIL_PL_I30_ 0
  #endif
  #if DETAIL_PL_I & (1ull << 31)
   #define DETAIL_PL_I31_ 1
  #else
   #define DETAIL_PL_I31_ 0
  #endif
  #if DETAIL_PL_I & (1ull << 32)
   #define DETAIL_PL_I32_ 1
  #else
   #define DETAIL_PL_I32_ 0
  #endif
  #if DETAIL_PL_I & (1ull << 33)
   #define DETAIL_PL_I33_ 1
  #else
   #define DETAIL_PL_I33_ 0
  #endif
  #if DETAIL_PL_I & (1ull << 34)
   #define DETAIL_PL_I34_ 1
  #else
   #define DETAIL_PL_I34_ 0
  #endif
  #if DETAIL_PL_I & (1ull << 35)
   #define DETAIL_PL_I35_ 1
  #else
   #define DETAIL_PL_I35_ 0
  #endif
  #if DETAIL_PL_I & (1ull << 36)
   #define DETAIL_PL_I36_ 1
  #else
   #define DETAIL_PL_I36_ 0
  #endif
  #if DETAIL_PL_I & (1ull << 37)
   #define DETAIL_PL_I37_ 1
  #else
   #define DETAIL_PL_I37_ 0
  #endif
  #if DETAIL_PL_I & (1ull << 38)
   #define DETAIL_PL_I38_ 1
  #else
   #define DETAIL_PL_I38_ 0
  #endif
  #if DETAIL_PL_I & (1ull << 39)
   #define DETAIL_PL_I39_ 1
  #else
   #define DETAIL_PL_I39_ 0
  #endif
  #if DETAIL_PL_I & (1ull << 40)
   #define DETAIL_PL_I40_ 1
  #else
   #define DETAIL_PL_I40_ 0
  #endif
  #if DETAIL_PL_I & (1ull << 41)
   #define DETAIL_PL_I41_ 1
  #else
   #define DETAIL_PL_I41_ 0
  #endif
  #if DETAIL_PL_I & (1ull << 42)
   #define DETAIL_PL_I42_ 1
  #else
   #define DETAIL_PL_I42_ 0
  #endif
  #if DETAIL_PL_I & (1ull << 43)
   #define DETAIL_PL_I43_ 1
  #else
   #define DETAIL_PL_I43_ 0
  #endif
  #if DETAIL_PL_I & (1ull << 44)
   #define DETAIL_PL_I44_ 1
  #else
   #define DETAIL_PL_I44_ 0
  #endif
  #if DETAIL_PL_I & (1ull << 45)
   #define DETAIL_PL_I45_ 1
  #else
   #define DETAIL_PL_I45_ 0
  #endif
  #if DETAIL_PL_I & (1ull << 46)
   #define DETAIL_PL_I46_ 1
  #else
   #define DETAIL_PL_I46_ 0
  #endif
  #if DETAIL_PL_I & (1ull << 47)
   #define DETAIL_PL_I47_ 1
  #else
   #define DETAIL_PL_I47_ 0
  #endif
  #if DETAIL_PL_I & (1ull << 48)
   #define DETAIL_PL_I48_ 1
  #else
   #define DETAIL_PL_I48_ 0
  #endif
  #if DETAIL_PL_I & (1ull << 49)
   #define DETAIL_PL_I49_ 1
  #else
   #define DETAIL_PL_I49_ 0
  #endif
  #if DETAIL_PL_I & (1ull << 50)
   #define DETAIL_PL_I50_ 1
  #else
   #define DETAIL_PL_I50_ 0
  #endif
  #if DETAIL_PL_I & (1ull << 51)
   #define DETAIL_PL_I51_ 1
  #else
   #define DETAIL_PL_I51_ 0
  #endif
  #if DETAIL_PL_I & (1ull << 52)
   #define DETAIL_PL_I52_ 1
  #else
   #define DETAIL_PL_I52_ 0
  #endif
  #if DETAIL_PL_I & (1ull << 53)
   #define DETAIL_PL_I53_ 1
  #else
   #define DETAIL_PL_I53_ 0
  #endif
  #if DETAIL_PL_I & (1ull << 54)
   #define DETAIL_PL_I54_ 1
  #else
   #define DETAIL_PL_I54_ 0
  #endif
  #if DETAIL_PL_I & (1ull << 55)
   #define DETAIL_PL_I55_ 1
  #else
   #define DETAIL_PL_I55_ 0
  #endif
  #if DETAIL_PL_I & (1ull << 56)
   #define DETAIL_PL_I56_ 1
  #else
   #define DETAIL_PL_I56_ 0
  #endif
  #if DETAIL_PL_I & (1ull << 57)
   #define DETAIL_PL_I57_ 1
  #else
   #define DETAIL_PL_I57_ 0
  #endif
  #if DETAIL_PL_I & (1ull << 58)
   #define DETAIL_PL_I58_ 1
  #else
   #define DETAIL_PL_I58_ 0
  #endif
  #if DETAIL_PL_I & (1ull << 59)
   #define DETAIL_PL_I59_ 1
  #else
   #define DETAIL_PL_I59_ 0
  #endif
  #if DETAIL_PL_I & (1ull << 60)
   #define DETAIL_PL_I60_ 1
  #else
   #define DETAIL_PL_I60_ 0
  #endif
  #if DETAIL_PL_I & (1ull << 61)
   #define DETAIL_PL_I61_ 1
  #else
   #define DETAIL_PL_I61_ 0
  #endif
  #if DETAIL_PL_I & (1ull << 62)
   #define DETAIL_PL_I62_ 1
  #else
   #define DETAIL_PL_I62_ 0
  #endif
  #if DETAIL_PL_I & (1ull << 63)
   #define DETAIL_PL_I63_ 1
  #else
   #define DETAIL_PL_I63_ 0
  #endif
  #undef DETAIL_PL_I0
  #undef DETAIL_PL_I1
  #undef DETAIL_PL_I2
  #undef DETAIL_PL_I3
  #undef DETAIL_PL_I4
  #undef DETAIL_PL_I5
  #undef DETAIL_PL_I6
  #undef DETAIL_PL_I7
  #undef DETAIL_PL_I8
  #undef DETAIL_PL_I9
  #undef DETAIL_PL_I10
  #undef DETAIL_PL_I11
  #undef DETAIL_PL_I12
  #undef DETAIL_PL_I13
  #undef DETAIL_PL_I14
  #undef DETAIL_PL_I15
  #undef DETAIL_PL_I16
  #undef DETAIL_PL_I17
  #undef DETAIL_PL_I18
  #undef DETAIL_PL_I19
  #undef DETAIL_PL_I20
  #undef DETAIL_PL_I21
  #undef DETAIL_PL_I22
  #undef DETAIL_PL_I23
  #undef DETAIL_PL_I24
  #undef DETAIL_PL_I25
  #undef DETAIL_PL_I26
  #undef DETAIL_PL_I27
  #undef DETAIL_PL_I28
  #undef DETAIL_PL_I29
  #undef DETAIL_PL_I30
  #undef DETAIL_PL_I31
  #undef DETAIL_PL_I32
  #undef DETAIL_PL_I33
  #undef DETAIL_PL_I34
  #undef DETAIL_PL_I35
  #undef DETAIL_PL_I36
  #undef DETAIL_PL_I37
  #undef DETAIL_PL_I38
  #undef DETAIL_PL_I39
  #undef DETAIL_PL_I40
  #undef DETAIL_PL_I41
  #undef DETAIL_PL_I42
  #undef DETAIL_PL_I43
  #undef DETAIL_PL_I44
  #undef DETAIL_PL_I45
  #undef DETAIL_PL_I46
  #undef DETAIL_PL_I47
  #undef DETAIL_PL_I48
  #undef DETAIL_PL_I49
  #undef DETAIL_PL_I50
  #undef DETAIL_PL_I51
  #undef DETAIL_PL_I52
  #undef DETAIL_PL_I53
  #undef DETAIL_PL_I54
  #undef DETAIL_PL_I55
  #undef DETAIL_PL_I56
  #undef DETAIL_PL_I57
  #undef DETAIL_PL_I58
  #undef DETAIL_PL_I59
  #undef DETAIL_PL_I60
  #undef DETAIL_PL_I61
  #undef DETAIL_PL_I62
  #undef DETAIL_PL_I63
  #undef PL_I
  #define PL_I PL_BITCAT64(DETAIL_PL_I63_, DETAIL_PL_I62_, DETAIL_PL_I61_, DETAIL_PL_I60_, DETAIL_PL_I59_, DETAIL_PL_I58_, DETAIL_PL_I57_, DETAIL_PL_I56_, DETAIL_PL_I55_, DETAIL_PL_I54_, DETAIL_PL_I53_, DETAIL_PL_I52_, DETAIL_PL_I51_, DETAIL_PL_I50_, DETAIL_PL_I49_, DETAIL_PL_I48_, DETAIL_PL_I47_, DETAIL_PL_I46_, DETAIL_PL_I45_, DETAIL_PL_I44_, DETAIL_PL_I43_, DETAIL_PL_I42_, DETAIL_PL_I41_, DETAIL_PL_I40_, DETAIL_PL_I39_, DETAIL_PL_I38_, DETAIL_PL_I37_, DETAIL_PL_I36_, DETAIL_PL_I35_, DETAIL_PL_I34_, DETAIL_PL_I33_, DETAIL_PL_I32_, DETAIL_PL_I31_, DETAIL_PL_I30_, DETAIL_PL_I29_, DETAIL_PL_I28_, DETAIL_PL_I27_, DETAIL_PL_I26_, DETAIL_PL_I25_, DETAIL_PL_I24_, DETAIL_PL_I23_, DETAIL_PL_I22_, DETAIL_PL_I21_, DETAIL_PL_I20_, DETAIL_PL_I19_, DETAIL_PL_I18_, DETAIL_PL_I17_, DETAIL_PL_I16_, DETAIL_PL_I15_, DETAIL_PL_I14_, DETAIL_PL_I13_, DETAIL_PL_I12_, DETAIL_PL_I11_, DETAIL_PL_I10_, DETAIL_PL_I9_, DETAIL_PL_I8_, DETAIL_PL_I7_, DETAIL_PL_I6_, DETAIL_PL_I5_, DETAIL_PL_I4_, DETAIL_PL_I3_, DETAIL_PL_I2_, DETAIL_PL_I1_, DETAIL_PL_I0_)
 #endif
 #undef DETAIL_PL_I
 #define DETAIL_PL_I (PL_APPLY(PL_AT_2, PL_LOOP)(PL_I))
 #if PL_APPLY(PL_AT_1, PL_LOOP)(PL_I)
  PL_APPLY(PL_FROM_3, PL_LOOP)
  #include __FILE__
 #else
  #undef PL_LOOP
  #undef PL_I
  #undef DETAIL_PL_I
 #endif
#endif
