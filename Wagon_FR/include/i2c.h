#ifndef I2C_h
#define I2C_h

/**
 * @brief From the beginning, we start working with PCF8575 port expanders
 *        These portexpanders provide 16 bits organized in 2 bytes.
 *        Thats the reason for the 2 byte array used here. Actually, we 
 *        are using only one byte named "action" whitch can have a value of
 *          0 = Stop the animation
 *          1 = start the animation
 * 
 */

#define SDA             PC4
#define SCL             PC5
#define DEVICE          0x36   //provide the bus adress here

#define NR_OF_PORTS     2
#define PCF_PORT_A      0       //equsls to cmd
#define PCF_PORT_B      1       //equals to val

#define CMD             0
#define VAL             1

enum I2CCommands {
  CMD_STOP,
  CMD_START,
  //extend with symbols you need
  CMD_NONE              //always the last element in the list
};

/**
 * @brief Setup the I2C communication
 * 
 */
void i2c_setup();

/**
 * @brief Checks, if there are some new data received via I2C
 * 
 * @return boolean   true = new data available, false otherwise
 */
boolean i2c_avail();

/**
 * @brief Provide the command received via the i2c bus
 * 
 * @return I2CCommands 
 */
I2CCommands i2c_command();

/**
 * @brief Provides the value, received via I2C bus, if any
 * 
 * @return uint8_t 
 */
uint8_t i2c_value();

#endif