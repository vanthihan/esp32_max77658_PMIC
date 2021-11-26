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


/**
  * @brief  Read generic device register
 */
int32_t max77658_pm_read_reg(max77658_pm_t *ctx, uint8_t reg, uint8_t *data);

/**
  * @brief  Write generic device register
 */
int32_t max77658_pm_write_reg(max77658_pm_t *ctx, uint8_t reg, uint8_t *data);


/*****************Read Register***********************/

/**
 * @brief  Interrupt Status Register 0x00.[get]
 *
 * @param  ctx      read / write interface definitions
 * @retval          Interrupt Status Register 0x00
 *
 */
int32_t max77658_pm_get_INT_GLBL0(max77658_pm_t *ctx);

/**
 * @brief  Interrupt Status Register 0x04.[get]
 *
 * @param  ctx      read / write interface definitions
 * @retval          Interrupt Status Register 0x04
 *
 */
int32_t max77658_pm_get_INT_GLBL1(max77658_pm_t *ctx);

/**
 * @brief  Flag Register (ERCFLAG) related reads.[get]
 *
 * @param  ctx      read / write interface definitions
 * @retval          ERCFLAG Register 0x04
 *
 */
int32_t max77658_pm_get_ERCFLAG(max77658_pm_t *ctx);

/**
 * @brief  Device Identification Bits for Metal Options.[get]
 *
 * @param  ctx      read / write interface definitions
 * @retval           -1: I2C error, 0 = MAX77658 
 *                                  1 = Reserved
 *
 */
int32_t max77658_pm_get_DIDM(max77658_pm_t *ctx);

/**
 * @brief  BOK Interrupt Status.[get]
 *
 * @param  ctx      read / write interface definitions
 * @retval           -1: I2C error, 0 = Main bias is not ready. 
 *                                  1 = Main bias enabled and ready.
 *
 */
int32_t max77658_pm_get_BOK(max77658_pm_t *ctx);

/**
 * @brief  LDO0 Dropout Detector Rising Status.[get]
 *
 * @param  ctx      read / write interface definitions
 * @retval           -1: I2C error, 0 =  LDO0 is not in dropout. 
 *                                  1 =  LDO0 is in dropout.
 *
 */
int32_t max77658_pm_get_DOD0_S(max77658_pm_t *ctx);

/**
 * @brief  LDO1 Dropout Detector Rising Status.[get]
 *
 * @param  ctx      read / write interface definitions
 * @retval           -1: I2C error, 0 =  LDO1 is not in dropout. 
 *                                  1 =  LDO1 is in dropout.
 *
 */
int32_t max77658_pm_get_DOD1_S(max77658_pm_t *ctx);

/**
 * @brief  Thermal Alarm 2 Status.[get]
 *
 * @param  ctx      read / write interface definitions
 * @retval           -1: I2C error, 0 = The junction temperature is less than TJA2. 
 *                                  1 = The junction temperature is greater than TJAL2.
 *
 */
int32_t max77658_pm_get_TJAL2_S(max77658_pm_t *ctx);

/**
 * @brief  Thermal Alarm 1 Status.[get]
 *
 * @param  ctx      read / write interface definitions
 * @retval           -1: I2C error, 0 = The junction temperature is less than TJA1. 
 *                                  1 = The junction temperature is greater than TJAL1.
 *
 */
int32_t max77658_pm_get_TJAL1_S(max77658_pm_t *ctx);

/**
 * @brief  Debounced Status for the nEN Input.[get]
 *
 * @param  ctx      read / write interface definitions
 * @retval           -1: I2C error, 0 = nEN is not active (logic-high). 
 *                                  1 = nEN is active (logic-low).
 *
 */
int32_t max77658_pm_get_STAT_EN(max77658_pm_t *ctx);

/**
 * @brief  Software Version of the nIRQ MOSFET Gate Drive.[get]
 *
 * @param  ctx      read / write interface definitions
 * @retval           -1: I2C error, 0 = Unmasked gate drive is logic-low. 
 *                                  1 = Unmasked gate drive is logic-high. 
 *
 */
int32_t max77658_pm_get_STAT_IRQ(max77658_pm_t *ctx);

/**
 * @brief  Global Interrupt Mask Register 0.[get]
 *
 * @param  ctx      read / write interface definitions
 * @retval           -1: I2C error, 0 = Unmasked gate drive is logic-low. 
 *                                  1 = Unmasked gate drive is logic-high. 
 *
 */
int32_t max77658_pm_get_INTM_GLBL0(max77658_pm_t *ctx);

/**
 * @brief  Global Interrupt Mask Register 1.[get]
 * 
 * @param  ctx      read / write interface definitions
 * @retval           -1: I2C error, 0 = Unmasked gate drive is logic-low. 
 *                                  1 = Unmasked gate drive is logic-high. 
 *
 */
int32_t max77658_pm_get_INTM_GLBL1(max77658_pm_t *ctx);

/**
 * @brief  nEN Internal Pullup Resistor.[get]
 * 
 * @param  ctx      read / write interface definitions
 * @retval           -1: I2C error, 0 = Strong internal nEN pullup (200kΩ) 
 *                                  1 = Weak internal nEN pullup (10MΩ) 
 *
 */
int32_t max77658_pm_get_PU_DIS(max77658_pm_t *ctx);

/**
 * @brief  Sets the Manual Reset Time (tMRST).[get]
 * 
 * @param  ctx      read / write interface definitions
 * @retval           -1: I2C error, 0 = 8s, 1 = 4s 
 *
 */
int32_t max77658_pm_get_T_MRST(max77658_pm_t *ctx);

/**
 * @brief  Main Bias Low-Power Mode Software Request.[get]
 * 
 * @param  ctx      read / write interface definitions
 * @retval           -1: I2C error, 0 = Main bias requested to be in normal-power mode by software. 
 *                                  1 = Main bias request to be in low-power mode by software. 
 *
 */
int32_t max77658_pm_get_SBIA_LPM(max77658_pm_t *ctx);

/**
 * @brief  nEN Input (ON-KEY) Default Configuration Mode .[get]
 * 
 * @param  ctx      read / write interface definitions
 * @retval           -1: I2C error, 0 = Main bias requested to be in normal-power mode by software. 
 *                                  1 = Main bias request to be in low-power mode by software. 
 *
 */
int32_t max77658_pm_get_nEN_MODE(max77658_pm_t *ctx);

/**
 * @brief  Debounce Timer Enable for the nEN Pin.[get]
 * 
 * @param  ctx      read / write interface definitions
 * @retval           -1: I2C error, 0 = 500μs Debounce 
 *                                  1 = 30ms Debounce 
 *
 */
int32_t max77658_pm_get_DBEN_nEN(max77658_pm_t *ctx);

/**
 * @brief  Software Reset Functions.[get]
 * 
 * @param  ctx      read / write interface definitions
 * @retval           -1: I2C error, 
 *
 */
int32_t max77658_pm_get_SFT_CTRL(max77658_pm_t *ctx);

/**
 * @brief  Software Reset Functions.[get]
 * 
 * @param  ctx      read / write interface definitions
 * @retval           -1: I2C error, 0b0 = The SBB regulator does not shut off when an SBB fault occurs 
 *                                  0b1 = The SBB regulator powers down sequentially when an SBB fault occurs 
 *
 */
int32_t max77658_pm_get_SBB_F_SHUTDN(max77658_pm_t *ctx);

/**
 * @brief  Alternate Mode Enable for GPIO0.[get]
 * 
 * @param  ctx      read / write interface definitions
 * @retval           -1: I2C error, 0 = Standard GPIO. 
 *                                  1 = Active-high input, Force USB Suspend (FUS). FUS is only active if the FUS_M bit is set to 0. 
 *
 */
int32_t max77658_pm_get_ALT_GPIO0(max77658_pm_t *ctx);

/**
 * @brief  Alternate Mode Enable for GPIO0.[get]
 * 
 * @param  ctx      read / write interface definitions
 * @retval           -1: I2C error, 0 = Standard GPIO. 
 *                                  1 = Active-high input, Force USB Suspend (FUS). FUS is only active if the FUS_M bit is set to 0. 
 *
 */
int32_t max77658_pm_get_DBEN_GPI_0(max77658_pm_t *ctx);

/**
 * @brief  General Purpose Output Data Output for GPO0.[get]
 * 
 * @param  ctx      read / write interface definitions
 * @retval           -1: I2C error, When set for GPO (DIR = 0): 
 *                                  0 = GPIO is output logic low. 
 *                                  1 = GPIO is output logic high when set as push-pull output (DRV = 1).
 *                                  GPIO is high-impedance when set as an open-drain output (DRV = 0). 
 *
 */
