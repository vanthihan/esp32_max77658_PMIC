/*
 * max77658_pm.h
 *
 *  Created on: Nov 9, 2021
 *      Author: kai
 */

#ifndef MAIN_COMPONENT_MAX77658_PM_H_
#define MAIN_COMPONENT_MAX77658_PM_H_


/* Includes ----------------------------------------------------------- */
#include <stdio.h>
#include <stdint32_t.h>
#include "max77658_pm_types.h"

/* Public defines ----------------------------------------------------- */
// Project specific definitions *** adapt to your requirements! ***
#define PMIC_partnumber 0x00  //placed PMIC part-numer on the board: MAX77650 or MAX77651
#define MAX77650_CID 0x78     //OTP option
#define MAX77650_ADDR 0x48    //alternate ADDR is 0x40
#ifndef MAX77650_debug
#define MAX77650_debug false
#endif
#ifndef MAX77650_I2C_port
#define MAX77650_I2C_port 2     //I2C port of the host µC
#endif

/* Public enumerate/structure ----------------------------------------- */

/** @addtogroup  Interfaces_Functions
  * @brief       This section provide a set of functions used to read and
  *              write a generic register of the device.
  *              MANDATORY: return 0 -> no Error.
  * @{
  *
  */

typedef int32_t (*pm_read_ptr)(uint8_t, uint8_t, uint8_t*, uint32_t);
typedef int32_t (*pm_write_ptr)(uint8_t, uint8_t, uint8_t*, uint32_t);

typedef struct
{
   uint8_t device_address;
   pm_read_ptr   read_reg;
   pm_write_ptr  write_reg;
} max77658_pm_t;


/**********Status Register (STAT_GLBL) related reads***********/
/**
 * @brief  Returns Part Number.[get]
 */
int32_t max77658_pm_get_DIDM(max77658_pm_t *ctx);

/**
 * @brief  Returns wheather the LDO is in Dropout or not.[get]
 */
int32_t max77658_pm_get_LDO_dropout_detector(max77658_pm_t *ctx);

/**
  * @brief  Returns Thermal Alarm (TJA1 limit).[get]
 */
int32_t max77658_pm_get_thermal_alarm1(max77658_pm_t *ctx);

/**
 * @brief  Therma2 Alarm (TJA2 limit).[get]
 */
int32_t max77658_pm_get_thermal_alarm2(max77658_pm_t *ctx);

/**
 * @brief  Debounced Status of nEN input.[get]
 */
int32_t max77658_pm_get_debounce_Status_nEN0(max77658_pm_t *ctx);

/**
 * @brief  Debounced Status of PWR_HLD input.[get]
 */
int32_t max77658_pm_get_debounce_Status_PWR_HLD(max77658_pm_t *ctx);

/**********************Flag Register (ERCFLAG) related reads****************/
/**
 * @brief  Flag Register (ERCFLAG) related reads.[get]
 */
int32_t max77658_pm_get_ERCFLAG(max77658_pm_t *ctx); //Returns the ERCFLAG Register 0x04

/**********************Register reads related to ChipID**************************/
/**
 * @brief  OTP parts.[get]
 */
int32_t max77658_pm_get_chipID(max77658_pm_t *ctx);

/**********************CID Register*******************************/
/**
 * @brief  OTP parts.[get]
 */
uint8_t MAX77650_getCID(max77658_pm_t *ctx); // Returns the OTP programmed Chip Identification Code

/************Charger Status Register (STAT_CHG_A and B) related reads*********/
/**
 * @brief  Minimum Input Voltage Regulation Loop Status.[get]
 */
int32_t max77658_pm_get_VCHGIN_MIN_STAT(max77658_pm_t *ctx);

/**
 * @brief  Input Current Limit Loop Status.[get]
 */
int32_t max77658_pm_get_ICHGIN_LIM_STAT(max77658_pm_t *ctx);

/**
 * @brief  Minimum System Voltage Regulation Loop Status.[get]
 */
int32_t max77658_pm_get_VSYS_MIN_STAT(max77658_pm_t *ctx);

/**
 * @brief  Maximum Junction Temperature Regulation Loop Status.[get]
 */
int32_t max77658_pm_get_TJ_REG_STAT(max77658_pm_t *ctx);

 /**
  * @brief  Battery Temperature Details.[get]
  */
int32_t max77658_pm_get_THM_DTLS(max77658_pm_t *ctx);

