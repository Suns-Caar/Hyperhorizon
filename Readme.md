This is the Task4 of FTE Question Set 

Build a system comprising two Arduino boards, A and B, with their roles defined as
follows:
● A and B communicate over SPI.
● A sends a pair of numbers (x, y) to B where x is an integer, and y is a number
denoting an arithmetic operation as follows:
B responds with f(x).
Note
Implement an ACK/NACK mechanism for the SPI transactions to handle invalid
commands and other edge cases.


Reference for SPI Initialization- 
[text](https://docs.arduino.cc/tutorials/generic/introduction-to-the-serial-peripheral-interface/)