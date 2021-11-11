/*
 * max77658_pm.c
 *
 *  Created on: Nov 9, 2021
 *      Author: kai
 */

/* Includes ----------------------------------------------------------- */
#include "max77658_pm.h"

/* Private defines ---------------------------------------------------- */


/* Private enumerate/structure ---------------------------------------- */
/* Private macros ----------------------------------------------------- */
/* Public variables --------------------------------------------------- */
/* Private variables -------------------------------------------------- */
static const char *TAG = "MAX77658 PM";


/* Private function prototypes ---------------------------------------- */
/* Function definitions ----------------------------------------------- */

/**
  * @brief  Read generic device register
  *
  * @param  ctx   communication interface handler.(ptr)
  * @param  reg   first register address to read.
  * @param  data  buffer for data read.(ptr)
  * @param  len   number of consecutive register to read.
  * @retval       interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t max77658_pm_read_reg(max77658_pm_t *ctx, uint8_t reg, uint8_t *data)
{
   int32_t ret;

   ret = ctx->read_reg(ctx->device_address, reg, data, 1);

   return ret;
}

/**
  * @brief  Write generic device register
  *
  * @param  ctx   communication interface handler.(ptr)
  * @param  reg   first register address to write.
  * @param  data  the buffer contains data to be written.(ptr)
  * @param  len   number of consecutive register to write.
  * @retval       interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t max77658_pm_write_reg(max77658_pm_t *ctx, uint8_t reg, uint8_t *data)
{
   int32_t ret;

   ret = ctx->write_reg(ctx->device_address, reg, data, 1);

   return ret;
}

/**
 * @brief  Returns Part Number.[get]
 *
 * @param  ctx      read / write interface definitions
 * @retval          1=MAX77650; 2=MAX77651; -1=error reading DeviceID
 *
 */
int32_t max77658_pm_get_DIDM(max77658_pm_t *ctx)
{
   int32_t ret = false;
   uint8_t data;

   ret = max77658_pm_read_reg(ctx, MAX77650_STAT_GLBL_ADDR, &data);
   if(ret > 0)
   {
      ret = (data >> 6) & 0b00000011;
   }

   return ret;
}

/**
 * @brief  Returns wheather the LDO is in Dropout or not.[get]
 *
 * @param  ctx      read / write interface definitions
 * @retval          0=LDO is not in dropout; 1=LDO is in dropout
 *
 */
int32_t max77658_pm_get_LDO_dropout_detector(max77658_pm_t *ctx)
{
   int32_t ret;
   uint8_t data;

   ret = max77658_pm_read_reg(ctx, MAX77650_STAT_GLBL_ADDR, &data);
   if(ret > 0)
   {
      ret = (data >> 5) & 0b00000001;
   }

   return ret;
}

/**
 * @brief  Returns Thermal Alarm (TJA1 limit).[get]
 *
 * @param  ctx      read / write interface definitions
 * @retval          0=Tj<TJA1; 1=Tj>TJA1
 *
 */
int32_t max77658_pm_get_thermal_alarm1(max77658_pm_t *ctx)
{
   int32_t ret;
   uint8_t data;

   ret = max77658_pm_read_reg(ctx, MAX77650_STAT_GLBL_ADDR, &data);
   if(ret > 0)
   {
      ret = (data >> 3) & 0b00000001;
   }

   return ret;
}

/**
 * @brief  Therma2 Alarm (TJA2 limit).[get]
 *
 * @param  ctx      read / write interface definitions
 * @retval          0=Tj<TJA2; 1=Tj>TJA2
 *
 */
int32_t max77658_pm_get_thermal_alarm2(max77658_pm_t *ctx)
{
   int32_t ret;
   uint8_t data;

   ret = max77658_pm_read_reg(ctx, MAX77650_STAT_GLBL_ADDR, &data);
   if(ret > 0)
   {
      ret = (data >> 4) & 0b00000001;
   }

   return ret;
}

/**
 * @brief  Debounced Status of nEN input.[get]
 *
 * @param  ctx      read / write interface definitions
 * @retval          0=nEN0 is not active; 1=nEN0 is active
 *
 */
int32_t max77658_pm_get_debounce_Status_nEN0(max77658_pm_t *ctx)
{
   int32_t ret;
   uint8_t data;

   ret = max77658_pm_read_reg(ctx, MAX77650_STAT_GLBL_ADDR, &data);
   if(ret > 0)
   {
      ret = (data >> 2) & 0b00000001;
   }

   return ret;
}

/**
 * @brief  Debounced Status of PWR_HLD input.[get]
 *
 * @param  ctx      read / write interface definitions
 * @retval          0=logic low; 1=logic high
 *
 */
int32_t max77658_pm_get_debounce_Status_PWR_HLD(max77658_pm_t *ctx)
{
   int32_t ret;
   uint8_t data;

   ret = max77658_pm_read_reg(ctx, MAX77650_STAT_GLBL_ADDR, &data);
   if(ret > 0)
   {
      ret = (data >> 1) & 0b00000001;
   }

   return ret;
}

/**
 * @brief  Flag Register (ERCFLAG) related reads.[get]
 *
 * @param  ctx      read / write interface definitions
 * @retval          ERCFLAG Register 0x04
 *
 */
int32_t max77658_pm_get_ERCFLAG(max77658_pm_t *ctx)
{
   int32_t ret;
   uint8_t data;

   ret = (max77658_pm_read_reg(ctx, MAX77650_ERCFLAG_ADDR, &data) > 0)?data:(-1);

   return ret;
}

/**
 * @brief  OTP parts.[get]
 *
 * @param  ctx      read / write interface definitions
 * @retval          Value regaring OTP parts of the MAX77658
 *
 */
int32_t max77658_pm_get_chipID(max77658_pm_t *ctx)
{
   int32_t ret;
   uint8_t data;

   ret = max77658_pm_read_reg(ctx, MAX77650_CID_ADDR, &data);
   if(ret > 0)
   {
      ret = (data & 0b00001111);
   }

   return ret;
}

/**
 * @brief  Minimum Input Voltage Regulation Loop Status.[get]
 *
 * @param  ctx      read / write interface definitions
 * @retval          0=no event; 1=The minimum CHGIN voltage regulation loop has engaged to regulate VCHGIN >= VCHGIN-MIN
 *
 */
int32_t max77658_pm_get_VCHGIN_MIN_STAT(max77658_pm_t *ctx)
{
   int32_t ret;
   uint8_t data;

   ret = max77658_pm_read_reg(ctx, MAX77650_STAT_CHG_A_ADDR, &data);
   if(ret > 0)
   {
      ret = (data >> 6) & 0b00000001;
   }

   return ret;
}

/**
 * @brief  Input Current Limit Loop Status.[get]
 *
 * @param  ctx      read / write interface definitions
 * @retval          0=no event; 1=The CHGIN current limit loop has engaged to regulate ICHGIN <= ICHGIN-LIM
 *
 */
int32_t max77658_pm_get_ICHGIN_LIM_STAT(max77658_pm_t *ctx)
{
   int32_t ret;
   uint8_t data;

   ret = max77658_pm_read_reg(ctx, MAX77650_STAT_CHG_A_ADDR, &data);
   if(ret > 0)
   {
      ret = (data >> 5) & 0b00000001;
   }

   return ret;
}

/**
 * @brief  Minimum System Voltage Regulation Loop Status.[get]
 *
 * @param  ctx      read / write interface definitions
 * @retval          0=no event; 1=The minimum system voltage regulation loop is engaged to regulate VSYS >= VSYS-MIN
 *
 */
int32_t max77658_pm_get_VSYS_MIN_STAT(max77658_pm_t *ctx)
{
   int32_t ret;
   uint8_t data;

   ret = max77658_pm_read_reg(ctx, MAX77650_STAT_CHG_A_ADDR, &data);
   if(ret > 0)
   {
      ret = (data >> 4) & 0b00000001;
   }

   return ret;
}

/**
 * @brief  Maximum Junction Temperature Regulation Loop Status.[get]
 *
 * @param  ctx      read / write interface definitions
 * @retval          0=no event; 1=The maximum junction temperature regulation loop has engaged to regulate the junction temperature less than TJ-REG
 *
 */
int32_t max77658_pm_get_TJ_REG_STAT(max77658_pm_t *ctx)
{
   int32_t ret;
   uint8_t data;

   ret = max77658_pm_read_reg(ctx, MAX77650_STAT_CHG_A_ADDR, &data);
   if(ret > 0)
   {
      ret = (data >> 3) & 0b00000001;
   }

   return ret;
}

/**
 * @brief  Battery Temperature Details.[get]
 *
 * @param  ctx      read / write interface definitions
 * @retval          Battery Temperature Details
 *
 */
int32_t max77658_pm_get_THM_DTLS(max77658_pm_t *ctx)
{
   int32_t ret;
   uint8_t data;

   ret = max77658_pm_read_reg(ctx, MAX77650_STAT_CHG_A_ADDR, &data);
   if(ret > 0)
   {
      ret = data & 0b00000111;
   }

   return ret;
}

/**
 * @brief  Charger Details.[get]
 *
 * @param  ctx      read / write interface definitions
 * @retval          Charger Details
 *
 */