/**
 * @brief  Charger Details.[get]
 */
int32_t max77658_pm_get_CHG_DTLS(max77658_pm_t *ctx);

/**
 * @brief  Charger Input Status Details
 */
uint8_t max77658_pm_get_CHGIN_DTLS(max77658_pm_t *ctx);

/**
 * @brief  Quick Charger Status.[get]
 */
int32_t max77658_pm_get_CHG(max77658_pm_t *ctx);

/**
 * @brief  Time Suspend Indicator.[get]
 */
int32_t max77658_pm_get_TIME_SUS(max77658_pm_t *ctx);

/*********************LED related registers*********************/
/**
 * @brief  LED0 Full Scale Range.[get]
 */
int32_t max77658_pm_get_LED_FS0(max77658_pm_t *ctx);

/**
 * @brief
 */
int32_t MAX77650_getCLK_64_S(max77658_pm_t *ctx); //Returns 64Hz Clock Status

/**
 * @brief
 */
int32_t MAX77650_getEN_LED_MSTR(max77658_pm_t *ctx); //Returns Master LED Enable Bit

/**
 * @brief  LED0 Invert.[get]
 */
int32_t max77658_pm_get_INV_LED0(max77658_pm_t *ctx);

/**
 * @brief  LED0 Brightness Control.[get]
 */
int32_t max77658_pm_get_BRT_LED0(max77658_pm_t *ctx);

/**
 * @brief  LED0 Period Settings.[get]
 */
int32_t max77658_pm_get_P_LED0(max77658_pm_t *ctx);

/**
 * @brief  LED0 On Duty-Cycle Settings.[get]
 */
int32_t max77658_pm_get_D_LED0(max77658_pm_t *ctx);

/**
 * @brief  LED1 Full Scale Range.[get]
 */
int32_t max77658_pm_get_LED_FS1(max77658_pm_t *ctx);

/**
 * @brief  LED1 Invert.[get]
 */
int32_t max77658_pm_get_INV_LED1(max77658_pm_t *ctx);

/**
 * @brief  LED1 Brightness Control.[get]
 */
int32_t max77658_pm_get_BRT_LED1(max77658_pm_t *ctx);

/**
 * @brief  LED1 Period Settings.[get]
 */
int32_t max77658_pm_get_P_LED1(max77658_pm_t *ctx);

/**
 * @brief  LED1 On Duty-Cycle Settings.[get]
 */
int32_t max77658_pm_get_D_LED1(max77658_pm_t *ctx);

/**
 * @brief  LED2 Full Scale Range.[get]
 */
int32_t max77658_pm_get_LED_FS2(max77658_pm_t *ctx);

/**
 * @brief  LED2 Invert.[get]
 */
int32_t max77658_pm_get_INV_LED2(max77658_pm_t *ctx);

/**
 * @brief  LED2 Brightness Control.[get]
 */
int32_t max77658_pm_get_BRT_LED2(max77658_pm_t *ctx);

/**
 * @brief  LED2 Period Settings.[get]
 */
int32_t max77658_pm_get_P_LED2(max77658_pm_t *ctx);

/**
 * @brief  LED2 On Duty-Cycle Settings.[get]
 */
int32_t max77658_pm_get_D_LED2(max77658_pm_t *ctx);

/**********************Global Configuration register 0x10*************************/
/**
 * @brief  Main Bias Okay Status Bit.[get]
 */
int32_t max77658_pm_get_BOK(max77658_pm_t *ctx);

/**
 * @brief  Main Bias Low-Power Mode software request.[get]
 */
int32_t max77658_pm_get_SBIA_LPM(max77658_pm_t *ctx);

/**
 * @brief  Main Bias Enable Software Request.[get]
 */
int32_t max77658_pm_get_SBIA_EN(max77658_pm_t *ctx);

/**
 * @brief  nEN Input (ONKEY) Default Configuration Mode.[get]
 */
int32_t max77658_pm_get_nEN_MODE(max77658_pm_t *ctx);

/**
 * @brief  Debounce Timer Enable for the nEN Pin.[get]
 */
int32_t max77658_pm_get_DBEN_nEN(max77658_pm_t *ctx); //Returns Debounce Timer Enable for the nEN Pin

/**
 * @brief  Software Reset Functions.[get]
 */
int32_t max77658_pm_get_SFT_RST(max77658_pm_t *ctx); //Returns Software Reset Functions.

