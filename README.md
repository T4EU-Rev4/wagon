# wagon
Modules located at each wagon to communicate with the loco and to control the electronic gadget.

## Module Test_PCF8575_0
This small test program shows how to talk to a PCF8575 via a library.


## Module Test_MCP23017_0
Shows the usage of a port expander named MCP23017. 
It is widely configurable and have real push-pull outputs, not only low-side switches like the PCF8575.
The wire library is directly used without a special library to show this issue.

## Module Test_Node_Pins
A small programm to test the hardware after assembling it.  Connect LEDs to the 16 pins mentioned in the source and run the programm. Each LED will flash 3 times. This requires many LEDs. I used 2 LED bars each connected to a ULN2803 driver because the LED bars are made of conventional 20mA LEDs. 

## Test_PCF8575_Emu
This program demonstrates the emulation of a PCF8575 by the nano every.
In this example, only the outputs are used. Input capabilities as well 
as the interrupt service of the PCF8575 is not used here, but of course could be.
For this simple case, no additional library is used. Just Wire.


## Test_Every_mp3
This programm demonstrates the usage of the Library DFRobotDFPlayerMini.
It is used to operate a small mp3-player. In the train projekt, this module
is planned to play the hymn  or any other mp3-file. The mp3's are placed 
on an micro-SD-card with up to 16 GB capacity.
You can start and stop the first 10 files by sending the digits 0..9 via
the serial monitor. + will increase the volume by a step, while - decreases 
the volume by one step. Use this scheme to test all the other features of the 
device an the lib.