int32_t max77658_pm_get_CHG_DTLS(max77658_pm_t *ctx)
{
   int32_t ret;
   uint8_t data;

   ret = max77658_pm_read_reg(ctx, MAX77650_STAT_CHG_B_ADDR, &data);
   if(ret > 0)
   {
      ret = (data >> 4) & 0b00001111;
   }

   return ret;
}

/**
 * @brief  CHGIN Status Details.[get]
 *
 * @param  ctx      read / write interface definitions
 * @retval          CHGIN Status Details
 *
 */
int32_t max77658_pm_get_CHGIN_DTLS(max77658_pm_t *ctx)
{
   int32_t ret;
   uint8_t data;

   ret = max77658_pm_read_reg(ctx, MAX77650_STAT_CHG_B_ADDR, &data);
   if(ret > 0)
   {
      ret = (data >> 2) & 0b00000011;
   }

   return ret;
}

/**
 * @brief  Quick Charger Status.[get]
 *
 * @param  ctx      read / write interface definitions
 * @retval          Quick Charger Status
 *
 */
int32_t max77658_pm_get_CHG(max77658_pm_t *ctx)
{
   int32_t ret;
   uint8_t data;

   ret = max77658_pm_read_reg(ctx, MAX77650_STAT_CHG_B_ADDR, &data);
   if(ret > 0)
   {
      ret = (data >> 1) & 0b00000001;
   }

   return ret;
}

/**
 * @brief  Time Suspend Indicator.[get]
 *
 * @param  ctx      read / write interface definitions
 * @retval          Time Suspend Indicator
 *
 */
int32_t max77658_pm_get_TIME_SUS(max77658_pm_t *ctx)
{
   int32_t ret;
   uint8_t data;

   ret = max77658_pm_read_reg(ctx, MAX77650_STAT_CHG_B_ADDR, &data);
   if(ret > 0)
   {
      ret = data & 0b00000001;
   }

   return ret;
}

/**
 * @brief  LED0 Full Scale Range.[get]
 *
 * @param  ctx      read / write interface definitions
 * @retval          LED0 Full Scale Range
 *
 */
int32_t max77658_pm_get_LED_FS0(max77658_pm_t *ctx)
{
   int32_t ret;
   uint8_t data;

   ret = max77658_pm_read_reg(ctx, MAX77650_CNFG_LED0_A_ADDR, &data);
   if(ret > 0)
   {
      ret = (data >> 6) & 0b00000011;
   }

   return ret;
}

/**
 * @brief  LED0 Invert.[get]
 *
 * @param  ctx      read / write interface definitions
 * @retval          LED0 Invert
 *
 */
int32_t max77658_pm_get_INV_LED0(max77658_pm_t *ctx)
{
   int32_t ret;
   uint8_t data;

   ret = max77658_pm_read_reg(ctx, MAX77650_CNFG_LED0_A_ADDR, &data);
   if(ret > 0)
   {
      ret = (data >> 5) & 0b00000001;
   }

   return ret;
}

/**
 * @brief  LED0 Brightness Control.[get]
 *
 * @param  ctx      read / write interface definitions
 * @retval          LED0 Full Scale Range
 *
 */
int32_t max77658_pm_get_BRT_LED0(max77658_pm_t *ctx)
{
   int32_t ret;
   uint8_t data;

   ret = max77658_pm_read_reg(ctx, MAX77650_CNFG_LED0_A_ADDR, &data);
   if(ret > 0)
   {
      ret = data & 0b00011111;
   }

   return ret;
}

/**
 * @brief  LED0 Period Settings.[get]
 *
 * @param  ctx      read / write interface definitions
 * @retval          LED0 Period Settings
 *
 */
int32_t max77658_pm_get_P_LED0(max77658_pm_t *ctx)
{
   int32_t ret;
   uint8_t data;

   ret = max77658_pm_read_reg(ctx, MAX77650_CNFG_LED0_B_ADDR, &data);
   if(ret > 0)
   {
      ret = (data >> 4) & 0b00001111;
   }

   return ret;
}

/**
 * @brief  LED0 On Duty-Cycle Settings.[get]
 *
 * @param  ctx      read / write interface definitions
 * @retval          LED0 On Duty-Cycle Settings
 *
 */
int32_t max77658_pm_get_D_LED0(max77658_pm_t *ctx)
{
   int32_t ret;
   uint8_t data;

   ret = max77658_pm_read_reg(ctx, MAX77650_CNFG_LED0_B_ADDR, &data);
   if(ret > 0)
   {
      ret = data & 0b00001111;
   }

   return ret;
}

/**
 * @brief  LED1 Full Scale Range.[get]
 *
 * @param  ctx      read / write interface definitions
 * @retval          LED1 Full Scale Range
 *
 */
int32_t max77658_pm_get_LED_FS1(max77658_pm_t *ctx)
{
   int32_t ret;
   uint8_t data;

   ret = max77658_pm_read_reg(ctx, MAX77650_CNFG_LED1_A_ADDR, &data);
   if(ret > 0)
   {
      ret = (data >> 6) & 0b00000011;
   }

   return ret;
}

/**
 * @brief  LED1 Invert.[get]
 *
 * @param  ctx      read / write interface definitions
 * @retval          LED1 Invert
 *
 */
int32_t max77658_pm_get_INV_LED1(max77658_pm_t *ctx)
{
   int32_t ret;
   uint8_t data;

   ret = max77658_pm_read_reg(ctx, MAX77650_CNFG_LED1_A_ADDR, &data);
   if(ret > 0)
   {
      ret = (data >> 5) & 0b00000001;
   }

   return ret;
}

/**
 * @brief  LED1 Brightness Control.[get]
 *
 * @param  ctx      read / write interface definitions
 * @retval          LED1 Brightness Control
 *
 */
int32_t max77658_pm_get_BRT_LED1(max77658_pm_t *ctx)
{
   int32_t ret;
   uint8_t data;

   ret = max77658_pm_read_reg(ctx, MAX77650_CNFG_LED1_A_ADDR, &data);
   if(ret > 0)
   {
      ret = data & 0b00011111;
   }

   return ret;
}

/**
 * @brief  LED1 Period Settings.[get]
 *
 * @param  ctx      read / write interface definitions
 * @retval          LED1 Period Settings
 *
 */
int32_t max77658_pm_get_P_LED1(max77658_pm_t *ctx)
{
   int32_t ret;
   uint8_t data;

   ret = max77658_pm_read_reg(ctx, MAX77650_CNFG_LED1_B_ADDR, &data);
   if(ret > 0)
   {
      ret = (data >> 4) & 0b00001111;
   }

   return ret;
}

/**
 * @brief  LED1 On Duty-Cycle Settings.[get]
 *
 * @param  ctx      read / write interface definitions
 * @retval          LED1 On Duty-Cycle Settings
 *
 */
uint8_t max77658_pm_get_D_LED1(max77658_pm_t *ctx)
{
   int32_t ret;
   uint8_t data;

   ret = max77658_pm_read_reg(ctx, MAX77650_CNFG_LED1_B_ADDR, &data);
   if(ret > 0)
   {
      ret = data & 0b00001111;
   }

   return ret;
}

/**
 * @brief  LED2 Full Scale Range.[get]
 *
 * @param  ctx      read / write interface definitions
 * @retval          LED0 Full Scale Range
 *
 */
int32_t max77658_pm_get_LED_FS2(max77658_pm_t *ctx)
{
   int32_t ret;
   uint8_t data;

   ret = max77658_pm_read_reg(ctx, MAX77650_CNFG_LED2_A_ADDR, &data);
   if(ret > 0)
   {
      ret = (data >> 6) & 0b00000011;
   }

   return ret;
}

/**
 * @brief  LED2 Invert.[get]
 *
 * @param  ctx      read / write interface definitions
 * @retval          LED2 Invert
 *
 */
int32_t max77658_pm_get_INV_LED2(max77658_pm_t *ctx)
{
   int32_t ret;
   uint8_t data;

   ret = max77658_pm_read_reg(ctx, MAX77650_CNFG_LED2_A_ADDR, &data);
   if(ret > 0)
   {
      ret = (data >> 5) & 0b00000001;
   }

   return ret;
}

/**
 * @brief  LED2 Brightness Control.[get]
 *
 * @param  ctx      read / write interface definitions
 * @retval          LED2 Brightness Control
 *
 */
int32_t max77658_pm_get_BRT_LED2(max77658_pm_t *ctx)
{
   int32_t ret;
   uint8_t data;

   ret = max77658_pm_read_reg(ctx, MAX77650_CNFG_LED2_A_ADDR, &data);
   if(ret > 0)
   {
      ret = data & 0b00011111;
   }

   return ret;
}

/**
 * @brief  LED2 Period Settings.[get]
 *
 * @param  ctx      read / write interface definitions
 * @retval          LED2 Period Settings
 *
 */
int32_t max77658_pm_get_P_LED2(max77658_pm_t *ctx)
{
   int32_t ret;
   uint8_t data;

   ret = max77658_pm_read_reg(ctx, MAX77650_CNFG_LED2_B_ADDR, &data);
   if(ret > 0)
   {
      ret = (data >> 4) & 0b00001111;
   }

   return ret;
}