/*****************Global Interrupt Status Register 0x00*********************/
/**
 * @brief
 */
int32_t max77658_pm_get_INT_GLBL(max77658_pm_t *ctx); //Returns Interrupt Status Register 0x00

/**
 * @brief
 */
//Global Interrupt Mask Register 0x06
uint8_t MAX77650_getINT_M_GLBL(max77658_pm_t *ctx); //Returns Global Interrupt Mask Register

/**
 * @brief
 */
//GPIO Configuration Register
int32_t MAX77650_getDBEN_GPI(max77658_pm_t *ctx); //Returns General Purpose Input Debounce Timer Enable

/**
 * @brief
 */
int32_t MAX77650_getDO(max77658_pm_t *ctx); //Returns General Purpose Output Data Output

/**
 * @brief
 */
int32_t MAX77650_getDRV(max77658_pm_t *ctx); //Returns General Purpose Output Driver Type

/**
 * @brief
 */
int32_t MAX77650_getDI(max77658_pm_t *ctx); //Returns GPIO Digital Input Value

/**
 * @brief
 */
int32_t MAX77650_getDIR(max77658_pm_t *ctx); //Returns GPIO Direction

/**
 * @brief
 */
//Charger Interrupt Status Register 0x01
uint8_t MAX77650_getINT_CHG(max77658_pm_t *ctx); //Returns Charger Interrupt Status Register 0x01

/**
 * @brief
 */
//Charger Interrupt Mask Register 0x07
uint8_t MAX77650_getINT_M_CHG(max77658_pm_t *ctx); //Returns Global Interrupt Mask Register

/**
 * @brief
 */
//Charger Configuration Register A 0x18
uint8_t MAX77650_getTHM_HOT(max77658_pm_t *ctx); //Returns the VHOT JEITA Temperature Threshold

/**
 * @brief
 */
uint8_t MAX77650_getTHM_WARM(max77658_pm_t *ctx); //Returns the VWARM JEITA Temperature Threshold

/**
 * @brief
 */
uint8_t MAX77650_getTHM_COOL(max77658_pm_t *ctx); //Returns the VCOOL JEITA Temperature Threshold

/**
 * @brief
 */
uint8_t MAX77650_getTHM_COLD(max77658_pm_t *ctx); //Returns the VCOLD JEITA Temperature Threshold

/**
 * @brief
 */
//Charger Configuration Register B 0x19
uint8_t MAX77650_getVCHGIN_MIN(max77658_pm_t *ctx); //Returns the Minimum CHGIN regulation voltage (VCHGIN-MIN)

/**
 * @brief
 */
uint8_t MAX77650_getICHGIN_LIM(max77658_pm_t *ctx); //Returns the CHGIN Input Current Limit (ICHGIN-LIM)

/**
 * @brief
 */
int32_t MAX77650_getI_PQ(max77658_pm_t *ctx); //Returns the prequalification charge current (IPQ) as a percentage of IFAST-CHG

/**
 * @brief
 */
int32_t MAX77650_getCHG_EN(max77658_pm_t *ctx); //Returns Charger Enable

/**
 * @brief
 */
//Charger Configuration Register C 0x1A
uint8_t MAX77650_getCHG_PQ(max77658_pm_t *ctx); //Returns the Battery prequalification voltage threshold (VPQ)

/**
 * @brief
 */
uint8_t MAX77650_getI_TERM(max77658_pm_t *ctx); //Returns the Charger Termination Current (ITERM). I_TERM[1:0] sets the charger termination current as a percentage of the fast charge current IFAST-CHG.

/**
 * @brief
 */
uint8_t MAX77650_getT_TOPOFF(max77658_pm_t *ctx); //Returns the Topoff timer value (tTO)

/**
 * @brief
 */
//Charger Configuration Register D 0x1B
uint8_t MAX77650_getTJ_REG(max77658_pm_t *ctx); //Returns the die junction temperature regulation point, TJ-REG

/**
 * @brief
 */
uint8_t MAX77650_getVSYS_REG(max77658_pm_t *ctx); //Returns the System voltage regulation (VSYS-REG)

/**
 * @brief
 */
//Charger Configuration Register E 0x1C
uint8_t MAX77650_getCHG_CC(max77658_pm_t *ctx); //Returns the fast-charge constant current value, IFAST-CHG.

/**
 * @brief
 */
