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
#include <stdint.h>
#include "max77658_pm_types.h"

/* Public defines ----------------------------------------------------- */
// Project specific definitions *** adapt to your requirements! ***
#define PMIC_partnumber 0x00  //placed PMIC part-numer on the board: MAX77650 or MAX77651
#define MAX77658_PM_CID 0x78     //OTP option
#define MAX77658_PM_ADDR 0x48    //alternate ADDR is 0x40
#ifndef MAX77658_PM_debug
#define MAX77658_PM_debug false
#endif
#ifndef MAX77658_PM_I2C_port
#define MAX77658_PM_I2C_port 2     //I2C port of the host µC
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
int32_t max77658_pm_get_CID(max77658_pm_t *ctx);

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
int32_t max77658_pm_get_CHGIN_DTLS(max77658_pm_t *ctx);

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
 * @brief Returns 64Hz Clock Status
 */
int32_t max77658_pm_get_CLK_64_S(max77658_pm_t *ctx);

/**
 * @brief  Returns Master LED Enable Bit.[get]
 */
int32_t max77658_pm_get_EN_LED_MSTR(max77658_pm_t *ctx);

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
int32_t max77658_pm_get_DBEN_nEN(max77658_pm_t *ctx);

/**
 * @brief  Software Reset Functions.[get]
 */
int32_t max77658_pm_get_SFT_RST(max77658_pm_t *ctx);

/*****************Global Interrupt Status Register 0x00*********************/
/**
 * @brief  Interrupt Status Register 0x00.[get]
 */
int32_t max77658_pm_get_INT_GLBL(max77658_pm_t *ctx);

/*****************Global Interrupt Mask Register 0x06***********************/
/**
  * @brief  Global Interrupt Mask Register.[get]
 */
int32_t max77658_pm_get_INT_M_GLBL(max77658_pm_t *ctx);

/*****************GPIO Configuration Register******************************/
/**
 * @brief  General Purpose Input Debounce Timer Enable.[get]
 */
int32_t max77658_pm_get_DBEN_GPI(max77658_pm_t *ctx);

/**
 * @brief  General Purpose Output Data Output.[get]
 */
int32_t max77658_pm_get_DO(max77658_pm_t *ctx);

/**
 * @brief  General Purpose Output Driver Type.[get]
 */
int32_t max77658_pm_get_DRV(max77658_pm_t *ctx);

/**
 * @brief  GPIO Digital Input Value.[get]
 */
int32_t max77658_pm_get_DI(max77658_pm_t *ctx);

/**
 * @brief  GPIO Direction.[get]
 */
int32_t max77658_pm_get_DIR(max77658_pm_t *ctx);

/*********************Charger Interrupt Status Register 0x01****************/
/**
 * @brief  Charger Interrupt Status Register 0x01.[get]
 */
int32_t max77658_pm_get_INT_CHG(max77658_pm_t *ctx);

/*********************Charger Interrupt Mask Register 0x07*************/
/**
 * @brief  Global Interrupt Mask Register.[get]
 */
int32_t max77658_pm_get_INT_M_CHG(max77658_pm_t *ctx);

/************************Charger Configuration Register A 0x18**********/
/**
 * @brief  VHOT JEITA Temperature Threshold.[get]
 */
int32_t max77658_pm_get_THM_HOT(max77658_pm_t *ctx);

/**
 * @brief  VWARM JEITA Temperature Threshold.[get]
 */
int32_t max77658_pm_get_THM_WARM(max77658_pm_t *ctx);

/**
 * @brief  VCOOL JEITA Temperature Threshold.[get]
 */
int32_t max77658_pm_get_THM_COOL(max77658_pm_t *ctx);

/**
 * @brief  VCOLD JEITA Temperature Threshold.[get]
 */
int32_t max77658_pm_get_THM_COLD(max77658_pm_t *ctx);

//Charger Configuration Register B 0x19
/**
 * @brief  Minimum CHGIN regulation voltage (VCHGIN-MIN).[get]
 */
int32_t max77658_pm_get_VCHGIN_MIN(max77658_pm_t *ctx);

/**
 * @brief  CHGIN Input Current Limit (ICHGIN-LIM).[get]
 */
int32_t max77658_pm_get_ICHGIN_LIM(max77658_pm_t *ctx);

/**
 * @brief  prequalification charge current (IPQ) as a percentage of IFAST-CHG.[get]
 */
int32_t max77658_pm_get_I_PQ(max77658_pm_t *ctx);