int32_t max77658_pm_get_DO_0(max77658_pm_t *ctx);

/**
 * @brief  General Purpose Output Driver Type for GPO0 .[get]
 * 
 * @param  ctx      read / write interface definitions
 * @retval           -1: I2C error, This bit is a don't care when DIR = 1 (configured as input). When set for GPO (DIR = 0): 
 *                                  0 = Open-drain 
 *                                  1 = Push-pull  
 *
 */
int32_t max77658_pm_get_DRV_0(max77658_pm_t *ctx);

/**
 * @brief  GPIO Digital Input Value for GPI0. Irrespective of whether the GPIO is set for 
 *          GPI (DIR = 1) or GPO (DIR = 0), DI reflects the state of the GPIO.[get]
 * 
 * @param  ctx      read / write interface definitions
 * @retval           -1: I2C error, 0 = Input logic-low 
 *                                  1 = Input logic-high 
 *
 */
int32_t max77658_pm_get_DI_0(max77658_pm_t *ctx);

/**
 * @brief  GPIO Direction for GPIO0.[get]
 * 
 * @param  ctx      read / write interface definitions
 * @retval           -1: I2C error, 0 = General purpose output (GPO) 
 *                                  1 = General purpose input (GPI) 
 *
 */
int32_t max77658_pm_get_DIR_0(max77658_pm_t *ctx);

/**
 * @brief  Alternate Mode Enable for GPIO1.[get]
 * 
 * @param  ctx      read / write interface definitions
 * @retval           -1: I2C error, Alternate Mode Enable for GPIO1 
 *                                  0b0 = SBB0 is set by TV_SBB0 
 *                                  1b0 = SBB0 is set by TV_SBB0_DVS  
 *
 */
int32_t max77658_pm_get_ALT_GPIO1(max77658_pm_t *ctx);

/**
 * @brief  General Purpose Input Debounce Timer Enable for GPIO.[get]
 * 
 * @param  ctx      read / write interface definitions
 * @retval           -1: I2C error, 0 = Standard GPIO. 
 *                                  1 = Active-high input, Force USB Suspend (FUS). FUS is only active if the FUS_M bit is set to 0. 
 *
 */
int32_t max77658_pm_get_DBEN_GPI_1(max77658_pm_t *ctx);

/**
 * @brief  General Purpose Output Data Output for GPO0.[get]
 * 
 * @param  ctx      read / write interface definitions
 * @retval           -1: I2C error, When set for GPO (DIR = 0): 
 *                                  0 = GPIO is output logic low. 
 *                                  1 = GPIO is output logic high when set as push-pull output (DRV = 1).
 *                                  GPIO is high-impedance when set as an open-drain output (DRV = 0). 
 *
 */
int32_t max77658_pm_get_DO_1(max77658_pm_t *ctx);

/**
 * @brief  General Purpose Output Driver Type for GPO0 .[get]
 * 
 * @param  ctx      read / write interface definitions
 * @retval           -1: I2C error, This bit is a don't care when DIR = 1 (configured as input). When set for GPO (DIR = 0): 
 *                                  0 = Open-drain 
 *                                  1 = Push-pull  
 *
 */
int32_t max77658_pm_get_DRV_1(max77658_pm_t *ctx);

/**
 * @brief  GPIO Digital Input Value for GPI0. Irrespective of whether the GPIO is set for 
 *          GPI (DIR = 1) or GPO (DIR = 0), DI reflects the state of the GPIO.[get]
 * 
 * @param  ctx      read / write interface definitions
 * @retval           -1: I2C error, 0 = Input logic-low 
 *                                  1 = Input logic-high 
 *
 */
int32_t max77658_pm_get_DI_1(max77658_pm_t *ctx);

/**
 * @brief  GPIO Direction for GPIO0.[get]
 * 
 * @param  ctx      read / write interface definitions
 * @retval           -1: I2C error, 0 = General purpose output (GPO) 
 *                                  1 = General purpose input (GPI) 
 *
 */
int32_t max77658_pm_get_DIR_1(max77658_pm_t *ctx);

/**
 * @brief  Alternate Mode Enable for GPIO1.[get]
 * 
 * @param  ctx      read / write interface definitions
 * @retval           -1: I2C error, Alternate Mode Enable for GPIO1 
 *                                  0b0 = SBB0 is set by TV_SBB0 
 *                                  1b0 = SBB0 is set by TV_SBB0_DVS  
 *
 */
int32_t max77658_pm_get_ALT_GPIO2(max77658_pm_t *ctx);

/**
 * @brief  General Purpose Input Debounce Timer Enable for GPI2.[get]
 * 
 * @param  ctx      read / write interface definitions
 * @retval           -1: I2C error, 0 = No debounce 
 *                                  1 = 30ms Debounce. 
 *
 */
int32_t max77658_pm_get_DBEN_GPI_2(max77658_pm_t *ctx);

/**
 * @brief  General Purpose Output Data Output for GPO0.[get]
 * 
 * @param  ctx      read / write interface definitions
 * @retval           -1: I2C error, When set for GPO (DIR = 0): 
 *                                  0 = GPIO is output logic low. 
 *                                  1 = GPIO is output logic high when set as push-pull output (DRV = 1).
 *                                  GPIO is high-impedance when set as an open-drain output (DRV = 0). 
 *
 */
int32_t max77658_pm_get_DO_2(max77658_pm_t *ctx);

/**
 * @brief  General Purpose Output Driver Type for GPO0 .[get]
 * 
 * @param  ctx      read / write interface definitions
 * @retval           -1: I2C error, This bit is a don't care when DIR = 1 (configured as input). When set for GPO (DIR = 0): 
 *                                  0 = Open-drain 
 *                                  1 = Push-pull  
 *
 */
int32_t max77658_pm_get_DRV_2(max77658_pm_t *ctx);

/**
 * @brief  GPIO Digital Input Value for GPI0. Irrespective of whether the GPIO is set for 
 *          GPI (DIR = 1) or GPO (DIR = 0), DI reflects the state of the GPIO.[get]
 * 
 * @param  ctx      read / write interface definitions
 * @retval           -1: I2C error, 0 = Input logic-low 
 *                                  1 = Input logic-high 
 *
 */
int32_t max77658_pm_get_DI_2(max77658_pm_t *ctx);

/**
 * @brief  GPIO Direction for GPIO0.[get]
 * 
 * @param  ctx      read / write interface definitions
 * @retval           -1: I2C error, 0 = General purpose output (GPO) 
 *                                  1 = General purpose input (GPI) 
 *
 */
int32_t max77658_pm_get_DIR_2(max77658_pm_t *ctx);

/**
 * @brief  Chip Identification Code.
 *          The chip identification code refers to a set of reset values in the register map, or the "OTP configuration."[get]
 * 
 * @param  ctx      read / write interface definitions
 * @retval           -1: I2C error, 
 *
 */
int32_t max77658_pm_get_CID(max77658_pm_t *ctx);

/**
 * @brief  Watchdog Timer Period. Sets tWD.[get]
 * 
 * @param  ctx      read / write interface definitions
 * @retval           -1: I2C error, 0b00 = 16 seconds 
 *                                  0b01 = 32 seconds 
 *                                  0b10 = 64 seconds 
 *                                  0b11 = 128 seconds
 *
 */
int32_t max77658_pm_get_WDT_PER(max77658_pm_t *ctx);

/**
 * @brief  Watchdog Timer Expired Action.[get]
 * 
 * @param  ctx      read / write interface definitions
 * @retval           -1: I2C error, 0 = Watchdog timer expire causes power-off. 
 *                                  1 = Watchdog timer expire causes power-reset.
 *
 */
int32_t max77658_pm_get_WDT_MODE(max77658_pm_t *ctx);

/**
 * @brief  Watchdog Timer Clear Control.[get]
 * 
 * @param  ctx      read / write interface definitions
 * @retval           -1: I2C error, 0 = Watchdog timer period is not reset. 
 *                                  1 = Watchdog timer is reset back to tWD.
 *
 */
int32_t max77658_pm_get_WDT_CLR(max77658_pm_t *ctx);

/**
 * @brief  Watchdog Timer Enable. Write protected depending on WDT_LOCK.[get]
 * 
 * @param  ctx      read / write interface definitions
 * @retval           -1: I2C error, 0 = Watchdog timer is not enabled. 
 *                                  1 = Watchdog timer is enabled. The timer expires if not reset by setting WDT_CLR.
 *
 */
int32_t max77658_pm_get_WDT_EN(max77658_pm_t *ctx);