uint8_t MAX77650_getT_FAST_CHG(max77658_pm_t *ctx); //Returns the fast-charge safety timer, tFC.

/**
 * @brief
 */
//Charger Configuration Register F 0x1D

/**
 * @brief
 */
uint8_t MAX77650_getCHG_CC_JEITA(max77658_pm_t *ctx); //Returns the IFAST-CHG_JEITA for when the battery is either cool or warm as defined by the TCOOL and TWARM temperature thresholds. This register is a don't care if the battery temperature is normal.

/**
 * @brief
 */
uint8_t MAX77650_getTHM_EN(max77658_pm_t *ctx); //Returns the Thermistor enable bit

/**
 * @brief
 */
//Charger Configuration Register G 0x1E
uint8_t MAX77650_getCHG_CV(max77658_pm_t *ctx); //Returns the fast-charge battery regulation voltage, VFAST-CHG.

/**
 * @brief
 */
int32_t MAX77650_getUSBS(max77658_pm_t *ctx); //this bit places CHGIN in USB suspend mode

/**
 * @brief
 */
//Charger Configuration Register H 0x1F
uint8_t MAX77650_getCHG_CV_JEITA(max77658_pm_t *ctx); //Returns the modified VFAST-CHG for when the battery is either cool or warm as defined by the TCOOL and TWARM temperature thresholds. This register is a don't care if the battery temperature is normal.

/**
 * @brief
 */
//Charger Configuration Register I 0x20
uint8_t MAX77650_getIMON_DISCHG_SCALE(max77658_pm_t *ctx); //Returns the Selects the battery discharge current full-scale current value This 4-bit configuration starts at 7.5mA and ends at 300mA.

/**
 * @brief
 */
uint8_t MAX77650_getMUX_SEL(max77658_pm_t *ctx); //Returns the analog channel to connect to AMUX configuration

/**
 * @brief
 */
//LDO Configuration Register A 0x38
uint8_t MAX77650_getTV_LDO(max77658_pm_t *ctx); //Returns the LDO Target Output Voltage

/**
 * @brief
 */
//LDO Configuration Register B 0x39
int32_t MAX77650_getADE_LDO(max77658_pm_t *ctx); //Returns LDO active-Discharge Enable

/**
 * @brief
 */
uint8_t MAX77650_getEN_LDO(max77658_pm_t *ctx); //Enable Control for LDO.

/**
 * @brief
 */
//SIMO Buck-Boost Global Configuration Register 0x28
int32_t MAX77650_getMRT_OTP(max77658_pm_t *ctx); //Returns Manual Reset Time Configuration

/**
 * @brief
 */
int32_t MAX77650_getSBIA_LPM_DEF(max77658_pm_t *ctx); //Returns Default voltage of the SBIA_LPM bit

/**
 * @brief
 */
int32_t MAX77650_getDBNC_nEN_DEF(max77658_pm_t *ctx); //Returns Default Value of the DBNC_nEN bit

/**
 * @brief
 */
uint8_t MAX77650_getDRV_SBB(max77658_pm_t *ctx); //Returns the SIMO Buck-Boost (all channels) Drive Strength Trim.

/**
 * @brief
 */
//SIMO Buck-Boost 0 Configuration Register A 0x29
uint8_t MAX77650_getIP_SBB0(max77658_pm_t *ctx); //Returns the SIMO Buck-Boost Channel 0 Peak Current Limit

/**
 * @brief
 */
uint8_t MAX77650_getTV_SBB0(max77658_pm_t *ctx); //Returns the SIMO Buck-Boost Channel 0 Target Output Voltage

/**
 * @brief
 */
//SIMO Buck-Boost 0 Configuration Register B 0x2A
int32_t MAX77650_getADE_SBB0(max77658_pm_t *ctx); //Returns SIMO Buck-Boost Channel 0 Active-Discharge Enable

/**
 * @brief
 */
uint8_t MAX77650_getEN_SBB0(max77658_pm_t *ctx); //Returns the Enable Control for SIMO Buck-Boost Channel 0.

/**
 * @brief
 */
//SIMO Buck-Boost 1 Configuration Register A 0x2B
uint8_t MAX77650_getIP_SBB1(max77658_pm_t *ctx); //Returns the SIMO Buck-Boost Channel 1 Peak Current Limit

/**
 * @brief
 */
uint8_t MAX77650_getTV_SBB1(max77658_pm_t *ctx); //Returns the SIMO Buck-Boost Channel 1 Target Output Voltage