/**
 * @brief  Charger Enable.[get]
 */
int32_t max77658_pm_get_CHG_EN(max77658_pm_t *ctx);

//Charger Configuration Register C 0x1A
/**
 * @brief  Battery prequalification voltage threshold (VPQ).[get]
 */
int32_t max77658_pm_get_CHG_PQ(max77658_pm_t *ctx);

/**
 * @brief  Charger Termination Current (ITERM). I_TERM[1:0] sets 
 *      the charger termination current as a percentage
 *      of the fast charge current IFAST-CHG.[get]
 */
int32_t max77658_pm_get_I_TERM(max77658_pm_t *ctx);

/**
 * @brief  Topoff timer value (tTO).[get]
 */
int32_t max77658_pm_get_T_TOPOFF(max77658_pm_t *ctx);

//Charger Configuration Register D 0x1B
/**
 * @brief  the die junction temperature regulation point, TJ-REG.[get]
 */
int32_t max77658_pm_get_TJ_REG(max77658_pm_t *ctx);

/**
 * @brief  System voltage regulation (VSYS-REG).[get]
 */
int32_t max77658_pm_get_VSYS_REG(max77658_pm_t *ctx);

//Charger Configuration Register E 0x1C
/**
 * @brief  fast-charge constant current value, IFAST-CHG.[get]
 */
int32_t max77658_pm_get_CHG_CC(max77658_pm_t *ctx);

/**
 * @brief  the fast-charge safety timer, tFC.[get]
 */
int32_t max77658_pm_get_T_FAST_CHG(max77658_pm_t *ctx);

//Charger Configuration Register F 0x1D
/**
 * @brief  Returns the IFAST-CHG_JEITA for when the battery is either cool or warm 
 *     as defined by the TCOOL and TWARM temperature thresholds. 
 *     This register is a don't care if the battery temperature is normal.[get]
 */
int32_t max77658_pm_get_CHG_CC_JEITA(max77658_pm_t *ctx);

/**
 * @brief  Returns the Thermistor enable bit.[get]
 */
int32_t max77658_pm_get_THM_EN(max77658_pm_t *ctx);

//Charger Configuration Register G 0x1E
/**
 * @brief  Returns the fast-charge battery regulation voltage, VFAST-CHG.[get]
 */
int32_t max77658_pm_get_CHG_CV(max77658_pm_t *ctx);

/**
 * @brief  this bit places CHGIN in USB suspend mode.[get]
 */
int32_t max77658_pm_get_USBS(max77658_pm_t *ctx);

//Charger Configuration Register H 0x1F
/**
 * @brief  Returns the modified VFAST-CHG for when the battery is either 
 *    cool or warm as defined by the TCOOL and TWARM temperature thresholds.
 *    This register is a don't care if the battery temperature is normal.[get]
 */
int32_t max77658_pm_get_CHG_CV_JEITA(max77658_pm_t *ctx);

//Charger Configuration Register I 0x20
/**
 * @brief  Returns the Selects the battery discharge current
 *       full-scale current value. This 4-bit configuration
 *       starts at 7.5mA and ends at 300mA.[get]
 */
int32_t max77658_pm_get_IMON_DISCHG_SCALE(max77658_pm_t *ctx);

/**
 * @brief Returns the analog channel to connect to AMUX configuration
 */
int32_t max77658_pm_get_MUX_SEL(max77658_pm_t *ctx);

//LDO Configuration Register A 0x38
/**
 * @brief Returns the LDO Target Output Voltage
 */
int32_t max77658_pm_get_TV_LDO(max77658_pm_t *ctx);

/**
 * @brief Returns LDO active-Discharge Enable
 */
//LDO Configuration Register B 0x39
int32_t max77658_pm_get_ADE_LDO(max77658_pm_t *ctx);

/**
 * @brief Enable Control for LDO.
 */
int32_t max77658_pm_get_EN_LDO(max77658_pm_t *ctx);

//SIMO Buck-Boost Global Configuration Register 0x28
/**
 * @brief Returns Manual Reset Time Configuration
 */
int32_t max77658_pm_get_MRT_OTP(max77658_pm_t *ctx);

/**
 * @brief Returns Default voltage of the SBIA_LPM bit
 */
int32_t max77658_pm_get_SBIA_LPM_DEF(max77658_pm_t *ctx);

/**
 * @brief Returns Default Value of the DBNC_nEN bit
 */
int32_t max77658_pm_get_DBNC_nEN_DEF(max77658_pm_t *ctx);