/**
 * @brief  Factory-Set Safety Bit for the Watchdog Timer.[get]
 * 
 * @param  ctx      read / write interface definitions
 * @retval           -1: I2C error, 0 = Watchdog timer can be enabled and disabled with WDT_EN. 
 *                                  1 = Watchdog timer can not be disabled with WDT_EN. However, WDT_EN can still be used to enable the watchdog timer.
 *
 */
int32_t max77658_pm_get_WDT_LOCK(max77658_pm_t *ctx);

/**
 * @brief  System Voltage Configuration Error Interrupt.[get]
 * 
 * @param  ctx      read / write interface definitions
 * @retval          -1 = I2C error.
 *                   0 = The bit combination in CHG_CV has not been forced to change since the last time this bit was read. 
 *                   1 = The bit combination in CHG_CV has been forced to change to ensure VSYS-REG = VFAST-CHG + 200mV since the last time this bit was read. 
 *
 */
int32_t max77658_pm_get_SYS_CNFG_I(max77658_pm_t *ctx);

/**
 * @brief  Minimum System Voltage Regulation-Loop Related Interrupt.[get]
 * 
 * @param  ctx    read / write interface definitions
 * @retval        -1 = I2C error.
 *                0 = The minimum system voltage regulation loop has not engaged since the last time this bit was read. 
 *                1 = The minimum system voltage regulation loop has engaged since the last time this bit was read. 
 *
 */
int32_t max77658_pm_get_SYS_CTRL_I(max77658_pm_t *ctx);

/**
 * @brief  CHGIN Control-Loop Related Interrupt.[get]
 * 
 * @param  ctx    read / write interface definitions
 * @retval        -1 = I2C error.
 *                0 = Neither the VCHGIN_MIN_STAT nor the ICHGIN_LIM_STAT bits have changed since the last time this bit was read. 
 *                1 = The VCHGIN_MIN_STAT or ICHGIN_LIM_STAT bits have changed since the last time this bit was read.
 *
 */
int32_t max77658_pm_get_CHGIN_CTRL_I(max77658_pm_t *ctx);

/**
 * @brief  Die Junction Temperature Regulation Interrupt.[get]
 * 
 * @param  ctx    read / write interface definitions
 * @retval        -1 = I2C error.
 *                0 = The die temperature has not exceeded TJ-REG since the last time this bit was read. 
 *                1 = The die temperature has exceeded TJ-REG since the last time this bit was read.
 *
 */
int32_t max77658_pm_get_TJ_REG_I(max77658_pm_t *ctx);

/**
 * @brief  CHGIN Related Interrupt.[get]
 * 
 * @param  ctx    read / write interface definitions
 * @retval        -1 = I2C error.
 *                0 = The bits in CHGIN_DTLS[1:0] have not changed since the last time this bit was read. 
 *                1 = The bits in CHGIN_DTLS[1:0] have changed since the last time this bit was read.
 *
 */
int32_t max77658_pm_get_CHGIN_I(max77658_pm_t *ctx);

/**
 * @brief  Charger Related Interrupt.[get]
 * 
 * @param  ctx    read / write interface definitions
 * @retval        -1 = I2C error.
 *                0 = The bits in CHG_DTLS[3:0] have not changed since the last time this bit was read. 
 *                1 = The bits in CHG_DTLS[3:0] have changed since the last time this bit was read. 
 *
 */
int32_t max77658_pm_get_CHG_I(max77658_pm_t *ctx);

/**
 * @brief  Thermistor Related Interrupt.[get]
 * 
 * @param  ctx    read / write interface definitions
 * @retval        -1 = I2C error.
 *                0 = The bits in THM_DTLS[2:0] have not changed since the last time this bit was read. 
 *                1 = The bits in THM_DTLS[2:0] have changed since the last time this bit was read.  
 *
 */
int32_t max77658_pm_get_THM_I(max77658_pm_t *ctx);

/**
 * @brief  Minimum Input Voltage Regulation Loop Status.[get]
 * 
 * @param  ctx    read / write interface definitions
 * @retval        -1 = I2C error.
 *                0 = The minimum CHGIN voltage regulation loop is not engaged. 
 *                1 = The minimum CHGIN voltage regulation loop has engaged to regulate VCHGIN ≥ VCHGIN-MIN. 
 *
 */
int32_t max77658_pm_get_VCHGIN_MIN_STAT(max77658_pm_t *ctx);

/**
 * @brief  Input Current Limit Loop Status.[get]
 * 
 * @param  ctx    read / write interface definitions
 * @retval        -1 = I2C error.
 *                0 = The CHGIN current limit loop is not engaged. 
 *                1 = The CHGIN current limit loop has engaged to regulate ICHGIN ≤ ICHGIN-LIM.  
 *
 */
int32_t max77658_pm_get_ICHGIN_LIM_STAT(max77658_pm_t *ctx);

/**
 * @brief  Minimum System Voltage Regulation Loop Status.[get]
 * 
 * @param  ctx    read / write interface definitions
 * @retval        -1 = I2C error.
 *                0 = The minimum system voltage regulation loop is not enganged. 
 *                1 = The minimum system voltage regulation loop is engaged to regulate VSYS ≥ VSYS-MIN.  
 *
 */
int32_t max77658_pm_get_VSYS_MIN_STAT(max77658_pm_t *ctx);

/**
 * @brief  Maximum Junction Temperature Regulation Loop Status.[get]
 * 
 * @param  ctx    read / write interface definitions
 * @retval        -1 = I2C error.
 *                0 = The maximum junction temperature regulation loop is not engaged. 
 *                1 = The maximum junction temperature regulation loop has engaged to regulate the junction temperature to less than TJ-REG.  
 *
 */
int32_t max77658_pm_get_TJ_REG_STAT(max77658_pm_t *ctx);

/**
 * @brief  Battery Temperature Details. Valid only when CHGIN_DTLS[1:0] = 0b11.[get]
 * 
 * @param  ctx    read / write interface definitions
 * @retval        -1 = I2C error.
 *                0b000 = Thermistor is disabled (Config.TSel = 0). 
 *                0b001 = Battery is cold as programmed by THM_COLD[1:0]. If thermistor and charger are enabled while the battery is cold, a battery temperature fault occurs. 
 *                0b010 = Battery is cool as programmed by THM_COOL[1:0]. 
 *                0b011 = Battery is warm as programmed by THM_WARM[1:0]. 
 *                0b100 = Battery is hot as programmed by THM_HOT[1:0]. If thermistor and charger are enabled while the battery is hot, a battery temperature fault occurs. 
 *                0b101 = Battery is in the normal temperature region. 
 *                0b110 to 0b111 = Reserved.   
 *
 */
int32_t max77658_pm_get_THM_DTLS(max77658_pm_t *ctx);

/**
 * @brief  Battery Temperature Details. Valid only when CHGIN_DTLS[1:0] = 0b11.[get]
 * 
 * @param  ctx    read / write interface definitions
 * @retval        -1 = I2C error.
 *                0b0000 = Off 
 *                0b0001 = Prequalification mode. 
 *                0b0010 = Fast-charge constant-current (CC) mode. 
 *                0b0011 = JEITA modified fast-charge constant-current mode. 
 *                0b0100 = Fast-charge constant-voltage (CV) mode. 
 *                0b0101 = JEITA modified fast-charge constant-voltage mode. 
 *                0b0110 = Top-off mode. 
 *                0b0111 = JEITA modified top-off mode. 
 *                0b1000 = Done 
 *                0b1001 = JEITA modified done (done was entered through the JEITA-modified fast-charge states). 
 *                0b1011 =  Fast-charge timer fault. 
 *                0b1100 =  Battery temperature fault. 
 *                0b1101 to 0b1111 = Reserved. 
 *                0b1010 = Prequalification timer fault. 
 *
 */
int32_t max77658_pm_get_CHG_DTLS(max77658_pm_t *ctx);

/**
 * @brief  CHGIN Status Detail.[get]
 * 
 * @param  ctx    read / write interface definitions
 * @retval        -1 = I2C error.
 *                0b00 = The CHGIN input voltage is below the UVLO threshold (VCHGIN < VUVLO). 
 *                0b01 = The CHGIN input voltage is above the OVP threshold (VCHGIN > VOVP). 
 *                0b10 = The CHGIN input is being debounced (no power accepted from CHGIN during debounce). 
 *                0b11 = The CHGIN input is okay and debounced.
 *
 */
int32_t max77658_pm_get_CHGIN_DTLS(max77658_pm_t *ctx);

/**
 * @brief  Quick Charger Status.[get]
 * 
 * @param  ctx    read / write interface definitions
 * @retval        -1 = I2C error.
 *                 0 = Charging is not happening. 
 *                 1 = Charging is happening. 
 *
 */