/**
 * @brief
 */
//SIMO Buck-Boost 1 Configuration Register B 0x2C
int32_t MAX77650_getADE_SBB1(max77658_pm_t *ctx); //Returns SIMO Buck-Boost Channel 1 Active-Discharge Enable

/**
 * @brief
 */
uint8_t MAX77650_getEN_SBB1(max77658_pm_t *ctx); //Returns the Enable Control for SIMO Buck-Boost Channel 1.

/**
 * @brief
 */
//SIMO Buck-Boost 2 Configuration Register A 0x2D
uint8_t MAX77650_getIP_SBB2(max77658_pm_t *ctx); //Returns the SIMO Buck-Boost Channel 2 Peak Current Limit

/**
 * @brief
 */
uint8_t MAX77650_getTV_SBB2(max77658_pm_t *ctx); //Returns the SIMO Buck-Boost Channel 2 Target Output Voltage

/**
 * @brief
 */
//SIMO Buck-Boost 2 Configuration Register B 0x2E
int32_t MAX77650_getADE_SBB2(max77658_pm_t *ctx); //Returns SIMO Buck-Boost Channel 2 Active-Discharge Enable

/**
 * @brief
 */
uint8_t MAX77650_getEN_SBB2(max77658_pm_t *ctx); //Returns the Enable Control for SIMO Buck-Boost Channel 2.


/**
 * @brief
 */
//***** Register writes *****

/**
 * @brief
 */
//LDO Configuration Register A 0x38
int32_t MAX77650_setTV_LDO(uint8_t); //Sets the LDO Target Output Voltage


/**
 * @brief
 */
//LDO Configuration Register B 0x39
int32_t MAX77650_setADE_LDO(uint8_t); //Sets LDO active-Discharge Enable

/**
 * @brief
 */
int32_t MAX77650_setEN_LDO(uint8_t); //Enable LDO


/**
 * @brief
 */
//Charger Configuration Register A 0x18
int32_t MAX77650_setTHM_HOT(uint8_t); //Sets the VHOT JEITA Temperature Threshold

/**
 * @brief
 */
int32_t MAX77650_setTHM_WARM(uint8_t); //Sets the VWARM JEITA Temperature Threshold

/**
 * @brief
 */
int32_t MAX77650_setTHM_COOL(uint8_t); //Sets the VCOOL JEITA Temperature Threshold

/**
 * @brief
 */
int32_t MAX77650_setTHM_COLD(uint8_t); //Sets the VCOLD JEITA Temperature Threshold


/**
 * @brief
 */
//Charger Configuration Register B 0x19
int32_t MAX77650_setVCHGIN_MIN(uint8_t); //Sets the Minimum CHGIN regulation voltage (VCHGIN-MIN)

/**
 * @brief
 */
int32_t MAX77650_setICHGIN_LIM(uint8_t); //Sets the CHGIN Input Current Limit (ICHGIN-LIM)

/**
 * @brief
 */
int32_t MAX77650_setI_PQ(int32_t); //Sets the prequalification charge current (IPQ) as a percentage of IFAST-CHG

/**
 * @brief
 */
int32_t MAX77650_setCHG_EN(int32_t); //Sets Charger Enable


/**
 * @brief
 */
//Charger Configuration Register C 0x1A
int32_t MAX77650_setCHG_PQ(uint8_t); //Sets the Battery prequalification voltage threshold (VPQ)


/**
 * @brief
 */
int32_t MAX77650_setI_TERM(uint8_t); //Sets the Charger Termination Current (ITERM). I_TERM[1:0] sets the charger termination current as a percentage of the fast charge current IFAST-CHG.

/**
 * @brief
 */
int32_t MAX77650_setT_TOPOFF(uint8_t); //Sets the Topoff timer value (tTO)


/**
 * @brief
 */
//Charger Configuration Register D 0x1B
int32_t MAX77650_setTJ_REG(uint8_t); //Sets the die junction temperature regulation point, TJ-REG

/**
 * @brief
 */
int32_t MAX77650_setVSYS_REG(uint8_t); //Sets the System voltage regulation (VSYS-REG)


/**
 * @brief
 */
//Charger Configuration Register E 0x1C
int32_t MAX77650_setCHG_CC(uint8_t); //Sets the fast-charge constant current value, IFAST-CHG.

/**
 * @brief
 */