/**
 * @brief Returns the SIMO Buck-Boost (all channels) Drive Strength Trim.
 */
int32_t max77658_pm_get_DRV_SBB(max77658_pm_t *ctx);

//SIMO Buck-Boost 0 Configuration Register A 0x29
/**
 * @brief Returns the SIMO Buck-Boost Channel 0 Peak Current Limit
 */
int32_t max77658_pm_get_IP_SBB0(max77658_pm_t *ctx);

/**
 * @brief Returns the SIMO Buck-Boost Channel 0 Target Output Voltage
 */
int32_t max77658_pm_get_TV_SBB0(max77658_pm_t *ctx);

//SIMO Buck-Boost 0 Configuration Register B 0x2A
/**
 * @brief Returns SIMO Buck-Boost Channel 0 Active-Discharge Enable
 */
int32_t max77658_pm_get_ADE_SBB0(max77658_pm_t *ctx);

/**
 * @brief Returns the Enable Control for SIMO Buck-Boost Channel 0.
 */
int32_t max77658_pm_get_EN_SBB0(max77658_pm_t *ctx);

/**
 * @brief Returns the SIMO Buck-Boost Channel 1 Peak Current Limit
 */
//SIMO Buck-Boost 1 Configuration Register A 0x2B
int32_t max77658_pm_get_IP_SBB1(max77658_pm_t *ctx);

/**
 * @brief Returns the SIMO Buck-Boost Channel 1 Target Output Voltage
 */
int32_t max77658_pm_get_TV_SBB1(max77658_pm_t *ctx);


/**
 * @brief Returns SIMO Buck-Boost Channel 1 Active-Discharge Enable
 */
//SIMO Buck-Boost 1 Configuration Register B 0x2C
int32_t max77658_pm_get_ADE_SBB1(max77658_pm_t *ctx);

/**
 * @brief Returns the Enable Control for SIMO Buck-Boost Channel 1.
 */
int32_t max77658_pm_get_EN_SBB1(max77658_pm_t *ctx);

//SIMO Buck-Boost 2 Configuration Register A 0x2D
/**
 * @brief Returns the SIMO Buck-Boost Channel 2 Peak Current Limit
 */
int32_t max77658_pm_get_IP_SBB2(max77658_pm_t *ctx);

/**
 * @brief Returns the SIMO Buck-Boost Channel 2 Target Output Voltage
 */
int32_t max77658_pm_get_TV_SBB2(max77658_pm_t *ctx);

//SIMO Buck-Boost 2 Configuration Register B 0x2E
/**
 * @brief Returns SIMO Buck-Boost Channel 2 Active-Discharge Enable
 */
int32_t max77658_pm_get_ADE_SBB2(max77658_pm_t *ctx);

/**
 * @brief  Returns the Enable Control for SIMO Buck-Boost Channel 2.[get]
 */
int32_t max77658_pm_get_EN_SBB2(max77658_pm_t *ctx);


/*=======================================================================*/
/*********************** Register writes *********************************/
/*=======================================================================*/

/**
 * @brief Sets the LDO Target Output Voltage
 */
//LDO Configuration Register A 0x38
int32_t max77658_pm_set_TV_LDO(max77658_pm_t *ctx, uint8_t target_val);

/**
 * @brief Sets LDO active-Discharge Enable
 */
//LDO Configuration Register B 0x39
int32_t max77658_pm_set_ADE_LDO(max77658_pm_t *ctx, uint8_t target_val);

/**
 * @brief Enable LDO.[set]
 */
int32_t max77658_pm_set_EN_LDO(max77658_pm_t *ctx, uint8_t target_val);

/**
 * @brief Sets the VHOT JEITA Temperature Threshold
 */
//Charger Configuration Register A 0x18
int32_t max77658_pm_set_THM_HOT(max77658_pm_t *ctx, uint8_t target_val);

/**
 * @brief Sets the VWARM JEITA Temperature Threshold
 */
int32_t max77658_pm_set_THM_WARM(max77658_pm_t *ctx, uint8_t target_val);

/**
 * @brief Sets the VCOOL JEITA Temperature Threshold
 */
int32_t max77658_pm_set_THM_COOL(max77658_pm_t *ctx, uint8_t target_val);

/**
 * @brief Sets the VCOLD JEITA Temperature Threshold
 */
int32_t max77658_pm_set_THM_COLD(max77658_pm_t *ctx, uint8_t target_val);


/**
 * @brief Sets the Minimum CHGIN regulation voltage (VCHGIN-MIN)
 */
