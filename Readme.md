This is the Task 3 of the FTE Question Set 


Task 3
Extending upon the previous example, instead of using LEDs, display the counter
output using an array of 7-segment displays.


Bonus
Can you reduce the number of I/Os used on the Arduino?


The current Code already reduces the number of GPIOs to a (7+1) but it can be further reduced by using a BCD to 7 Segment Decoder and a mux or by using a shift register.