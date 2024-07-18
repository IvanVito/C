# SmartCalc Documentation

## Copyright Information
This calculator is protected by copyright. All rights reserved.
© 2024 by lesleyle.

## Installation
To use this calculator, the user needs to install the following utilities:
- `gcc`
- `make`
- `qmake`

## Development Details
The calculator has been developed using the C/C++ programming language and the QT Creator version 6.6.2

## Make comands
### Installation Command
To install the calculator, please run the following command:
```
make install
```
### Unistallation Command
To unistall the calculator, please run the following command:
```
make uninstall
```
### Reboot Command
To return project original state, please run the following command:
```
make reboot
```
### Test Command
To run tests, please run the following command:
```
make test
./test
```
### Clean Command
To clear the project from the build result and test sides, please run the following command:
 ```
make clear
```
### Check Command
To check the project on the CPP and style and fix it, please run the following command:
 ```
make clear
```
### Dvi Command
To open documentation this project, please run the following command:
 ```
make dvi
```
### Dist Command
To create an archive with the calculator and documentation, please run the following command:
 ```
make dist
```
### Rebuild Command
To rebuild the project, please run the following command:
 ```
make rebuild
```
### All Command
To execute all commands (except rebuild), please run the following command:
 ```
make all
```

## Arithmetic Operations
The calculator supports the following arithmetic operations:

| Operator name | Infix notation (Classic) | Prefix notation (Polish notation) | Postfix notation (Reverse Polish notation) |
| --------- | ------ | ------ | -------------- |
| Brackets | (a + b) | (+ a b) | a b + |
| Addition | a + b | + a b | a b + |
| Subtraction | a - b | - a b | a b - |
| Multiplication | a * b | * a b | a b * |
| Division | a / b | / a b | a b \ |
| Power | a ^ b | ^ a b | a b ^ |
| Modulus | a mod b | mod a b | a b mod |
| Unary plus | +a | +a | a+ |
| Unary minus | -a | -a | a- |


## Mathematical Functions
The calculator includes various mathematical functions, including:

| Function description | Function |
| -------------------- | -------- |
| Computes cosine    | cos(x)  |
| Computes sine      | sin(x)  |
| Computes tangent   | tan(x)  |
| Computes arc cosine | acos(x) |
| Computes arc sine  | asin(x) |
| Computes arc tangent | atan(x) |
| Computes square root | sqrt(x) |
| Computes natural logarithm | ln(x) |
| Computes common logarithm | log(x) |


## Function Plotting
* The calculator provides the ability to plot functions. To plot a graph, please click the "Graph" button in the main menu of the application.
* Range of values is limited from -1 000 000 to 1 000 000
* Domain is limited from -1 000 000 to 1 000 000
* The scale remains unchanged and is 1:1

## Features of the Calculator
* Zero has multiple representations:
0 == 0. == .0 == 0.0 == .

* Explicit sign required:
"5x" - wrong
"5 * x" - true

* Spaces (" ") are allowed:
"5+x" -true
"5 + x" -true

* The calculator guarantees accuracy up to 14 digits inclusive (include field "x").
* The calculator provides only output of numbers or error ("ERROR")
* The calculator always displays 7 decimal places (except for the initial value "0").

## Calculation of Annuity or Differentiated Loan
* At the top of the main window, you can click on the "Credit Calculate" button. Here, you can calculate two types of loans: annuity or differentiated.
* Total loan amount: not exceeding 99 999 999 999 999
* Term: not exceeding 600 months
* Interest rate: 0.01 - 999.99 percent

        
