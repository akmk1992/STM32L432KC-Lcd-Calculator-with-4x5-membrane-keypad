STM32-Based Keypad Calculator
Author : Arkar

Overview
This project implements a basic calculator using an STM32L432KC microcontroller, a 4x5 keypad, and a 16x2 LCD. It performs basic arithmetic operations: addition, subtraction, multiplication, and division.

Features
Arithmetic operations: +, -, *, /,^(power)
Keypad input and LCD display
Basic error handling (e.g., division by zero and wrong operator input)

Hardware
STM32L432KC Microcontroller (Nucleo Board)
16x2 LCD Display
4x5 Keypad
Breadboard and Wires
1 x push button 
Resistors

Software
STM32CubeMX for code generation
STM32CubeIDE for development and debugging

Import the project and build it.
Flash and Run:

Connect the STM32 board and upload the firmware.
How It Works
The calculator reads inputs from the keypad and displays results on the LCD. Use the keypad to enter numbers and operators, then press "Enter" to calculate.

Code Structure
main.c: Main application code
keypad.c/h: Keypad handling
HD44780_F3.c/h: LCD interface
calculator.c/h: Calculator logic

Challenges & Solutions
Keypad Debouncing: Implemented software debouncing.


License
MIT License. See LICENSE for details.

Contact

Email: thantshinarkar@gmail.com
