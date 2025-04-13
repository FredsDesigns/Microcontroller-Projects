# Revolve-Programmed-Logic
Attached is the working code that I used in my senior project titled "Revolve". More information about the project itself can be found under my LinkedIn! This project was done entirely under the Arduino IDE, with C++ Language.

USAGE REQUIREMENTS:
This project includes the usage of "Sprites" which may require enough processing power to properly run!
My Design Specifications:
 -For the Microcontroller I went with the Adafruit ESP32 Feather V2, offering more than enough Flash memory, and the RAM was plenty to avoid screen issues.
 -Touchscreen used was the 4.0" TFT SPI 480x320 V1.1
   *Notes regarding the touchscreen
    When setting up the necessary libraries for the microcontroller, it is imperative that you either keep the refresh rate defaulted, increasing it will cause visual errors.
    This project uses the exact measuresments (480x320) for the designing of menuing, and also is used to properly map touched locations to ranges that the code reads to determine what/where you pressed. If you want to use another display, you'll have to introduce your dimensions, otherwise the code will run fine. 
  -A Hall-effect sensor is needed. You will have to change the Pinout assuming you plan on using a different microcontroller
  -A BPM Reader (I personally used the Pulse Sensor from pulsesensor.com, but found it is not worth a long-term investment, as I and others found that it degrades, however, if you plan on using it as soon as you purchase it, the readings are extremely accurate) Same changes need to be applied, but also worth noting is that this sensor requires a good analog signal Pin to read. Beware as some boards do offer this, but will read in poorly, I've had issues with this on various boards so I adivse you to read if your particular board has a history of bad analog reads.

For the programming aspect, you will need to use the Arduino IDE.
First unzip the files and open them through the Arduino IDE. 
Second confirm that you are using the proper libraries for each device (Refer to the MAINLCDMENU file, as it contains every library extension used)
Third, once each library is downloaded make sure you initialize the microcontroller with the proper ESP32 libraries found in the IDE. 
Fourth, attached sensors properly to the assigned pins (you may need to change them depending on the board you use, as the pulse sensor does require a analog input.) Pinouts can be found on the main Arduino file itself.
Finally, confirm the proper drivers are selected Under TFT_eSPI -> User_Setup.h, and include the correct pinouts.
(This video by XTronical goes over the drivers and pinouts and is a very useful example to refer to if your struggling: https://youtu.be/rq5yPJbX_uk?si=YqN9DWk-hG0FbhFN)

Here I'll include the main menu, usage videos, and a look at a prototype design we used for our senior project.


![RevolveTitle](https://github.com/user-attachments/assets/8e066da9-be35-48bd-9927-7fe67e9b6802)

Link to video showcasing its usage: https://youtu.be/1DN2k2Ynfio?si=fezZHY7DkGfHwogX&t=183

![RevolveUsage](https://github.com/user-attachments/assets/39b9b7c4-4717-4471-91f8-e8579dc5ebe6)

