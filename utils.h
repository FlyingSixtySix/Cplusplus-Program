/**
 * Header file for the program's utilities.
 * author: Andrew Black
 * date: 2021-07-17
 */
#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <string>
#include <iomanip>
#include <thread>
#include <atomic>
#include <sstream>

using namespace std;
using namespace std::this_thread;
using namespace std::chrono_literals;
using std::chrono::system_clock;

string centeredText(const string& text, int length);
void clearScreen();
void sleep(int milliseconds);
tm getTimeDataOffset(const int* offset);
string formatTimeData(const tm* timeData, const char* format);

#endif
