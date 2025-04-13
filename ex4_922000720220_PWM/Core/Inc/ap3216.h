
 
 #ifndef INC_AP3216C_H_
 #define INC_AP3216C_H_
  
 #include "main.h"
  
 #define AP3216_ADDR (0x3C)
 #define AP3216_W (0x00)
 #define AP3216_R (0x01)
  
 /**************** System Register ****************/
 #define SYS_CONFIG_ADDR (0x00) // System Configuration, Default:0x00,Bits[2:0],System Mode
 #define SYS_ALS_ACT (0x01) // 0x01: ALS function active
 #define SYS_SW_RESET (0x04) // 0x04: SW reset
 #define ALS_DATA_LOW (0x0C) // Bits[7:0](RO) ALS lower byte of ADC OUTPUT
 #define ALS_DATA_HIGH (0x0D) // Bits[7:0](RO) ALS Higher byte of ADC OUTPUT
  
 extern uint8_t AP3216_Init(void);
 extern uint8_t AP3216_WriteOneByte(uint8_t reg, uint8_t data);
 extern uint8_t AP3216_ReadOneByte(uint8_t reg);
 extern uint16_t AP3216_Read_ALS_Data();
  
 #endif