/**
 * @brief  LED2 On Duty-Cycle Settings.[get]
 *
 * @param  ctx      read / write interface definitions
 * @retval          LED2 On Duty-Cycle Settings
 *
 */
int32_t max77658_pm_get_D_LED2(max77658_pm_t *ctx)
{
   int32_t ret;
   uint8_t data;

   ret = max77658_pm_read_reg(ctx, MAX77650_CNFG_LED2_B_ADDR, &data);
   if(ret > 0)
   {
      ret = data & 0b00001111;
   }

   return ret;
}

/**
 * @brief  Main Bias Okay Status Bit.[get]
 *
 * @param  ctx      read / write interface definitions
 * @retval          Main Bias Okay Status Bit
 *
 */
int32_t max77658_pm_get_BOK(max77658_pm_t *ctx)
{
   int32_t ret;
   uint8_t data;

   ret = max77658_pm_read_reg(ctx, MAX77650_CNFG_GLBL_ADDR, &data);
   if(ret > 0)
   {
      ret = (data >> 6) & 0b00000001;
   }

   return ret;
}

/**
 * @brief  Main Bias Low-Power Mode software request.[get]
 *
 * @param  ctx      read / write interface definitions
 * @retval          Main Bias Low-Power Mode software request
 *
 */
int32_t max77658_pm_get_SBIA_LPM(max77658_pm_t *ctx)
{
   int32_t ret;
   uint8_t data;

   ret = max77658_pm_read_reg(ctx, MAX77650_CNFG_GLBL_ADDR, &data);
   if(ret > 0)
   {
      ret = (data >> 5) & 0b00000001;
   }

   return ret;
}

/**
 * @brief  Main Bias Enable Software Request.[get]
 *
 * @param  ctx      read / write interface definitions
 * @retval          Main Bias Enable Software Request
 *
 */
int32_t max77658_pm_get_SBIA_EN(max77658_pm_t *ctx)
{
   int32_t ret;
   uint8_t data;

   ret = max77658_pm_read_reg(ctx, MAX77650_CNFG_GLBL_ADDR, &data);
   if(ret > 0)
   {
      ret = (data >> 4) & 0b00000001;
   }

   return ret;
}

/**
 * @brief  nEN Input (ONKEY) Default Configuration Mode.[get]
 *
 * @param  ctx      read / write interface definitions
 * @retval          nEN Input (ONKEY) Default Configuration Mode
 *
 */
int32_t max77658_pm_get_nEN_MODE(max77658_pm_t *ctx)
{
   int32_t ret;
   uint8_t data;

   ret = max77658_pm_read_reg(ctx, MAX77650_CNFG_GLBL_ADDR, &data);
   if(ret > 0)
   {
      ret = (data >> 3) & 0b00000001;
   }

   return ret;
}

/**
 * @brief  Debounce Timer Enable for the nEN Pin.[get]
 *
 * @param  ctx      read / write interface definitions
 * @retval          Debounce Timer Enable for the nEN Pin
 *
 */
int32_t max77658_pm_get_DBEN_nEN(max77658_pm_t *ctx)
{
   int32_t ret;
   uint8_t data;

   ret = max77658_pm_read_reg(ctx, MAX77650_CNFG_GLBL_ADDR, &data);
   if(ret > 0)
   {
      ret = (data >> 2) & 0b00000001;
   }

   return ret;
}

/**
 * @brief  Software Reset Functions.[get]
 *
 * @param  ctx      read / write interface definitions
 * @retval          Software Reset Functions
 *
 */
int32_t max77658_pm_get_SFT_RST(max77658_pm_t *ctx)
{
   int32_t ret;
   uint8_t data;

   ret = max77658_pm_read_reg(ctx, MAX77650_CNFG_GLBL_ADDR, &data);
   if(ret > 0)
   {
      ret = data & 0b00000001;
   }

   return ret;
}

/**
 * @brief  Interrupt Status Register 0x00.[get]
 *
 * @param  ctx      read / write interface definitions
 * @retval          Interrupt Status Register 0x00
 *
 */
int32_t max77658_pm_get_INT_GLBL(max77658_pm_t *ctx){ //Returns
  return max77658_pm_read_reg(ctx, MAX77650_INT_GLBL_ADDR);
}

uint8_t MAX77650_getINT_M_GLBL(max77658_pm_t *ctx){ //Returns Global Interrupt Mask Register
   return (max77658_pm_read_reg(ctx, MAX77650_INTM_GLBL_ADDR) & 0b01111111);
}

int32_t MAX77650_getDBEN_GPI(max77658_pm_t *ctx){ //Returns General Purpose Input Debounce Timer Enable
   return ((max77658_pm_read_reg(ctx, MAX77650_CNFG_GPIO_ADDR) >> 4) & 0b00000001);
}
int32_t MAX77650_getDO(max77658_pm_t *ctx){ //Returns General Purpose Output Data Output
   return ((max77658_pm_read_reg(ctx, MAX77650_CNFG_GPIO_ADDR) >> 3) & 0b00000001);
}
int32_t MAX77650_getDRV(max77658_pm_t *ctx){ //Returns General Purpose Output Driver Type
   return ((max77658_pm_read_reg(ctx, MAX77650_CNFG_GPIO_ADDR) >> 2) & 0b00000001);
}
int32_t MAX77650_getDI(max77658_pm_t *ctx){ //Returns GPIO Digital Input Value
   return ((max77658_pm_read_reg(ctx, MAX77650_CNFG_GPIO_ADDR) >> 1) & 0b00000001);
}
int32_t MAX77650_getDIR(max77658_pm_t *ctx){ //Returns GPIO Direction
   return (max77658_pm_read_reg(ctx, MAX77650_CNFG_GPIO_ADDR) & 0b00000001);
}

//Charger Interrupt Status Register 0x01
uint8_t MAX77650_getINT_CHG(max77658_pm_t *ctx){ //Returns Charger Interrupt Status Register 0x01
 return max77658_pm_read_reg(ctx, MAX77650_INT_CHG_ADDR);
}

//Charger Interrupt Mask Register 0x07
uint8_t MAX77650_getINT_M_CHG(max77658_pm_t *ctx){ //Returns Global Interrupt Mask Register
   return (max77658_pm_read_reg(ctx, MAX77650_INT_M_CHG_ADDR) & 0b01111111);
}

//Charger Configuration Register A 0x18
uint8_t MAX77650_getTHM_HOT(max77658_pm_t *ctx){ //Returns the VHOT JEITA Temperature Threshold
  return ((max77658_pm_read_reg(ctx, MAX77650_CNFG_CHG_A_ADDR) >> 6) & 0b00000011);
}
uint8_t MAX77650_getTHM_WARM(max77658_pm_t *ctx){ //Returns the VWARM JEITA Temperature Threshold
  return ((max77658_pm_read_reg(ctx, MAX77650_CNFG_CHG_A_ADDR) >> 4) & 0b00000011);
}
uint8_t MAX77650_getTHM_COOL(max77658_pm_t *ctx){ //Returns the VCOOL JEITA Temperature Threshold
  return ((max77658_pm_read_reg(ctx, MAX77650_CNFG_CHG_A_ADDR) >> 2) & 0b00000011);
}
uint8_t MAX77650_getTHM_COLD(max77658_pm_t *ctx){ //Returns the VCOLD JEITA Temperature Threshold
  return (max77658_pm_read_reg(ctx, MAX77650_CNFG_CHG_A_ADDR) & 0b00000011);
}

//Charger Configuration Register B 0x19
uint8_t MAX77650_getVCHGIN_MIN(max77658_pm_t *ctx){ //Returns the Minimum CHGIN regulation voltage (VCHGIN-MIN)
  return ((max77658_pm_read_reg(ctx, MAX77650_CNFG_CHG_B_ADDR) >> 5) & 0b00000111);
}
uint8_t MAX77650_getICHGIN_LIM(max77658_pm_t *ctx){ //Returns the CHGIN Input Current Limit (ICHGIN-LIM)
  return ((max77658_pm_read_reg(ctx, MAX77650_CNFG_CHG_B_ADDR) >> 2) & 0b00000111);
}
int32_t MAX77650_getI_PQ(max77658_pm_t *ctx){ //Returns the prequalification charge current (IPQ) as a percentage of IFAST-CHG
  return ((max77658_pm_read_reg(ctx, MAX77650_CNFG_CHG_B_ADDR) >> 1) & 0b00000001);
}
int32_t MAX77650_getCHG_EN(max77658_pm_t *ctx){ //Returns Charger Enable
  return (max77658_pm_read_reg(ctx, MAX77650_CNFG_CHG_B_ADDR) & 0b00000001);
}

//Charger Configuration Register C 0x1A
uint8_t MAX77650_getCHG_PQ(max77658_pm_t *ctx){ //Returns the Battery prequalification voltage threshold (VPQ)
  return ((max77658_pm_read_reg(ctx, MAX77650_CNFG_CHG_C_ADDR) >> 5) & 0b00000111);
}
uint8_t MAX77650_getI_TERM(max77658_pm_t *ctx){ //Returns the Charger Termination Current (ITERM). I_TERM[1:0] sets the charger termination current as a percentage of the fast charge current IFAST-CHG.
  return ((max77658_pm_read_reg(ctx, MAX77650_CNFG_CHG_C_ADDR) >> 3) & 0b00000011);
}
uint8_t MAX77650_getT_TOPOFF(max77658_pm_t *ctx){ //Returns the Topoff timer value (tTO)
  return (max77658_pm_read_reg(ctx, MAX77650_CNFG_CHG_C_ADDR) & 0b00000111);
}