int32_t max77658_pm_get_CHG(max77658_pm_t *ctx);

/**
 * @brief  Time Suspend Indicator.[get]
 * 
 * @param  ctx    read / write interface definitions
 * @retval        -1 = I2C error.
 *                 0 = The charger's timers are either not active, or not suspended. 
 *                 1 = The charger's active timer is suspended due to one of three reasons: charge current dropped 
 *                     below 20% of IFAST-CHG while the charger state machine is in FAST CHARGE CC mode, the 
 *                     charger is in SUPPLEMENT mode, or the charger state machine is in BATTERY TEMPERATURE FAULT mode. 
 *
 */
int32_t max77658_pm_get_TIME_SUS(max77658_pm_t *ctx);

/**
 * @brief  Global Interrupt Mask Register.[get]
 * 
 * @param  ctx    read / write interface definitions
 * @retval        -1 = I2C error.
 *
 */
int32_t max77658_pm_get_INT_M_CHG(max77658_pm_t *ctx);

/**
 * @brief  Sets the THOT JEITA Temperature Threshold.[get]
 * 
 * @param  ctx    read / write interface definitions
 * @retval        -1 = I2C error.
 *                0b00 = THOT = 45ºC 
 *                0b01 = THOT = 50ºC 
 *                0b10 = THOT = 55ºC 
 *                0b11 = THOT = 60ºC 
 */
int32_t max77658_pm_get_THM_HOT(max77658_pm_t *ctx);

/**
 * @brief  Sets the TWARM JEITA Temperature Threshold.[get]
 * 
 * @param  ctx    read / write interface definitions
 * @retval        -1 = I2C error.
 *                0b00 = TWARM = 35ºC  
 *                0b01 = TWARM = 40ºC  
 *                0b10 = TWARM = 45ºC  
 *                0b11 = TWARM = 50ºC  
 */
int32_t max77658_pm_get_THM_WARM(max77658_pm_t *ctx);

/**
 * @brief  Sets the TCOOL JEITA Temperature Threshold.[get]
 * 
 * @param  ctx    read / write interface definitions
 * @retval        -1 = I2C error.
 *                0b00 = TCOOL = 0ºC   
 *                0b01 = TCOOL = 5ºC   
 *                0b10 = TCOOL = 10ºC   
 *                0b11 = TCOOL = 15ºC  
 */
int32_t max77658_pm_get_THM_COOL(max77658_pm_t *ctx);

/**
 * @brief  Sets the TCOOL JEITA Temperature Threshold.[get]
 * 
 * @param  ctx    read / write interface definitions
 * @retval        -1 = I2C error.
 *                0b00 = TCOLD = -10ºC 
 *                0b01 = TCOLD = -5ºC 
 *                0b10 = TCOLD = 0ºC  
 *                0b11 = TCOLD = 5ºC 
 */
int32_t max77658_pm_get_THM_COLD(max77658_pm_t *ctx);

/**
 * @brief  Minimum CHGIN Regulation Voltage (VCHGIN-MIN).[get]
 * 
 * @param  ctx    read / write interface definitions
 * @retval        -1 = I2C error.
 *                 0b000 = 4.0V 
 *                 0b001 = 4.1V 
 *                 0b010 = 4.2V 
 *                 0b011 = 4.3V 
 *                 0b100 = 4.4V 
 *                 0b101 = 4.5V 
 *                 0b110 = 4.6V 
 *                 0b111 = 4.7V 
 */
int32_t max77658_pm_get_VCHGIN_MIN(max77658_pm_t *ctx);

/**
 * @brief  CHGIN Input Current Limit (ICHGIN-LIM).[get]
 * 
 * @param  ctx    read / write interface definitions
 * @retval        -1 = I2C error.
 *                 0b000 = 475mA  
 *                 0b001 = 380mA  
 *                 0b010 = 285mA  
 *                 0b011 = 190mA  
 *                 0b100 = 95mA  
 *                 0b101 to 0b111 = Reserved. Defaults to 0b100. 
 */
int32_t max77658_pm_get_ICHGIN_LIM(max77658_pm_t *ctx);

/**
 * @brief  Sets the prequalification charge current (IPQ) as a percentage of IFAST-CHG..[get]
 * 
 * @param  ctx    read / write interface definitions
 * @retval        -1 = I2C error.
 *                 0 = 10%   
 *                 1 = 20%   
 */
int32_t max77658_pm_get_I_PQ(max77658_pm_t *ctx);

/**
 * @brief  Sets the prequalification charge current (IPQ) as a percentage of IFAST-CHG..[get]
 * 
 * @param  ctx    read / write interface definitions
 * @retval        -1 = I2C error.
 *                 Default value defined by OTP bit  CHG_EN_DFT: 
 *                 0 = The battery charger is disabled. 
 *                 1 = The battery charger is enabled.   
 */
int32_t max77658_pm_get_CHG_EN(max77658_pm_t *ctx);

/**
 * @brief  Battery Prequalification Voltage Threshold (VPQ).[get]
 * 
 * @param  ctx    read / write interface definitions
 * @retval        -1 = I2C error.
 *                 0b000 = 2.3V 
 *                 0b001 = 2.4V 
 *                 0b010 = 2.5V 
 *                 0b011 = 2.6V 
 *                 0b100 = 2.7V 
 *                 0b101 = 2.8V 
 *                 0b110 = 2.9V 
 *                 0b111 = 3.0V   
 */
int32_t max77658_pm_get_CHG_PQ(max77658_pm_t *ctx);

/**
 * @brief  Charger Termination Current (ITERM). I_TERM[1:0] sets the charger termination current 
 *          as a percentage of the fast-charge current IFAST-CHG.[get]
 * 
 * @param  ctx    read / write interface definitions
 * @retval        -1 = I2C error.
 *                 00 = 5% 
 *                 01 = 7.5% 
 *                 10 = 10% 
 *                 11 = 15%
 */
int32_t max77658_pm_get_I_TERM(max77658_pm_t *ctx);

/**
 * @brief  Top-Off Timer Value (tTO).[get]
 * 
 * @param  ctx    read / write interface definitions
 * @retval        -1 = I2C error.
 *                0b000 = 0 minutes 
 *                0b001 = 5 minutes 
 *                0b010 = 10 minutes 
 *                0b011 = 15 minutes 
 *                0b100 = 20 minutes 
 *                0b101 = 25 minutes 
 *                0b110 = 30 minutes 
 *                0b111 = 35 minutes 
 */
int32_t max77658_pm_get_T_TOPOFF(max77658_pm_t *ctx);

/**
 * @brief  Sets the die junction temperature regulation point, TJ-REG.[get]
 * 
 * @param  ctx    read / write interface definitions
 * @retval        -1 = I2C error.
 *                0b000 = 60ºC 
 *                0b001 = 70ºC 
 *                0b010 = 80ºC  
 *                0b011 = 90ºC  
 *                0b100 to 0b111 = 100ºC 
 */
int32_t max77658_pm_get_TJ_REG(max77658_pm_t *ctx);

/**
 * @brief  System Voltage Regulation (VSYS-REG).[get]
 * 
 * @param  ctx    read / write interface definitions
 * @retval        -1 = I2C error.
 *                This 5-bit configuration is a linear transfer 
 *                function that starts at 3.4V and ends at 4.8V, with 50mV increments. 
 */
int32_t max77658_pm_get_VSYS_REG(max77658_pm_t *ctx);

/**
 * @brief  Sets the fast-charge constant current value, IFAST-CHG.[get]
 * 
 * @param  ctx    read / write interface definitions
 * @retval        -1 = I2C error.
 *                This 6-bit configuration is a transfer function 
 *                with 7.5mA increments starts at 7.5mA and ends at 300mA, with 7.5mA increments. 
 */
int32_t max77658_pm_get_CHG_CC(max77658_pm_t *ctx);

/**
 * @brief  Sets the fast-charge safety timer, tFC.[get]
 * 
 * @param  ctx    read / write interface definitions
 * @retval        -1 = I2C error.
 *                0b00 = Timer disabled 
 *                0b01 = 3 hours 
 *                0b10 = 5 hours 
 *                0b11 = 7 hours 
 */
int32_t max77658_pm_get_T_FAST_CHG(max77658_pm_t *ctx);

/**
 * @brief  Sets IFAST-CHG-JEITA for when the battery is 
 *         either cool or warm as defined by the VCOOL and VWARM temperature thresholds. This 
 *         register is a don't care if the battery temperature is normal.[get]
 * 
 * @param  ctx    read / write interface definitions
 * @retval        -1 = I2C error.
 *                This 6-bit configuration is a transfer function 
 *                with 7.5mA increments starts at 7.5mA and ends at 300mA, with 7.5mA increments. 
 */
