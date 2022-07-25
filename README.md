# wagon
Modules located at each wagon to communicate with the loco and to control the electronic gadget.

## Module Test_PCF8575_0
This small test program shows how to talk to a PCF8575 via a library.


## Module Test_MCP23017_0
Shows the usage of a port expander named MCP23017. 
It is widely configurable and habe read push-pull outputs, not only low-side switches like the PCF8575.
The wire library is directly used without a special library to show this issue.

## Module Test_Node_Pins
A small programm to test the hardware after assembling it.  Connect LEDs to the 16 pins mentioned in the source and run the programm. Each LED will flash 3 times. This requires many LEDs. I used 2 LED bars each connected to a ULN2803 driver because the LED bars are made of conventional 20mA LEDs. 
