# Adaptive-Signal-Processing-System-with-Mixed-Domain-Filtering-Logic
Attached is the code needed to generate signals to be processed, and handling of the filtered results

To start things off, this project is very circuit heavy as we are working with signal processing, the goal is work alongside an OP AMP IC to filter signals. The board itself still has a purpose but It is very minimal compared to the boards overwhelming presence in the project!

Parts needed:
1x Trimmer Potentiometer
1x 0.1uF Ceramic Capacitor
1x 1uF Capacitor
1x AS385AP-E1 (OP AMP IC used, can be replaced with another IC, but it must contain two OP AMPS within to work properly!
1x PNP Transistor
2x 100kOhm Resistors
6x 10kOhm Resistors
4x 220 Ohm Resistors
4x LEDs
2x IN4148 Diodes

I'll now go over the connections, here is a reference image to show the wiring results:
![SignalProcConnections](https://github.com/user-attachments/assets/ab3553c5-08a8-4757-bd31-deefa3a0744f)
Ignore connections to the board for now, lets first work on developing the circuit itself
Here is the datasheet of the OP AMP used, please refer your connections to it!
https://www.mouser.com/datasheet/2/115/DIOD_S_A0005046231_1-2542568.pdf
1.Place OP AMP in center rail
2.Attach VCC to 3v3 and GND to GND rails
3.Place the trimmer, and attach the Top to 3V3 and bottom to GND
4.Take a 10k resistor and place it at the middle pin, the other end will feed to a new row.
5.On the row the resistor feeds to, place a diode with its cathode (black end) to 3v3, and another diode with its anode (clear end) to GND
6.Now on this row place a 100k resistor from this row to a new one to connect with Pin A0. Also on the diode/10k resistor row place a connection to Input 1+ of the OP AMP
7.Now place a 10k resistor from Input 1- to GND, and then another 10k in parallel with the 0.1uF Capacitor going to Output 1.
8.At this point you can verify that the Low Pass Filter (LPF) is working by attaching an LED and 220 Ohm resistor in series from Output 1 to GND.
9. Now connect Output 1 in series with a 1uF Capacitor, to Input 2+.
10.Between that series connection, place a wire from it to the boards Pin A1
11.Connect another 10k resistor from Input 2+ to GND, and another one from Input 2- to GND.
12.Add a 100k resistor from Input 2- to Output 2.
13.Connect output 2 to a row with a LED and 220 ohm resistor to GND. 
14.On that same row, attach a 10k resistor to the PNP transistors base, also attach an LED with 220 Ohm resistor at the collector pin of the transistor, and make the emitter go to 3v3
15.Finally make a connection from Pin D12 on the board to an LED /220 ohm resistor anywhere on the board.

Now we can move onto the code itself
When booting up the IDE, start the project using my selected board (Go to board select -> enter NUCLEO-U385RG-Q). Then you can set PA0 to be a GPIO Output (this gives off the signal), set PA1 to be ADC1_IN4, and PA6 to TIM3_CH1.
For settings please click on Analog and set gloabal interrupts on
Also go to timmers -> TIM3 -> make Counter Period set to 4095 for 12 bits, set the clock source to the interal clock, Channel 1 should be set to PWM Generation CH1, do the same for Channel 2.
Finally all you need to do is update your main.c file to include the code to handle the signal processing and your finished!