int32_t max77658_pm_get_CHG_CC_JEITA(max77658_pm_t *ctx);

/**
 * @brief  Sets fast-charge battery regulation voltage, VFAST-CHG.[get]
 * 
 * @param  ctx    read / write interface definitions
 * @retval        -1 = I2C error.
 *                This 6-bit configuration is a linear transfer 
 *                function that starts at 3.6V and ends at 4.6V, with 25mV increments. 
 */
int32_t max77658_pm_get_CHG_CV(max77658_pm_t *ctx);

/**
 * @brief  Setting this bit places CHGIN in USB suspend mode.[get]
 * 
 * @param  ctx    read / write interface definitions
 * @retval        -1 = I2C error.
 *                0 = CHGIN is not suspended and may draw current from an adapter source. 
 *                1 = CHGIN is suspended and may not draw current from an adapter source. 
 *                   Note: USBS = 1 results in CHGIN_I interrupt AND CHGIN_DTLS[1:0] = 0b00.
 */   
int32_t max77658_pm_get_USBS(max77658_pm_t *ctx);

/**
 * @brief  Forced USB Suspend Mask.[get]
 * 
 * @param  ctx    read / write interface definitions
 * @retval        -1 = I2C error.
 *                FUS (ALT mode of GPIO0) is only active if the FUS_M bit is set to 0. See the GPIO Alternate Mode section for more details.
 */   
int32_t max77658_pm_get_FUS_M(max77658_pm_t *ctx);

/**
 * @brief  Sets the modified VFAST-CHG-JEITA for when the battery is either cool or warm as defined 
 *         by the VCOOL and VWARM temperature thresholds. This register is a don't care if the battery temperature is normal.[get]
 * 
 * @param  ctx    read / write interface definitions
 * @retval        -1 = I2C error.
 *                This 6-bit configuration is a linear transfer 
 *                function that starts at 3.6V and ends at 4.6V, with 25mV increments. 
 */   
int32_t max77658_pm_get_CHG_CV_JEITA(max77658_pm_t *ctx);

/**
 * @brief  VSYS_REG - CHG_CV clamp.[get]
 * 
 * @param  ctx    read / write interface definitions
 * @retval        -1 = I2C error.
 *                By default, the VSYS_REG has to be at least 200mV higher than the programmed 
 *                CHG_CV. If this bit is set (hardware protection is turned off), the software has to 
 *                provide the protection (the SYS voltage has to be 200mV higher than the BATT voltage). 
 *                If the VSYS_REG is lower than CHG_CV+200mV, the charger reduces CHG_CV to satisfy the 200mV requirement.
 */   
int32_t max77658_pm_get_SYS_BAT_PRT(max77658_pm_t *ctx);

/**
 * @brief  Charger restart threshold enable.[get]
 * 
 * @param  ctx    read / write interface definitions
 * @retval        -1 = I2C error.
 */   
int32_t max77658_pm_get_CHR_TH_EN(max77658_pm_t *ctx);

/**
 * @brief  Selects the battery discharge current full-scale current value..[get]
 * 
 * @param  ctx    read / write interface definitions
 * @retval        -1 = I2C error.
 *                0x0 = 8.2mA 
 *                0x1 = 40.5mA 
 *                0x2 = 72.3mA 
 *                0x3 = 103.4mA 
 *                0x4 = 134.1mA 
 *                0x5 = 164.1mA 
 *                0x6 = 193.7mA 
 *                0x7 = 222.7mA 
 *                0x8 = 251.2mA 
 *                0x9 = 279.3mA 
 *                0xA to 0xF = 300.0mA
 */   
int32_t max77658_pm_get_IMON_DISCHG_SCALE(max77658_pm_t *ctx);

/**
 * @brief  Selects the analog channel to connect to AMUX.[get]
 * 
 * @param  ctx    read / write interface definitions
 * @retval        -1 = I2C error.
 *                0b0000 = Multiplexer is disabled and AMUX is high-impedance. 
 *                0b0001 = CHGIN voltage monitor. 
 *                0b0010 = CHGIN current monitor. 
 *                0b0011 = BATT voltage monitor. 
 *                0b0100 = BATT charge current monitor. Valid only while battery charging is happening (CHG = 1). 
 *                0b0101 = BATT discharge current monitor normal measurement. 
 *                0b0110 = BATT discharge current monitor nulling measurement. 
 *                0b0111 = Reserved. 
 *                0b1000 = Reserved. 
 *                0b1001 =  AGND voltage monitor (through 100Ω pulldown resistor). 
 *                0b1010 to 0b1111 = SYS voltage monitor.
 */   
int32_t max77658_pm_get_MUX_SEL(max77658_pm_t *ctx);

/**
 * @brief  Disables the automatic Low-Power Mode for Each SIMO Channel.[get]
 */   
int32_t max77658_pm_get_DIS_LPM(max77658_pm_t *ctx);

/**
 * @brief  SBB2 Inductor Current Limit Offset .[get]
 * 
 * @param  ctx    read / write interface definitions
 * @retval        -1 = I2C error.
 *                0b0 = SBB2 inductor current limit is 1.0A for the 1.0A setting. 
 *                0b1 = SBB2 inductor current limit is 1.5A for the 1.0A setting. 
 */   
int32_t max77658_pm_get_IPK_1P5A(max77658_pm_t *ctx);

/**
 * @brief  SIMO Buck-Boost (all channels) Drive Strength Trim.[get]
 * 
 * @param  ctx    read / write interface definitions
 * @retval        -1 = I2C error.
 *                0b00 = Fastest transition time 
 *                0b01 = A little slower than 0b00 
 *                0b10 = A little slower than 0b01 
 *                0b11 = A little slower than 0b10 
 */   
int32_t max77658_pm_get_DRV_SBB(max77658_pm_t *ctx);

/**
 * @brief  SIMO Buck-Boost Channel 0 Target Output Voltage.[get]
 * 
 * @param  ctx    read / write interface definitions
 * @retval        -1 = I2C error.
 *                This 8-bit configuration is a linear transfer function that starts at 0.5V, ends at 5.5V, with 25mV increments.
 */   
int32_t max77658_pm_get_TV_SBB0(max77658_pm_t *ctx);

/**
 * @brief  Operation Mode of SBB0.[get]
 * 
 * @param  ctx    read / write interface definitions
 * @retval        -1 = I2C error.
 *                0b00 = Automatic 
 *                0b01 = Buck mode 
 *                0b10 = Boost mode 
 *                0b11 = Buck-boost mode
 */   
int32_t max77658_pm_get_OP_MODE(max77658_pm_t *ctx);

/**
 * @brief  SIMO Buck-Boost Channel 0 Peak Current Limit.[get]
 * 
 * @param  ctx    read / write interface definitions
 * @retval        -1 = I2C error.
 *                0b00 = 1.000A 
 *                0b01 = 0.750A 
 *                0b10 = 0.500A 
 *                0b11 = 0.333A 
 */   
int32_t max77658_pm_get_IP_SBB0(max77658_pm_t *ctx);

/**
 * @brief  SIMO Buck-Boost Channel 0 Active-Discharge Enable .[get]
 * 
 * @param  ctx    read / write interface definitions
 * @retval        -1 = I2C error.
 *                0b0 = The active discharge function is disabled. 
 *                      When SBB0 is disabled, its discharge rate is a function of the output capacitance and the external load. 
 *                0b1 = The active discharge function is enabled. 
 *                      When SBB0 is disabled, an internal resistor (RAD_SBB0) is activated from SBB0 to PGND to help the output voltage discharge.
 *                      The output voltage discharge rate is a function of the output capacitance, the external loading, and the internal RAD_SBB0 load.
 */   
int32_t max77658_pm_get_ADE_SBB0(max77658_pm_t *ctx);

/**
 * @brief  Enable Control for SIMO Buck-Boost Channel 0, selecting either an FPS slot the channel 
 *          powers-up and powers-down in or whether the channel is forced on or off.[get]
 * 
 * @param  ctx    read / write interface definitions
 * @retval        -1 = I2C error.
 *                0b000 = FPS slot 0 
 *                0b001 = FPS slot 1 
 *                0b010 = FPS slot 2 
 *                0b011 = FPS slot 3 
 *                0b100 = Off irrespective of FPS 
 *                0b101 = Same as 0b100 
 *                0b110 = On irrespective of FPS 
 *                0b111 = Same as 0b110 
 */   
int32_t max77658_pm_get_EN_SBB0(max77658_pm_t *ctx);

