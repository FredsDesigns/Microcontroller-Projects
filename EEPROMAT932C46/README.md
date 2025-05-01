This project is a sequential read/write of the first 128 addresses of the AT932C46 EEPROM. It works in 8-bit mode and performs commands entirely through bit bang logic.
Bit bang refers to the exclusion of external libraries to create the SPI protocol.

Parts used:
Logical Analyzer (Used PulseView Nightly to view timings, download: https://github.com/sigrokproject/pulseview/releases)
Arduino UNO R4 WiFi
AT932C46 Chip
Jumper Cables

Hardware Setup:
(Mandatory)
First place the AT932C46 onto your breadboard and refer to the datasheet regarding pin layout
Here is the layout of this specific chip



![image](https://github.com/user-attachments/assets/251b2047-4044-4ae1-93e3-0814176a676c)




To begin, first attach GND to GND of your Arduino
Do the same for your ORG Pin, as we will be working in 8-bit mode
Then attach Vcc to 5V of your Arduino
Attach CS to Pin 10
*These next pins are board dependent! If your using an Arduino (like the R4) with specific SPI bus connections, please refer to this image to see your connections!
However, since this is a bit bang project, you can always exchange these pins, to any others in the ino file, I just like to keep them referred to the offical SPI bus lines!*


![image](https://github.com/user-attachments/assets/c8fa1591-d3df-4d5d-99f8-4ab2c7df22c9)



The bottom of the R4 has specific headers for the SPI bus, note if your board has these pins make sure to always use them for MOSI/MISO/SK! The regular headers may cause issues!
Attach DO (MISO) to pin 11 (PIN 4 on the R4)
Attach DI (MOSI) to pin 12 (PIN 1 on the R4)
Attach SK to pin 13 (PIN 1 on the R4)
Leave DC without any connections

(Optional)
Assuming you'd like to use a Logical Analyzer, (This is the one I used in this project: https://www.amazon.com/dp/B077LSG5P2?ref=ppx_yo2ov_dt_b_fed_asin_title)
Attach channels 0 to 3 to the nodes that are transmitting data (MOSI/MISO/SK/CS)
Set GND pins to GND

Software Setup (Logical Analyzer):
Since were working with the SPI Protocol, we can add a protocol decoder to view the timings decoded to bits to confirm the data is properly being sent.
First find the protocol decoder tab as shown here:
![image](https://github.com/user-attachments/assets/353a95e2-b576-4f97-9e31-c565326bee77)

Then select Embedded/Industrial -> SPI
This will add an SPI line but will still require setup
Click on the SPI line and assign which channels are responsible for each line (Ex. Channel 0 is CS / Channel 1 is SK / Channel 2 is MOSI / Channel 3 is MISO)
Make sure CS# Polarity is set to high, as the EEPROM works with an active high chip select signal
Lastly increase the word size to 9, as this helps view the most bits.
Now when the code is properly ran, you can view the lines decoded to bits and make sure the data is being sent properly


Code Setup:
Simply upload the code to the board, and if using a logical analyzer, start the timing sampling before code is uploaded
*Note: When the code is uploaded, you may need to hit the reset button on the Arduino board your using to view the results in the serial monitor!*
*Not doing so will have the code ran and uploaded but you wont see any response back, so make sure to reset after uploading!*
You should be able to see the instructions as shown below, being sent properly, starting with EWEN which enables write and should always be the first command before any other is assigned.



![image](https://github.com/user-attachments/assets/cf17e1e1-25b3-41b2-bda0-a6c0454b9e2c)




*Note, that mandatory bits are grouped together for efficiency, such as EWEN sends (10011) first which is composed of:
The start bit (1)
The opcode (00)
Mandatory Address bits (11)*
We also need to send 5 dummy dont care bits to classify that were trying to do a EWEN, so we sent 5 0-bits in the code to do so.

Debugging:
Here are a various compilation of debugging issues I've came accross:
Using delayMicroseconds() instead of delay()
  The datasheet lists various time periods between pulses, but the majority require short nanosecond delays between timings to properly initilize and work with the SPI lines.
  Using delayMicroseconds() might seem a better fit, since delay() is in milliseconds and most timings require delays of nanoseconds.
  However running the code with delayMicroseconds() causes timing issues, and it works 100% of the time running using delay() instead,
  please keep this in mind if you choose to program with delayMicroseconds() instead, as it will also require a logical analyzer that can view shorter timespans aswell
  (PulseView is perfect for viewing millisecond periods, which is another reason to use delay() instead!)
Breadboard
  Funnily enough, Im not sure what exactly went wrong, but I was using an older breadboard and the code simply wouldnt read properly from an address 
  (It showed as 0xFF, which means MISO never dropped to 0/GND but the read command itself came in correctly!)
  Without changing the code, I exchanged the board for a newer one and it worked perfectly!
Logical Analyzer
  Without using one, it will be extremely harsh to see which timings are causing errors. Of course the code should work assuming your using the exact same chip, but if your planning on programming the IC
  I'd highly recommend purchasing one as it's very cheap, and the software is free!
Resetting
  As I've mentioned before, initialization requires a reset of the board to view data through the serial monitor. This might not be the case if you're using a different board, so please be aware of this!