//Charger Configuration Register D 0x1B
uint8_t MAX77650_getTJ_REG(max77658_pm_t *ctx){ //Returns the die junction temperature regulation point, TJ-REG
  return ((max77658_pm_read_reg(ctx, MAX77650_CNFG_CHG_D_ADDR) >> 5) & 0b00000111);
}
uint8_t MAX77650_getVSYS_REG(max77658_pm_t *ctx){ //Returns the System voltage regulation (VSYS-REG)
  return (max77658_pm_read_reg(ctx, MAX77650_CNFG_CHG_D_ADDR) & 0b00011111);
}

//Charger Configuration Register E 0x1C
uint8_t MAX77650_getCHG_CC(max77658_pm_t *ctx){ //Returns the fast-charge constant current value, IFAST-CHG.
  return ((max77658_pm_read_reg(ctx, MAX77650_CNFG_CHG_E_ADDR) >> 2) & 0b00111111);
}
uint8_t MAX77650_getT_FAST_CHG(max77658_pm_t *ctx){ //Returns the fast-charge safety timer, tFC.
  return (max77658_pm_read_reg(ctx, MAX77650_CNFG_CHG_E_ADDR) & 0b00000011);
}

//Charger Configuration Register F 0x1D
uint8_t MAX77650_getCHG_CC_JEITA(max77658_pm_t *ctx){ //Returns the IFAST-CHG_JEITA for when the battery is either cool or warm as defined by the TCOOL and TWARM temperature thresholds. This register is a don't care if the battery temperature is normal.
  return ((max77658_pm_read_reg(ctx, MAX77650_CNFG_CHG_F_ADDR) >> 2) & 0b00111111);
}
uint8_t MAX77650_getTHM_EN(max77658_pm_t *ctx){ //Returns the Thermistor enable bit
  return ((max77658_pm_read_reg(ctx, MAX77650_CNFG_CHG_F_ADDR) >> 1) & 0b00000001);
}

//Charger Configuration Register G 0x1E
uint8_t MAX77650_getCHG_CV(max77658_pm_t *ctx){ //Returns the fast-charge battery regulation voltage, VFAST-CHG.
  return ((max77658_pm_read_reg(ctx, MAX77650_CNFG_CHG_G_ADDR) >> 2) & 0b00111111);
}
int32_t MAX77650_getUSBS(max77658_pm_t *ctx){ //this bit places CHGIN in USB suspend mode
  return ((max77658_pm_read_reg(ctx, MAX77650_CNFG_CHG_G_ADDR) >> 1) & 0b00000001);
}

//Charger Configuration Register H 0x1F
uint8_t MAX77650_getCHG_CV_JEITA(max77658_pm_t *ctx){ //Returns the modified VFAST-CHG for when the battery is either cool or warm as defined by the TCOOL and TWARM temperature thresholds. This register is a don't care if the battery temperature is normal.
  return ((max77658_pm_read_reg(ctx, MAX77650_CNFG_CHG_H_ADDR) >> 2) & 0b00111111);
}

//Charger Configuration Register I 0x20
uint8_t MAX77650_getIMON_DISCHG_SCALE(max77658_pm_t *ctx){ //Returns the Selects the battery discharge current full-scale current value This 4-bit configuration starts at 7.5mA and ends at 300mA.
  return ((max77658_pm_read_reg(ctx, MAX77650_CNFG_CHG_I_ADDR) >> 4) & 0b00001111);
}
uint8_t MAX77650_getMUX_SEL(max77658_pm_t *ctx){ //Returns the analog channel to connect to AMUX configuration
  return (max77658_pm_read_reg(ctx, MAX77650_CNFG_CHG_I_ADDR) & 0b00001111);
}

//LDO Configuration Register A 0x38
uint8_t MAX77650_getTV_LDO(max77658_pm_t *ctx){ //Returns the LDO Target Output Voltage
  return (max77658_pm_read_reg(ctx, MAX77650_CNFG_LDO_A_ADDR) & 0b01111111);
}

//LDO Configuration Register B 0x39
int32_t MAX77650_getADE_LDO(max77658_pm_t *ctx){ //Returns LDO active-Discharge Enable
  return ((max77658_pm_read_reg(ctx, MAX77650_CNFG_LDO_B_ADDR) >> 3) & 0b00000001);
}
uint8_t MAX77650_getEN_LDO(max77658_pm_t *ctx){ //Enable Control for LDO.
  return (max77658_pm_read_reg(ctx, MAX77650_CNFG_LDO_B_ADDR) & 0b00000111);
}

//SIMO Buck-Boost Global Configuration Register 0x28
int32_t MAX77650_getMRT_OTP(max77658_pm_t *ctx){ //Returns Manual Reset Time Configuration
  return ((max77658_pm_read_reg(ctx, MAX77650_CNFG_SBB_TOP_ADDR) >> 6) & 0b00000001);
}
int32_t MAX77650_getSBIA_LPM_DEF(max77658_pm_t *ctx){ //Returns Default voltage of the SBIA_LPM bit
  return ((max77658_pm_read_reg(ctx, MAX77650_CNFG_SBB_TOP_ADDR) >> 5) & 0b00000001);
}
int32_t MAX77650_getDBNC_nEN_DEF(max77658_pm_t *ctx){ //Returns Default Value of the DBNC_nEN bit
  return ((max77658_pm_read_reg(ctx, MAX77650_CNFG_SBB_TOP_ADDR) >> 4) & 0b00000001);
}
uint8_t MAX77650_getDRV_SBB(max77658_pm_t *ctx){ //Returns the SIMO Buck-Boost (all channels) Drive Strength Trim.
  return (max77658_pm_read_reg(ctx, MAX77650_CNFG_SBB_TOP_ADDR) & 0b00000011);
}

//SIMO Buck-Boost 0 Configuration Register A 0x29
uint8_t MAX77650_getIP_SBB0(max77658_pm_t *ctx){ //Returns the SIMO Buck-Boost Channel 1 Peak Current Limit
  return ((max77658_pm_read_reg(ctx, MAX77650_CNFG_SBB0_A_ADDR) >> 6) & 0b00000011);
}
uint8_t MAX77650_getTV_SBB0(max77658_pm_t *ctx){ //Returns the SIMO Buck-Boost Channel 0 Target Output Voltage
  return (max77658_pm_read_reg(ctx, MAX77650_CNFG_SBB0_A_ADDR) & 0b00111111);
}

//SIMO Buck-Boost 0 Configuration Register B 0x2A
int32_t MAX77650_getADE_SBB0(max77658_pm_t *ctx){ //Returns SIMO Buck-Boost Channel 0 Active-Discharge Enable
  return ((max77658_pm_read_reg(ctx, MAX77650_CNFG_SBB0_B_ADDR) >> 3) & 0b00000001);
}
uint8_t MAX77650_getEN_SBB0(max77658_pm_t *ctx){ //Returns the Enable Control for SIMO Buck-Boost Channel 0.
  return (max77658_pm_read_reg(ctx, MAX77650_CNFG_SBB0_B_ADDR) & 0b00000111);
}

//SIMO Buck-Boost 1 Configuration Register A 0x2B
uint8_t MAX77650_getIP_SBB1(max77658_pm_t *ctx){ //Returns the SIMO Buck-Boost Channel 1 Peak Current Limit
  return ((max77658_pm_read_reg(ctx, MAX77650_CNFG_SBB1_A_ADDR) >> 6) & 0b00000011);
}
uint8_t MAX77650_getTV_SBB1(max77658_pm_t *ctx){ //Returns the SIMO Buck-Boost Channel 1 Target Output Voltage
  return (max77658_pm_read_reg(ctx, MAX77650_CNFG_SBB1_A_ADDR) & 0b00111111);
}

//SIMO Buck-Boost 1 Configuration Register B 0x2C
int32_t MAX77650_getADE_SBB1(max77658_pm_t *ctx){ //Returns SIMO Buck-Boost Channel 1 Active-Discharge Enable
  return ((max77658_pm_read_reg(ctx, MAX77650_CNFG_SBB1_B_ADDR) >> 3) & 0b00000001);
}
uint8_t MAX77650_getEN_SBB1(max77658_pm_t *ctx){ //Returns the Enable Control for SIMO Buck-Boost Channel 1.
  return (max77658_pm_read_reg(ctx, MAX77650_CNFG_SBB1_B_ADDR) & 0b00000111);
}

//SIMO Buck-Boost 2 Configuration Register A 0x2D
uint8_t MAX77650_getIP_SBB2(max77658_pm_t *ctx){ //Returns the SIMO Buck-Boost Channel 2 Peak Current Limit
  return ((max77658_pm_read_reg(ctx, MAX77650_CNFG_SBB2_A_ADDR) >> 6) & 0b00000011);
}
uint8_t MAX77650_getTV_SBB2(max77658_pm_t *ctx){ //Returns the SIMO Buck-Boost Channel 2 Target Output Voltage
  return (max77658_pm_read_reg(ctx, MAX77650_CNFG_SBB2_A_ADDR) & 0b00111111);
}

