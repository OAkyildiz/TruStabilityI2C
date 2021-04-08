Honeywell TruStability High Accuracy Silicon Ceramic (HSC) Series and Standard 
Accuracy Silicon Ceramic (SSC) Series are piezoresistive silicon pressure 
sensors offering a digital output for reading pressure over the specified full 
scale pressure span and temperature range. They are available in standard 
pressure ranges from 1 psi to 150 psi (60 mbar to 10 bar) and are intended for 
use with non-corrosive, non-ionic gases, such as air and other dry gases. 
The liquid media option extends the performance of these sensors to 
non-corrosive, non-ionic liquids.

The library uses I2C to connect to the sensor (see the Wire library). 
SPI can also be used (with some sensors, see datasheet), but is not implemented 
in this library.



Check your sensor characteristics by referencing the product number to the page 13 of the [datasheet](https://sensing.honeywell.com/honeywell-sensing-trustability-ssc-series-standard-accuracy-board-mount-pressure-sensors-50099533-a-en.pdf)

This library has been tested, but might still contain bugs, so please be careful.
Bugs, suggestions, comments are always welcome. 

[TruStability familiy Datasheet](https://sensing.honeywell.com/honeywell-sensing-trustability-ssc-series-standard-accuracy-board-mount-pressure-sensors-50099533-a-en.pdf)
[I<sup>2</sup>C Communications with Honeywell Digital Output Pressure Sensors](https://sensing.honeywell.com/honeywell-sensing-force-i2c-comms-tech-note-008291.pdf)

Example Product:
Single Bore Digital Gage Pressure Sensor - [SSCMRNN100MG2A5](https://www.mouser.com/ProductDetail/Honeywell/SSCMRNN100MG2A5)


  Original Author:          Petre Rodan <2b4eda@subdimension.ro>
  Available from:  https://github.com/rodan/honeywell_hsc_ssc_i2c
  License:         GNU GPLv3

