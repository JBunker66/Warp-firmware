#Balance Sensor

by James Bunker, Trinity Hall, jwb66

## Description and set-up

This sensor is designed to detect how balanced an object is. If you are transporting an object it can give a visual output via an OLED screen and/or a more detailed statistical output via a cable and terminal. It gives green if it is in the fully safe range, orange if it is in a middle range, and red if it is in the danger zone. 

The bulk of the code is in the devSSD1331.c/h, devMMA8451Q.c/h and boot.c files in the scr/boot/ksdk1.1.0 path. For correct set up however CMakeLists-Warp.txt, config.h, gpio_pins.c/h and warp.h are also needed in the same directory as previous and build.sh in the build/ksdk1.1 path are needed. **To compile this script correctly first the build script must be run, then make warp**. 

The angle of the zones is customizable in the boot.c file. The default for green is 0$^{\circ}-$45$^{\circ}$, orange 45$^{\circ}-$-45$^{\circ}$ and red -45$^{\circ}-$-90$^{\circ}$. This can be changed to any combination of plus minus 15, 30 or 45 degrees built in and custom angles can be defined as 4000*cos($\theta$). 

## Outputs

This system has two output methods in which either one or both can be utilized. 

Method one is a colour via an OLED screen SSD1331. The pinout for this to work is as follows: 

| OLED Pin | Board Pin      |
|----------|----------------|
| GND      | J3 Pin 6/GND   |
| VCC - 5V | J3 Pin 5/5V    |
| OCS      | J4 Pin 5/PTB13 |
| RST      | J2 Pin 6/PTB0  |
| D/C      | J4 Pin 3/PTA12 |
| SCK      | J4 Pin 1/PTA9  |
| MOSI     | J4 Pin 2/PTA8  |


This will then print a green screen if safe, orange if in the middle zone and red if in the danger zone. These functions are defined in the devSSD1331.c/h files and can be changed to different RGB values if desired by changing the labeled lines that control rgb. 


Method Two is via the terminal if the board is plugged into a computer with the correct client. When active this outputs the mean and standard deviation in millig's, i.e. 1/1000 of the acceleration caused by gravity. It also outputs the skew and kurtosis of the data as mili-skew and mili-kurtosis. These values should be close to 0 for the certainties to be acuate. Since they are done in 1000ths any value of both below 500 for skew and 4000 for kurtosis should be enough for the next output to be valid. The next output is the certainty of the selected group. Note that 4% is the lowest value, so in reality a 4% value could be much smaller. The categorizer is done on the mean of the data, so in niche circumstances orange could be the output, but not the most probable. If this is the case however the device is in very turbulent motion. The last output is the time in seconds that covers both the data gathering and classifier. In normal use this should be four seconds. 

###Method two options

 There are two simple changes to implement to change the output to the terminal. One is to uncomment the relevant labeled line in boot.c around line 1890. This makes the device output all the data to the terminal so it can be manually exported and tested. Note if testing externally it could also be wise to remove the divide by 4 on the printing of data. The use of this line is to make the data more easy to understand, but does lose data. The second is the delay. The delay between recordings is done with a OSA_TimeDelay(50). This 50 can be made larger or smaller depending on the personal use-case. Smaller values emphasizes the change due to the uncertainty of the sensor, and a larger value emphasizes the change due to the uncertainty of the environment.