//SIMO Buck-Boost 2 Configuration Register B 0x2E
int32_t MAX77650_getADE_SBB2(max77658_pm_t *ctx){ //Returns SIMO Buck-Boost Channel 2 Active-Discharge Enable
  return ((max77658_pm_read_reg(ctx, MAX77650_CNFG_SBB2_B_ADDR) >> 3) & 0b00000001);
}
uint8_t MAX77650_getEN_SBB2(max77658_pm_t *ctx){ //Returns the Enable Control for SIMO Buck-Boost Channel 2.
  return (max77658_pm_read_reg(ctx, MAX77650_CNFG_SBB2_B_ADDR) & 0b00000111);
}

int32_t MAX77650_getCLK_64_S(max77658_pm_t *ctx){ //Returns 64Hz Clock Status
  return ((max77658_pm_read_reg(ctx, MAX77650_CNFG_LED_TOP_ADDR) >> 1) & 0b00000001);
}
int32_t MAX77650_getEN_LED_MSTR(max77658_pm_t *ctx){ //Returns Master LED Enable Bit
  return (max77658_pm_read_reg(ctx, MAX77650_CNFG_LED_TOP_ADDR) & 0b00000001);
}


//CID Register
uint8_t MAX77650_getCID(max77658_pm_t *ctx){ // Returns the OTP programmed Chip Identification Code
  return (max77658_pm_read_reg(ctx, MAX77650_CID_ADDR) & 0b00001111);
}


//***** Register writes *****

int32_t MAX77650_setTV_LDO(uint8_t target_val){ //Sets the LDO Target Output Voltage
  max77658_pm_write_reg(ctx, MAX77650_CNFG_LDO_A_ADDR,((max77658_pm_read_reg(ctx, MAX77650_CNFG_LDO_A_ADDR) & 0b10000000) | ((target_val & 0b01111111) << 0)));
  if(MAX77650_getTV_LDO()==target_val)
   return true;
  else
   return false;
}

//LDO Configuration Register B 0x39
int32_t MAX77650_setADE_LDO(uint8_t target_val){ //Sets LDO active-Discharge Enable
  max77658_pm_write_reg(ctx, MAX77650_CNFG_LDO_B_ADDR,((max77658_pm_read_reg(ctx, MAX77650_CNFG_LDO_B_ADDR) & 0b11110111) | ((target_val & 0b00000001) << 3)));
  if(MAX77650_getADE_LDO()==target_val)
   return true;
  else
   return false;
}

int32_t MAX77650_setEN_LDO(uint8_t target_val){ //Enable LDO
  max77658_pm_write_reg(ctx, MAX77650_CNFG_LDO_B_ADDR,((max77658_pm_read_reg(ctx, MAX77650_CNFG_LDO_B_ADDR) & 0b11111000) | ((target_val & 0b00000111) << 0)));
  if(MAX77650_getEN_LDO()==target_val)
   return true;
  else
   return false;
}

//Charger Configuration Register A 0x18
int32_t MAX77650_setTHM_HOT(uint8_t target_val){ //Returns the VHOT JEITA Temperature Threshold
  max77658_pm_write_reg(ctx, MAX77650_CNFG_CHG_A_ADDR,((max77658_pm_read_reg(ctx, MAX77650_CNFG_CHG_A_ADDR) & 0b00111111) | ((target_val & 0b00000011) << 6)));
  if(MAX77650_getTHM_HOT()==target_val)
   return true;
  else
   return false;
}
int32_t MAX77650_setTHM_WARM(uint8_t target_val){ //Returns the VWARM JEITA Temperature Threshold
  max77658_pm_write_reg(ctx, MAX77650_CNFG_CHG_A_ADDR,((max77658_pm_read_reg(ctx, MAX77650_CNFG_CHG_A_ADDR) & 0b11001111) | ((target_val & 0b00000011) << 4)));
  if(MAX77650_getTHM_WARM()==target_val)
   return true;
  else
   return false;
}
int32_t MAX77650_setTHM_COOL(uint8_t target_val){ //Returns the VCOOL JEITA Temperature Threshold
  max77658_pm_write_reg(ctx, MAX77650_CNFG_CHG_A_ADDR,((max77658_pm_read_reg(ctx, MAX77650_CNFG_CHG_A_ADDR) & 0b11110011) | ((target_val & 0b00000011) << 2)));
  if(MAX77650_getTHM_COOL()==target_val)
   return true;
  else
   return false;
}
int32_t MAX77650_setTHM_COLD(uint8_t target_val){ //Returns the VCOLD JEITA Temperature Threshold
  max77658_pm_write_reg(ctx, MAX77650_CNFG_CHG_A_ADDR,((max77658_pm_read_reg(ctx, MAX77650_CNFG_CHG_A_ADDR) & 0b11111100) | ((target_val & 0b00000011) << 0)));
  if(MAX77650_getTHM_COLD()==target_val)
   return true;
  else
   return false;
}

//Charger Configuration Register B 0x19
int32_t MAX77650_setVCHGIN_MIN(uint8_t target_val){ //Returns the Minimum CHGIN regulation voltage (VCHGIN-MIN)
  max77658_pm_write_reg(ctx, MAX77650_CNFG_CHG_B_ADDR,((max77658_pm_read_reg(ctx, MAX77650_CNFG_CHG_B_ADDR) & 0b00011111) | ((target_val & 0b00000111) << 5)));
  if(MAX77650_getVCHGIN_MIN()==target_val)
   return true;
  else
   return false;
}
int32_t MAX77650_setICHGIN_LIM(uint8_t target_val){ //Returns the CHGIN Input Current Limit (ICHGIN-LIM)
  max77658_pm_write_reg(ctx, MAX77650_CNFG_CHG_B_ADDR,((max77658_pm_read_reg(ctx, MAX77650_CNFG_CHG_B_ADDR) & 0b11100011) | ((target_val & 0b00000111) << 2)));
  if(MAX77650_getICHGIN_LIM()==target_val)
   return true;
  else
   return false;
}
int32_t MAX77650_setI_PQ(int32_t target_val){ //Returns the prequalification charge current (IPQ) as a percentage of IFAST-CHG
  max77658_pm_write_reg(ctx, MAX77650_CNFG_CHG_B_ADDR,((max77658_pm_read_reg(ctx, MAX77650_CNFG_CHG_B_ADDR) & 0b11111101) | ((target_val & 0b00000001) << 1)));
  if(MAX77650_getI_PQ()==target_val)
   return true;
  else
   return false;
}
int32_t MAX77650_setCHG_EN(int32_t target_val){ //Returns Charger Enable
  max77658_pm_write_reg(ctx, MAX77650_CNFG_CHG_B_ADDR,((max77658_pm_read_reg(ctx, MAX77650_CNFG_CHG_B_ADDR) & 0b11111110) | ((target_val & 0b00000001) << 0)));
  if(MAX77650_getCHG_EN()==target_val)
   return true;
  else
   return false;
}

//Charger Configuration Register C 0x1A
int32_t MAX77650_setCHG_PQ(uint8_t target_val){ //Returns the Battery prequalification voltage threshold (VPQ)
  max77658_pm_write_reg(ctx, MAX77650_CNFG_CHG_C_ADDR,((max77658_pm_read_reg(ctx, MAX77650_CNFG_CHG_C_ADDR) & 0b00011111) | ((target_val & 0b00000111) << 5)));
  if(MAX77650_getCHG_PQ()==target_val)
   return true;
  else
   return false;
}
int32_t MAX77650_setI_TERM(uint8_t target_val){ //Returns the Charger Termination Current (ITERM). I_TERM[1:0] sets the charger termination current as a percentage of the fast charge current IFAST-CHG.
  max77658_pm_write_reg(ctx, MAX77650_CNFG_CHG_C_ADDR,((max77658_pm_read_reg(ctx, MAX77650_CNFG_CHG_C_ADDR) & 0b11100111) | ((target_val & 0b00000011) << 3)));
  if(MAX77650_getI_TERM()==target_val)
   return true;
  else
   return false;
}
int32_t MAX77650_setT_TOPOFF(uint8_t target_val){ //Returns the Topoff timer value (tTO)
  max77658_pm_write_reg(ctx, MAX77650_CNFG_CHG_C_ADDR,((max77658_pm_read_reg(ctx, MAX77650_CNFG_CHG_C_ADDR) & 0b11111000) | ((target_val & 0b00000111) << 0)));
  if(MAX77650_getT_TOPOFF()==target_val)
   return true;
  else
   return false;
}

