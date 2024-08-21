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

Software
STM32CubeMX for code generation
STM32CubeIDE for development and debugging

Setup
Clone the Repository:
bash
Copy code
git clone https://github.com/yourusername/stm32-calculator.git
cd stm32-calculator
Open in STM32CubeIDE:

Import the project and build it.
Flash and Run:

Connect the STM32 board and upload the firmware.
How It Works
The calculator reads inputs from the keypad and displays results on the LCD. Use the keypad to enter numbers and operators, then press "Enter" to calculate.
If inputs are wrong, the values can be cleared using "Esc" key.

Code Structure
main.c: Main application code
keypad.c/h: Keypad handling
HD44780_F3.c/h: LCD interface
calculator.c/h: Calculator logic

Challenges & Solutions
Key scanning
Keypad Debouncing: Implemented software debouncing.

## Credits

- **Source Files:**
  - **HD44780_F3.c/h**: Adapted from resources found on GitHub.
  - **debounce.c/h**: Based on code from other programmers; respective authors are mentioned in the header of the source files.

- **Libraries and Tools Used:**
  - [STM32CubeMX](https://www.st.com/en/development-tools/stm32cube-mx.html) - For configuration and initialization.
  - [HAL Library](https://www.st.com/en/development-tools/stm32cube-embedded-software.html) - For hardware abstraction.


License
MIT License. See LICENSE for details.

Contact
LinkedIn: www.linkedin.com/in/arkar-myint-kyaw
Email: thantshinarkar@gmail.com