//Charger Configuration Register B 0x19
int32_t max77658_pm_set_VCHGIN_MIN(max77658_pm_t *ctx, uint8_t target_val);

/**
 * @brief Sets the CHGIN Input Current Limit (ICHGIN-LIM)
 */
int32_t max77658_pm_set_ICHGIN_LIM(max77658_pm_t *ctx, uint8_t target_val);

/**
 * @brief Sets the prequalification charge current (IPQ) as a percentage of IFAST-CHG
 */
int32_t max77658_pm_set_I_PQ(max77658_pm_t *ctx, uint8_t target_val);

/**
 * @brief Sets Charger Enable
 */
int32_t max77658_pm_set_CHG_EN(max77658_pm_t *ctx, uint8_t target_val);


/** 
 * @brief Sets the Battery prequalification voltage threshold (VPQ)
 */
//Charger Configuration Register C 0x1A
int32_t max77658_pm_set_CHG_PQ(max77658_pm_t *ctx, uint8_t target_val);


/**
 * @brief Sets the Charger Termination Current (ITERM).
 *   I_TERM[1:0] sets the charger termination current as a percentage of the fast charge current IFAST-CHG.
 */
int32_t max77658_pm_set_I_TERM(max77658_pm_t *ctx, uint8_t target_val);

/**
 * @brief Sets the Topoff timer value (tTO)
 */
int32_t max77658_pm_set_T_TOPOFF(max77658_pm_t *ctx, uint8_t target_val);


/**
 * @brief Sets the die junction temperature regulation point, TJ-REG
 */
//Charger Configuration Register D 0x1B
int32_t max77658_pm_set_TJ_REG(max77658_pm_t *ctx, uint8_t target_val);

/**
 * @brief Sets the System voltage regulation (VSYS-REG)
 */
int32_t max77658_pm_set_VSYS_REG(max77658_pm_t *ctx, uint8_t target_val);

/**
 * @brief Sets the fast-charge constant current value, IFAST-CHG.
 */
//Charger Configuration Register E 0x1C
int32_t max77658_pm_set_CHG_CC(max77658_pm_t *ctx, uint8_t target_val);

/**
 * @brief Sets the fast-charge safety timer, tFC.
 */
int32_t max77658_pm_set_T_FAST_CHG(max77658_pm_t *ctx, uint8_t target_val);


/**
 * @brief Sets the IFAST-CHG_JEITA for when the battery is either cool or warm
 *  as defined by the TCOOL and TWARM temperature thresholds.
 *  This register is a don't care if the battery temperature is normal.
 */
//Charger Configuration Register F 0x1D
int32_t max77658_pm_set_CHG_CC_JEITA(max77658_pm_t *ctx, uint8_t target_val);

/**
 * @brief Sets the Thermistor enable bit
 */
int32_t max77658_pm_set_THM_EN(max77658_pm_t *ctx, uint8_t target_val);


/**
 * @brief Sets the fast-charge battery regulation voltage, VFAST-CHG.
 */
//Charger Configuration Register G 0x1E
int32_t max77658_pm_set_CHG_CV(max77658_pm_t *ctx, uint8_t target_val);

/**
 * @brief this bit places CHGIN in USB suspend mode
 */
int32_t max77658_pm_set_USBS(max77658_pm_t *ctx, uint8_t target_val);


/**
 * @brief Sets the modified VFAST-CHG for when the battery is either 
 * cool or warm as defined by the TCOOL and TWARM temperature thresholds.
 * This register is a don't care if the battery temperature is normal.
 */
//Charger Configuration Register H 0x1F
int32_t max77658_pm_set_CHG_CV_JEITA(max77658_pm_t *ctx, uint8_t target_val);


/**
 * @brief Sets the Selects the battery discharge current full-scale current value.
 *  This 4-bit configuration starts at 7.5mA and ends at 300mA.
 */
//Charger Configuration Register I 0x20
int32_t max77658_pm_set_IMON_DISCHG_SCALE(max77658_pm_t *ctx, uint8_t target_val);

/**
 * @brief Sets the analog channel to connect to AMUX configuration
 */
int32_t max77658_pm_set_MUX_SEL(max77658_pm_t *ctx, uint8_t target_val);


/**
 * @brief Sets Manual Reset Time Configuration
 */
//SIMO Buck-Boost Global Configuration Register 0x28
int32_t max77658_pm_set_MRT_OTP(max77658_pm_t *ctx, uint8_t target_val);