int32_t MAX77650_setT_FAST_CHG(uint8_t); //Sets the fast-charge safety timer, tFC.


/**
 * @brief
 */
//Charger Configuration Register F 0x1D
int32_t MAX77650_setCHG_CC_JEITA(uint8_t); //Sets the IFAST-CHG_JEITA for when the battery is either cool or warm as defined by the TCOOL and TWARM temperature thresholds. This register is a don't care if the battery temperature is normal.

/**
 * @brief
 */
int32_t MAX77650_setTHM_EN(int32_t); //Sets the Thermistor enable bit


/**
 * @brief
 */
//Charger Configuration Register G 0x1E
int32_t MAX77650_setCHG_CV(uint8_t); //Sets the fast-charge battery regulation voltage, VFAST-CHG.

/**
 * @brief
 */
int32_t MAX77650_setUSBS(int32_t); //this bit places CHGIN in USB suspend mode


/**
 * @brief
 */
//Charger Configuration Register H 0x1F
int32_t MAX77650_setCHG_CV_JEITA(uint8_t); //Sets the modified VFAST-CHG for when the battery is either cool or warm as defined by the TCOOL and TWARM temperature thresholds. This register is a don't care if the battery temperature is normal.


/**
 * @brief
 */
//Charger Configuration Register I 0x20
int32_t MAX77650_setIMON_DISCHG_SCALE(uint8_t); //Sets the Selects the battery discharge current full-scale current value This 4-bit configuration starts at 7.5mA and ends at 300mA.

/**
 * @brief
 */
int32_t MAX77650_setMUX_SEL(uint8_t); //Sets the analog channel to connect to AMUX configuration


/**
 * @brief
 */
//SIMO Buck-Boost Global Configuration Register 0x28
int32_t MAX77650_setMRT_OTP(int32_t); //Sets Manual Reset Time Configuration

/**
 * @brief
 */
int32_t MAX77650_setSBIA_LPM_DEF(int32_t); //Sets Default voltage of the SBIA_LPM bit

/**
 * @brief
 */
int32_t MAX77650_setDBNC_nEN_DEF(int32_t); //Sets Default Value of the DBNC_nEN bit

/**
 * @brief
 */
int32_t MAX77650_setDRV_SBB(uint8_t); //Sets the SIMO Buck-Boost (all channels) Drive Strength Trim.


/**
 * @brief
 */
//SIMO Buck-Boost 0 Configuration Register A 0x29
int32_t MAX77650_setIP_SBB0(uint8_t); //Sets the SIMO Buck-Boost Channel 0 Peak Current Limit

/**
 * @brief
 */
int32_t MAX77650_setTV_SBB0(uint8_t); //Sets the SIMO Buck-Boost Channel 0 Target Output Voltage


/**
 * @brief
 */
//SIMO Buck-Boost 0 Configuration Register B 0x2A
int32_t MAX77650_setADE_SBB0(int32_t); //Sets SIMO Buck-Boost Channel 0 Active-Discharge Enable

/**
 * @brief
 */
int32_t MAX77650_setEN_SBB0(uint8_t); //Sets the Enable Control for SIMO Buck-Boost Channel 0.


/**
 * @brief
 */
//SIMO Buck-Boost 1 Configuration Register A 0x2B
int32_t MAX77650_setIP_SBB1(uint8_t); //Sets the SIMO Buck-Boost Channel 1 Peak Current Limit

/**
 * @brief
 */
int32_t MAX77650_setTV_SBB1(uint8_t); //Sets the SIMO Buck-Boost Channel 1 Target Output Voltage


/**
 * @brief
 */
//SIMO Buck-Boost 1 Configuration Register B 0x2C
int32_t MAX77650_setADE_SBB1(int32_t); //Sets SIMO Buck-Boost Channel 1 Active-Discharge Enable

/**
 * @brief
 */
int32_t MAX77650_setEN_SBB1(uint8_t); //Sets the Enable Control for SIMO Buck-Boost Channel 1.


/**
 * @brief
 */
//SIMO Buck-Boost 2 Configuration Register A 0x2D
int32_t MAX77650_setIP_SBB2(uint8_t); //Sets the SIMO Buck-Boost Channel 2 Peak Current Limit

/**
 * @brief
 */
int32_t MAX77650_setTV_SBB2(uint8_t); //Sets the SIMO Buck-Boost Channel 2 Target Output Voltage


/**
 * @brief
 */