//Charger Configuration Register D 0x1B
int32_t MAX77650_setTJ_REG(uint8_t target_val){ //Returns the die junction temperature regulation point, TJ-REG
  max77658_pm_write_reg(ctx, MAX77650_CNFG_CHG_D_ADDR,((max77658_pm_read_reg(ctx, MAX77650_CNFG_CHG_D_ADDR) & 0b00011111) | ((target_val & 0b00000111) << 5)));
  if(MAX77650_getTJ_REG()==target_val)
   return true;
  else
   return false;
}
int32_t MAX77650_setVSYS_REG(uint8_t target_val){ //Returns the System voltage regulation (VSYS-REG)
  max77658_pm_write_reg(ctx, MAX77650_CNFG_CHG_D_ADDR,((max77658_pm_read_reg(ctx, MAX77650_CNFG_CHG_D_ADDR) & 0b11100000) | ((target_val & 0b00011111) << 0)));
  if(MAX77650_getVSYS_REG()==target_val)
   return true;
  else
   return false;
}

//Charger Configuration Register E 0x1C
int32_t MAX77650_setCHG_CC(uint8_t target_val){ //Returns the fast-charge constant current value, IFAST-CHG.
  max77658_pm_write_reg(ctx, MAX77650_CNFG_CHG_E_ADDR,((max77658_pm_read_reg(ctx, MAX77650_CNFG_CHG_E_ADDR) & 0b00000011) | ((target_val & 0b00111111) << 2)));
  if(MAX77650_getCHG_CC()==target_val)
   return true;
  else
   return false;
}
int32_t MAX77650_setT_FAST_CHG(uint8_t target_val){ //Returns the fast-charge safety timer, tFC.
  max77658_pm_write_reg(ctx, MAX77650_CNFG_CHG_E_ADDR,((max77658_pm_read_reg(ctx, MAX77650_CNFG_CHG_E_ADDR) & 0b11111100) | ((target_val & 0b00000011) << 0)));
  if(MAX77650_getT_FAST_CHG()==target_val)
   return true;
  else
   return false;
}

//Charger Configuration Register F 0x1D
int32_t MAX77650_setCHG_CC_JEITA(uint8_t target_val){ //Returns the IFAST-CHG_JEITA for when the battery is either cool or warm as defined by the TCOOL and TWARM temperature thresholds. This register is a don't care if the battery temperature is normal.
  max77658_pm_write_reg(ctx, MAX77650_CNFG_CHG_F_ADDR,((max77658_pm_read_reg(ctx, MAX77650_CNFG_CHG_F_ADDR) & 0b00000011) | ((target_val & 0b00111111) << 2)));
  if(MAX77650_getCHG_CC_JEITA()==target_val)
   return true;
  else
   return false;
}
int32_t MAX77650_setTHM_EN(int32_t target_val){ //Returns the Thermistor enable bit
  max77658_pm_write_reg(ctx, MAX77650_CNFG_CHG_F_ADDR,((max77658_pm_read_reg(ctx, MAX77650_CNFG_CHG_F_ADDR) & 0b11111101) | ((target_val & 0b00000001) << 1)));
  if(MAX77650_getTHM_EN()==target_val)
   return true;
  else
   return false;
}

//Charger Configuration Register G 0x1E
int32_t MAX77650_setCHG_CV(uint8_t target_val){ //Returns the fast-charge battery regulation voltage, VFAST-CHG.
  max77658_pm_write_reg(ctx, MAX77650_CNFG_CHG_G_ADDR,((max77658_pm_read_reg(ctx, MAX77650_CNFG_CHG_G_ADDR) & 0b00000011) | ((target_val & 0b00111111) << 2)));
  if(MAX77650_getCHG_CV()==target_val)
   return true;
  else
   return false;
}
int32_t MAX77650_setUSBS(int32_t target_val){ //this bit places CHGIN in USB suspend mode
  max77658_pm_write_reg(ctx, MAX77650_CNFG_CHG_G_ADDR,((max77658_pm_read_reg(ctx, MAX77650_CNFG_CHG_G_ADDR) & 0b11111101) | ((target_val & 0b00000001) << 1)));
  if(MAX77650_getUSBS()==target_val)
   return true;
  else
   return false;
}

//Charger Configuration Register H 0x1F
int32_t MAX77650_setCHG_CV_JEITA(uint8_t target_val){ //Returns the modified VFAST-CHG for when the battery is either cool or warm as defined by the TCOOL and TWARM temperature thresholds. This register is a don't care if the battery temperature is normal.
  max77658_pm_write_reg(ctx, MAX77650_CNFG_CHG_H_ADDR,((max77658_pm_read_reg(ctx, MAX77650_CNFG_CHG_H_ADDR) & 0b00000011) | ((target_val & 0b00111111) << 2)));
  if(MAX77650_getCHG_CV_JEITA()==target_val)
   return true;
  else
   return false;
}

//Charger Configuration Register I 0x20
int32_t MAX77650_setIMON_DISCHG_SCALE(uint8_t target_val){ //Returns the Selects the battery discharge current full-scale current value This 4-bit configuration starts at 7.5mA and ends at 300mA.
  max77658_pm_write_reg(ctx, MAX77650_CNFG_CHG_I_ADDR,((max77658_pm_read_reg(ctx, MAX77650_CNFG_CHG_I_ADDR) & 0b00001111) | ((target_val & 0b00001111) << 4)));
  if(MAX77650_getIMON_DISCHG_SCALE()==target_val)
   return true;
  else
   return false;
}
int32_t MAX77650_setMUX_SEL(uint8_t target_val){ //Returns the analog channel to connect to AMUX configuration
  max77658_pm_write_reg(ctx, MAX77650_CNFG_CHG_I_ADDR,((max77658_pm_read_reg(ctx, MAX77650_CNFG_CHG_I_ADDR) & 0b11110000) | ((target_val & 0b00001111) << 0)));
  if(MAX77650_getMUX_SEL()==target_val)
   return true;
  else
   return false;
}

//SIMO Buck-Boost Global Configuration Register 0x28
int32_t MAX77650_setMRT_OTP(int32_t target_val){ //Returns Manual Reset Time Configuration
  max77658_pm_write_reg(ctx, MAX77650_CNFG_SBB_TOP_ADDR,((max77658_pm_read_reg(ctx, MAX77650_CNFG_SBB_TOP_ADDR) & 0b10111111) | ((target_val & 0b00000001) << 6)));
  if(MAX77650_getMRT_OTP()==target_val)
   return true;
  else
   return false;
}
int32_t MAX77650_setSBIA_LPM_DEF(int32_t target_val){ //Returns Default voltage of the SBIA_LPM bit
  max77658_pm_write_reg(ctx, MAX77650_CNFG_SBB_TOP_ADDR,((max77658_pm_read_reg(ctx, MAX77650_CNFG_SBB_TOP_ADDR) & 0b11011111) | ((target_val & 0b00000001) << 5)));
  if(MAX77650_getSBIA_LPM_DEF()==target_val)
   return true;
  else
   return false;
}
int32_t MAX77650_setDBNC_nEN_DEF(int32_t target_val){ //Returns Default Value of the DBNC_nEN bit
  max77658_pm_write_reg(ctx, MAX77650_CNFG_SBB_TOP_ADDR,((max77658_pm_read_reg(ctx, MAX77650_CNFG_SBB_TOP_ADDR) & 0b11101111) | ((target_val & 0b00000001) << 4)));
  if(MAX77650_getDBNC_nEN_DEF()==target_val)
   return true;
  else
   return false;
}
int32_t MAX77650_setDRV_SBB(uint8_t target_val){ //Returns the SIMO Buck-Boost (all channels) Drive Strength Trim.
  max77658_pm_write_reg(ctx, MAX77650_CNFG_SBB_TOP_ADDR,((max77658_pm_read_reg(ctx, MAX77650_CNFG_SBB_TOP_ADDR) & 0b11111100) | ((target_val & 0b00000011) << 0)));
  if(MAX77650_getDRV_SBB()==target_val)
   return true;
  else
   return false;
}

//SIMO Buck-Boost 0 Configuration Register A 0x29
int32_t MAX77650_setIP_SBB0(uint8_t target_val){ //Returns the SIMO Buck-Boost Channel 0 Peak Current Limit
  max77658_pm_write_reg(ctx, MAX77650_CNFG_SBB0_A_ADDR,((max77658_pm_read_reg(ctx, MAX77650_CNFG_SBB0_A_ADDR) & 0b00111111) | ((target_val & 0b00000011) << 6)));
  if(MAX77650_getIP_SBB0()==target_val)
   return true;
  else
   return false;
}
int32_t MAX77650_setTV_SBB0(uint8_t target_val){ //Returns the SIMO Buck-Boost Channel 0 Target Output Voltage
  max77658_pm_write_reg(ctx, MAX77650_CNFG_SBB0_A_ADDR,((max77658_pm_read_reg(ctx, MAX77650_CNFG_SBB0_A_ADDR) & 0b11000000) | ((target_val & 0b00111111) << 0)));
  if(MAX77650_getTV_SBB0()==target_val)
   return true;
  else
   return false;
}

