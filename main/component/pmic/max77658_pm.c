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
#define SUCCESS   0
#define ERROR     -1
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
   int32_t ret;
   uint8_t data;

   ret = max77658_pm_read_reg(ctx, MAX77658_PM_STAT_GLBL_ADDR, &data);
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

   ret = max77658_pm_read_reg(ctx, MAX77658_PM_STAT_GLBL_ADDR, &data);
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

   ret = max77658_pm_read_reg(ctx, MAX77658_PM_STAT_GLBL_ADDR, &data);
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

   ret = max77658_pm_read_reg(ctx, MAX77658_PM_STAT_GLBL_ADDR, &data);
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

   ret = max77658_pm_read_reg(ctx, MAX77658_PM_STAT_GLBL_ADDR, &data);
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

   ret = max77658_pm_read_reg(ctx, MAX77658_PM_STAT_GLBL_ADDR, &data);
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

   ret = (max77658_pm_read_reg(ctx, MAX77658_PM_ERCFLAG_ADDR, &data) > 0)?data:(-1);

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

   ret = max77658_pm_read_reg(ctx, MAX77658_PM_CID_ADDR, &data);
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

   ret = max77658_pm_read_reg(ctx, MAX77658_PM_STAT_CHG_A_ADDR, &data);
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

   ret = max77658_pm_read_reg(ctx, MAX77658_PM_STAT_CHG_A_ADDR, &data);
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

   ret = max77658_pm_read_reg(ctx, MAX77658_PM_STAT_CHG_A_ADDR, &data);
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

   ret = max77658_pm_read_reg(ctx, MAX77658_PM_STAT_CHG_A_ADDR, &data);
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

   ret = max77658_pm_read_reg(ctx, MAX77658_PM_STAT_CHG_A_ADDR, &data);
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

   ret = max77658_pm_read_reg(ctx, MAX77658_PM_STAT_CHG_B_ADDR, &data);
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

   ret = max77658_pm_read_reg(ctx, MAX77658_PM_STAT_CHG_B_ADDR, &data);
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

   ret = max77658_pm_read_reg(ctx, MAX77658_PM_STAT_CHG_B_ADDR, &data);
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

   ret = max77658_pm_read_reg(ctx, MAX77658_PM_STAT_CHG_B_ADDR, &data);
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

   ret = max77658_pm_read_reg(ctx, MAX77658_PM_CNFG_LED0_A_ADDR, &data);
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

   ret = max77658_pm_read_reg(ctx, MAX77658_PM_CNFG_LED0_A_ADDR, &data);
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

   ret = max77658_pm_read_reg(ctx, MAX77658_PM_CNFG_LED0_A_ADDR, &data);
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

   ret = max77658_pm_read_reg(ctx, MAX77658_PM_CNFG_LED0_B_ADDR, &data);
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

   ret = max77658_pm_read_reg(ctx, MAX77658_PM_CNFG_LED0_B_ADDR, &data);
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

   ret = max77658_pm_read_reg(ctx, MAX77658_PM_CNFG_LED1_A_ADDR, &data);
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

   ret = max77658_pm_read_reg(ctx, MAX77658_PM_CNFG_LED1_A_ADDR, &data);
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

   ret = max77658_pm_read_reg(ctx, MAX77658_PM_CNFG_LED1_A_ADDR, &data);
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

   ret = max77658_pm_read_reg(ctx, MAX77658_PM_CNFG_LED1_B_ADDR, &data);
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
int32_t max77658_pm_get_D_LED1(max77658_pm_t *ctx)
{
   int32_t ret;
   uint8_t data;

   ret = max77658_pm_read_reg(ctx, MAX77658_PM_CNFG_LED1_B_ADDR, &data);
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

   ret = max77658_pm_read_reg(ctx, MAX77658_PM_CNFG_LED2_A_ADDR, &data);
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

   ret = max77658_pm_read_reg(ctx, MAX77658_PM_CNFG_LED2_A_ADDR, &data);
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

   ret = max77658_pm_read_reg(ctx, MAX77658_PM_CNFG_LED2_A_ADDR, &data);
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

   ret = max77658_pm_read_reg(ctx, MAX77658_PM_CNFG_LED2_B_ADDR, &data);
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

   ret = max77658_pm_read_reg(ctx, MAX77658_PM_CNFG_LED2_B_ADDR, &data);
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

   ret = max77658_pm_read_reg(ctx, MAX77658_PM_CNFG_GLBL_ADDR, &data);
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

   ret = max77658_pm_read_reg(ctx, MAX77658_PM_CNFG_GLBL_ADDR, &data);
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

   ret = max77658_pm_read_reg(ctx, MAX77658_PM_CNFG_GLBL_ADDR, &data);
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

   ret = max77658_pm_read_reg(ctx, MAX77658_PM_CNFG_GLBL_ADDR, &data);
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

   ret = max77658_pm_read_reg(ctx, MAX77658_PM_CNFG_GLBL_ADDR, &data);
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

   ret = max77658_pm_read_reg(ctx, MAX77658_PM_CNFG_GLBL_ADDR, &data);
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
int32_t max77658_pm_get_INT_GLBL(max77658_pm_t *ctx)
{
   int32_t ret;
   uint8_t data;

   ret = max77658_pm_read_reg(ctx, MAX77658_PM_INT_GLBL_ADDR, &data);
   if(ret > 0)
   {
      ret = data;
   }

   return ret;
}

/**
 * @brief  Global Interrupt Mask Register.[get]
 *
 * @param  ctx      read / write interface definitions
 * @retval          Interrupt Status Register 0x00
 *
 */
int32_t max77658_pm_get_INT_M_GLBL(max77658_pm_t *ctx)
{
   int32_t ret;
   uint8_t data;

   ret = max77658_pm_read_reg(ctx, MAX77658_PM_INTM_GLBL_ADDR, &data);
   if(ret > 0)
   {
      ret = (data & 0b01111111);
   }

   return ret;
}

/**
 * @brief  General Purpose Input Debounce Timer Enable.[get]
 *
 * @param  ctx      read / write interface definitions
 * @retval          Interrupt Status Register 0x00
 *
 */
int32_t max77658_pm_get_DBEN_GPI(max77658_pm_t *ctx)
{
   int32_t ret;
   uint8_t data;

   ret = max77658_pm_read_reg(ctx, MAX77658_PM_CNFG_GPIO_ADDR, &data);
   if(ret > 0)
   {
      ret = (data >> 4) & 0b00000001;
   }

   return ret;
}

/**
 * @brief  General Purpose Output Data Output.[get]
 *
 * @param  ctx      read / write interface definitions
 * @retval          -1: I2C error: General Purpose Output Data Output
 *
 */
int32_t max77658_pm_get_DO(max77658_pm_t *ctx)
{
   int32_t ret;
   uint8_t data;

   ret = max77658_pm_read_reg(ctx, MAX77658_PM_CNFG_GPIO_ADDR, &data);
   if(ret > 0)
   {
      ret = (data >> 3) & 0b00000001;
   }

   return ret;
}

/**
 * @brief  General Purpose Output Driver Type.[get]
 *
 * @param  ctx      read / write interface definitions
 * @retval          -1: I2C error: General Purpose Output Driver Type
 *
 */
int32_t max77658_pm_get_DRV(max77658_pm_t *ctx)
{
   int32_t ret;
   uint8_t data;

   ret = max77658_pm_read_reg(ctx, MAX77658_PM_CNFG_GPIO_ADDR, &data);
   if(ret > 0)
   {
      ret = (data >> 2) & 0b00000001;
   }

   return ret;
}

/**
 * @brief  GPIO Digital Input Value.[get]
 *
 * @param  ctx      read / write interface definitions
 * @retval          -1: I2C error: GPIO Digital Input Value
 *
 */
int32_t max77658_pm_get_DI(max77658_pm_t *ctx)
{
   int32_t ret;
   uint8_t data;

   ret = max77658_pm_read_reg(ctx, MAX77658_PM_CNFG_GPIO_ADDR, &data);
   if(ret > 0)
   {
      ret = (data >> 1) & 0b00000001;
   }

   return ret;
}

/**
 * @brief  GPIO Direction.[get]
 *
 * @param  ctx      read / write interface definitions
 * @retval          -1: I2C error: GPIO Direction
 *
 */
int32_t max77658_pm_get_DIR(max77658_pm_t *ctx)
{
   int32_t ret;
   uint8_t data;

   ret = max77658_pm_read_reg(ctx, MAX77658_PM_CNFG_GPIO_ADDR, &data);
   if(ret > 0)
   {
      ret = (data & 0b00000001);
   }

   return ret;
}

//Charger Interrupt Status Register 0x01
/**
 * @brief  Charger Interrupt Status Register 0x01.[get]
 *
 * @param  ctx      read / write interface definitions
 * @retval          -1: I2C error: Charger Interrupt Status Register 0x01
 *
 */
int32_t max77658_pm_get_INT_CHG(max77658_pm_t *ctx)
{
   int32_t ret;
   uint8_t data;

   ret = max77658_pm_read_reg(ctx, MAX77658_PM_INT_CHG_ADDR, &data);
   if(ret > 0)
   {
      ret = data;
   }

   return ret;
}

//Charger Interrupt Mask Register 0x07
/**
 * @brief  Global Interrupt Mask Register.[get]
 *
 * @param  ctx      read / write interface definitions
 * @retval          -1: I2C error: Global Interrupt Mask Register
 *
 */
int32_t max77658_pm_get_INT_M_CHG(max77658_pm_t *ctx)
{
   int32_t ret;
   uint8_t data;

   ret = max77658_pm_read_reg(ctx, MAX77658_PM_INT_M_CHG_ADDR, &data);
   if(ret > 0)
   {
      ret = data & 0b01111111;
   }

   return ret; 
}

//Charger Configuration Register A 0x18
/**
 * @brief  VHOT JEITA Temperature Threshold.[get]
 *
 * @param  ctx      read / write interface definitions
 * @retval          -1: I2C error: VHOT JEITA Temperature Threshold
 *
 */
int32_t max77658_pm_get_THM_HOT(max77658_pm_t *ctx)
{
   int32_t ret;
   uint8_t data;

   ret = max77658_pm_read_reg(ctx, MAX77658_PM_CNFG_CHG_A_ADDR, &data);
   if(ret > 0)
   {
      ret = (data >> 6) & 0b00000011;
   }

   return ret; 
}

/**
 * @brief  VWARM JEITA Temperature Threshold.[get]
 *
 * @param  ctx      read / write interface definitions
 * @retval          -1: I2C error: Global Interrupt Mask Register
 *
 */
int32_t max77658_pm_get_THM_WARM(max77658_pm_t *ctx)
{
   int32_t ret;
   uint8_t data;

   ret = max77658_pm_read_reg(ctx, MAX77658_PM_CNFG_CHG_A_ADDR, &data);
   if(ret > 0)
   {
      ret = (data >> 4) & 0b00000011;
   }

   return ret; 
}

/**
 * @brief  VCOOL JEITA Temperature Threshold.[get]
 *
 * @param  ctx      read / write interface definitions
 * @retval          -1: I2C error: VCOOL JEITA Temperature Threshold
 *
 */
int32_t max77658_pm_get_THM_COOL(max77658_pm_t *ctx)
{
   int32_t ret;
   uint8_t data;

   ret = max77658_pm_read_reg(ctx, MAX77658_PM_CNFG_CHG_A_ADDR, &data);
   if(ret > 0)
   {
      ret = (data >> 2) & 0b00000011;
   }

   return ret; 
}

/**
 * @brief  VCOLD JEITA Temperature Threshold.[get]
 *
 * @param  ctx      read / write interface definitions
 * @retval          -1: I2C error: VCOLD JEITA Temperature Threshold
 *
 */
int32_t max77658_pm_get_THM_COLD(max77658_pm_t *ctx)
{
   int32_t ret;
   uint8_t data;

   ret = max77658_pm_read_reg(ctx, MAX77658_PM_CNFG_CHG_A_ADDR, &data);
   if(ret > 0)
   {
      ret = data & 0b00000011;
   }

   return ret; 
}

//Charger Configuration Register B 0x19
/**
 * @brief  Minimum CHGIN regulation voltage (VCHGIN-MIN).[get]
 *
 * @param  ctx      read / write interface definitions
 * @retval          -1: I2C error: VCHGIN-MIN
 *
 */
int32_t max77658_pm_get_VCHGIN_MIN(max77658_pm_t *ctx)
{
   int32_t ret;
   uint8_t data;

   ret = max77658_pm_read_reg(ctx, MAX77658_PM_CNFG_CHG_B_ADDR, &data);
   if(ret > 0)
   {
      ret = (data >> 5) & 0b00000111;
   }

   return ret; 
}

/**
 * @brief  CHGIN Input Current Limit (ICHGIN-LIM).[get]
 *
 * @param  ctx      read / write interface definitions
 * @retval          -1: I2C error: CHGIN Input Current Limit (ICHGIN-LIM)
 *
 */
int32_t max77658_pm_get_ICHGIN_LIM(max77658_pm_t *ctx)
{
   int32_t ret;
   uint8_t data;

   ret = max77658_pm_read_reg(ctx, MAX77658_PM_CNFG_CHG_B_ADDR, &data);
   if(ret > 0)
   {
      ret = (data >> 2) & 0b00000111;
   }

   return ret; 
}

/**
 * @brief  prequalification charge current (IPQ) as a percentage of IFAST-CHG.[get]
 *
 * @param  ctx      read / write interface definitions
 * @retval          -1: I2C error: percentage of IFAST-CHG
 *
 */
int32_t max77658_pm_get_I_PQ(max77658_pm_t *ctx)
{
   int32_t ret;
   uint8_t data;

   ret = max77658_pm_read_reg(ctx, MAX77658_PM_CNFG_CHG_B_ADDR, &data);
   if(ret > 0)
   {
      ret = (data >> 1) & 0b00000001;
   }

   return ret;
}

/**
 * @brief  Charger Enable.[get]
 *
 * @param  ctx      read / write interface definitions
 * @retval          -1: I2C error: Charger Enable
 *
 */
int32_t max77658_pm_get_CHG_EN(max77658_pm_t *ctx)
{
   int32_t ret;
   uint8_t data;

   ret = max77658_pm_read_reg(ctx, MAX77658_PM_CNFG_CHG_B_ADDR, &data);
   if(ret > 0)
   {
      ret = data & 0b00000001;
   }

   return ret;
}

//Charger Configuration Register C 0x1A
/**
 * @brief  Battery prequalification voltage threshold (VPQ).[get]
 *
 * @param  ctx      read / write interface definitions
 * @retval          -1: I2C error: Battery prequalification voltage threshold (VPQ)
 *
 */
int32_t max77658_pm_get_CHG_PQ(max77658_pm_t *ctx)
{
   int32_t ret;
   uint8_t data;

   ret = max77658_pm_read_reg(ctx, MAX77658_PM_CNFG_CHG_C_ADDR, &data);
   if(ret > 0)
   {
      ret = (data >> 5) & 0b00000111;
   }

   return ret;
}

/**
 * @brief  Charger Termination Current (ITERM). I_TERM[1:0] sets the charger termination current 
 *                      as a percentage of the fast charge current IFAST-CHG.[get]
 *
 * @param  ctx      read / write interface definitions
 * @retval          -1: I2C error: percentage of the fast charge current IFAST-CHG
 *
 */
int32_t max77658_pm_get_I_TERM(max77658_pm_t *ctx)
{
   int32_t ret;
   uint8_t data;

   ret = max77658_pm_read_reg(ctx, MAX77658_PM_CNFG_CHG_C_ADDR, &data);
   if(ret > 0)
   {
      ret = (data >> 3) & 0b00000011;
   }

   return ret;
}

/**
 * @brief  Topoff timer value (tTO).[get]
 *
 * @param  ctx      read / write interface definitions
 * @retval          -1: I2C error. > 0: Topoff timer value (tTO)
 *
 */
int32_t max77658_pm_get_T_TOPOFF(max77658_pm_t *ctx)
{
   int32_t ret;
   uint8_t data;

   ret = max77658_pm_read_reg(ctx, MAX77658_PM_CNFG_CHG_C_ADDR, &data);
   if(ret > 0)
   {
      ret = data & 0b00000111;
   }

   return ret;
}

//Charger Configuration Register D 0x1B
/**
 * @brief  the die junction temperature regulation point, TJ-REG.[get]
 *
 * @param  ctx      read / write interface definitions
 * @retval          -1: I2C error. > 0: the die junction temperature regulation point, TJ-REG
 *
 */
int32_t max77658_pm_get_TJ_REG(max77658_pm_t *ctx)
{
   int32_t ret;
   uint8_t data;

   ret = max77658_pm_read_reg(ctx, MAX77658_PM_CNFG_CHG_D_ADDR, &data);
   if(ret > 0)
   {
      ret = (data >> 5) & 0b00000111;
   }

   return ret;
}

/**
 * @brief  System voltage regulation (VSYS-REG).[get]
 *
 * @param  ctx      read / write interface definitions
 * @retval          -1: I2C error. > 0: System voltage regulation (VSYS-REG)
 *
 */
int32_t max77658_pm_get_VSYS_REG(max77658_pm_t *ctx)
{
   int32_t ret;
   uint8_t data;

   ret = max77658_pm_read_reg(ctx, MAX77658_PM_CNFG_CHG_D_ADDR, &data);
   if(ret > 0)
   {
      ret = data & 0b00011111;
   }

   return ret;
}

//Charger Configuration Register E 0x1C
/**
 * @brief  fast-charge constant current value, IFAST-CHG.[get]
 *
 * @param  ctx      read / write interface definitions
 * @retval          -1: I2C error. > 0: fast-charge constant current value, IFAST-CHG
 *
 */
int32_t max77658_pm_get_CHG_CC(max77658_pm_t *ctx)
{
   int32_t ret;
   uint8_t data;

   ret = max77658_pm_read_reg(ctx, MAX77658_PM_CNFG_CHG_E_ADDR, &data);
   if(ret > 0)
   {
      ret = (data >> 2) & 0b00111111;
   }

   return ret;
}

/**
 * @brief  the fast-charge safety timer, tFC.[get]
 *
 * @param  ctx      read / write interface definitions
 * @retval          -1: I2C error. > 0: the fast-charge safety timer, tFC.
 */
int32_t max77658_pm_get_T_FAST_CHG(max77658_pm_t *ctx)
{
   int32_t ret;
   uint8_t data;

   ret = max77658_pm_read_reg(ctx, MAX77658_PM_CNFG_CHG_E_ADDR, &data);
   if(ret > 0)
   {
      ret = data & 0b00000011;
   }

   return ret;
}

//Charger Configuration Register F 0x1D
/**
 * @brief  Returns the IFAST-CHG_JEITA for when the battery is either cool or warm 
 *     as defined by the TCOOL and TWARM temperature thresholds. 
 *     This register is a don't care if the battery temperature is normal.[get]
 *
 * @param  ctx      read / write interface definitions
 * @retval          -1: I2C error. > 0: 
 */
int32_t max77658_pm_get_CHG_CC_JEITA(max77658_pm_t *ctx)
{
   int32_t ret;
   uint8_t data;

   ret = max77658_pm_read_reg(ctx, MAX77658_PM_CNFG_CHG_F_ADDR, &data);
   if(ret > 0)
   {
      ret = (data >> 2) & 0b00111111;
   }

   return ret;
}

/**
 * @brief  Returns the Thermistor enable bit.[get]
 *
 * @param  ctx      read / write interface definitions
 * @retval          -1: I2C error. > 0: Returns the Thermistor enable bit
 */
int32_t max77658_pm_get_THM_EN(max77658_pm_t *ctx)
{
   int32_t ret;
   uint8_t data;

   ret = max77658_pm_read_reg(ctx, MAX77658_PM_CNFG_CHG_F_ADDR, &data);
   if(ret > 0)
   {
      ret = (data >> 1) & 0b00000001;
   }

   return ret;
}

//Charger Configuration Register G 0x1E
/**
 * @brief  Returns the fast-charge battery regulation voltage, VFAST-CHG.[get]
 *
 * @param  ctx      read / write interface definitions
 * @retval          -1: I2C error. > 0: Returns the fast-charge battery regulation voltage, VFAST-CHG.
 */
int32_t max77658_pm_get_CHG_CV(max77658_pm_t *ctx)
{
   int32_t ret;
   uint8_t data;

   ret = max77658_pm_read_reg(ctx, MAX77658_PM_CNFG_CHG_G_ADDR, &data);
   if(ret > 0)
   {
      ret = (data >> 2) & 0b00111111;
   }

   return ret;
}

/**
 * @brief  this bit places CHGIN in USB suspend mode.[get]
 *
 * @param  ctx      read / write interface definitions
 * @retval          -1: I2C error. > 0: this bit places CHGIN in USB suspend mode
 */
int32_t max77658_pm_get_USBS(max77658_pm_t *ctx)
{
   int32_t ret;
   uint8_t data;

   ret = max77658_pm_read_reg(ctx, MAX77658_PM_CNFG_CHG_G_ADDR, &data);
   if(ret > 0)
   {
      ret = (data >> 1) & 0b00000001;
   }

   return ret;
}

//Charger Configuration Register H 0x1F
/**
 * @brief  Returns the modified VFAST-CHG for when the battery is either 
 *    cool or warm as defined by the TCOOL and TWARM temperature thresholds.
 *    This register is a don't care if the battery temperature is normal.[get]
 *
 * @param  ctx      read / write interface definitions
 * @retval          -1: I2C error. > 0: 
 */
int32_t max77658_pm_get_CHG_CV_JEITA(max77658_pm_t *ctx)
{
   int32_t ret;
   uint8_t data;

   ret = max77658_pm_read_reg(ctx, MAX77658_PM_CNFG_CHG_H_ADDR, &data);
   if(ret > 0)
   {
      ret = (data >> 2) & 0b00111111;
   }

   return ret;
}

//Charger Configuration Register I 0x20
/**
 * @brief  Returns the Selects the battery discharge current
 *       full-scale current value. This 4-bit configuration
 *       starts at 7.5mA and ends at 300mA.[get]
 *
 * @param  ctx      read / write interface definitions
 * @retval          -1: I2C error. > 0: battery discharge current full-scale current value
 */
int32_t max77658_pm_get_IMON_DISCHG_SCALE(max77658_pm_t *ctx)
{
   int32_t ret;
   uint8_t data;

   ret = max77658_pm_read_reg(ctx, MAX77658_PM_CNFG_CHG_I_ADDR, &data);
   if(ret > 0)
   {
      ret = (data >> 4) & 0b00001111;
   }

   return ret;
}

/**
 * @brief  Returns the analog channel to connect to AMUX configuration.[get]
 *
 * @param  ctx      read / write interface definitions
 * @retval          -1: I2C error. > 0: Returns the analog channel to connect to AMUX configuration
 */
int32_t max77658_pm_get_MUX_SEL(max77658_pm_t *ctx)
{
   int32_t ret;
   uint8_t data;

   ret = max77658_pm_read_reg(ctx, MAX77658_PM_CNFG_CHG_I_ADDR, &data);
   if(ret > 0)
   {
      ret = data & 0b00001111;
   }

   return ret;
}

//LDO Configuration Register A 0x38
/**
 * @brief  Returns the LDO Target Output Voltage.[get]
 *
 * @param  ctx      read / write interface definitions
 * @retval          -1: I2C error. > 0: Returns the LDO Target Output Voltage
 */
int32_t max77658_pm_get_TV_LDO(max77658_pm_t *ctx)
{
   int32_t ret;
   uint8_t data;

   ret = max77658_pm_read_reg(ctx, MAX77658_PM_CNFG_LDO_A_ADDR, &data);
   if(ret > 0)
   {
      ret = data & 0b01111111;
   }

   return ret;
}

//LDO Configuration Register B 0x39
/**
 * @brief  Returns LDO active-Discharge Enable.[get]
 *
 * @param  ctx      read / write interface definitions
 * @retval          -1: I2C error. > 0: Returns LDO active-Discharge Enable
 */
int32_t max77658_pm_get_ADE_LDO(max77658_pm_t *ctx)
{
   int32_t ret;
   uint8_t data;

   ret = max77658_pm_read_reg(ctx, MAX77658_PM_CNFG_LDO_B_ADDR, &data);
   if(ret > 0)
   {
      ret = (data >> 3) & 0b00000001;
   }

   return ret;
}

/**
 * @brief  Enable Control for LDO.[get]
 *
 * @param  ctx      read / write interface definitions
 * @retval          -1: I2C error. > 0: Enable Control for LDO.
 */
int32_t max77658_pm_get_EN_LDO(max77658_pm_t *ctx)
{
   int32_t ret;
   uint8_t data;

   ret = max77658_pm_read_reg(ctx, MAX77658_PM_CNFG_LDO_B_ADDR, &data);
   if(ret > 0)
   {
      ret = data & 0b00000111;
   }

   return ret;
}

//SIMO Buck-Boost Global Configuration Register 0x28
/**
 * @brief  Returns Manual Reset Time Configuration.[get]
 *
 * @param  ctx      read / write interface definitions
 * @retval          -1: I2C error. > 0: Returns Manual Reset Time Configuration
 */
int32_t max77658_pm_get_MRT_OTP(max77658_pm_t *ctx)
{
   int32_t ret;
   uint8_t data;

   ret = max77658_pm_read_reg(ctx, MAX77658_PM_CNFG_SBB_TOP_ADDR, &data);
   if(ret > 0)
   {
      ret = (data >> 6) & 0b00000001;
   }

   return ret;
}

/**
 * @brief  Returns Default voltage of the SBIA_LPM bit.[get]
 *
 * @param  ctx      read / write interface definitions
 * @retval          -1: I2C error. > 0: Returns Default voltage of the SBIA_LPM bit
 */
int32_t max77658_pm_get_SBIA_LPM_DEF(max77658_pm_t *ctx)
{
   int32_t ret;
   uint8_t data;

   ret = max77658_pm_read_reg(ctx, MAX77658_PM_CNFG_SBB_TOP_ADDR, &data);
   if(ret > 0)
   {
      ret = (data >> 5) & 0b00000001;
   }

   return ret;
}

/**
 * @brief  Returns Default Value of the DBNC_nEN bit.[get]
 *
 * @param  ctx      read / write interface definitions
 * @retval          -1: I2C error. > 0: Returns Default Value of the DBNC_nEN bit
 */
int32_t max77658_pm_get_DBNC_nEN_DEF(max77658_pm_t *ctx)
{
   int32_t ret;
   uint8_t data;

   ret = max77658_pm_read_reg(ctx, MAX77658_PM_CNFG_SBB_TOP_ADDR, &data);
   if(ret > 0)
   {
      ret = (data >> 4) & 0b00000001;
   }

   return ret;
}

/**
 * @brief  Returns the SIMO Buck-Boost (all channels) Drive Strength Trim.[get]
 *
 * @param  ctx      read / write interface definitions
 * @retval          -1: I2C error. > 0: Returns the SIMO Buck-Boost (all channels) Drive Strength Trim.
 */
int32_t max77658_pm_get_DRV_SBB(max77658_pm_t *ctx)
{
   int32_t ret;
   uint8_t data;

   ret = max77658_pm_read_reg(ctx, MAX77658_PM_CNFG_SBB_TOP_ADDR, &data);
   if(ret > 0)
   {
      ret = data & 0b00000011;
   }

   return ret;
}

//SIMO Buck-Boost 0 Configuration Register A 0x29
/**
 * @brief  Returns the SIMO Buck-Boost Channel 1 Peak Current Limit.[get]
 *
 * @param  ctx      read / write interface definitions
 * @retval          -1: I2C error. > 0: Returns the SIMO Buck-Boost Channel 1 Peak Current Limit
 */
int32_t max77658_pm_get_IP_SBB0(max77658_pm_t *ctx)
{
   int32_t ret;
   uint8_t data;

   ret = max77658_pm_read_reg(ctx, MAX77658_PM_CNFG_SBB0_A_ADDR, &data);
   if(ret > 0)
   {
      ret = (data >> 6) & 0b00000011;
   }

   return ret;
}

/**
 * @brief  Returns the SIMO Buck-Boost Channel 0 Target Output Voltage.[get]
 *
 * @param  ctx      read / write interface definitions
 * @retval          -1: I2C error. > 0: Returns the SIMO Buck-Boost Channel 0 Target Output Voltage
 */
int32_t max77658_pm_get_TV_SBB0(max77658_pm_t *ctx)
{
   int32_t ret;
   uint8_t data;

   ret = max77658_pm_read_reg(ctx, MAX77658_PM_CNFG_SBB0_A_ADDR, &data);
   if(ret > 0)
   {
      ret = data & 0b00111111;
   }

   return ret;
}

//SIMO Buck-Boost 0 Configuration Register B 0x2A
/**
 * @brief  Returns SIMO Buck-Boost Channel 0 Active-Discharge Enable.[get]
 *
 * @param  ctx      read / write interface definitions
 * @retval          -1: I2C error. > 0: Returns SIMO Buck-Boost Channel 0 Active-Discharge Enable
 */
int32_t max77658_pm_get_ADE_SBB0(max77658_pm_t *ctx){ //
   int32_t ret;
   uint8_t data;

   ret = max77658_pm_read_reg(ctx, MAX77658_PM_CNFG_SBB0_B_ADDR, &data);
   if(ret > 0)
   {
      ret = (data >> 3) & 0b00000001;
   }

   return ret;
}

/**
 * @brief  Returns the Enable Control for SIMO Buck-Boost Channel 0.[get]
 *
 * @param  ctx      read / write interface definitions
 * @retval          -1: I2C error. > 0: Returns the Enable Control for SIMO Buck-Boost Channel 0.
 */
int32_t max77658_pm_get_EN_SBB0(max77658_pm_t *ctx)
{
   int32_t ret;
   uint8_t data;

   ret = max77658_pm_read_reg(ctx, MAX77658_PM_CNFG_SBB0_B_ADDR, &data);
   if(ret > 0)
   {
      ret = data & 0b00000111;
   }

   return ret;
}

//SIMO Buck-Boost 1 Configuration Register A 0x2B
/**
 * @brief  Returns the SIMO Buck-Boost Channel 1 Peak Current Limit.[get]
 *
 * @param  ctx      read / write interface definitions
 * @retval          -1: I2C error. > 0: Returns the SIMO Buck-Boost Channel 1 Peak Current Limit
 */
int32_t max77658_pm_get_IP_SBB1(max77658_pm_t *ctx)
{
   int32_t ret;
   uint8_t data;

   ret = max77658_pm_read_reg(ctx, MAX77658_PM_CNFG_SBB1_A_ADDR, &data);
   if(ret > 0)
   {
      ret = (data >> 6) & 0b00000011;
   }

   return ret;
}

/**
 * @brief  Returns the SIMO Buck-Boost Channel 1 Target Output Voltage.[get]
 *
 * @param  ctx      read / write interface definitions
 * @retval          -1: I2C error. > 0: Returns the SIMO Buck-Boost Channel 1 Target Output Voltage
 */
int32_t max77658_pm_get_TV_SBB1(max77658_pm_t *ctx)
{
   int32_t ret;
   uint8_t data;

   ret = max77658_pm_read_reg(ctx, MAX77658_PM_CNFG_SBB1_A_ADDR, &data);
   if(ret > 0)
   {
      ret = data & 0b00111111;
   }

   return ret;
}

//SIMO Buck-Boost 1 Configuration Register B 0x2C
/**
 * @brief  Returns SIMO Buck-Boost Channel 1 Active-Discharge Enable.[get]
 *
 * @param  ctx      read / write interface definitions
 * @retval          -1: I2C error. > 0: Returns SIMO Buck-Boost Channel 1 Active-Discharge Enable
 */
int32_t max77658_pm_get_ADE_SBB1(max77658_pm_t *ctx)
{
   int32_t ret;
   uint8_t data;

   ret = max77658_pm_read_reg(ctx, MAX77658_PM_CNFG_SBB1_B_ADDR, &data);
   if(ret > 0)
   {
      ret = (data >> 3) & 0b00000001;
   }

   return ret;
}

/**
 * @brief  Returns the Enable Control for SIMO Buck-Boost Channel 1.[get]
 *
 * @param  ctx      read / write interface definitions
 * @retval          -1: I2C error. > 0: Returns the Enable Control for SIMO Buck-Boost Channel 1.
 */
int32_t max77658_pm_get_EN_SBB1(max77658_pm_t *ctx)
{
   int32_t ret;
   uint8_t data;

   ret = max77658_pm_read_reg(ctx, MAX77658_PM_CNFG_SBB1_B_ADDR, &data);
   if(ret > 0)
   {
      ret = data & 0b00000111;
   }

   return ret;
}

//SIMO Buck-Boost 2 Configuration Register A 0x2D
/**
 * @brief  Returns the SIMO Buck-Boost Channel 2 Peak Current Limit.[get]
 *
 * @param  ctx      read / write interface definitions
 * @retval          -1: I2C error. > 0: Returns the SIMO Buck-Boost Channel 2 Peak Current Limit
 */
int32_t max77658_pm_get_IP_SBB2(max77658_pm_t *ctx)
{
   int32_t ret;
   uint8_t data;

   ret = max77658_pm_read_reg(ctx, MAX77658_PM_CNFG_SBB2_A_ADDR, &data);
   if(ret > 0)
   {
      ret = (data >> 6) & 0b00000011;
   }

   return ret;
}

/**
 * @brief  Returns the SIMO Buck-Boost Channel 2 Target Output Voltage.[get]
 *
 * @param  ctx      read / write interface definitions
 * @retval          -1: I2C error. > 0: Returns the SIMO Buck-Boost Channel 2 Target Output Voltage
 */
int32_t max77658_pm_get_TV_SBB2(max77658_pm_t *ctx)
{
   int32_t ret;
   uint8_t data;

   ret = max77658_pm_read_reg(ctx, MAX77658_PM_CNFG_SBB2_A_ADDR, &data);
   if(ret > 0)
   {
      ret = data& 0b00111111;
   }

   return ret;
}

//SIMO Buck-Boost 2 Configuration Register B 0x2E
/**
 * @brief  Returns SIMO Buck-Boost Channel 2 Active-Discharge Enable.[get]
 *
 * @param  ctx      read / write interface definitions
 * @retval          -1: I2C error. > 0: Returns SIMO Buck-Boost Channel 2 Active-Discharge Enable
 */
int32_t max77658_pm_get_ADE_SBB2(max77658_pm_t *ctx)
{
   int32_t ret;
   uint8_t data;

   ret = max77658_pm_read_reg(ctx, MAX77658_PM_CNFG_SBB2_B_ADDR, &data);
   if(ret > 0)
   {
      ret = (data >> 3) & 0b00000001;
   }

   return ret;
}

/**
 * @brief  Returns the Enable Control for SIMO Buck-Boost Channel 2.[get]
 *
 * @param  ctx      read / write interface definitions
 * @retval          -1: I2C error. > 0: Returns the Enable Control for SIMO Buck-Boost Channel 2.
 */
int32_t max77658_pm_get_EN_SBB2(max77658_pm_t *ctx)
{
   int32_t ret;
   uint8_t data;

   ret = max77658_pm_read_reg(ctx, MAX77658_PM_CNFG_SBB2_B_ADDR, &data);
   if(ret > 0)
   {
      ret = data & 0b00000111;
   }

   return ret;
}

/**
 * @brief  Returns 64Hz Clock Status.[get]
 *
 * @param  ctx      read / write interface definitions
 * @retval          -1: I2C error. > 0: Returns 64Hz Clock Status
 */
int32_t max77658_pm_get_CLK_64_S(max77658_pm_t *ctx)
{
   int32_t ret;
   uint8_t data;

   ret = max77658_pm_read_reg(ctx, MAX77658_PM_CNFG_LED_TOP_ADDR, &data);
   if(ret > 0)
   {
      ret = (data >> 1) & 0b00000001;
   }

   return ret;
}

/**
 * @brief  Returns Master LED Enable Bit.[get]
 *
 * @param  ctx      read / write interface definitions
 * @retval          -1: I2C error. > 0: Returns Master LED Enable Bit
 */
int32_t max77658_pm_get_EN_LED_MSTR(max77658_pm_t *ctx)
{
   int32_t ret;
   uint8_t data;

   ret = max77658_pm_read_reg(ctx, MAX77658_PM_CNFG_LED_TOP_ADDR, &data);
   if(ret > 0)
   {
      ret = data & 0b00000001;
   }

   return ret;
}


//CID Register
/**
 * @brief  RReturns the OTP programmed Chip Identification Code.[get]
 *
 * @param  ctx      read / write interface definitions
 * @retval          -1: I2C error. > 0: Returns the OTP programmed Chip Identification Code
 */
int32_t max77658_pm_get_CID(max77658_pm_t *ctx)
{
   int32_t ret;
   uint8_t data;

   ret = max77658_pm_read_reg(ctx, MAX77658_PM_CID_ADDR, &data);
   if(ret > 0)
   {
      ret = data & 0b00001111;
   }

   return ret;
}

/*=======================================================================*/
/*********************** Register writes *********************************/
/*=======================================================================*/

/**
 * @brief  Sets the LDO Target Output Voltage.[set]
 *
 * @param  ctx      read / write interface definitions
 * @retval          -1: I2C error. 0: Success
 */
int32_t max77658_pm_set_TV_LDO(max77658_pm_t *ctx, uint8_t target_val)
{
   int32_t ret;
   uint8_t curr_data;
   uint8_t write_data[1];

   ret = max77658_pm_read_reg(ctx, MAX77658_PM_CNFG_LDO_A_ADDR, &curr_data);
   write_data[0] = (curr_data & 0b10000000) | ((target_val & 0b01111111) << 0);
   ret = max77658_pm_write_reg(ctx, MAX77658_PM_CNFG_LDO_A_ADDR, write_data);
   ret = (max77658_pm_get_TV_LDO(ctx) == target_val)?SUCCESS:ERROR;
  
   return ret;
}

//LDO Configuration Register B 0x39
/**
 * @brief  Sets LDO active-Discharge Enable.[set]
 *
 * @param  ctx      read / write interface definitions
 * @retval          -1: I2C error. 0: Success
 */
int32_t max77658_pm_set_ADE_LDO(max77658_pm_t *ctx, uint8_t target_val)
{
   int32_t ret;
   uint8_t curr_data;
   uint8_t write_data[1];

   ret = max77658_pm_read_reg(ctx, MAX77658_PM_CNFG_LDO_B_ADDR, &curr_data);
   write_data[0] = (curr_data & 0b11110111) | ((target_val & 0b00000001) << 3);
   ret = max77658_pm_write_reg(ctx, MAX77658_PM_CNFG_LDO_B_ADDR, write_data);
   ret = (max77658_pm_get_ADE_LDO(ctx) == target_val)?SUCCESS:ERROR;
  
   return ret;
}

/**
 * @brief  Enable LDO.[set]
 *
 * @param  ctx      read / write interface definitions
 * @retval          -1: I2C error. 0: Success
 */
int32_t max77658_pm_set_EN_LDO(max77658_pm_t *ctx, uint8_t target_val)
{
   int32_t ret;
   uint8_t curr_data;
   uint8_t write_data[1];

   ret = max77658_pm_read_reg(ctx, MAX77658_PM_CNFG_LDO_B_ADDR, &curr_data);
   write_data[0] = (curr_data & 0b11111000) | ((target_val & 0b00000111) << 0);
   ret = max77658_pm_write_reg(ctx, MAX77658_PM_CNFG_LDO_B_ADDR, write_data);
   ret = (max77658_pm_get_EN_LDO(ctx) == target_val)?SUCCESS:ERROR;
  
   return ret;
}

//Charger Configuration Register A 0x18
/**
 * @brief  Returns the VHOT JEITA Temperature Threshold.[set]
 *
 * @param  ctx      read / write interface definitions
 * @retval          -1: I2C error. 0: Success
 */
int32_t max77658_pm_set_THM_HOT(max77658_pm_t *ctx, uint8_t target_val)
{
   int32_t ret;
   uint8_t curr_data;
   uint8_t write_data[1];

   ret = max77658_pm_read_reg(ctx, MAX77658_PM_CNFG_CHG_A_ADDR, &curr_data);
   write_data[0] = (curr_data & 0b00111111) | ((target_val & 0b00000011) << 6);
   ret = max77658_pm_write_reg(ctx, MAX77658_PM_CNFG_CHG_A_ADDR, write_data);
   ret = (max77658_pm_get_THM_HOT(ctx) == target_val)?SUCCESS:ERROR;
  
   return ret;
}

/**
 * @brief  Returns the VWARM JEITA Temperature Threshold.[set]
 *
 * @param  ctx      read / write interface definitions
 * @retval          -1: I2C error. 0: Success
 */
int32_t max77658_pm_set_THM_WARM(max77658_pm_t *ctx, uint8_t target_val)
{
   int32_t ret;
   uint8_t curr_data;
   uint8_t write_data[1];

   ret = max77658_pm_read_reg(ctx, MAX77658_PM_CNFG_CHG_A_ADDR, &curr_data);
   write_data[0] = (curr_data & 0b11001111) | ((target_val & 0b00000011) << 4);
   ret = max77658_pm_write_reg(ctx, MAX77658_PM_CNFG_CHG_A_ADDR, write_data);
   ret = (max77658_pm_get_THM_WARM(ctx) == target_val)?SUCCESS:ERROR;
  
   return ret;
}

/**
 * @brief  Returns the VCOOL JEITA Temperature Threshold.[set]
 *
 * @param  ctx      read / write interface definitions
 * @retval          -1: I2C error. 0: Success
 */
int32_t max77658_pm_set_THM_COOL(max77658_pm_t *ctx, uint8_t target_val)
{
   int32_t ret;
   uint8_t curr_data;
   uint8_t write_data[1];

   ret = max77658_pm_read_reg(ctx, MAX77658_PM_CNFG_CHG_A_ADDR, &curr_data);
   write_data[0] = (curr_data & 0b11110011) | ((target_val & 0b00000011) << 2);
   ret = max77658_pm_write_reg(ctx, MAX77658_PM_CNFG_CHG_A_ADDR, write_data);
   ret = (max77658_pm_get_THM_COOL(ctx) == target_val)?SUCCESS:ERROR;
  
   return ret;
}

/**
 * @brief  Returns the VCOLD JEITA Temperature Threshold.[set]
 *
 * @param  ctx      read / write interface definitions
 * @retval          -1: I2C error. 0: Success
 */
int32_t max77658_pm_set_THM_COLD(max77658_pm_t *ctx, uint8_t target_val)
{
   int32_t ret;
   uint8_t curr_data;
   uint8_t write_data[1];

   ret = max77658_pm_read_reg(ctx, MAX77658_PM_CNFG_CHG_A_ADDR, &curr_data);
   write_data[0] = (curr_data & 0b11111100) | ((target_val & 0b00000011) << 0);
   ret = max77658_pm_write_reg(ctx, MAX77658_PM_CNFG_CHG_A_ADDR, write_data);
   ret = (max77658_pm_get_THM_COLD(ctx) == target_val)?SUCCESS:ERROR;
  
   return ret;
}

//Charger Configuration Register B 0x19
/**
 * @brief  Returns the Minimum CHGIN regulation voltage (VCHGIN-MIN).[set]
 *
 * @param  ctx      read / write interface definitions
 * @retval          -1: I2C error. 0: Success
 */
int32_t max77658_pm_set_VCHGIN_MIN(max77658_pm_t *ctx, uint8_t target_val)
{
   int32_t ret;
   uint8_t curr_data;
   uint8_t write_data[1];

   ret = max77658_pm_read_reg(ctx, MAX77658_PM_CNFG_CHG_B_ADDR, &curr_data);
   write_data[0] = (curr_data & 0b00011111) | ((target_val & 0b00000111) << 5);
   ret = max77658_pm_write_reg(ctx, MAX77658_PM_CNFG_CHG_B_ADDR, write_data);
   ret = (max77658_pm_get_VCHGIN_MIN(ctx) == target_val)?SUCCESS:ERROR;
  
   return ret;
}

/**
 * @brief  Returns the CHGIN Input Current Limit (ICHGIN-LIM).[set]
 *
 * @param  ctx      read / write interface definitions
 * @retval          -1: I2C error. 0: Success
 */
int32_t max77658_pm_set_ICHGIN_LIM(max77658_pm_t *ctx, uint8_t target_val)
{
   int32_t ret;
   uint8_t curr_data;
   uint8_t write_data[1];

   ret = max77658_pm_read_reg(ctx, MAX77658_PM_CNFG_CHG_B_ADDR, &curr_data);
   write_data[0] = (curr_data & 0b11100011) | ((target_val & 0b00000111) << 2);
   ret = max77658_pm_write_reg(ctx, MAX77658_PM_CNFG_CHG_B_ADDR, write_data);
   ret = (max77658_pm_get_ICHGIN_LIM(ctx) == target_val)?SUCCESS:ERROR;
  
   return ret;
}

/**
 * @brief  Returns the prequalification charge current (IPQ) as a percentage of IFAST-CHG.[set]
 *
 * @param  ctx      read / write interface definitions
 * @retval          -1: I2C error. 0: Success
 */
int32_t max77658_pm_set_I_PQ(max77658_pm_t *ctx, uint8_t target_val)
{
   int32_t ret;
   uint8_t curr_data;
   uint8_t write_data[1];

   ret = max77658_pm_read_reg(ctx, MAX77658_PM_CNFG_CHG_B_ADDR, &curr_data);
   write_data[0] = (curr_data & 0b11111101) | ((target_val & 0b00000001) << 1);
   ret = max77658_pm_write_reg(ctx, MAX77658_PM_CNFG_CHG_B_ADDR, write_data);
   ret = (max77658_pm_get_I_PQ(ctx) == target_val)?SUCCESS:ERROR;
  
   return ret;
}

/**
 * @brief  Returns Charger Enable.[set]
 *
 * @param  ctx      read / write interface definitions
 * @retval          -1: I2C error. 0: Success
 */
int32_t max77658_pm_set_CHG_EN(max77658_pm_t *ctx, uint8_t target_val)
{
   int32_t ret;
   uint8_t curr_data;
   uint8_t write_data[1];

   ret = max77658_pm_read_reg(ctx, MAX77658_PM_CNFG_CHG_B_ADDR, &curr_data);
   write_data[0] = (curr_data & 0b11111110) | ((target_val & 0b00000001) << 0);
   ret = max77658_pm_write_reg(ctx, MAX77658_PM_CNFG_CHG_B_ADDR, write_data);
   ret = (max77658_pm_get_CHG_EN(ctx) == target_val)?SUCCESS:ERROR;
  
   return ret;
}

//Charger Configuration Register C 0x1A
/**
 * @brief  Returns the Battery prequalification voltage threshold (VPQ).[set]
 *
 * @param  ctx      read / write interface definitions
 * @retval          -1: I2C error. 0: Success
 */
int32_t max77658_pm_set_CHG_PQ(max77658_pm_t *ctx, uint8_t target_val)
{
   int32_t ret;
   uint8_t curr_data;
   uint8_t write_data[1];

   ret = max77658_pm_read_reg(ctx, MAX77658_PM_CNFG_CHG_C_ADDR, &curr_data);
   write_data[0] = (curr_data & 0b00011111) | ((target_val & 0b00000111) << 5);
   ret = max77658_pm_write_reg(ctx, MAX77658_PM_CNFG_CHG_C_ADDR, write_data);
   ret = (max77658_pm_get_CHG_PQ(ctx) == target_val)?SUCCESS:ERROR;
  
   return ret;
}

/**
 * @brief  Returns the Charger Termination Current (ITERM). I_TERM[1:0] sets 
 *             the charger termination current as a percentage of 
 *             the fast charge current IFAST-CHG..[set]
 *
 * @param  ctx      read / write interface definitions
 * @retval          -1: I2C error. 0: Success
 */
int32_t max77658_pm_set_I_TERM(max77658_pm_t *ctx, uint8_t target_val)
{
   int32_t ret;
   uint8_t curr_data;
   uint8_t write_data[1];

   ret = max77658_pm_read_reg(ctx, MAX77658_PM_CNFG_CHG_C_ADDR, &curr_data);
   write_data[0] = (curr_data & 0b11100111) | ((target_val & 0b00000011) << 3);
   ret = max77658_pm_write_reg(ctx, MAX77658_PM_CNFG_CHG_C_ADDR, write_data);
   ret = (max77658_pm_get_I_TERM(ctx) == target_val)?SUCCESS:ERROR;
  
   return ret;
}

/**
 * @brief  Returns the Topoff timer value (tTO).[set]
 *
 * @param  ctx      read / write interface definitions
 * @retval          -1: I2C error. 0: Success
 */
int32_t max77658_pm_set_T_TOPOFF(max77658_pm_t *ctx, uint8_t target_val)
{
   int32_t ret;
   uint8_t curr_data;
   uint8_t write_data[1];

   ret = max77658_pm_read_reg(ctx, MAX77658_PM_CNFG_CHG_C_ADDR, &curr_data);
   write_data[0] = (curr_data & 0b11111000) | ((target_val & 0b00000111) << 0);
   ret = max77658_pm_write_reg(ctx, MAX77658_PM_CNFG_CHG_C_ADDR, write_data);
   ret = (max77658_pm_get_T_TOPOFF(ctx) == target_val)?SUCCESS:ERROR;
  
   return ret;
}

//Charger Configuration Register D 0x1B
/**
 * @brief  Returns the die junction temperature regulation point, TJ-REG.[set]
 *
 * @param  ctx      read / write interface definitions
 * @retval          -1: I2C error. 0: Success
 */
int32_t max77658_pm_set_TJ_REG(max77658_pm_t *ctx, uint8_t target_val)
{
   int32_t ret;
   uint8_t curr_data;
   uint8_t write_data[1];

   ret = max77658_pm_read_reg(ctx, MAX77658_PM_CNFG_CHG_D_ADDR, &curr_data);
   write_data[0] = (curr_data & 0b00011111) | ((target_val & 0b00000111) << 5);
   ret = max77658_pm_write_reg(ctx, MAX77658_PM_CNFG_CHG_D_ADDR, write_data);
   ret = (max77658_pm_get_TJ_REG(ctx) == target_val)?SUCCESS:ERROR;
  
   return ret;
}

/**
 * @brief  Returns the System voltage regulation (VSYS-REG).[set]
 *
 * @param  ctx      read / write interface definitions
 * @retval          -1: I2C error. 0: Success
 */
int32_t max77658_pm_set_VSYS_REG(max77658_pm_t *ctx, uint8_t target_val)
{
   int32_t ret;
   uint8_t curr_data;
   uint8_t write_data[1];

   ret = max77658_pm_read_reg(ctx, MAX77658_PM_CNFG_CHG_D_ADDR, &curr_data);
   write_data[0] = (curr_data & 0b11100000) | ((target_val & 0b00011111) << 0);
   ret = max77658_pm_write_reg(ctx, MAX77658_PM_CNFG_CHG_D_ADDR, write_data);
   ret = (max77658_pm_get_VSYS_REG(ctx) == target_val)?SUCCESS:ERROR;
  
   return ret;
}

//Charger Configuration Register E 0x1C
/**
 * @brief  Returns the fast-charge constant current value, IFAST-CHG.[set]
 *
 * @param  ctx      read / write interface definitions
 * @retval          -1: I2C error. 0: Success
 */
int32_t max77658_pm_set_CHG_CC(max77658_pm_t *ctx, uint8_t target_val)
{
   int32_t ret;
   uint8_t curr_data;
   uint8_t write_data[1];

   ret = max77658_pm_read_reg(ctx, MAX77658_PM_CNFG_CHG_E_ADDR, &curr_data);
   write_data[0] = (curr_data & 0b00000011) | ((target_val & 0b00111111) << 2);
   ret = max77658_pm_write_reg(ctx, MAX77658_PM_CNFG_CHG_E_ADDR, write_data);
   ret = (max77658_pm_get_CHG_CC(ctx) == target_val)?SUCCESS:ERROR;
  
   return ret;
}

/**
 * @brief  Returns the fast-charge safety timer, tFC.[set]
 *
 * @param  ctx      read / write interface definitions
 * @retval          -1: I2C error. 0: Success
 */
int32_t max77658_pm_set_T_FAST_CHG(max77658_pm_t *ctx, uint8_t target_val)
{
   int32_t ret;
   uint8_t curr_data;
   uint8_t write_data[1];

   ret = max77658_pm_read_reg(ctx, MAX77658_PM_CNFG_CHG_E_ADDR, &curr_data);
   write_data[0] = (curr_data & 0b11111100) | ((target_val & 0b00000011) << 0);
   ret = max77658_pm_write_reg(ctx, MAX77658_PM_CNFG_CHG_E_ADDR, write_data);
   ret = (max77658_pm_get_T_FAST_CHG(ctx) == target_val)?SUCCESS:ERROR;
  
   return ret;
}

//Charger Configuration Register F 0x1D
/**
 * @brief  Returns the IFAST-CHG_JEITA for when the battery 
 * is either cool or warm as defined by the TCOOL and TWARM temperature thresholds.
 * This register is a don't care if the battery temperature is normal.[set]
 *
 * @param  ctx      read / write interface definitions
 * @retval          -1: I2C error. 0: Success
 */
int32_t max77658_pm_set_CHG_CC_JEITA(max77658_pm_t *ctx, uint8_t target_val)
{
   int32_t ret;
   uint8_t curr_data;
   uint8_t write_data[1];

   ret = max77658_pm_read_reg(ctx, MAX77658_PM_CNFG_CHG_F_ADDR, &curr_data);
   write_data[0] = (curr_data & 0b00000011) | ((target_val & 0b00111111) << 2);
   ret = max77658_pm_write_reg(ctx, MAX77658_PM_CNFG_CHG_F_ADDR, write_data);
   ret = (max77658_pm_get_CHG_CC_JEITA(ctx) == target_val)?SUCCESS:ERROR;
  
   return ret;
}

/**
 * @brief  Returns the Thermistor enable bit.[set]
 *
 * @param  ctx      read / write interface definitions
 * @retval          -1: I2C error. 0: Success
 */
int32_t max77658_pm_set_THM_EN(max77658_pm_t *ctx, uint8_t target_val)
{
   int32_t ret;
   uint8_t curr_data;
   uint8_t write_data[1];

   ret = max77658_pm_read_reg(ctx, MAX77658_PM_CNFG_CHG_F_ADDR, &curr_data);
   write_data[0] = (curr_data & 0b11111101) | ((target_val & 0b00000001) << 1);
   ret = max77658_pm_write_reg(ctx, MAX77658_PM_CNFG_CHG_F_ADDR, write_data);
   ret = (max77658_pm_get_THM_EN(ctx) == target_val)?SUCCESS:ERROR;
  
   return ret;
}

//Charger Configuration Register G 0x1E
/**
 * @brief  Returns the fast-charge battery regulation voltage, VFAST-CHG.[set]
 *
 * @param  ctx      read / write interface definitions
 * @retval          -1: I2C error. 0: Success
 */
int32_t max77658_pm_set_CHG_CV(max77658_pm_t *ctx, uint8_t target_val)
{
   int32_t ret;
   uint8_t curr_data;
   uint8_t write_data[1];

   ret = max77658_pm_read_reg(ctx, MAX77658_PM_CNFG_CHG_G_ADDR, &curr_data);
   write_data[0] = (curr_data & 0b00000011) | ((target_val & 0b00111111) << 2);
   ret = max77658_pm_write_reg(ctx, MAX77658_PM_CNFG_CHG_G_ADDR, write_data);
   ret = (max77658_pm_get_CHG_CV(ctx) == target_val)?SUCCESS:ERROR;
  
   return ret;
}

/**
 * @brief  this bit places CHGIN in USB suspend mode.[set]
 *
 * @param  ctx      read / write interface definitions
 * @retval          -1: I2C error. 0: Success
 */
int32_t max77658_pm_set_USBS(max77658_pm_t *ctx, uint8_t target_val)
{
   int32_t ret;
   uint8_t curr_data;
   uint8_t write_data[1];

   ret = max77658_pm_read_reg(ctx, MAX77658_PM_CNFG_CHG_G_ADDR, &curr_data);
   write_data[0] = (curr_data & 0b11111101) | ((target_val & 0b00000001) << 1);
   ret = max77658_pm_write_reg(ctx, MAX77658_PM_CNFG_CHG_G_ADDR, write_data);
   ret = (max77658_pm_get_USBS(ctx) == target_val)?SUCCESS:ERROR;
  
   return ret;
}

//Charger Configuration Register H 0x1F
/**
 * @brief  Returns the modified VFAST-CHG for when the battery 
 * is either cool or warm as defined by the TCOOL and TWARM temperature thresholds.
 * This register is a don't care if the battery temperature is normal.[set]
 *
 * @param  ctx      read / write interface definitions
 * @retval          -1: I2C error. 0: Success
 */
int32_t max77658_pm_set_CHG_CV_JEITA(max77658_pm_t *ctx, uint8_t target_val)
{
   int32_t ret;
   uint8_t curr_data;
   uint8_t write_data[1];

   ret = max77658_pm_read_reg(ctx, MAX77658_PM_CNFG_CHG_H_ADDR, &curr_data);
   write_data[0] = (curr_data & 0b00000011) | ((target_val & 0b00111111) << 2);
   ret = max77658_pm_write_reg(ctx, MAX77658_PM_CNFG_CHG_H_ADDR, write_data);
   ret = (max77658_pm_get_CHG_CV_JEITA(ctx) == target_val)?SUCCESS:ERROR;
  
   return ret;
}

//Charger Configuration Register I 0x20
/**
 * @brief  Returns the Selects the battery discharge current full-scale 
 * current value This 4-bit configuration starts at 7.5mA and ends at 300mA.[set]
 *
 * @param  ctx      read / write interface definitions
 * @retval          -1: I2C error. 0: Success
 */
int32_t max77658_pm_set_IMON_DISCHG_SCALE(max77658_pm_t *ctx, uint8_t target_val)
{
   int32_t ret;
   uint8_t curr_data;
   uint8_t write_data[1];

   ret = max77658_pm_read_reg(ctx, MAX77658_PM_CNFG_CHG_I_ADDR, &curr_data);
   write_data[0] = (curr_data & 0b00001111) | ((target_val & 0b00001111) << 4);
   ret = max77658_pm_write_reg(ctx, MAX77658_PM_CNFG_CHG_I_ADDR, write_data);
   ret = (max77658_pm_get_IMON_DISCHG_SCALE(ctx) == target_val)?SUCCESS:ERROR;
  
   return ret;
}

/**
 * @brief  Returns the analog channel to connect to AMUX configuration.[set]
 *
 * @param  ctx      read / write interface definitions
 * @retval          -1: I2C error. 0: Success
 */
int32_t max77658_pm_set_MUX_SEL(max77658_pm_t *ctx, uint8_t target_val)
{
   int32_t ret;
   uint8_t curr_data;
   uint8_t write_data[1];

   ret = max77658_pm_read_reg(ctx, MAX77658_PM_CNFG_CHG_I_ADDR, &curr_data);
   write_data[0] = (curr_data & 0b11110000) | ((target_val & 0b00001111) << 0);
   ret = max77658_pm_write_reg(ctx, MAX77658_PM_CNFG_CHG_I_ADDR, write_data);
   ret = (max77658_pm_get_MUX_SEL(ctx) == target_val)?SUCCESS:ERROR;
  
   return ret;
}

//SIMO Buck-Boost Global Configuration Register 0x28
/**
 * @brief  Returns Manual Reset Time Configuration.[set]
 *
 * @param  ctx      read / write interface definitions
 * @retval          -1: I2C error. 0: Success
 */
int32_t max77658_pm_set_MRT_OTP(max77658_pm_t *ctx, uint8_t target_val)
{
   int32_t ret;
   uint8_t curr_data;
   uint8_t write_data[1];

   ret = max77658_pm_read_reg(ctx, MAX77658_PM_CNFG_SBB_TOP_ADDR, &curr_data);
   write_data[0] = (curr_data & 0b10111111) | ((target_val & 0b00000001) << 6);
   ret = max77658_pm_write_reg(ctx, MAX77658_PM_CNFG_SBB_TOP_ADDR, write_data);
   ret = (max77658_pm_get_MRT_OTP(ctx) == target_val)?SUCCESS:ERROR;
  
   return ret;
}

/**
 * @brief  Returns Default voltage of the SBIA_LPM bit.[set]
 *
 * @param  ctx      read / write interface definitions
 * @retval          -1: I2C error. 0: Success
 */
int32_t max77658_pm_set_SBIA_LPM_DEF(max77658_pm_t *ctx, uint8_t target_val)
{
   int32_t ret;
   uint8_t curr_data;
   uint8_t write_data[1];

   ret = max77658_pm_read_reg(ctx, MAX77658_PM_CNFG_SBB_TOP_ADDR, &curr_data);
   write_data[0] = (curr_data & 0b11011111) | ((target_val & 0b00000001) << 5);
   ret = max77658_pm_write_reg(ctx, MAX77658_PM_CNFG_SBB_TOP_ADDR, write_data);
   ret = (max77658_pm_get_SBIA_LPM_DEF(ctx) == target_val)?SUCCESS:ERROR;
  
   return ret;
}

/**
 * @brief  Returns Default Value of the DBNC_nEN bit.[set]
 *
 * @param  ctx      read / write interface definitions
 * @retval          -1: I2C error. 0: Success
 */
int32_t max77658_pm_set_DBNC_nEN_DEF(max77658_pm_t *ctx, uint8_t target_val){
   int32_t ret;
   uint8_t curr_data;
   uint8_t write_data[1];

   ret = max77658_pm_read_reg(ctx, MAX77658_PM_CNFG_SBB_TOP_ADDR, &curr_data);
   write_data[0] = (curr_data & 0b11101111) | ((target_val & 0b00000001) << 4);
   ret = max77658_pm_write_reg(ctx, MAX77658_PM_CNFG_SBB_TOP_ADDR, write_data);
   ret = (max77658_pm_get_DBNC_nEN_DEF(ctx) == target_val)?SUCCESS:ERROR;
  
   return ret;
}

/**
 * @brief  Returns the SIMO Buck-Boost (all channels) Drive Strength Trim.[set]
 *
 * @param  ctx      read / write interface definitions
 * @retval          -1: I2C error. 0: Success
 */
int32_t max77658_pm_set_DRV_SBB(max77658_pm_t *ctx, uint8_t target_val)
{
   int32_t ret;
   uint8_t curr_data;
   uint8_t write_data[1];

   ret = max77658_pm_read_reg(ctx, MAX77658_PM_CNFG_SBB_TOP_ADDR, &curr_data);
   write_data[0] = (curr_data & 0b11111100) | ((target_val & 0b00000011) << 0);
   ret = max77658_pm_write_reg(ctx, MAX77658_PM_CNFG_SBB_TOP_ADDR, write_data);
   ret = (max77658_pm_get_DRV_SBB(ctx) == target_val)?SUCCESS:ERROR;
  
   return ret;
}

//SIMO Buck-Boost 0 Configuration Register A 0x29
/**
 * @brief  Returns the SIMO Buck-Boost Channel 0 Peak Current Limit.[set]
 *
 * @param  ctx      read / write interface definitions
 * @retval          -1: I2C error. 0: Success
 */
int32_t max77658_pm_set_IP_SBB0(max77658_pm_t *ctx, uint8_t target_val)
{
   int32_t ret;
   uint8_t curr_data;
   uint8_t write_data[1];

   ret = max77658_pm_read_reg(ctx, MAX77658_PM_CNFG_SBB0_A_ADDR, &curr_data);
   write_data[0] = (curr_data & 0b00111111) | ((target_val & 0b00000011) << 6);
   ret = max77658_pm_write_reg(ctx, MAX77658_PM_CNFG_SBB0_A_ADDR, write_data);
   ret = (max77658_pm_get_IP_SBB0(ctx) == target_val)?SUCCESS:ERROR;
  
   return ret;
}

/**
 * @brief  Returns the SIMO Buck-Boost Channel 0 Target Output Voltage.[set]
 *
 * @param  ctx      read / write interface definitions
 * @retval          -1: I2C error. 0: Success
 */
int32_t max77658_pm_set_TV_SBB0(max77658_pm_t *ctx, uint8_t target_val)
{
   int32_t ret;
   uint8_t curr_data;
   uint8_t write_data[1];

   ret = max77658_pm_read_reg(ctx, MAX77658_PM_CNFG_SBB0_A_ADDR, &curr_data);
   write_data[0] = (curr_data & 0b11000000) | ((target_val & 0b00111111) << 0);
   ret = max77658_pm_write_reg(ctx, MAX77658_PM_CNFG_SBB0_A_ADDR, write_data);
   ret = (max77658_pm_get_TV_SBB0(ctx) == target_val)?SUCCESS:ERROR;
  
   return ret;
}

//SIMO Buck-Boost 0 Configuration Register B 0x2A
/**
 * @brief  Returns SIMO Buck-Boost Channel 0 Active-Discharge Enable.[set]
 *
 * @param  ctx      read / write interface definitions
 * @retval          -1: I2C error. 0: Success
 */
int32_t max77658_pm_set_ADE_SBB0(max77658_pm_t *ctx, uint8_t target_val)
{
   int32_t ret;
   uint8_t curr_data;
   uint8_t write_data[1];

   ret = max77658_pm_read_reg(ctx, MAX77658_PM_CNFG_SBB0_B_ADDR, &curr_data);
   write_data[0] = (curr_data & 0b11110111) | ((target_val & 0b00000001) << 3);
   ret = max77658_pm_write_reg(ctx, MAX77658_PM_CNFG_SBB0_B_ADDR, write_data);
   ret = (max77658_pm_get_ADE_SBB0(ctx) == target_val)?SUCCESS:ERROR;
  
   return ret;
}

/**
 * @brief  Returns the Enable Control for SIMO Buck-Boost Channel 0..[set]
 *
 * @param  ctx      read / write interface definitions
 * @retval          -1: I2C error. 0: Success
 */
int32_t max77658_pm_set_EN_SBB0(max77658_pm_t *ctx, uint8_t target_val)
{
   int32_t ret;
   uint8_t curr_data;
   uint8_t write_data[1];

   ret = max77658_pm_read_reg(ctx, MAX77658_PM_CNFG_SBB0_B_ADDR, &curr_data);
   write_data[0] = (curr_data & 0b11111000) | ((target_val & 0b00000111) << 0);
   ret = max77658_pm_write_reg(ctx, MAX77658_PM_CNFG_SBB0_B_ADDR, write_data);
   ret = (max77658_pm_get_EN_SBB0(ctx) == target_val)?SUCCESS:ERROR;
  
   return ret;
}

//SIMO Buck-Boost 1 Configuration Register A 0x2B
/**
 * @brief  Sets the LDO Target Output Voltage.[set]
 *
 * @param  ctx      read / write interface definitions
 * @retval          -1: I2C error. 0: Success
 */
int32_t max77658_pm_set_IP_SBB1(max77658_pm_t *ctx, uint8_t target_val){ //Returns the SIMO Buck-Boost Channel 1 Peak Current Limit
   int32_t ret;
   uint8_t curr_data;
   uint8_t write_data[1];

   ret = max77658_pm_read_reg(ctx, MAX77658_PM_CNFG_SBB1_A_ADDR, &curr_data);
   write_data[0] = (curr_data & 0b00111111) | ((target_val & 0b00000011) << 6);
   ret = max77658_pm_write_reg(ctx, MAX77658_PM_CNFG_SBB1_A_ADDR, write_data);
   ret = (max77658_pm_get_IP_SBB1(ctx) == target_val)?SUCCESS:ERROR;
  
   return ret;
}

/**
 * @brief  Returns the SIMO Buck-Boost Channel 1 Target Output Voltage.[set]
 *
 * @param  ctx      read / write interface definitions
 * @retval          -1: I2C error. 0: Success
 */
int32_t max77658_pm_set_TV_SBB1(max77658_pm_t *ctx, uint8_t target_val)
{
   int32_t ret;
   uint8_t curr_data;
   uint8_t write_data[1];

   ret = max77658_pm_read_reg(ctx, MAX77658_PM_CNFG_SBB1_A_ADDR, &curr_data);
   write_data[0] = (curr_data & 0b00111111) | ((target_val & 0b00000011) << 0);
   ret = max77658_pm_write_reg(ctx, MAX77658_PM_CNFG_SBB1_A_ADDR, write_data);
   ret = (max77658_pm_get_TV_SBB1(ctx) == target_val)?SUCCESS:ERROR;
  
   return ret;
}

//SIMO Buck-Boost 1 Configuration Register B 0x2C
/**
 * @brief  Returns SIMO Buck-Boost Channel 1 Active-Discharge Enable.[set]
 *
 * @param  ctx      read / write interface definitions
 * @retval          -1: I2C error. 0: Success
 */
int32_t max77658_pm_set_ADE_SBB1(max77658_pm_t *ctx, uint8_t target_val)
{
   int32_t ret;
   uint8_t curr_data;
   uint8_t write_data[1];

   ret = max77658_pm_read_reg(ctx, MAX77658_PM_CNFG_SBB1_B_ADDR, &curr_data);
   write_data[0] = (curr_data & 0b11110111) | ((target_val & 0b00000001) << 3);
   ret = max77658_pm_write_reg(ctx, MAX77658_PM_CNFG_SBB1_B_ADDR, write_data);
   ret = (max77658_pm_get_ADE_SBB1(ctx) == target_val)?SUCCESS:ERROR;
  
   return ret;
}

/**
 * @brief  Sets the LDO Target Output Voltage.[set]
 *
 * @param  ctx      read / write interface definitions
 * @retval          -1: I2C error. 0: Success
 */
int32_t max77658_pm_set_EN_SBB1(max77658_pm_t *ctx, uint8_t target_val){ //Returns the Enable Control for SIMO Buck-Boost Channel 1.
   int32_t ret;
   uint8_t curr_data;
   uint8_t write_data[1];

   ret = max77658_pm_read_reg(ctx, MAX77658_PM_CNFG_SBB1_B_ADDR, &curr_data);
   write_data[0] = (curr_data & 0b11111000) | ((target_val & 0b00000111) << 0);
   ret = max77658_pm_write_reg(ctx, MAX77658_PM_CNFG_SBB1_B_ADDR, write_data);
   ret = (max77658_pm_get_EN_SBB1(ctx) == target_val)?SUCCESS:ERROR;
  
   return ret;
}

//SIMO Buck-Boost 2 Configuration Register A 0x2D
/**
 * @brief  Returns the SIMO Buck-Boost Channel 2 Peak Current Limit.[set]
 *
 * @param  ctx      read / write interface definitions
 * @retval          -1: I2C error. 0: Success
 */
int32_t max77658_pm_set_IP_SBB2(max77658_pm_t *ctx, uint8_t target_val)
{
   int32_t ret;
   uint8_t curr_data;
   uint8_t write_data[1];

   ret = max77658_pm_read_reg(ctx, MAX77658_PM_CNFG_SBB2_A_ADDR, &curr_data);
   write_data[0] = (curr_data & 0b00111111) | ((target_val & 0b00000011) << 6);
   ret = max77658_pm_write_reg(ctx, MAX77658_PM_CNFG_SBB2_A_ADDR, write_data);
   ret = (max77658_pm_get_IP_SBB2(ctx) == target_val)?SUCCESS:ERROR;
  
   return ret;
}

/**
 * @brief  Returns the SIMO Buck-Boost Channel 2 Target Output Voltage.[set]
 *
 * @param  ctx      read / write interface definitions
 * @retval          -1: I2C error. 0: Success
 */
int32_t max77658_pm_set_TV_SBB2(max77658_pm_t *ctx, uint8_t target_val)
{
   int32_t ret;
   uint8_t curr_data;
   uint8_t write_data[1];

   ret = max77658_pm_read_reg(ctx, MAX77658_PM_CNFG_SBB2_A_ADDR, &curr_data);
   write_data[0] = (curr_data & 0b11000000) | ((target_val & 0b00111111) << 0);
   ret = max77658_pm_write_reg(ctx, MAX77658_PM_CNFG_SBB2_A_ADDR, write_data);
   ret = (max77658_pm_get_TV_SBB2(ctx) == target_val)?SUCCESS:ERROR;
  
   return ret;
}

//SIMO Buck-Boost 2 Configuration Register B 0x2E
/**
 * @brief  Returns SIMO Buck-Boost Channel 2 Active-Discharge Enable.[set]
 *
 * @param  ctx      read / write interface definitions
 * @retval          -1: I2C error. 0: Success
 */
int32_t max77658_pm_set_ADE_SBB2(max77658_pm_t *ctx, uint8_t target_val)
{
   int32_t ret;
   uint8_t curr_data;
   uint8_t write_data[1];

   ret = max77658_pm_read_reg(ctx, MAX77658_PM_CNFG_SBB2_B_ADDR, &curr_data);
   write_data[0] = (curr_data & 0b11110111) | ((target_val & 0b00000001) << 3);
   ret = max77658_pm_write_reg(ctx, MAX77658_PM_CNFG_SBB2_B_ADDR, write_data);
   ret = (max77658_pm_get_ADE_SBB2(ctx) == target_val)?SUCCESS:ERROR;
  
   return ret;
}

/**
 * @brief  Returns the Enable Control for SIMO Buck-Boost Channel 2.[set]
 *
 * @param  ctx      read / write interface definitions
 * @retval          -1: I2C error. 0: Success
 */
int32_t max77658_pm_set_EN_SBB2(max77658_pm_t *ctx, uint8_t target_val)
{
   int32_t ret;
   uint8_t curr_data;
   uint8_t write_data[1];

   ret = max77658_pm_read_reg(ctx, MAX77658_PM_CNFG_SBB2_B_ADDR, &curr_data);
   write_data[0] = (curr_data & 0b11111000) | ((target_val & 0b00000111) << 0);
   ret = max77658_pm_write_reg(ctx, MAX77658_PM_CNFG_SBB2_B_ADDR, write_data);
   ret = (max77658_pm_get_EN_SBB2(ctx) == target_val)?SUCCESS:ERROR;
  
   return ret;
}

//LED related registers
/**
 * @brief  Returns Master LED Enable Bit.[set]
 *
 * @param  ctx      read / write interface definitions
 * @retval          -1: I2C error. 0: Success
 */
int32_t max77658_pm_set_EN_LED_MSTR(max77658_pm_t *ctx, uint8_t target_val)
{
   int32_t ret;
   uint8_t curr_data;
   uint8_t write_data[1];

   ret = max77658_pm_read_reg(ctx, MAX77658_PM_CNFG_LED_TOP_ADDR, &curr_data);
   write_data[0] = (curr_data & 0b11111110) | ((target_val & 0b00000001) << 0);
   ret = max77658_pm_write_reg(ctx, MAX77658_PM_CNFG_LED_TOP_ADDR, write_data);
   ret = (max77658_pm_get_EN_LED_MSTR(ctx) == target_val)?SUCCESS:ERROR;
  
   return ret;
}

//Register LED0
/**
 * @brief  Returns LED0 Full Scale Range.[set]
 *
 * @param  ctx      read / write interface definitions
 * @retval          -1: I2C error. 0: Success
 */
int32_t max77658_pm_set_LED_FS0(max77658_pm_t *ctx, uint8_t target_val)
{
   int32_t ret;
   uint8_t curr_data;
   uint8_t write_data[1];

   ret = max77658_pm_read_reg(ctx, MAX77658_PM_CNFG_LED0_A_ADDR, &curr_data);
   write_data[0] = (curr_data & 0b00111111) | ((target_val & 0b00000011) << 6);
   ret = max77658_pm_write_reg(ctx, MAX77658_PM_CNFG_LED0_A_ADDR, write_data);
   ret = (max77658_pm_get_LED_FS0(ctx) == target_val)?SUCCESS:ERROR;
  
   return ret;
}

/**
 * @brief  Returns LED0 Invert.[set]
 *
 * @param  ctx      read / write interface definitions
 * @retval          -1: I2C error. 0: Success
 */
int32_t max77658_pm_set_INV_LED0(max77658_pm_t *ctx, uint8_t target_val)
{
   int32_t ret;
   uint8_t curr_data;
   uint8_t write_data[1];

   ret = max77658_pm_read_reg(ctx, MAX77658_PM_CNFG_LED0_A_ADDR, &curr_data);
   write_data[0] = (curr_data & 0b11011111) | ((target_val & 0b00000001) << 5);
   ret = max77658_pm_write_reg(ctx, MAX77658_PM_CNFG_LED0_A_ADDR, write_data);
   ret = (max77658_pm_get_INV_LED0(ctx) == target_val)?SUCCESS:ERROR;
  
   return ret;
}

/**
 * @brief  Returns LED0 Brightness Control.[set]
 *
 * @param  ctx      read / write interface definitions
 * @retval          -1: I2C error. 0: Success
 */
int32_t max77658_pm_set_BRT_LED0(max77658_pm_t *ctx, uint8_t target_val)
{
   int32_t ret;
   uint8_t curr_data;
   uint8_t write_data[1];

   ret = max77658_pm_read_reg(ctx, MAX77658_PM_CNFG_LED0_A_ADDR, &curr_data);
   write_data[0] = (curr_data & 0b11100000) | ((target_val & 0b00011111) << 0);
   ret = max77658_pm_write_reg(ctx, MAX77658_PM_CNFG_LED0_A_ADDR, write_data);
   ret = (max77658_pm_get_BRT_LED0(ctx) == target_val)?SUCCESS:ERROR;
  
   return ret;
}

/**
 * @brief  Returns LED0 Period Settings.[set]
 *
 * @param  ctx      read / write interface definitions
 * @retval          -1: I2C error. 0: Success
 */
int32_t max77658_pm_set_P_LED0(max77658_pm_t *ctx, uint8_t target_val)
{
   int32_t ret;
   uint8_t curr_data;
   uint8_t write_data[1];

   ret = max77658_pm_read_reg(ctx, MAX77658_PM_CNFG_LED0_B_ADDR, &curr_data);
   write_data[0] = (curr_data & 0b00001111) | ((target_val & 0b00001111) << 4);
   ret = max77658_pm_write_reg(ctx, MAX77658_PM_CNFG_LED0_B_ADDR, write_data);
   ret = (max77658_pm_get_P_LED0(ctx) == target_val)?SUCCESS:ERROR;
  
   return ret;
}

/**
 * @brief  Returns LED0 On Duty-Cycle Settings.[set]
 *
 * @param  ctx      read / write interface definitions
 * @retval          -1: I2C error. 0: Success
 */
int32_t max77658_pm_set_D_LED0(max77658_pm_t *ctx, uint8_t target_val)
{
   int32_t ret;
   uint8_t curr_data;
   uint8_t write_data[1];

   ret = max77658_pm_read_reg(ctx, MAX77658_PM_CNFG_LED0_B_ADDR, &curr_data);
   write_data[0] = (curr_data & 0b11110000) | ((target_val & 0b00001111) << 0);
   ret = max77658_pm_write_reg(ctx, MAX77658_PM_CNFG_LED0_B_ADDR, write_data);
   ret = (max77658_pm_get_D_LED0(ctx) == target_val)?SUCCESS:ERROR;
  
   return ret;
}

//Register LED1
/**
 * @brief  Returns LED1 Full Scale Range.[set]
 *
 * @param  ctx      read / write interface definitions
 * @retval          -1: I2C error. 0: Success
 */
int32_t max77658_pm_set_LED_FS1(max77658_pm_t *ctx, uint8_t target_val)
{
   int32_t ret;
   uint8_t curr_data;
   uint8_t write_data[1];

   ret = max77658_pm_read_reg(ctx, MAX77658_PM_CNFG_LED1_A_ADDR, &curr_data);
   write_data[0] = (curr_data & 0b00111111) | ((target_val & 0b00000011) << 6);
   ret = max77658_pm_write_reg(ctx, MAX77658_PM_CNFG_LED1_A_ADDR, write_data);
   ret = (max77658_pm_get_LED_FS1(ctx) == target_val)?SUCCESS:ERROR;
  
   return ret;
}

/**
 * @brief  Returns LED1 Invert.[set]
 *
 * @param  ctx      read / write interface definitions
 * @retval          -1: I2C error. 0: Success
 */
int32_t max77658_pm_set_INV_LED1(max77658_pm_t *ctx, uint8_t target_val)
{
   int32_t ret;
   uint8_t curr_data;
   uint8_t write_data[1];

   ret = max77658_pm_read_reg(ctx, MAX77658_PM_CNFG_LED1_A_ADDR, &curr_data);
   write_data[0] = (curr_data & 0b11011111) | ((target_val & 0b00000001) << 5);
   ret = max77658_pm_write_reg(ctx, MAX77658_PM_CNFG_LED1_A_ADDR, write_data);
   ret = (max77658_pm_get_INV_LED1(ctx) == target_val)?SUCCESS:ERROR;
  
   return ret;
}

/**
 * @brief  Returns LED1 Brightness Control.[set]
 *
 * @param  ctx      read / write interface definitions
 * @retval          -1: I2C error. 0: Success
 */
int32_t max77658_pm_set_BRT_LED1(max77658_pm_t *ctx, uint8_t target_val)
{
   int32_t ret;
   uint8_t curr_data;
   uint8_t write_data[1];

   ret = max77658_pm_read_reg(ctx, MAX77658_PM_CNFG_LED1_A_ADDR, &curr_data);
   write_data[0] = (curr_data & 0b11100000) | ((target_val & 0b00011111) << 0);
   ret = max77658_pm_write_reg(ctx, MAX77658_PM_CNFG_LED1_A_ADDR, write_data);
   ret = (max77658_pm_get_BRT_LED1(ctx) == target_val)?SUCCESS:ERROR;
  
   return ret;
}

/**
 * @brief  Sets the LDO Target Output Voltage.[set]
 *
 * @param  ctx      read / write interface definitions
 * @retval          -1: I2C error. 0: Success
 */
int32_t max77658_pm_set_P_LED1(max77658_pm_t *ctx, uint8_t target_val){ //Returns LED1 Period Settings
   int32_t ret;
   uint8_t curr_data;
   uint8_t write_data[1];

   ret = max77658_pm_read_reg(ctx, MAX77658_PM_CNFG_LED1_B_ADDR, &curr_data);
   write_data[0] = (curr_data & 0b00001111) | ((target_val & 0b00001111) << 4);
   ret = max77658_pm_write_reg(ctx, MAX77658_PM_CNFG_LED1_B_ADDR, write_data);
   ret = (max77658_pm_get_P_LED1(ctx) == target_val)?SUCCESS:ERROR;
  
   return ret;
}

/**
 * @brief  Returns LED1 On Duty-Cycle Settings.[set]
 *
 * @param  ctx      read / write interface definitions
 * @retval          -1: I2C error. 0: Success
 */
int32_t max77658_pm_set_D_LED1(max77658_pm_t *ctx, uint8_t target_val)
{
   int32_t ret;
   uint8_t curr_data;
   uint8_t write_data[1];

   ret = max77658_pm_read_reg(ctx, MAX77658_PM_CNFG_LED1_B_ADDR, &curr_data);
   write_data[0] = (curr_data & 0b11110000) | ((target_val & 0b00001111) << 0);
   ret = max77658_pm_write_reg(ctx, MAX77658_PM_CNFG_LED1_B_ADDR, write_data);
   ret = (max77658_pm_get_D_LED1(ctx) == target_val)?SUCCESS:ERROR;
  
   return ret;
}

//Register LED2
/**
 * @brief  Returns LED2 Full Scale Range.[set]
 *
 * @param  ctx      read / write interface definitions
 * @retval          -1: I2C error. 0: Success
 */
int32_t max77658_pm_set_LED_FS2(max77658_pm_t *ctx, uint8_t target_val)
{
   int32_t ret;
   uint8_t curr_data;
   uint8_t write_data[1];

   ret = max77658_pm_read_reg(ctx, MAX77658_PM_CNFG_LED2_A_ADDR, &curr_data);
   write_data[0] = (curr_data & 0b00111111) | ((target_val & 0b00000011) << 6);
   ret = max77658_pm_write_reg(ctx, MAX77658_PM_CNFG_LED2_A_ADDR, write_data);
   ret = (max77658_pm_get_LED_FS2(ctx) == target_val)?SUCCESS:ERROR;
  
   return ret;
}

/**
 * @brief  Returns LED2 Invert.[set]
 *
 * @param  ctx      read / write interface definitions
 * @retval          -1: I2C error. 0: Success
 */
int32_t max77658_pm_set_INV_LED2(max77658_pm_t *ctx, uint8_t target_val)
{
   int32_t ret;
   uint8_t curr_data;
   uint8_t write_data[1];

   ret = max77658_pm_read_reg(ctx, MAX77658_PM_CNFG_LED2_A_ADDR, &curr_data);
   write_data[0] = (curr_data & 0b11011111) | ((target_val & 0b00000001) << 5);
   ret = max77658_pm_write_reg(ctx, MAX77658_PM_CNFG_LED2_A_ADDR, write_data);
   ret = (max77658_pm_get_INV_LED2(ctx) == target_val)?SUCCESS:ERROR;
  
   return ret;
}

/**
 * @brief  Returns LED2 Brightness Control.[set]
 *
 * @param  ctx      read / write interface definitions
 * @retval          -1: I2C error. 0: Success
 */
int32_t max77658_pm_set_BRT_LED2(max77658_pm_t *ctx, uint8_t target_val)
{
   int32_t ret;
   uint8_t curr_data;
   uint8_t write_data[1];

   ret = max77658_pm_read_reg(ctx, MAX77658_PM_CNFG_LED2_A_ADDR, &curr_data);
   write_data[0] = (curr_data & 0b11100000) | ((target_val & 0b00011111) << 0);
   ret = max77658_pm_write_reg(ctx, MAX77658_PM_CNFG_LED2_A_ADDR, write_data);
   ret = (max77658_pm_get_BRT_LED2(ctx) == target_val)?SUCCESS:ERROR;
  
   return ret;
}

/**
 * @brief  Returns LED2 Period Settings.[set]
 *
 * @param  ctx      read / write interface definitions
 * @retval          -1: I2C error. 0: Success
 */
int32_t max77658_pm_set_P_LED2(max77658_pm_t *ctx, uint8_t target_val)
{
   int32_t ret;
   uint8_t curr_data;
   uint8_t write_data[1];

   ret = max77658_pm_read_reg(ctx, MAX77658_PM_CNFG_LED2_B_ADDR, &curr_data);
   write_data[0] = (curr_data & 0b00001111) | ((target_val & 0b00001111) << 4);
   ret = max77658_pm_write_reg(ctx, MAX77658_PM_CNFG_LED2_B_ADDR, write_data);
   ret = (max77658_pm_get_P_LED2(ctx) == target_val)?SUCCESS:ERROR;
  
   return ret;
}

/**
 * @brief  Returns LED2 On Duty-Cycle Settings.[set]
 *
 * @param  ctx      read / write interface definitions
 * @retval          -1: I2C error. 0: Success
 */
int32_t max77658_pm_set_D_LED2(max77658_pm_t *ctx, uint8_t target_val)
{
   int32_t ret;
   uint8_t curr_data;
   uint8_t write_data[1];

   ret = max77658_pm_read_reg(ctx, MAX77658_PM_CNFG_LED2_B_ADDR, &curr_data);
   write_data[0] = (curr_data & 0b11110000) | ((target_val & 0b00001111) << 0);
   ret = max77658_pm_write_reg(ctx, MAX77658_PM_CNFG_LED2_B_ADDR, write_data);
   ret = (max77658_pm_get_D_LED2(ctx) == target_val)?SUCCESS:ERROR;
  
   return ret;
}

//Global Configuration register 0x10
/**
 * @brief  Returns Main Bias Okay Status Bit.[set]
 *
 * @param  ctx      read / write interface definitions
 * @retval          -1: I2C error. 0: Success
 */
int32_t max77658_pm_set_BOK(max77658_pm_t *ctx, uint8_t target_val)
{
   int32_t ret;
   uint8_t curr_data;
   uint8_t write_data[1];

   ret = max77658_pm_read_reg(ctx, MAX77658_PM_CNFG_GLBL_ADDR, &curr_data);
   write_data[0] = (curr_data & 0b10111111) | ((target_val & 0b00000001) << 6);
   ret = max77658_pm_write_reg(ctx, MAX77658_PM_CNFG_GLBL_ADDR, write_data);
   ret = (max77658_pm_get_BOK(ctx) == target_val)?SUCCESS:ERROR;
  
   return ret;
}

/**
 * @brief  Returns Main Bias Low-Power Mode software request.[set]
 *
 * @param  ctx      read / write interface definitions
 * @retval          -1: I2C error. 0: Success
 */
int32_t max77658_pm_set_SBIA_LPM(max77658_pm_t *ctx, uint8_t target_val)
{
   int32_t ret;
   uint8_t curr_data;
   uint8_t write_data[1];

   ret = max77658_pm_read_reg(ctx, MAX77658_PM_CNFG_GLBL_ADDR, &curr_data);
   write_data[0] = (curr_data & 0b11011111) | ((target_val & 0b00000001) << 5);
   ret = max77658_pm_write_reg(ctx, MAX77658_PM_CNFG_GLBL_ADDR, write_data);
   ret = (max77658_pm_get_SBIA_LPM(ctx) == target_val)?SUCCESS:ERROR;
  
   return ret;
}

/**
 * @brief  Returns Main Bias Enable Software Request.[set]
 *
 * @param  ctx      read / write interface definitions
 * @retval          -1: I2C error. 0: Success
 */
int32_t max77658_pm_set_SBIA_EN(max77658_pm_t *ctx, uint8_t target_val)
{
   int32_t ret;
   uint8_t curr_data;
   uint8_t write_data[1];

   ret = max77658_pm_read_reg(ctx, MAX77658_PM_CNFG_GLBL_ADDR, &curr_data);
   write_data[0] = (curr_data & 0b11101111) | ((target_val & 0b00000001) << 4);
   ret = max77658_pm_write_reg(ctx, MAX77658_PM_CNFG_GLBL_ADDR, write_data);
   ret = (max77658_pm_get_SBIA_EN(ctx) == target_val)?SUCCESS:ERROR;
  
   return ret;
}

/**
 * @brief  Returns nEN Input (ONKEY) Default Configuration Mode.[set]
 *
 * @param  ctx      read / write interface definitions
 * @retval          -1: I2C error. 0: Success
 */
int32_t max77658_pm_set_nEN_MODE(max77658_pm_t *ctx, uint8_t target_val)
{
   int32_t ret;
   uint8_t curr_data;
   uint8_t write_data[1];

   ret = max77658_pm_read_reg(ctx, MAX77658_PM_CNFG_GLBL_ADDR, &curr_data);
   write_data[0] = (curr_data & 0b11110111) | ((target_val & 0b00000001) << 3);
   ret = max77658_pm_write_reg(ctx, MAX77658_PM_CNFG_GLBL_ADDR, write_data);
   ret = (max77658_pm_get_nEN_MODE(ctx) == target_val)?SUCCESS:ERROR;
  
   return ret;
}

/**
 * @brief  Returns Debounce Timer Enable for the nEN Pin.[set]
 *
 * @param  ctx      read / write interface definitions
 * @retval          -1: I2C error. 0: Success
 */
int32_t max77658_pm_set_DBEN_nEN(max77658_pm_t *ctx, uint8_t target_val)
{
   int32_t ret;
   uint8_t curr_data;
   uint8_t write_data[1];

   ret = max77658_pm_read_reg(ctx, MAX77658_PM_CNFG_GLBL_ADDR, &curr_data);
   write_data[0] = (curr_data & 0b11111011) | ((target_val & 0b00000001) << 2);
   ret = max77658_pm_write_reg(ctx, MAX77658_PM_CNFG_GLBL_ADDR, write_data);
   ret = (max77658_pm_get_DBEN_nEN(ctx) == target_val)?SUCCESS:ERROR;
  
   return ret;
}

/**
 * @brief  Returns Software Reset Functions.[set]
 *
 * @param  ctx      read / write interface definitions
 * @retval          -1: I2C error. 0: Success
 */
int32_t max77658_pm_set_SFT_RST(max77658_pm_t *ctx, uint8_t target_val)
{
   int32_t ret;
   uint8_t curr_data;
   uint8_t write_data[1];

   ret = max77658_pm_read_reg(ctx, MAX77658_PM_CNFG_GLBL_ADDR, &curr_data);
   write_data[0] = (curr_data & 0b11111100) | ((target_val & 0b00000011) << 0);
   ret = max77658_pm_write_reg(ctx, MAX77658_PM_CNFG_GLBL_ADDR, write_data);
   ret = (max77658_pm_get_SFT_RST(ctx) == target_val)?SUCCESS:ERROR;
  
   return ret;
}

//Global Interrupt Mask Register 0x06
/**
 * @brief  Sets Global Interrupt Mask Register.[set]
 *
 * @param  ctx      read / write interface definitions
 * @retval          -1: I2C error. 0: Success
 */
int32_t max77658_pm_set_INT_M_GLBL(max77658_pm_t *ctx, uint8_t target_val)
{
   int32_t ret;
   uint8_t write_data[1];

   write_data[0] = target_val & 0b01111111;
   ret = max77658_pm_write_reg(ctx, MAX77658_PM_INTM_GLBL_ADDR, write_data);
   ret = (max77658_pm_get_INT_M_GLBL(ctx) == (target_val & 0b01111111))?SUCCESS:ERROR;
  
   return ret;
}

//GPIO Configuration Register
/**
 * @brief  Returns General Purpose Input Debounce Timer Enable.[set]
 *
 * @param  ctx      read / write interface definitions
 * @retval          -1: I2C error. 0: Success
 */
int32_t max77658_pm_set_DBEN_GPI(max77658_pm_t *ctx, uint8_t target_val)
{
   int32_t ret;
   uint8_t curr_data;
   uint8_t write_data[1];

   ret = max77658_pm_read_reg(ctx, MAX77658_PM_CNFG_GPIO_ADDR, &curr_data);
   write_data[0] = (curr_data & 0b11101111) | ((target_val & 0b00000001) << 4);
   ret = max77658_pm_write_reg(ctx, MAX77658_PM_CNFG_GPIO_ADDR, write_data);
   ret = (max77658_pm_get_DBEN_GPI(ctx) == target_val)?SUCCESS:ERROR;
  
   return ret;
}

/**
 * @brief  Sets the LDO Target Output Voltage.[set]
 *
 * @param  ctx      read / write interface definitions
 * @retval          -1: I2C error. 0: Success
 */
int32_t max77658_pm_set_DO(max77658_pm_t *ctx, uint8_t target_val)
{
   int32_t ret;
   uint8_t curr_data;
   uint8_t write_data[1];

   ret = max77658_pm_read_reg(ctx, MAX77658_PM_CNFG_GPIO_ADDR, &curr_data);
   write_data[0] = (curr_data & 0b11110111) | ((target_val & 0b00000001) << 3);
   ret = max77658_pm_write_reg(ctx, MAX77658_PM_CNFG_GPIO_ADDR, write_data);
   ret = (max77658_pm_get_DO(ctx) == target_val)?SUCCESS:ERROR;
  
   return ret;
}

/**
 * @brief  Returns General Purpose Output Driver Type.[set]
 *
 * @param  ctx      read / write interface definitions
 * @retval          -1: I2C error. 0: Success
 */
int32_t max77658_pm_set_DRV(max77658_pm_t *ctx, uint8_t target_val)
{
   int32_t ret;
   uint8_t curr_data;
   uint8_t write_data[1];

   ret = max77658_pm_read_reg(ctx, MAX77658_PM_CNFG_GPIO_ADDR, &curr_data);
   write_data[0] = (curr_data & 0b11111011) | ((target_val & 0b00000001) << 2);
   ret = max77658_pm_write_reg(ctx, MAX77658_PM_CNFG_GPIO_ADDR, write_data);
   ret = (max77658_pm_get_DRV(ctx) == target_val)?SUCCESS:ERROR;
  
   return ret;
}

/**
 * @brief  Returns GPIO Digital Input Value.[set]
 *
 * @param  ctx      read / write interface definitions
 * @retval          -1: I2C error. 0: Success
 */
int32_t max77658_pm_set_DI(max77658_pm_t *ctx, uint8_t target_val)
{
   int32_t ret;
   uint8_t curr_data;
   uint8_t write_data[1];

   ret = max77658_pm_read_reg(ctx, MAX77658_PM_CNFG_GPIO_ADDR, &curr_data);
   write_data[0] = (curr_data & 0b11111101) | ((target_val & 0b00000001) << 1);
   ret = max77658_pm_write_reg(ctx, MAX77658_PM_CNFG_GPIO_ADDR, write_data);
   ret = (max77658_pm_get_DI(ctx) == target_val)?SUCCESS:ERROR;
  
   return ret;
}

/**
 * @brief  Sets the LDO Target Output Voltage.[set]
 *
 * @param  ctx      read / write interface definitions
 * @retval          -1: I2C error. 0: Success
 */
int32_t max77658_pm_set_DIR(max77658_pm_t *ctx, uint8_t target_val){ //Returns GPIO Direction
   int32_t ret;
   uint8_t curr_data;
   uint8_t write_data[1];

   ret = max77658_pm_read_reg(ctx, MAX77658_PM_CNFG_GPIO_ADDR, &curr_data);
   write_data[0] = (curr_data & 0b11111110) | ((target_val & 0b00000001) << 0);
   ret = max77658_pm_write_reg(ctx, MAX77658_PM_CNFG_GPIO_ADDR, write_data);
   ret = (max77658_pm_get_DIR(ctx) == target_val)?SUCCESS:ERROR;
  
   return ret;
}

//Charger Interrupt Mask Register 0x07
/**
 * @brief  Sets Global Interrupt Mask Register.[set]
 *
 * @param  ctx      read / write interface definitions
 * @retval          -1: I2C error. 0: Success
 */
int32_t max77658_pm_set_INT_M_CHG(max77658_pm_t *ctx, uint8_t target_val)
{
   int32_t ret;
   uint8_t write_data[1];

   write_data[0] = target_val & 0b01111111;
   ret = max77658_pm_write_reg(ctx, MAX77658_PM_INT_M_CHG_ADDR, write_data);
   ret = (max77658_pm_get_INT_M_CHG(ctx) == write_data[0])?SUCCESS:ERROR;
  
   return ret;
}

