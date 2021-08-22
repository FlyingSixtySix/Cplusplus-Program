# Cplusplus-Program

## Summary

Chada Tech asked me to complete a coding skills test to "audition" for the role of junior developer.  My task was to apply program logic by creating two clocks that display simultaneously and allow for user input using secure and efficient C++ code.  That user input would allow for adding a second, minute, or hour to the clock at a time, along with exiting the program when needed.  The clock would tick once every second, starting at the current date and time.

## What was done particularly well

I believe the involvement of threading and atomics tied the program together in a way that was both stable and efficient.  By making use of threading, we can separate the user input and clock display logic.

## Room for improvement

I am having trouble determining the best place to begin improving my code.  Moving more of the logic to separate files could help, along with abstracting rendering the clocks themselves.  Making use of a third-party library such as ncurses would allow for easier theming but at the cost of efficiency and portability.  One aspect I did not think of was if the computer took longer than 1000 ms to sleep for 1000 ms.  This would result in a broken/offset clock, but how long it would take to get to this point is random.

## Challenges

The initial thought process of how I should get the user input and separate it from the clock rendering process was the most prevalent challenge.  I had no experience working with threads nor atomics.  The other challenge was retrieving the current time of day and determining the best way to offset it.  Luckily, rendering the time is as easy as calling a method with the current seconds past epoch, which allows for the user-provided offset.

## Skills

I think threading, modularization, atomics, time formatting, and documenting are particularly transferrable skills that I can apply to other projects.

## Maintainability, readability and adaptability

The program was made maintainable, readable and adaptable by making use of multiple files and documenting most of the logic of the program.  For anyone new to my code, such as my instructor, they should be able to follow the logical steps.  I did my best to document every important bit.  Making sure the components were split into multiple relevant files (i.e. main, utils) helped for future expandability.