//SIMO Buck-Boost 0 Configuration Register B 0x2A
int32_t MAX77650_setADE_SBB0(int32_t target_val){ //Returns SIMO Buck-Boost Channel 0 Active-Discharge Enable
  max77658_pm_write_reg(ctx, MAX77650_CNFG_SBB0_B_ADDR,((max77658_pm_read_reg(ctx, MAX77650_CNFG_SBB0_B_ADDR) & 0b11110111) | ((target_val & 0b00000001) << 3)));
  if(MAX77650_getADE_SBB0()==target_val)
   return true;
  else
   return false;
}
int32_t MAX77650_setEN_SBB0(uint8_t target_val){ //Returns the Enable Control for SIMO Buck-Boost Channel 0.
  max77658_pm_write_reg(ctx, MAX77650_CNFG_SBB0_B_ADDR,((max77658_pm_read_reg(ctx, MAX77650_CNFG_SBB0_B_ADDR) & 0b11111000) | ((target_val & 0b00000111) << 0)));
  if(MAX77650_getEN_SBB0()==target_val)
   return true;
  else
   return false;
}

//SIMO Buck-Boost 1 Configuration Register A 0x2B
int32_t MAX77650_setIP_SBB1(uint8_t target_val){ //Returns the SIMO Buck-Boost Channel 1 Peak Current Limit
  max77658_pm_write_reg(ctx, MAX77650_CNFG_SBB1_A_ADDR,((max77658_pm_read_reg(ctx, MAX77650_CNFG_SBB1_A_ADDR) & 0b00111111) | ((target_val & 0b00000011) << 6)));
  if(MAX77650_getIP_SBB1()==target_val)
   return true;
  else
   return false;
}
int32_t MAX77650_setTV_SBB1(uint8_t target_val){ //Returns the SIMO Buck-Boost Channel 1 Target Output Voltage
  max77658_pm_write_reg(ctx, MAX77650_CNFG_SBB1_A_ADDR,((max77658_pm_read_reg(ctx, MAX77650_CNFG_SBB1_A_ADDR) & 0b11000000) | ((target_val & 0b00111111) << 0)));
  if(MAX77650_getTV_SBB1()==target_val)
   return true;
  else
   return false;
}

//SIMO Buck-Boost 1 Configuration Register B 0x2C
int32_t MAX77650_setADE_SBB1(int32_t target_val){ //Returns SIMO Buck-Boost Channel 1 Active-Discharge Enable
  max77658_pm_write_reg(ctx, MAX77650_CNFG_SBB1_B_ADDR,((max77658_pm_read_reg(ctx, MAX77650_CNFG_SBB1_B_ADDR) & 0b11110111) | ((target_val & 0b00000001) << 3)));
  if(MAX77650_getADE_SBB1()==target_val)
   return true;
  else
   return false;
}
int32_t MAX77650_setEN_SBB1(uint8_t target_val){ //Returns the Enable Control for SIMO Buck-Boost Channel 1.
  max77658_pm_write_reg(ctx, MAX77650_CNFG_SBB1_B_ADDR,((max77658_pm_read_reg(ctx, MAX77650_CNFG_SBB1_B_ADDR) & 0b11111000) | ((target_val & 0b00000111) << 0)));
  if(MAX77650_getEN_SBB1()==target_val)
   return true;
  else
   return false;
}

//SIMO Buck-Boost 2 Configuration Register A 0x2D
int32_t MAX77650_setIP_SBB2(uint8_t target_val){ //Returns the SIMO Buck-Boost Channel 2 Peak Current Limit
  max77658_pm_write_reg(ctx, MAX77650_CNFG_SBB2_A_ADDR,((max77658_pm_read_reg(ctx, MAX77650_CNFG_SBB2_A_ADDR) & 0b00111111) | ((target_val & 0b00000011) << 6)));
  if(MAX77650_getIP_SBB2()==target_val)
   return true;
  else
   return false;
}
int32_t MAX77650_setTV_SBB2(uint8_t target_val){ //Returns the SIMO Buck-Boost Channel 2 Target Output Voltage
  max77658_pm_write_reg(ctx, MAX77650_CNFG_SBB2_A_ADDR,((max77658_pm_read_reg(ctx, MAX77650_CNFG_SBB2_A_ADDR) & 0b11000000) | ((target_val & 0b00111111) << 0)));
  if(MAX77650_getTV_SBB2()==target_val)
   return true;
  else
   return false;
}

//SIMO Buck-Boost 2 Configuration Register B 0x2E
int32_t MAX77650_setADE_SBB2(int32_t target_val){ //Returns SIMO Buck-Boost Channel 2 Active-Discharge Enable
  max77658_pm_write_reg(ctx, MAX77650_CNFG_SBB2_B_ADDR,((max77658_pm_read_reg(ctx, MAX77650_CNFG_SBB2_B_ADDR) & 0b11110111) | ((target_val & 0b00000001) << 3)));
  if(MAX77650_getADE_SBB2()==target_val)
   return true;
  else
   return false;
}
int32_t MAX77650_setEN_SBB2(uint8_t target_val){ //Returns the Enable Control for SIMO Buck-Boost Channel 2.
  max77658_pm_write_reg(ctx, MAX77650_CNFG_SBB2_B_ADDR,((max77658_pm_read_reg(ctx, MAX77650_CNFG_SBB2_B_ADDR) & 0b11111000) | ((target_val & 0b00000111) << 0)));
  if(MAX77650_getEN_SBB2()==target_val)
   return true;
  else
   return false;
}

//LED related registers
int32_t MAX77650_setEN_LED_MSTR(int32_t target_val){ //Returns Master LED Enable Bit
  max77658_pm_write_reg(ctx, MAX77650_CNFG_LED_TOP_ADDR,((max77658_pm_read_reg(ctx, MAX77650_CNFG_LED_TOP_ADDR) & 0b11111110) | ((target_val & 0b00000001) << 0)));
  if(MAX77650_getEN_LED_MSTR()==target_val)
   return true;
  else
   return false;
}

//Register LED0
int32_t MAX77650_setLED_FS0(uint8_t target_val){ //Returns LED0 Full Scale Range
  max77658_pm_write_reg(ctx, MAX77650_CNFG_LED0_A_ADDR,((max77658_pm_read_reg(ctx, MAX77650_CNFG_LED0_A_ADDR) & 0b00111111) | ((target_val & 0b00000011) << 6)));
  if(MAX77650_getLED_FS0()==target_val)
   return true;
  else
   return false;
}
int32_t MAX77650_setINV_LED0(int32_t target_val){ //Returns LED0 Invert
  max77658_pm_write_reg(ctx, MAX77650_CNFG_LED0_A_ADDR,((max77658_pm_read_reg(ctx, MAX77650_CNFG_LED0_A_ADDR) & 0b11011111) | ((target_val & 0b00000001) << 5)));
  if(MAX77650_getINV_LED0()==target_val)
   return true;
  else
   return false;
}
int32_t MAX77650_setBRT_LED0(uint8_t target_val){ //Returns LED0 Brightness Control
  max77658_pm_write_reg(ctx, MAX77650_CNFG_LED0_A_ADDR,((max77658_pm_read_reg(ctx, MAX77650_CNFG_LED0_A_ADDR) & 0b11100000) | ((target_val & 0b00011111) << 0)));
  if(MAX77650_getBRT_LED0()==target_val)
   return true;
  else
   return false;
}
int32_t MAX77650_setP_LED0(uint8_t target_val){ //Returns LED0 Period Settings
  max77658_pm_write_reg(ctx, MAX77650_CNFG_LED0_B_ADDR,((max77658_pm_read_reg(ctx, MAX77650_CNFG_LED0_B_ADDR) & 0b00001111) | ((target_val & 0b00001111) << 4)));
  if(MAX77650_getP_LED0()==target_val)
   return true;
  else
   return false;
}
int32_t MAX77650_setD_LED0(uint8_t target_val){ //Returns LED0 On Duty-Cycle Settings
  max77658_pm_write_reg(ctx, MAX77650_CNFG_LED0_B_ADDR,((max77658_pm_read_reg(ctx, MAX77650_CNFG_LED0_B_ADDR) & 0b11110000) | ((target_val & 0b00001111) << 0)));
  if(MAX77650_getD_LED0()==target_val)
   return true;
  else
   return false;
}

//Register LED1
int32_t MAX77650_setLED_FS1(uint8_t target_val){ //Returns LED1 Full Scale Range
  max77658_pm_write_reg(ctx, MAX77650_CNFG_LED1_A_ADDR,((max77658_pm_read_reg(ctx, MAX77650_CNFG_LED1_A_ADDR) & 0b00111111) | ((target_val & 0b00000011) << 6)));
  if(MAX77650_getLED_FS1()==target_val)
   return true;
  else
   return false;
}
int32_t MAX77650_setINV_LED1(int32_t target_val){ //Returns LED1 Invert
  max77658_pm_write_reg(ctx, MAX77650_CNFG_LED1_A_ADDR,((max77658_pm_read_reg(ctx, MAX77650_CNFG_LED1_A_ADDR) & 0b11011111) | ((target_val & 0b00000001) << 5)));
  if(MAX77650_getINV_LED1()==target_val)
   return true;
  else
   return false;
}
int32_t MAX77650_setBRT_LED1(uint8_t target_val){ //Returns LED1 Brightness Control
  max77658_pm_write_reg(ctx, MAX77650_CNFG_LED1_A_ADDR,((max77658_pm_read_reg(ctx, MAX77650_CNFG_LED1_A_ADDR) & 0b11100000) | ((target_val & 0b00011111) << 0)));
  if(MAX77650_getBRT_LED1()==target_val)
   return true;
  else
   return false;
}
int32_t MAX77650_setP_LED1(uint8_t target_val){ //Returns LED1 Period Settings
  max77658_pm_write_reg(ctx, MAX77650_CNFG_LED1_B_ADDR,((max77658_pm_read_reg(ctx, MAX77650_CNFG_LED1_B_ADDR) & 0b00001111) | ((target_val & 0b00001111) << 4)));
  if(MAX77650_getP_LED1()==target_val)
   return true;
  else
   return false;
}
int32_t MAX77650_setD_LED1(uint8_t target_val){ //Returns LED1 On Duty-Cycle Settings
  max77658_pm_write_reg(ctx, MAX77650_CNFG_LED1_B_ADDR,((max77658_pm_read_reg(ctx, MAX77650_CNFG_LED1_B_ADDR) & 0b11110000) | ((target_val & 0b00001111) << 0)));
  if(MAX77650_getD_LED1()==target_val)
   return true;
  else
   return false;
}

