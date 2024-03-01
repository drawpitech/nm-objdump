/*
** EPITECH PROJECT, 2024
** nm/objdump
** File description:
** debug
*/

#pragma once

#ifdef DEBUG_MODE
    #define FORMAT(s) "%s:%d: " s "\n"
    #define HEAD __FILE_NAME__, __LINE__
    #define DEBUG_DO(code) (code)
#else
    #define DEBUG_DO(code)
#endif

#define DEBUG(fmt, ...) DEBUG_DO(printf(FORMAT(fmt), HEAD, __VA_ARGS__))
#define DEBUGV(fmt, va) DEBUG_DO(vprintf(FORMAT(fmt), HEAD, (va)))
#define DEBUG_MSG(string) DEBUG_DO(printf(FORMAT(string), HEAD))
