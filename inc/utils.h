/**
 * @file utils.h
 * @author Owen Zeller (zelle105@umn.edu)
 * @brief Utility macros to help handle errors and parse strings.
 * @version 0.1
 * @date 2023-11-20
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/**
 * @brief Given a condition and a message, error out of the program
 * if the condition is met, and print the message.
 */
#define ON_ERROR_EXIT(cond, message) \
do { \
    if((cond)) { \
        printf("Error in function: %s at line %d\n", __func__, __LINE__); \
        perror((message)); \
        exit(1); \
    } \
} while(0)

/**
 * @brief Check if a string "str" ends with a substring "ends"
 * 
 * @param str The string to check
 * @param ends The substring to check against
 * @return true If the substring terminates the string
 * @return false Otherwise
 */
static inline bool str_ends_in(const char *str, const char *ends) {
    const char *pos = strrchr(str, '.');
    return !strcmp(pos, ends);
}