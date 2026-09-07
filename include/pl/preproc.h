#ifndef PL_PREPROC_H
#define PL_PREPROC_H

#define PL_EAT(...)

#define PL_SCAN(...) __VA_ARGS__

#define PL_PARENS ()

#define PL_CALL(F, ...) F(__VA_ARGS__)

#define PL_IF(B) PL_IIF(B)
#define PL_IIF(B) DETAIL_PL_IIF##B
#define DETAIL_PL_IIF1(...) __VA_ARGS__ PL_EAT
#define DETAIL_PL_IIF0(...) PL_SCAN

#define PL_EVAL(...) DETAIL_PL_EVAL0(DETAIL_PL_EVAL0(DETAIL_PL_EVAL0(DETAIL_PL_EVAL0(__VA_ARGS__))))
#define DETAIL_PL_EVAL0(...) DETAIL_PL_EVAL1(DETAIL_PL_EVAL1(DETAIL_PL_EVAL1(DETAIL_PL_EVAL1(__VA_ARGS__))))
#define DETAIL_PL_EVAL1(...) DETAIL_PL_EVAL2(DETAIL_PL_EVAL2(DETAIL_PL_EVAL2(DETAIL_PL_EVAL2(__VA_ARGS__))))
#define DETAIL_PL_EVAL2(...) DETAIL_PL_EVAL3(DETAIL_PL_EVAL3(DETAIL_PL_EVAL3(DETAIL_PL_EVAL3(__VA_ARGS__))))
#define DETAIL_PL_EVAL3(...) __VA_ARGS__

#define PL_EACH(F, ...) __VA_OPT__(PL_EVAL(DETAIL_PL_EACH_(F, __VA_ARGS__)))
#define DETAIL_PL_EACH_(F, X, ...) F(X) __VA_OPT__(DETAIL_PL_EACH_NEXT PL_PARENS (F, __VA_ARGS__))
#define DETAIL_PL_EACH_NEXT() DETAIL_PL_EACH_

#define PL_BITCAT64(...) DETAIL_PL_BITCAT64(__VA_ARGS__)
#define DETAIL_PL_BITCAT64(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62, _63) 0b##_0##_1##_2##_3##_4##_5##_6##_7##_8##_9##_10##_11##_12##_13##_14##_15##_16##_17##_18##_19##_20##_21##_22##_23##_24##_25##_26##_27##_28##_29##_30##_31##_32##_33##_34##_35##_36##_37##_38##_39##_40##_41##_42##_43##_44##_45##_46##_47##_48##_49##_50##_51##_52##_53##_54##_55##_56##_57##_58##_59##_60##_61##_62##_63

#define PL_AT_0(X, ...) X
#define PL_AT_1(_0, X, ...) X
#define PL_AT_2(_0, _1, X, ...) X
#define PL_AT_3(_0, _1, _2, X, ...) X

#define PL_FROM_0(...) __VA_ARGS__
#define PL_FROM_1(_0, ...) __VA_ARGS__
#define PL_FROM_2(_0, _1, ...) __VA_ARGS__
#define PL_FROM_3(_0, _1, _2, ...) __VA_ARGS__

#endif