/**
 * @brief Sets Default voltage of the SBIA_LPM bit
 */
int32_t max77658_pm_set_SBIA_LPM_DEF(max77658_pm_t *ctx, uint8_t target_val);

/**
 * @brief Sets Default Value of the DBNC_nEN bit
 */
int32_t max77658_pm_set_DBNC_nEN_DEF(max77658_pm_t *ctx, uint8_t target_val);

/**
 * @brief Sets the SIMO Buck-Boost (all channels) Drive Strength Trim.
 */
int32_t max77658_pm_set_DRV_SBB(max77658_pm_t *ctx, uint8_t target_val);


/**
 * @brief Sets the SIMO Buck-Boost Channel 0 Peak Current Limit
 */
//SIMO Buck-Boost 0 Configuration Register A 0x29
int32_t max77658_pm_set_IP_SBB0(max77658_pm_t *ctx, uint8_t target_val);

/**
 * @brief Sets the SIMO Buck-Boost Channel 0 Target Output Voltage
 */
int32_t max77658_pm_set_TV_SBB0(max77658_pm_t *ctx, uint8_t target_val);


/**
 * @brief Sets SIMO Buck-Boost Channel 0 Active-Discharge Enable
 */
//SIMO Buck-Boost 0 Configuration Register B 0x2A
int32_t max77658_pm_set_ADE_SBB0(max77658_pm_t *ctx, uint8_t target_val);

/**
 * @brief Sets the Enable Control for SIMO Buck-Boost Channel 0.
 */
int32_t max77658_pm_set_EN_SBB0(max77658_pm_t *ctx, uint8_t target_val);


/**
 * @brief Sets the SIMO Buck-Boost Channel 1 Peak Current Limit
 */
//SIMO Buck-Boost 1 Configuration Register A 0x2B
int32_t max77658_pm_set_IP_SBB1(max77658_pm_t *ctx, uint8_t target_val);

/**
 * @brief Sets the SIMO Buck-Boost Channel 1 Target Output Voltage
 */
int32_t max77658_pm_set_TV_SBB1(max77658_pm_t *ctx, uint8_t target_val);


/**
 * @brief Sets SIMO Buck-Boost Channel 1 Active-Discharge Enable
 */
//SIMO Buck-Boost 1 Configuration Register B 0x2C
int32_t max77658_pm_set_ADE_SBB1(max77658_pm_t *ctx, uint8_t target_val);

/**
 * @brief Sets the Enable Control for SIMO Buck-Boost Channel 1.
 */
int32_t max77658_pm_set_EN_SBB1(max77658_pm_t *ctx, uint8_t target_val);


/**
 * @brief Sets the SIMO Buck-Boost Channel 2 Peak Current Limit
 */
//SIMO Buck-Boost 2 Configuration Register A 0x2D
int32_t max77658_pm_set_IP_SBB2(max77658_pm_t *ctx, uint8_t target_val);

/**
 * @brief Sets the SIMO Buck-Boost Channel 2 Target Output Voltage
 */
int32_t max77658_pm_set_TV_SBB2(max77658_pm_t *ctx, uint8_t target_val);


/**
 * @brief Sets SIMO Buck-Boost Channel 2 Active-Discharge Enable
 */
//SIMO Buck-Boost 2 Configuration Register B 0x2E
int32_t max77658_pm_set_ADE_SBB2(max77658_pm_t *ctx, uint8_t target_val);

/**
 * @brief Sets the Enable Control for SIMO Buck-Boost Channel 2.
 */
int32_t max77658_pm_set_EN_SBB2(max77658_pm_t *ctx, uint8_t target_val);


/**
 * @brief Sets Master LED Enable Bit
 */
//LED related registers
int32_t max77658_pm_set_EN_LED_MSTR(max77658_pm_t *ctx, uint8_t target_val);

/**
 * @brief Sets LED0 Full Scale Range
 */
int32_t max77658_pm_set_LED_FS0(max77658_pm_t *ctx, uint8_t target_val);

/**
 * @brief Sets LED0 Invert
 */
int32_t max77658_pm_set_INV_LED0(max77658_pm_t *ctx, uint8_t target_val);

/**
 * @brief Sets LED0 Brightness Control
 */
int32_t max77658_pm_set_BRT_LED0(max77658_pm_t *ctx, uint8_t target_val);

/**
 * @brief Sets LED0 Period Settings
 */
int32_t max77658_pm_set_P_LED0(max77658_pm_t *ctx, uint8_t target_val);