/**
 * @brief  SIMO Buck-Boost Channel 1 Target Output Voltage.[get]
 * 
 * @param  ctx    read / write interface definitions
 * @retval        -1 = I2C error.
 *                This 8-bit configuration is a linear transfer function that starts at 0.5V, ends at 5.5V, with 25mV increments. 
 */   
int32_t max77658_pm_get_TV_SBB1(max77658_pm_t *ctx);

/**
 * @brief  Operation Mode of SBB1.[get]
 * 
 * @param  ctx    read / write interface definitions
 * @retval        -1 = I2C error.
 *                0b00 = Automatic 
 *                0b01 = Buck mode 
 *                0b10 = Boost mode 
 *                0b11 = Buck-boost mode
 */   
int32_t max77658_pm_get_OP_MODE_1(max77658_pm_t *ctx);

/**
 * @brief  SIMO Buck-Boost Channel 1 Active-Discharge Enable.[get]
 * 
 * @param  ctx    read / write interface definitions
 * @retval        -1 = I2C error.
 *                0b0 = The active discharge function is disabled. 
 *                   When SBB1 is disabled, its discharge rate is a function of the output capacitance and the external load. 
 *                0b1 = The active discharge function is enabled. 
 *                   When SBB1 is disabled, an internal resistor (RAD_SBB1) is activated from SBB1 to PGND to help the output voltage discharge. 
 *                   The output voltage discharge rate is a function of the output capacitance, the external loading, and the internal RAD_SBB1 load.
 */   
int32_t max77658_pm_get_ADE_SBB1(max77658_pm_t *ctx);

/**
 * @brief  Enable control for SIMO buck-boost channel 1, selecting either an FPS slot the channel 
 *          powers-up and powers-down in or whether the channel is forced on or off.[get]
 * 
 * @param  ctx    read / write interface definitions
 * @retval        -1 = I2C error.
 *                0b000 = FPS slot 0 
 *                0b001 = FPS slot 1 
 *                0b010 = FPS slot 2 
 *                0b011 = FPS slot 3 
 *                0b100 = Off irrespective of FPS 
 *                0b101 = Same as 0b100 
 *                0b110 = On irrespective of FPS 
 *                0b111 = Same as 0b110
 */   
int32_t max77658_pm_get_EN_SBB1(max77658_pm_t *ctx);

/**
 * @brief  SIMO Buck-Boost Channel 2 Target Output Voltage.[get]
 * 
 * @param  ctx    read / write interface definitions
 * @retval        -1 = I2C error.
 *                This 8-bit configuration is a linear transfer function that starts at 0.5V, ends at 5.5V, with 25mV increments. 
 */   
int32_t max77658_pm_get_TV_SBB2(max77658_pm_t *ctx);

/**
 * @brief  SIMO Buck-Boost Channel 2 Peak Current Limit.[get]
 * 
 * @param  ctx    read / write interface definitions
 * @retval        -1 = I2C error.
 *                0b00 = 1.000A 
 *                0b01 = 0.750A 
 *                0b10 = 0.500A 
 *                0b11 = 0.333A 
 */   
int32_t max77658_pm_get_IP_SBB2(max77658_pm_t *ctx);

/**
 * @brief  SIMO Buck-Boost Channel 2 Active-Discharge Enable.[get]
 * 
 * @param  ctx    read / write interface definitions
 * @retval        -1 = I2C error.
 *                0b0 = The active discharge function is disabled. 
 *                0b1 = The active discharge function is enabled. 
 */   
int32_t max77658_pm_get_ADE_SBB2(max77658_pm_t *ctx);

/**
 * @brief   Enable control for SIMO buck-boost channel 2, selecting either an FPS slot the channel 
 *          powers-up and powers-down in or whether the channel is forced on or off.[get]
 * 
 * @param  ctx    read / write interface definitions
 * @retval        -1 = I2C error.
 *                0b000 = FPS slot 0 
 *                0b001 = FPS slot 1 
 *                0b010 = FPS slot 2 
 *                0b011 = FPS slot 3 
 *                0b100 = Off irrespective of FPS 
 *                0b101 = Same as 0b100 
 *                0b110 = On irrespective of FPS 
 *                0b111 = Same as 0b110
 */   
int32_t max77658_pm_get_EN_SBB2(max77658_pm_t *ctx);

/**
 * @brief  SIMO Buck-Boost Channel 0 Target Output Voltage.[get]
 * 
 * @param  ctx    read / write interface definitions
 * @retval        -1 = I2C error.
 *                This 7-bit configuration is a linear transfer function that starts at 0.5V, ends at 5.5V, with 25mV increments.
 */   
int32_t max77658_pm_get_TV_SBB0_DVS (max77658_pm_t *ctx);

/**
 * @brief  LDO0 Output Voltage Offset.[get]
 * 
 * @param  ctx    read / write interface definitions
 * @retval        -1 = I2C error.
 *                This bit applies a 1.325V offset to the output voltage of the LDO0
 *                0b0 = No Offset 
 *                0b1 = 1.325V Offset 
 */   
int32_t max77658_pm_get_TV_OFS_LDO0(max77658_pm_t *ctx);

/**
 * @brief  LDO0 Target Output Voltage.[get]
 * 
 * @param  ctx    read / write interface definitions
 * @retval        -1 = I2C error.
 *                This 7-bit configuration is a linear transfer function that 
 *                starts at 0.5V, ends at 3.675V, with 25mV increments.
 */   
int32_t max77658_pm_get_TV_LDO0(max77658_pm_t *ctx);

/**
 * @brief  Operation Mode of LDO0.[get]
 * 
 * @param  ctx    read / write interface definitions
 * @retval        -1 = I2C error.
 *                0b0 = Low dropout linear regulator (LDO) mode 
 *                0b1 = Load switch (LSW) mode 
 */   
int32_t max77658_pm_get_LDO0_MD(max77658_pm_t *ctx);

/**
 * @brief   Enable Control for LDO0, selecting either an FPS slot the channel powers-up and 
 *          powers-down in or whether the channel is forced on or off.[get]
 * 
 * @param  ctx    read / write interface definitions
 * @retval        -1 = I2C error.
 *                0b000 = FPS slot 0 
 *                0b001 = FPS slot 1 
 *                0b010 = FPS slot 2 
 *                0b011 = FPS slot 3 
 *                0b100 = Off irrespective of FPS 
 *                0b101 = Same as 0b100 
 *                0b110 = On irrespective of FPS 
 *                0b111 = Same as 0b110
 */   
int32_t max77658_pm_get_EN_LDO0(max77658_pm_t *ctx);

/**
 * @brief  LDO1 Output Voltage Offset. This bit applies 
 *         a 1.325V offset to the output voltage of the LDO1.[get]
 * 
 * @param  ctx    read / write interface definitions
 * @retval        -1 = I2C error.
 *                0b0 = No offset 
 *                0b1 = 1.325V offset 
 */   
int32_t max77658_pm_get_TV_OFS_LDO1(max77658_pm_t *ctx);

/**
 * @brief  LDO1 Target Output Voltage
 *          The tareget output voltage of the LDO would be TV_OFS_LDO1 + TV_LDO1.[get]
 * 
 * @param  ctx    read / write interface definitions
 * @retval        -1 = I2C error.
 *                This 7-bit configuration is a linear transfer function that starts at 0.5V, ends at 3.675V, with 25mV increments.
 */   
int32_t max77658_pm_get_TV_LDO1(max77658_pm_t *ctx);

/**
 * @brief  LDO1 Active-Discharge Enable.[get]
 * 
 * @param  ctx    read / write interface definitions
 * @retval        -1 = I2C error.
 *                0b0 = The active discharge function is disabled. 
 *                0b1 = The active discharge function is enabled. 
 */   
int32_t max77658_pm_get_ADE_LDO1(max77658_pm_t *ctx);

/**
 * @brief   Enable Control for LDO1, selecting either an FPS slot the channel powers-up and powers-
 *          down in or whether the channel is forced on or off.[get]
 * 
 * @param  ctx    read / write interface definitions
 * @retval        -1 = I2C error.
 *                0b000 = FPS slot 0 
 *                0b001 = FPS slot 1 
 *                0b010 = FPS slot 2 
 *                0b011 = FPS slot 3 
 *                0b100 = Off irrespective of FPS 
 *                0b101 = Same as 0b100 
 *                0b110 = On irrespective of FPS 
 *                0b111 = Same as 0b110
 */   
int32_t max77658_pm_get_EN_LDO1(max77658_pm_t *ctx);

/*=======================================================================*/
/*********************** Register writes *********************************/
/*=======================================================================*/

/**
 * @brief  Global Interrupt Mask Register 0.[set]
 */
int32_t max77658_pm_set_INTM_GLBL0(max77658_pm_t *ctx, uint8_t target_val);