//Register LED2
int32_t MAX77650_setLED_FS2(uint8_t target_val){ //Returns LED2 Full Scale Range
  max77658_pm_write_reg(ctx, MAX77650_CNFG_LED2_A_ADDR,((max77658_pm_read_reg(ctx, MAX77650_CNFG_LED2_A_ADDR) & 0b00111111) | ((target_val & 0b00000011) << 6)));
  if(MAX77650_getLED_FS2()==target_val)
   return true;
  else
   return false;
}
int32_t MAX77650_setINV_LED2(int32_t target_val){ //Returns LED2 Invert
  max77658_pm_write_reg(ctx, MAX77650_CNFG_LED2_A_ADDR,((max77658_pm_read_reg(ctx, MAX77650_CNFG_LED2_A_ADDR) & 0b11011111) | ((target_val & 0b00000001) << 5)));
  if(MAX77650_getINV_LED2()==target_val)
   return true;
  else
   return false;
}
int32_t MAX77650_setBRT_LED2(uint8_t target_val){ //Returns LED2 Brightness Control
  max77658_pm_write_reg(ctx, MAX77650_CNFG_LED2_A_ADDR,((max77658_pm_read_reg(ctx, MAX77650_CNFG_LED2_A_ADDR) & 0b11100000) | ((target_val & 0b00011111) << 0)));
  if(MAX77650_getBRT_LED2()==target_val)
   return true;
  else
   return false;
}
int32_t MAX77650_setP_LED2(uint8_t target_val){ //Returns LED2 Period Settings
  max77658_pm_write_reg(ctx, MAX77650_CNFG_LED2_B_ADDR,((max77658_pm_read_reg(ctx, MAX77650_CNFG_LED2_B_ADDR) & 0b00001111) | ((target_val & 0b00001111) << 4)));
  if(MAX77650_getP_LED2()==target_val)
   return true;
  else
   return false;
}
int32_t MAX77650_setD_LED2(uint8_t target_val){ //Returns LED2 On Duty-Cycle Settings
  max77658_pm_write_reg(ctx, MAX77650_CNFG_LED2_B_ADDR,((max77658_pm_read_reg(ctx, MAX77650_CNFG_LED2_B_ADDR) & 0b11110000) | ((target_val & 0b00001111) << 0)));
  if(MAX77650_getD_LED2()==target_val)
   return true;
  else
   return false;
}

//Global Configuration register 0x10
int32_t MAX77650_setBOK(int32_t target_val){ //Returns Main Bias Okay Status Bit
  max77658_pm_write_reg(ctx, MAX77650_CNFG_GLBL_ADDR,((max77658_pm_read_reg(ctx, MAX77650_CNFG_GLBL_ADDR) & 0b10111111) | ((target_val & 0b00000001) << 6)));
  if(MAX77650_getBOK()==target_val)
   return true;
  else
   return false;
}
int32_t MAX77650_setSBIA_LPM(int32_t target_val){ //Returns Main Bias Low-Power Mode software request
  max77658_pm_write_reg(ctx, MAX77650_CNFG_GLBL_ADDR,((max77658_pm_read_reg(ctx, MAX77650_CNFG_GLBL_ADDR) & 0b11011111) | ((target_val & 0b00000001) << 5)));
  if(MAX77650_getSBIA_LPM()==target_val)
   return true;
  else
   return false;
}
int32_t MAX77650_setSBIA_EN(int32_t target_val){ //Returns Main Bias Enable Software Request
  max77658_pm_write_reg(ctx, MAX77650_CNFG_GLBL_ADDR,((max77658_pm_read_reg(ctx, MAX77650_CNFG_GLBL_ADDR) & 0b11101111) | ((target_val & 0b00000001) << 4)));
  if(MAX77650_getSBIA_EN()==target_val)
   return true;
  else
   return false;
}
int32_t MAX77650_setnEN_MODE(int32_t target_val){ //Returns nEN Input (ONKEY) Default Configuration Mode
  max77658_pm_write_reg(ctx, MAX77650_CNFG_GLBL_ADDR,((max77658_pm_read_reg(ctx, MAX77650_CNFG_GLBL_ADDR) & 0b11110111) | ((target_val & 0b00000001) << 3)));
  if(MAX77650_getnEN_MODE()==target_val)
   return true;
  else
   return false;
}
int32_t MAX77650_setDBEN_nEN(int32_t target_val){ //Returns Debounce Timer Enable for the nEN Pin
  max77658_pm_write_reg(ctx, MAX77650_CNFG_GLBL_ADDR,((max77658_pm_read_reg(ctx, MAX77650_CNFG_GLBL_ADDR) & 0b11111011) | ((target_val & 0b00000001) << 2)));
  if(MAX77650_getDBEN_nEN()==target_val)
   return true;
  else
   return false;
}
int32_t MAX77650_setSFT_RST(uint8_t target_val){ //Returns Software Reset Functions.
  max77658_pm_write_reg(ctx, MAX77650_CNFG_GLBL_ADDR,((max77658_pm_read_reg(ctx, MAX77650_CNFG_GLBL_ADDR) & 0b11111100) | ((target_val & 0b00000011) << 0)));
  if(MAX77650_getSFT_RST()==target_val)
   return true;
  else
   return false;
}

//Global Interrupt Mask Register 0x06
int32_t MAX77650_setINT_M_GLBL(uint8_t target_val){ //Sets Global Interrupt Mask Register
  max77658_pm_write_reg(ctx, MAX77650_INTM_GLBL_ADDR,(target_val & 0b01111111));
  if(MAX77650_getINT_M_GLBL()==(target_val & 0b01111111))
   return true;
  else
   return false;
}

//GPIO Configuration Register
int32_t MAX77650_setDBEN_GPI(int32_t target_val){ //Returns General Purpose Input Debounce Timer Enable
  max77658_pm_write_reg(ctx, MAX77650_CNFG_GPIO_ADDR,((max77658_pm_read_reg(ctx, MAX77650_CNFG_GPIO_ADDR) & 0b11101111) | ((target_val & 0b00000001) << 4)));
  if(MAX77650_getDBEN_GPI()==target_val)
   return true;
  else
   return false;
}
int32_t MAX77650_setDO(int32_t target_val){ //Returns General Purpose Output Data Output
  max77658_pm_write_reg(ctx, MAX77650_CNFG_GPIO_ADDR,((max77658_pm_read_reg(ctx, MAX77650_CNFG_GPIO_ADDR) & 0b11110111) | ((target_val & 0b00000001) << 3)));
  if(MAX77650_getDO()==target_val)
   return true;
  else
   return false;
}
int32_t MAX77650_setDRV(int32_t target_val){ //Returns General Purpose Output Driver Type
  max77658_pm_write_reg(ctx, MAX77650_CNFG_GPIO_ADDR,((max77658_pm_read_reg(ctx, MAX77650_CNFG_GPIO_ADDR) & 0b11111011) | ((target_val & 0b00000001) << 2)));
  if(MAX77650_getDRV()==target_val)
   return true;
  else
   return false;
}
int32_t MAX77650_setDI(int32_t target_val){ //Returns GPIO Digital Input Value
  max77658_pm_write_reg(ctx, MAX77650_CNFG_GPIO_ADDR,((max77658_pm_read_reg(ctx, MAX77650_CNFG_GPIO_ADDR) & 0b11111101) | ((target_val & 0b00000001) << 1)));
  if(MAX77650_getDI()==target_val)
   return true;
  else
   return false;
}
int32_t MAX77650_setDIR(int32_t target_val){ //Returns GPIO Direction
  max77658_pm_write_reg(ctx, MAX77650_CNFG_GPIO_ADDR,((max77658_pm_read_reg(ctx, MAX77650_CNFG_GPIO_ADDR) & 0b11111110) | ((target_val & 0b00000001) << 0)));
  if(MAX77650_getDIR()==target_val)
   return true;
  else
   return false;
}

//Charger Interrupt Mask Register 0x07
int32_t MAX77650_setINT_M_CHG(uint8_t target_val){ //Sets Global Interrupt Mask Register
  max77658_pm_write_reg(ctx, MAX77650_INT_M_CHG_ADDR,(target_val & 0b01111111));
  if(MAX77650_getINT_M_CHG()==(target_val & 0b01111111))
   return true;
  else
   return false;
}