/**
 * @brief Sets LED0 On Duty-Cycle Settings
 */
int32_t max77658_pm_set_D_LED0(max77658_pm_t *ctx, uint8_t target_val);

/**
 * @brief Sets LED1 Full Scale Range
 */
int32_t max77658_pm_set_LED_FS1(max77658_pm_t *ctx, uint8_t target_val);

/**
 * @brief Sets LED1 Invert
 */
int32_t max77658_pm_set_INV_LED1(max77658_pm_t *ctx, uint8_t target_val);

/**
 * @brief Sets LED1 Brightness Control
 */
int32_t max77658_pm_set_BRT_LED1(max77658_pm_t *ctx, uint8_t target_val);

/**
 * @brief Sets LED1 Period Settings
 */
int32_t max77658_pm_set_P_LED1(max77658_pm_t *ctx, uint8_t target_val);

/**
 * @brief Sets LED1 On Duty-Cycle Settings
 */
int32_t max77658_pm_set_D_LED1(max77658_pm_t *ctx, uint8_t target_val);

/**
 * @brief Sets LED2 Full Scale Range
 */
int32_t max77658_pm_set_LED_FS2(max77658_pm_t *ctx, uint8_t target_val);

/**
 * @brief Sets LED2 Invert
 */
int32_t max77658_pm_set_INV_LED2(max77658_pm_t *ctx, uint8_t target_val);

/**
 * @brief Sets LED2 Brightness Control
 */
int32_t max77658_pm_set_BRT_LED2(max77658_pm_t *ctx, uint8_t target_val);

/**
 * @brief Sets LED2 Period Settings
 */
int32_t max77658_pm_set_P_LED2(max77658_pm_t *ctx, uint8_t target_val);

/**
 * @brief Sets LED2 On Duty-Cycle Settings
 */
int32_t max77658_pm_set_D_LED2(max77658_pm_t *ctx, uint8_t target_val);

/**
 * @brief Sets Main Bias Okay Status Bit
 */
//Global Configuration register 0x10
int32_t max77658_pm_set_BOK(max77658_pm_t *ctx, uint8_t target_val);

/**
 * @brief Sets Main Bias Low-Power Mode software request
 */
int32_t max77658_pm_set_SBIA_LPM(max77658_pm_t *ctx, uint8_t target_val);

/**
 * @brief Sets Main Bias Enable Software Request
 */
int32_t max77658_pm_set_SBIA_EN(max77658_pm_t *ctx, uint8_t target_val);

/**
 * @brief Sets nEN Input (ONKEY) Default Configuration Mode
 */
int32_t max77658_pm_set_nEN_MODE(max77658_pm_t *ctx, uint8_t target_val);

/**
 * @brief Sets Debounce Timer Enable for the nEN Pin
 */
int32_t max77658_pm_set_DBEN_nEN(max77658_pm_t *ctx, uint8_t target_val);

/**
 * @brief Sets Software Reset Functions.
 */ 
int32_t max77658_pm_set_SFT_RST(max77658_pm_t *ctx, uint8_t target_val);

/**
 * @brief Sets Global Interrupt Mask Register
 */
//Global Interrupt Mask Register 0x06
int32_t max77658_pm_set_INT_M_GLBL(max77658_pm_t *ctx, uint8_t target_val);


/**
 * @brief Sets General Purpose Input Debounce Timer Enable
 */
//GPIO Configuration Register
int32_t max77658_pm_set_DBEN_GPI(max77658_pm_t *ctx, uint8_t target_val);

/**
 * @brief Sets General Purpose Output Data Output
 */
int32_t max77658_pm_set_DO(max77658_pm_t *ctx, uint8_t target_val);

/**
 * @brief Sets General Purpose Output Driver Type
 */
int32_t max77658_pm_set_DRV(max77658_pm_t *ctx, uint8_t target_val);

/**
 * @brief Sets GPIO Digital Input Value
 */
int32_t max77658_pm_set_DI(max77658_pm_t *ctx, uint8_t target_val);

/**
 * @brief Sets GPIO Direction
 */
int32_t max77658_pm_set_DIR(max77658_pm_t *ctx, uint8_t target_val);

/**
 * @brief Sets Global Interrupt Mask Register
 */
//Charger Interrupt Mask Register 0x07
int32_t max77658_pm_set_INT_M_CHG(max77658_pm_t *ctx, uint8_t target_val);

#endif /* MAIN_COMPONENT_MAX77658_PM_H_ */