//SIMO Buck-Boost 2 Configuration Register B 0x2E
int32_t MAX77650_setADE_SBB2(int32_t); //Sets SIMO Buck-Boost Channel 2 Active-Discharge Enable

/**
 * @brief
 */
int32_t MAX77650_setEN_SBB2(uint8_t); //Sets the Enable Control for SIMO Buck-Boost Channel 2.


/**
 * @brief
 */
//LED related registers
int32_t MAX77650_setEN_LED_MSTR(int32_t); //Sets Master LED Enable Bit

/**
 * @brief
 */
int32_t MAX77650_setLED_FS0(uint8_t); //Sets LED0 Full Scale Range

/**
 * @brief
 */
int32_t MAX77650_setINV_LED0(int32_t); //Sets LED0 Invert

/**
 * @brief
 */
int32_t MAX77650_setBRT_LED0(uint8_t); //Sets LED0 Brightness Control

/**
 * @brief
 */
int32_t MAX77650_setP_LED0(uint8_t); //Sets LED0 Period Settings

/**
 * @brief
 */
int32_t MAX77650_setD_LED0(uint8_t); //Sets LED0 On Duty-Cycle Settings

/**
 * @brief
 */
int32_t MAX77650_setLED_FS1(uint8_t); //Sets LED1 Full Scale Range

/**
 * @brief
 */
int32_t MAX77650_setINV_LED1(int32_t); //Sets LED1 Invert

/**
 * @brief
 */
int32_t MAX77650_setBRT_LED1(uint8_t); //Sets LED1 Brightness Control

/**
 * @brief
 */
int32_t MAX77650_setP_LED1(uint8_t); //Sets LED1 Period Settings

/**
 * @brief
 */
int32_t MAX77650_setD_LED1(uint8_t); //Sets LED1 On Duty-Cycle Settings

/**
 * @brief
 */
int32_t MAX77650_setLED_FS2(uint8_t); //Sets LED2 Full Scale Range

/**
 * @brief
 */
int32_t MAX77650_setINV_LED2(int32_t); //Sets LED2 Invert

/**
 * @brief
 */
int32_t MAX77650_setBRT_LED2(uint8_t); //Sets LED2 Brightness Control

/**
 * @brief
 */
int32_t MAX77650_setP_LED2(uint8_t); //Sets LED2 Period Settings

/**
 * @brief
 */
int32_t MAX77650_setD_LED2(uint8_t); //Sets LED2 On Duty-Cycle Settings

/**
 * @brief
 */
//Global Configuration register 0x10
int32_t MAX77650_setBOK(int32_t); //Sets Main Bias Okay Status Bit

/**
 * @brief
 */
int32_t MAX77650_setSBIA_LPM(int32_t); //Sets Main Bias Low-Power Mode software request

/**
 * @brief
 */
int32_t MAX77650_setSBIA_EN(int32_t); //Sets Main Bias Enable Software Request

/**
 * @brief
 */
int32_t MAX77650_setnEN_MODE(int32_t); //Sets nEN Input (ONKEY) Default Configuration Mode

/**
 * @brief
 */
int32_t MAX77650_setDBEN_nEN(int32_t); //Sets Debounce Timer Enable for the nEN Pin

/**
 * @brief
 */
int32_t MAX77650_setSFT_RST(uint8_t); //Sets Software Reset Functions.

/**
 * @brief
 */
//Global Interrupt Mask Register 0x06
int32_t MAX77650_setINT_M_GLBL(uint8_t); //Sets Global Interrupt Mask Register


/**
 * @brief
 */
//GPIO Configuration Register
int32_t MAX77650_setDBEN_GPI(int32_t); //Sets General Purpose Input Debounce Timer Enable

/**
 * @brief
 */
int32_t MAX77650_setDO(int32_t); //Sets General Purpose Output Data Output

/**
 * @brief
 */
int32_t MAX77650_setDRV(int32_t); //Sets General Purpose Output Driver Type

/**
 * @brief
 */
int32_t MAX77650_setDI(int32_t); //Sets GPIO Digital Input Value

/**
 * @brief
 */
int32_t MAX77650_setDIR(int32_t); //Sets GPIO Direction

/**
 * @brief
 */
//Charger Interrupt Mask Register 0x07
int32_t MAX77650_setINT_M_CHG(uint8_t); //Sets Global Interrupt Mask Register

#endif /* MAIN_COMPONENT_MAX77658_PM_H_ */