/**
 * @brief  Global Interrupt Mask Register 1.[set]
 */
int32_t max77658_pm_set_INTM_GLBL1(max77658_pm_t *ctx, uint8_t target_val);

/**
 * @brief  nEN Internal Pullup Resistor.[set]
 */
int32_t max77658_pm_set_PU_DIS(max77658_pm_t *ctx, uint8_t target_val);

/**
 * @brief  nEN Internal Pullup Resistor.[set]                        
 */
int32_t max77658_pm_set_PU_DIS(max77658_pm_t *ctx, uint8_t target_val);

/**
 * @brief  Sets the Manual Reset Time (tMRST).[set]                           
 */
int32_t max77658_pm_set_T_MRST(max77658_pm_t *ctx, uint8_t target_val);

/**
 * @brief  nEN Input (ON-KEY) Default Configuration Modes.[set]
 */
int32_t max77658_pm_set_nEN_MODE(max77658_pm_t *ctx, uint8_t target_val);

/**
 * @brief  Debounce Timer Enable for the nEN Pin.[set]
 */
int32_t max77658_pm_set_DBEN_nEN(max77658_pm_t *ctx, uint8_t target_val);

/**
 * @brief  Software Reset Functions.[set]
 */
int32_t max77658_pm_set_SFT_CTRL(max77658_pm_t *ctx, uint8_t target_val);

/**
 * @brief  Software Reset Functions.[set]
 */
int32_t max77658_pm_set_SBB_F_SHUTDN(max77658_pm_t *ctx, uint8_t target_val);

/**
 * @brief  Alternate Mode Enable for GPIO0.[get]
 */
int32_t max77658_pm_set_ALT_GPIO0(max77658_pm_t *ctx, uint8_t target_val);

/**
 * @brief  General Purpose Input Debounce Timer Enable for GPI0.[get]
 */
int32_t max77658_pm_set_DBEN_GPI_0(max77658_pm_t *ctx, uint8_t target_val);

/**
 * @brief  General Purpose Output Data Output for GPO0.[set]
 */
int32_t max77658_pm_set_DO_0(max77658_pm_t *ctx, uint8_t target_val);

/**
 * @brief  General Purpose Output Driver Type for GPO0.[set]
 */
int32_t max77658_pm_set_DRV_0(max77658_pm_t *ctx, uint8_t target_val);

/**
 * @brief  GPIO Direction for GPIO0.[get]
 */
int32_t max77658_pm_set_DIR_0(max77658_pm_t *ctx, uint8_t target_val);

/**
 * @brief  Alternate Mode Enable for GPIO1.[set]
 */
int32_t max77658_pm_set_ALT_GPIO1(max77658_pm_t *ctx, uint8_t target_val);

/**
 * @brief  General Purpose Input Debounce Timer Enable for GPI0.[set]
 */
int32_t max77658_pm_set_DBEN_GPI_1(max77658_pm_t *ctx, uint8_t target_val);

/**
 * @brief  General Purpose Output Data Output for GPO0.[get]
 */
int32_t max77658_pm_set_DO_1(max77658_pm_t *ctx, uint8_t target_val);

/**
 * @brief  General Purpose Output Driver Type for GPO0.[set]
 */
int32_t max77658_pm_set_DRV_1(max77658_pm_t *ctx, uint8_t target_val);

/**
 * @brief  GPIO Direction for GPIO0.[set]
 */
int32_t max77658_pm_set_DIR_1(max77658_pm_t *ctx, uint8_t target_val);

/**
 * @brief  Alternate Mode Enable for GPIO1.[get]
 */
int32_t max77658_pm_set_ALT_GPIO2(max77658_pm_t *ctx, uint8_t target_val);

/**
 * @brief  General Purpose Input Debounce Timer Enable for GPI2.[get]
 */
int32_t max77658_pm_set_DBEN_GPI_2(max77658_pm_t *ctx, uint8_t target_val);

/**
 * @brief  General Purpose Output Data Output for GPO0.[get]
 */
int32_t max77658_pm_set_DO_2(max77658_pm_t *ctx, uint8_t target_val);

/**
 * @brief  General Purpose Output Driver Type for GPO0 .[get]
 */
int32_t max77658_pm_set_DRV_2(max77658_pm_t *ctx, uint8_t target_val);

/**
 * @brief  GPIO Direction for GPIO0.[get]
 */
int32_t max77658_pm_set_DIR_2(max77658_pm_t *ctx, uint8_t target_val);

/**
 * @brief  Watchdog Timer Period. Sets tWD.[get]
 */
int32_t max77658_pm_set_WDT_PER(max77658_pm_t *ctx, uint8_t target_val);

/**
 * @brief  Watchdog Timer Expired Action.[get]
 */
int32_t max77658_pm_set_WDT_MODE(max77658_pm_t *ctx, uint8_t target_val);

/**
 * @brief  Watchdog Timer Clear Control.[get]
 */
int32_t max77658_pm_set_WDT_CLR(max77658_pm_t *ctx, uint8_t target_val);

/**
 * @brief  Watchdog Timer Enable. Write protected depending on WDT_LOCK.[get]
 */
int32_t max77658_pm_set_WDT_EN(max77658_pm_t *ctx, uint8_t target_val);

/**************************************************************/
/************************CHARGER*******************************/
/**************************************************************/

/**
 * @brief  Global Interrupt Mask Register.[get]
 */
int32_t max77658_pm_set_INT_M_CHG(max77658_pm_t *ctx, uint8_t target_val);

/**
 * @brief  Sets the THOT JEITA Temperature Threshold.[get]
 */
int32_t max77658_pm_set_THM_HOT(max77658_pm_t *ctx, uint8_t target_val);

/**
 * @brief  Sets the TWARM JEITA Temperature Threshold.[get]
 */
int32_t max77658_pm_set_THM_WARM(max77658_pm_t *ctx, uint8_t target_val);

/**
 * @brief  Sets the TCOOL JEITA Temperature Threshold.[get]
 */
int32_t max77658_pm_set_THM_COOL(max77658_pm_t *ctx, uint8_t target_val);

/**
 * @brief  Sets the TCOOL JEITA Temperature Threshold.[get]
 */
int32_t max77658_pm_set_THM_COLD(max77658_pm_t *ctx, uint8_t target_val);

/**
 * @brief  Minimum CHGIN Regulation Voltage (VCHGIN-MIN).[get]
 */
int32_t max77658_pm_set_VCHGIN_MIN(max77658_pm_t *ctx, uint8_t target_val);

/**
 * @brief  CHGIN Input Current Limit (ICHGIN-LIM).[get]
 */
int32_t max77658_pm_set_ICHGIN_LIM(max77658_pm_t *ctx, uint8_t target_val);

/**
 * @brief  Sets the prequalification charge current (IPQ) as a percentage of IFAST-CHG..[get]
 */
int32_t max77658_pm_set_I_PQ(max77658_pm_t *ctx, uint8_t target_val);

/**
 * @brief  Sets the prequalification charge current (IPQ) as a percentage of IFAST-CHG..[get]
 */
int32_t max77658_pm_set_CHG_EN(max77658_pm_t *ctx, uint8_t target_val);

/**
 * @brief  Battery Prequalification Voltage Threshold (VPQ).[get]
 */
int32_t max77658_pm_set_CHG_PQ(max77658_pm_t *ctx, uint8_t target_val);

/**
 * @brief  Charger Termination Current (ITERM). I_TERM[1:0] sets the charger termination current 
 *          as a percentage of the fast-charge current IFAST-CHG.[get]
 */
int32_t max77658_pm_set_I_TERM(max77658_pm_t *ctx, uint8_t target_val);

/**
 * @brief  Top-Off Timer Value (tTO).[get]
 */
int32_t max77658_pm_set_T_TOPOFF(max77658_pm_t *ctx, uint8_t target_val);

/**
 * @brief  Sets the die junction temperature regulation point, TJ-REG.[get]
 */
int32_t max77658_pm_set_TJ_REG(max77658_pm_t *ctx, uint8_t target_val);

/**
 * @brief  System Voltage Regulation (VSYS-REG).[get]
 */
int32_t max77658_pm_set_VSYS_REG(max77658_pm_t *ctx, uint8_t target_val);

/**
 * @brief  Sets the fast-charge constant current value, IFAST-CHG.[get]
 */
int32_t max77658_pm_set_CHG_CC(max77658_pm_t *ctx, uint8_t target_val);

/**
 * @brief  Sets the fast-charge safety timer, tFC.[get]
 */
int32_t max77658_pm_set_T_FAST_CHG(max77658_pm_t *ctx, uint8_t target_val);

