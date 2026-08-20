#ifndef PL_WARN_H
#define PL_WARN_H

// Suppresses warnings about unused values.
#ifdef __GNUC__
 #define pl_ignore_unused(...) do{_Pragma("GCC diagnostic push")_Pragma("GCC diagnostic ignored\"-Wunused-value\"")__VA_ARGS__;_Pragma("GCC diagnostic pop")}while(0)
#else
 #define pl_ignore_unused(...) do{__VA_ARGS__;}while(0)
#endif

#endif
