/**
 * This program will display a user-modifiable 12-hour and 24-hour clock.
 * author: Andrew Black
 * date: 2021-07-17
 */

#include "main.h"

/**
 * This method will display the 12-hour and 24-hour clocks next to each other.
 *
 * @param offset The time offset in seconds.
 *
 * The 12-hour display format is "%I:%M:%S %p".
 * The 24-hour display format is "%H:%M:%S".
 */
void displayClocks(const int* offset)
{
    // Get the current time data with the user-defined offset.
    struct tm time = getTimeDataOffset(offset);

    // Format the current time into 12-hour and 24-hour time strings.
    string time12hr = formatTimeData(&time, "%I:%M:%S %p");
    string time24hr = formatTimeData(&time, "%H:%M:%S");

    // Display the top of the frames for both clocks.
    cout << string(CLOCK_WIDTH, '*') << string(CLOCK_SPACE, ' ') << string(CLOCK_WIDTH, '*') << endl;
    // Display "12-Hour Clock" centered.
    cout << '*' << centeredText("12-Hour Clock", CLOCK_WIDTH - 2) << '*';
    // Display space between the two clocks.
    cout << string(CLOCK_SPACE, ' ');
    // Display "24-Hour Clock" centered.
    cout << '*' << centeredText("24-Hour Clock", CLOCK_WIDTH - 2) << '*' << endl;
    // Display the 12-hour time centered.
    cout << '*' << centeredText(time12hr, CLOCK_WIDTH - 2) << '*';
    // Display space between the two clocks.
    cout << string(CLOCK_SPACE, ' ');
    // Display the 24-hour time centered.
    cout << '*' << centeredText(time24hr, CLOCK_WIDTH - 2) << '*' << endl;
    // Draw the bottom of the frames for both clocks.
    cout << string(CLOCK_WIDTH, '*') << string(CLOCK_SPACE, ' ') << string(CLOCK_WIDTH, '*') << endl;
}

/**
 * This method will display the user menu, allowing users to add to the time
 * and exit the program.
 */
void displayUserMenu()
{
    // Add extra space between the clocks and the user menu.
    cout << endl;
    // Draw the top of the frame.
    cout << string(USERMENU_WIDTH, '*') << endl;
    // Draw the menu options left-aligned.
    cout << "* " << left << setw(USERMENU_WIDTH - 3) << "1 - Add One Hour" << '*' << endl;
    cout << "* " << left << setw(USERMENU_WIDTH - 3) << "2 - Add One Minute" << '*' << endl;
    cout << "* " << left << setw(USERMENU_WIDTH - 3) << "3 - Add One Second" << '*' << endl;
    cout << "* " << left << setw(USERMENU_WIDTH - 3) << "4 - Exit Program" << '*' << endl;
    // Draw the bottom of the frame.
    cout << string(USERMENU_WIDTH, '*') << endl;
}

/**
 * Threaded method to assign the passed in UserOption atomic with the
 * UserOption associated with the user's input.
 * @param option The UserOption atomic.
 * 
 * Note that the user's input will be processed on the next loop.
 */
void getUserInput(atomic<UserOption>& option)
{
    while (option.load() != UserOption::EXIT)
    {
        int inputChar = _getch();
        switch (inputChar)
        {
            case '1':
                option.store(UserOption::ADD_HOUR);
                break;
            case '2':
                option.store(UserOption::ADD_MINUTE);
                break;
            case '3':
                option.store(UserOption::ADD_SECOND);
                break;
            case '4':
                option.store(UserOption::EXIT);
                break;
        }
    }
}

/**
 * Creates the user input thread and starts a while loop that loops every
 * second until the user enters the exit option. This loop will clear the
 * screen, display both clocks, display the user menu and sleep a second.
 */
void startTimer()
{
    // Create an atomic for the user input set to none.
    // NOTE: We could have used an atomic char but handling user input in
    // another method was more straight-forward.
    atomic<UserOption> userOption(UserOption::NONE);
    // Instantiate a new thread for getting the user input with the atomic.
    thread userInputThread(getUserInput, ref(userOption));

    // This is the time offset in seconds.
    int offset = 0;

    // Loop until the user decides to exit.
    while (userOption != UserOption::EXIT)
    {
        // Determine what to do with the user option.
        // We do not need to handle NONE or EXIT here.
        switch (userOption)
        {
            case ADD_HOUR:
                offset += 3600;
                break;
            case ADD_MINUTE:
                offset += 60;
                break;
            case ADD_SECOND:
                offset += 1;
                break;
        }
        // Default to the user inputting no option.
        userOption = UserOption::NONE;
        // According to spec, clear the screen first.
        clearScreen();
        // Display the time in two formats.
        displayClocks(&offset);
        // Display the user menu.
        displayUserMenu();
        // Wait a second before looping.
        sleep(1000);
    }
    // Join the user input thread.
    userInputThread.join();
}

/**
 * The main method will start the timer to display the time, user menu, and
 * handle user input.
 * @return The status code.
 */
int main()
{
    startTimer();
    return 0;
}
