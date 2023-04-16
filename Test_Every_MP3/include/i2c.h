#ifndef I2C_h
#define I2C_h


#define SDA             PC4
#define SCL             PC5
#define DEVICE          0x32

#define NR_OF_PORTS     2
#define PCF_PORT_A      0       //equsls to cmd
#define PCF_PORT_B      1       //equals to val

#define CMD             0
#define VAL             1

enum I2CCommands {
  CMD_STOP,
  CMD_START,
  CMD_PLAY,
  CMD_SKIP,
  CMD_VOLUP,
  CMD_VOLDOWN,
  CMD_VOLSETTO,
  CMD_VOLMAX,
  CMD_NONE              //always the last element in the list
};

void i2c_setup();

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