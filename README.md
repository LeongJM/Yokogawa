# Yokogawa - Basic Calculator - C++

## Brief Project Description
This project is the Development process of a Calculator program for Yokogawa Interview.

## Instructions
Calculations are done using a single string:\
eg. 100+200 ✔\
eg. 1*5 ✔

e and decimals are allowed:\
eg. 1e10+100 ✔\
eg. 1.15+20 ✔\
eg. 1.15e20+20 ✔

No whitespaces or invalid non-numerics are allowed:\
eg. 1 + 2 ❌\
eg. 1a+3 ❌

All available operations:
- Plus (+)
- Minus (-)
- Multiply (*)
- Divide (/)
- Power (^)
- Square Root (~)

Special instructions are:
- info
- history [number]
- exit

Initial Window
<img width="979" height="512" alt="1" src="https://github.com/user-attachments/assets/19b0f69b-8214-4d7d-a6bf-ff504338ad5a"/>
All Basic Operations
<img width="979" height="512" alt="8" src="https://github.com/user-attachments/assets/b21f6af6-5a5f-4ee8-9561-a86d3e53bb2b" />
<img width="979" height="512" alt="10" src="https://github.com/user-attachments/assets/619ca4a2-ff30-4833-91f3-7602bc233be8" />

## Testing
Initial setup:
- Basic environment testing
  * Building Project and Solution Files.
  * Basic class framework - Three classes - UI, Calculation, Error Handling.
- Basic functionality testing
  * Testing console std::getline or std::cin input.
- UI class console output testing
  * Checking if console is outputting correct values from UI Class.

Main Calculations Testing:
- Tokenization
  * Separating input into 3 tokens: Value 1, operation, Value 2.
- Individual Operations
  * Testing each individual operation.
  * Addition, Subtraction, Multiplication, Division, Power, Root.
  * Testing with whitespaces and non-numerics.
  * Testing with exponent and decimals.
- Error Handling for each Operation
  * Overflow/underflow.
  * Infinity/NaN.
  * Divide by Zero.
  * Invalid arguments.
  * Error Handling properly being properly sent out and viewable.
- History
  * Storing of all History Data.
  * Output of History Data.

Polish:
- Testing Reworked areas
  * History was reworked from circular array buffer to infinite vector (no imposed limit on number of stored calculations).
  * Reworked Operations from hard-coded to stored in Singleton vector (potential to add additional 2 input value operations from outside the class).
- Further stress testing with Individual operations:
  * Large numbers with large numbers, small numbers with small numbers.
  * Small decimal values.
- Polish of UI console output.

## Known Issues
- Calculating with a huge number and small number causes potential issues leading to inaccurate calculations.
- Decimals are always printed at 6 decimal places (non-dynamic decimal string outputs).


