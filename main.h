/**
 * Header file for the main program.
 * author: Andrew Black
 * date: 2021-07-17
 */
#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <string>
#include <iomanip>
#include <thread>
#include <conio.h>
#include <atomic>

#include "utils.h"

using namespace std;
using namespace std::this_thread;
using namespace std::chrono_literals;
using std::chrono::system_clock;

#define CLOCK_WIDTH 26
#define CLOCK_SPACE 5
#define USERMENU_WIDTH 26

/**
 * The different user input option types.
 */
enum UserOption {
    // Used as a placeholder for when the user entered nothing in the
    // current user input loop.
    NONE,
    ADD_HOUR,
    ADD_MINUTE,
    ADD_SECOND,
    // Used when the user wishes to exit the program, handled on the next loop.
    EXIT
};

#endif
