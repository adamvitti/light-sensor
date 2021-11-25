# Mighty Gecko EFR32MG12 Light Sensor Project

This project includes i2c drivers (implemented as an interrupt driven state machine), SI1133 drivers, and application logic from scratch. 
The mighty gecko calls upon the SI1133 functions, which then uses the i2c protocols to communicate with the si1133 embedded sensor to take white light readings.
A blue LED will turn on if it is dark, and will turn off if it is bright. 

##Documentation
Included in this project is a compiled Doxygen report of all functions which can be found [here](light-sensor/html/index.html) 
