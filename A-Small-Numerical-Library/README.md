## DESCRIPTION

In this lab assignment, the user will be able to input a command in the command line in order to output a numerical library of the **Sin**, **Cosine**, **Tangent**, and **Exponential** functions. 

#### Sin (-s)

For the Sin function, the calculation will be done using the Pade approximation for a 14 term series. The function will be calculating sin(x) in the domain of [-2pi, 2pi], as anything less than or greater will result in higher degrees of difference between the Pade approximation and the actual math.h library. 


#### Cosine (-c)

For the Cosine function, the calculation will also be done using the Pade approximation for a 14 term series. The function will be calculating cos(x) in the domain of [-2pi, 2pi], as anything less than or greater will result in higher degrees of difference between the Pade approximation and the actual math.h library.


#### Tangent (-t)

For the Tangent function, the calculation will also be done using a Pade approximation. The function will be calculating tan(x) in the domain of [-pi/3, pi/3], as anything less than or greater will result in higher degrees of difference between the Pade approximation and the actual math.h library.


#### Exponential (-e)

For the Exponential function, the calculation will be done by using a Taylor Series approximation. This function will be calculating exp(x) in the domain of [0,9]. In order to achieve a high level of accuracy, the Taylor Series approximation will run until the current term is less than EPSILON (10^-9).  The result of the Taylor Series approximation will be compared to the actual exp(x) function in the math.h library.

The user is also able to call **all (-a)** which will run all of these tests.

See DESIGN.pdf for Pade approximation and Taylor Series approximation formulas for each function.

## FILES

***math.c***

This file contains the source code for the lab in C.

***Makefile***

This file includes the instructions when building, compiling, and running the source code using make.

***Design.pdf***

This file includes the description of the numerical library and the design behind each of the functions

in the source code. This file also contains answers to the Pre-Lab questions and addresses the main

function.

***WRITEUP.pdf***

This file contains post-lab discussion of the results from the given outputs when implementing these

functions. Discusses the differences between output using Pade approxmations and Taylor Series

approximations in relation to the math.h library.

## INSTRUCTIONS

#### **Compiling**

This program is intended to be compiled using the makefile associated with the assignment folder. Running make on the command prompt will create file executable math. Typing ./math followed by any command (see Description) will print out the specified numerical function. 

#### Execution

In order for the program to work, when the user calls ./math, the user must input a command (-s, -c, -t, -e, -a), which represent the following functions Sin, Cosine, Tangent, Exponential, and All respectively. 

The command inputs are mutually exclusive, meaning the user is only able to input one command at a time.

#### Known Issues

- The user is still able to input more than one command when running the executable. The program is coded in a way that will only accept one command at a time.
  - If the user inputs more than one command (e.g. ./math -s -t or ./math -st), the program will only run the first character that is typed.
- Invalid inputs will cause to program to stop.

