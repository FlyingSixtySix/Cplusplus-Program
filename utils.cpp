/**
 * This file provides various utility method implementations for the program.
 * author: Andrew Black
 * date: 2021-07-17
 */
#include "utils.h"

/**
 * Centers text within the length in spaces.
 * @param text The text to center.
 * @param length The length to center in.
 * @return The centered text.
 *
 * To center the text, we will first get the offset by subtracting the length
 * of the string from the total length and dividing by two. This will leave us
 * with the start position--the amount of spaces to repeat. To get the amount
 * of spaces to repeat on the other side, it is as simple as subtracting the
 * text length and offset from the total length.
 */
string centeredText(const string& text, int length)
{
    // For example, the text could be "TEXT" and the length could be 10.
    // The end result should look like so, with stars being spaces:
    //     ***TEXT***
    // The offset would be 3.
    int offset = (length - text.length()) / 2;
    // We will start off by repeating spaces for the offset.
    // We should now have ***.
    string centeredText = string(offset, ' ');
    // Add the text.
    // We should now have ***TEXT.
    centeredText += text;
    // Finally, repeat spaces until finished.
    // We should now have ***TEXT***.
    centeredText += string(length - text.length() - offset, ' ');
    return centeredText;
}

/**
 * Clears the console.
 */
void clearScreen()
{
    // NOTE: Not cross-platform!
    system("cls");
}

/**
 * Pauses the main thread for the specified amount of milliseconds.
 * @param milliseconds How long to pause the main thread for.
 */
void sleep(int milliseconds)
{
    sleep_for(milliseconds * 1000000ns);
}

/**
 * Gets the current time as a struct with time data.
 * @param offset The time offset in seconds.
 * @return The time data struct.
 */
tm getTimeDataOffset(const int* offset)
{
    // now is an integer of the seconds since January 1st, 1970 at 12:00:00 AM.
    time_t now = system_clock::to_time_t(system_clock::now());
    // Add the user-adjusted offset in seconds.
    now += *offset;

    // Create and fill a tm struct. Included the hour, minute second, etc.
    struct tm timeData;
    localtime_s(&timeData, &now);
    // Return the filled tm struct.
    return timeData;
}

/**
 * Formats the time data struct with the given strftime format string.
 * @param timeData The time data struct.
 * @param format The strftime-formatted string.
 * @return The formatted time string.
 */
string formatTimeData(const tm* timeData, const char* format)
{
    // Create a stringstream and put the formatted time data in it.
    stringstream timeStream;
    timeStream << put_time(timeData, format);
    // Make a string out of the stringstream.
    return timeStream.str();
}
