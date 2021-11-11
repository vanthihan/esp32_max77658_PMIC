/*
 * max77658_pm_types.h
 *
 *  Created on: Nov 9, 2021
 *      Author: kai
 */

#ifndef MAIN_COMPONENT_PMIC_MAX77658_PM_TYPES_H_
#define MAIN_COMPONENT_PMIC_MAX77658_PM_TYPES_H_

//***** Begin MAX77650 Register Definitions *****
#define MAX77650_CNFG_GLBL_ADDR     0x10     //Global Configuration Register; Reset Value OTP
#define MAX77650_INT_GLBL_ADDR      0x00      //Interrupt; Reset Value 0x00
#define MAX77650_INTM_GLBL_ADDR     0x06     //Interrupt Mask; Reset Value 0xFF
#define MAX77650_STAT_GLBL_ADDR     0x05     //Global Status Register; Reset Value OTP
#define MAX77650_ERCFLAG_ADDR       0x04       //Flags; Reset Value 0x00
#define MAX77650_CNFG_GPIO_ADDR     0x12     //GPIO Configuration Register; Reset Value 0x01
#define MAX77650_CID_ADDR           0x11           //Chip ID Register; Reset Value OTP; Read only
#define MAX77650_INT_CHG_ADDR       0x01       //Charger Interrupt Register; Reset Value 0x00; RC
#define MAX77650_INT_M_CHG_ADDR     0x07     //Charger Interrupt Mask Register; Reset Value 0xFF; Read/Write
#define MAX77650_STAT_CHG_A_ADDR    0x02    //Charger Status Register A; Reset Value 0x00; Read only
#define MAX77650_STAT_CHG_B_ADDR    0x03    //Charger Status Register B; Reset Value 0x00; Read only
#define MAX77650_CNFG_CHG_A_ADDR    0x018   //Charger Configuration Register A; Reset Value 0x0F; Read/Write
#define MAX77650_CNFG_CHG_B_ADDR    0x019   //Charger Configuration Register B; Reset Value OTP; Read/Write
#define MAX77650_CNFG_CHG_C_ADDR    0x01A   //Charger Configuration Register C; Reset Value 0xF8; Read/Write
#define MAX77650_CNFG_CHG_D_ADDR    0x01B   //Charger Configuration Register D; Reset Value 0x10; Read/Write
#define MAX77650_CNFG_CHG_E_ADDR    0x01C   //Charger Configuration Register E; Reset Value 0x05; Read/Write
#define MAX77650_CNFG_CHG_F_ADDR    0x01D   //Charger Configuration Register F; Reset Value 0x04; Read/Write
#define MAX77650_CNFG_CHG_G_ADDR    0x01E   //Charger Configuration Register G; Reset Value 0x00; Read/Write
#define MAX77650_CNFG_CHG_H_ADDR    0x01F   //Charger Configuration Register H; Reset Value 0x00; Read/Write
#define MAX77650_CNFG_CHG_I_ADDR    0x020   //Charger Configuration Register I; Reset Value 0xF0; Read/Write
#define MAX77650_CNFG_LDO_A_ADDR    0x38    //LDO Configuration Register A; Reset Value OTP; Read/Write
#define MAX77650_CNFG_LDO_B_ADDR    0x39    //LDO Configuration Register B; Reset Value OTP; Read/Write
#define MAX77650_CNFG_SBB_TOP_ADDR  0x28  //SIMO Buck-Boost Configuration Register; Reset Value OTP; Read/Write
#define MAX77650_CNFG_SBB0_A_ADDR   0x29   //SIMO Buck-Boost 0 Configuration Register A; Reset Value OTP; Read/Write
#define MAX77650_CNFG_SBB0_B_ADDR   0x2A   //SIMO Buck-Boost 0 Configuration Register B; Reset Value OTP; Read/Write
#define MAX77650_CNFG_SBB1_A_ADDR   0x2B   //SIMO Buck-Boost 1 Configuration Register A; Reset Value OTP; Read/Write
#define MAX77650_CNFG_SBB1_B_ADDR   0x2C   //SIMO Buck-Boost 1 Configuration Register B; Reset Value OTP; Read/Write
#define MAX77650_CNFG_SBB2_A_ADDR   0x2D   //SIMO Buck-Boost 2 Configuration Register A; Reset Value OTP; Read/Write
#define MAX77650_CNFG_SBB2_B_ADDR   0x2E   //SIMO Buck-Boost 2 Configuration Register B; Reset Value OTP; Read/Write
#define MAX77650_CNFG_LED0_A_ADDR   0x40   //LED 0 Configuration Register A; Reset Value 0x04; Read/Write
#define MAX77650_CNFG_LED0_B_ADDR   0x43   //LED 0 Configuration Register B; Reset Value 0x0F; Read/Write
#define MAX77650_CNFG_LED1_A_ADDR   0x41   //LED 1 Configuration Register A; Reset Value 0x04; Read/Write
#define MAX77650_CNFG_LED1_B_ADDR   0x44   //LED 1 Configuration Register B; Reset Value 0x0F; Read/Write
#define MAX77650_CNFG_LED2_A_ADDR   0x42   //LED 2 Configuration Register A; Reset Value 0x04; Read/Write
#define MAX77650_CNFG_LED2_B_ADDR   0x45   //LED 2 Configuration Register A; Reset Value 0x0F; Read/Write
#define MAX77650_CNFG_LED_TOP_ADDR  0x46  //LED Configuration Register; Reset Value 0x0D; Read/Write
//***** End MAX77650 Register Definitions *****

#endif /* MAIN_COMPONENT_PMIC_MAX77658_PM_TYPES_H_ */