/**
 * @brief  Sets IFAST-CHG-JEITA for when the battery is 
 *         either cool or warm as defined by the VCOOL and VWARM temperature thresholds. This 
 *         register is a don't care if the battery temperature is normal.[get]
 */
int32_t max77658_pm_set_CHG_CC_JEITA(max77658_pm_t *ctx, uint8_t target_val);

/**
 * @brief  Sets fast-charge battery regulation voltage, VFAST-CHG.[get]
 */
int32_t max77658_pm_set_CHG_CV(max77658_pm_t *ctx, uint8_t target_val);

/**
 * @brief  Setting this bit places CHGIN in USB suspend mode.[get]
 */   
int32_t max77658_pm_set_USBS(max77658_pm_t *ctx, uint8_t target_val);

/**
 * @brief  Forced USB Suspend Mask.[get]
 */   
int32_t max77658_pm_set_FUS_M(max77658_pm_t *ctx, uint8_t target_val);

/**
 * @brief  Sets the modified VFAST-CHG-JEITA for when the battery is either cool or warm as defined 
 *         by the VCOOL and VWARM temperature thresholds. This register is a don't care if the battery temperature is normal.[get]
 */   
int32_t max77658_pm_set_CHG_CV_JEITA(max77658_pm_t *ctx, uint8_t target_val);

/**
 * @brief  VSYS_REG - CHG_CV clamp.[get]
 */   
int32_t max77658_pm_set_SYS_BAT_PRT(max77658_pm_t *ctx, uint8_t target_val);

/**
 * @brief  Charger restart threshold enable.[get]
 */   
int32_t max77658_pm_set_CHR_TH_EN(max77658_pm_t *ctx, uint8_t target_val);

/**
 * @brief  Selects the battery discharge current full-scale current value..[get]
 */   
int32_t max77658_pm_set_IMON_DISCHG_SCALE(max77658_pm_t *ctx, uint8_t target_val);

/**
 * @brief  Selects the analog channel to connect to AMUX.[get]
 */   
int32_t max77658_pm_set_MUX_SEL(max77658_pm_t *ctx, uint8_t target_val);

/**
 * @brief  Disables the automatic Low-Power Mode for Each SIMO Channel.[get]
 */   
int32_t max77658_pm_set_DIS_LPM(max77658_pm_t *ctx, uint8_t target_val);

/**
 * @brief  SBB2 Inductor Current Limit Offset .[get]
 */   
int32_t max77658_pm_set_IPK_1P5A(max77658_pm_t *ctx, uint8_t target_val);

/**
 * @brief  SIMO Buck-Boost (all channels) Drive Strength Trim.[get]
 */   
int32_t max77658_pm_set_DRV_SBB(max77658_pm_t *ctx, uint8_t target_val);

/**
 * @brief  SIMO Buck-Boost Channel 0 Target Output Voltage.[get]
 */   
int32_t max77658_pm_set_TV_SBB0(max77658_pm_t *ctx, uint8_t target_val);

/**
 * @brief  Operation Mode of SBB0.[get]
 */   
int32_t max77658_pm_set_OP_MODE(max77658_pm_t *ctx, uint8_t target_val);

/**
 * @brief  SIMO Buck-Boost Channel 0 Peak Current Limit.[get]
 */   
int32_t max77658_pm_set_IP_SBB0(max77658_pm_t *ctx, uint8_t target_val);

/**
 * @brief  SIMO Buck-Boost Channel 0 Active-Discharge Enable .[get]
 */   
int32_t max77658_pm_set_ADE_SBB0(max77658_pm_t *ctx, uint8_t target_val);

/**
 * @brief  Enable Control for SIMO Buck-Boost Channel 0, selecting either an FPS slot the channel 
 *          powers-up and powers-down in or whether the channel is forced on or off.[get]
 */   
int32_t max77658_pm_set_EN_SBB0(max77658_pm_t *ctx, uint8_t target_val);

/**
 * @brief  SIMO Buck-Boost Channel 1 Target Output Voltage.[get]
 */   
int32_t max77658_pm_set_TV_SBB1(max77658_pm_t *ctx, uint8_t target_val);

/**
 * @brief  Operation Mode of SBB1.[get]
 */   
int32_t max77658_pm_set_OP_MODE_1(max77658_pm_t *ctx, uint8_t target_val);

/**
 * @brief  SIMO Buck-Boost Channel 1 Peak Current Limit.[get]
 */   
int32_t max77658_pm_set_IP_SBB1(max77658_pm_t *ctx, uint8_t target_val);

/**
 * @brief  SIMO Buck-Boost Channel 1 Active-Discharge Enable.[get]
 */   
int32_t max77658_pm_set_ADE_SBB1(max77658_pm_t *ctx, uint8_t target_val);

/**
 * @brief  Enable control for SIMO buck-boost channel 1, selecting either an FPS slot the channel 
 *          powers-up and powers-down in or whether the channel is forced on or off.[get]
 */   
int32_t max77658_pm_set_EN_SBB1(max77658_pm_t *ctx, uint8_t target_val);

/**
 * @brief  SIMO Buck-Boost Channel 2 Target Output Voltage.[get]
 */   
int32_t max77658_pm_set_TV_SBB2(max77658_pm_t *ctx, uint8_t target_val);

/**
 * @brief  Operation Mode of SBB2 .[get]
 */   
int32_t max77658_pm_set_OP_MODE_2(max77658_pm_t *ctx, uint8_t target_val);

/**
 * @brief  SIMO Buck-Boost Channel 2 Peak Current Limit.[get]
 */   
int32_t max77658_pm_set_IP_SBB2(max77658_pm_t *ctx, uint8_t target_val);

/**
 * @brief  SIMO Buck-Boost Channel 2 Active-Discharge Enable.[get]
 */   
int32_t max77658_pm_set_ADE_SBB2(max77658_pm_t *ctx, uint8_t target_val);

/**
 * @brief   Enable control for SIMO buck-boost channel 2, selecting either an FPS slot the channel 
 *          powers-up and powers-down in or whether the channel is forced on or off.[get]
 */   
int32_t max77658_pm_set_EN_SBB2(max77658_pm_t *ctx, uint8_t target_val);

/**
 * @brief  SIMO Buck-Boost Channel 0 Target Output Voltage.[get]
 */   
int32_t max77658_pm_set_TV_SBB0_DVS(max77658_pm_t *ctx, uint8_t target_val);

/**
 * @brief  LDO0 Output Voltage Offset.[get]
 */   
int32_t max77658_pm_set_TV_OFS_LDO0(max77658_pm_t *ctx, uint8_t target_val);

/**
 * @brief  LDO0 Target Output Voltage.[get]
 */   
int32_t max77658_pm_set_TV_LDO0(max77658_pm_t *ctx, uint8_t target_val);

/**
 * @brief  Operation Mode of LDO0.[get]
 */   
int32_t max77658_pm_set_LDO0_MD(max77658_pm_t *ctx, uint8_t target_val);

/**
 * @brief  LDO0 Active-Discharge Enable.[get]
 */   
int32_t max77658_pm_set_ADE_LDO0(max77658_pm_t *ctx, uint8_t target_val);

/**
 * @brief   Enable Control for LDO0, selecting either an FPS slot the channel powers-up and 
 *          powers-down in or whether the channel is forced on or off.[get]
 */   
int32_t max77658_pm_set_EN_LDO0(max77658_pm_t *ctx, uint8_t target_val);

/**
 * @brief  LDO1 Output Voltage Offset. This bit applies 
 *         a 1.325V offset to the output voltage of the LDO1.[get]
 */   
int32_t max77658_pm_set_TV_OFS_LDO1(max77658_pm_t *ctx, uint8_t target_val);

/**
 * @brief  LDO1 Target Output Voltage
 *          The tareget output voltage of the LDO would be TV_OFS_LDO1 + TV_LDO1.[get]
 */ 
int32_t max77658_pm_set_TV_LDO1(max77658_pm_t *ctx, uint8_t target_val);

/**
 * @brief  Operation Mode of LDO.[get]
 */   
int32_t max77658_pm_set_LDO1_MD(max77658_pm_t *ctx, uint8_t target_val);

/**
 * @brief  LDO1 Active-Discharge Enable.[get]
 */   
int32_t max77658_pm_set_ADE_LDO1(max77658_pm_t *ctx, uint8_t target_val);

/**
 * @brief   Enable Control for LDO1, selecting either an FPS slot the channel powers-up and powers-
 *          down in or whether the channel is forced on or off.[get]
 */   
int32_t max77658_pm_set_EN_LDO1(max77658_pm_t *ctx, uint8_t target_val);


#endif /* MAIN_COMPONENT_MAX77658_PM_H_ */

