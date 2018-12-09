# MultiKeyboard
A example program for linux for programming keys from a second keyboard to macros.

# Usage
This is mostly straightforward to use and modify. When opened, it will ask you to select a second keyboard for macro usage.
After that, whatever macros you programmed will be effective.

To make your own macro, you can modify the switch statement on line 85 to your liking.
By default, the program will steal key events from the operating system. If you want the second keyboard to type AND perform some action, you can use the included keystrokes header. It has functions for sending characters to the operating system to be typed, and a function for sending key events to the operating system.
