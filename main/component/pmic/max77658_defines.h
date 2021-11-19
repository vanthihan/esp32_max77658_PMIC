/*
 * max77658_defines.h
 *
 *  Created on: Oct 31, 2021
 *      Author: kai
 */

#ifndef MAIN_COMPONENT_PMIC_MAX77658_DEFINES_H_
#define MAIN_COMPONENT_PMIC_MAX77658_DEFINES_H_

/*
 * Global
 */
#define MAX77658_INT_GLBL0    0x00U
#define MAX77658_INT_GLBL1    0x04U
#define MAX77658_ERCFLAG      0x05U
#define MAX77658_STAT_GLBL    0x06U
#define MAX77658_INTM_GLBL0   0x08U
#define MAX77658_INTM_GLBL1   0x09U
#define MAX77658_CNFG_GLBL    0x10U
#define MAX77658_CNFG_GPIO0   0x11U
#define MAX77658_CNFG_GPIO1   0x12U
#define MAX77658_CNFG_GPIO2   0x13U
#define MAX77658_CID          0x14U
#define MAX77658_CNFG_WDT     0x17U

/*
 * Charger
 */
#define MAX77658_INT_CHG     0x01U
#define MAX77658_STAT_CHG_A  0x02U
#define MAX77658_STAT_CHG_B  0x03U
#define MAX77658_INT_M_CHG   0x07U
#define MAX77658_CNFG_CHG_A  0x20U
#define MAX77658_CNFG_CHG_B  0x21U
#define MAX77658_CNFG_CHG_C  0x22U
#define MAX77658_CNFG_CHG_D  0x23U
#define MAX77658_CNFG_CHG_E  0x24U
#define MAX77658_CNFG_CHG_F  0x25U
#define MAX77658_CNFG_CHG_G  0x26U
#define MAX77658_CNFG_CHG_H  0x27U
#define MAX77658_CNFG_CHG_I  0x28U

/*
 * SBB
 */
#define MAX77658_CNFG_SBB_TOP        0x38U
#define MAX77658_CNFG_SBB0_A         0x39U
#define MAX77658_CNFG_SBB0_B         0x3AU
#define MAX77658_CNFG_SBB1_A         0x3BU
#define MAX77658_CNFG_SBB1_B         0x3CU
#define MAX77658_CNFG_SBB2_A         0x3DU
#define MAX77658_CNFG_SBB2_B         0x3EU
#define MAX77658_CNFG_DVS_SBB0_A     0x3FU

/*
 * LDO
 */
#define MAX77658_CNFG_LDO0_A  0x48U
#define MAX77658_CNFG_LDO0_B  0x49U
#define MAX77658_CNFG_LDO1_A  0x4AU
#define MAX77658_CNFG_LDO1_B  0x4BU

/*
 * Fuel Gauge
 */
//Status and Configuration Registers
#define MAX77658_FG_Status       0x00U
#define MAX77658_FG_VAlrtTh      0x01U
#define MAX77658_FG_TAlrtTh      0x02U
#define MAX77658_FG_SAlrtTh      0x03U
#define MAX77658_FG_FullSOCThr   0x13U
#define MAX77658_FG_DesignCap    0x18U
#define MAX77658_FG_Config       0x1DU
#define MAX77658_FG_IChgTerm     0x1EU
#define MAX77658_FG_DevName      0x21U
#define MAX77658_FG_LearnCfg     0x28U
#define MAX77658_FG_FilterCfg    0x29U
#define MAX77658_FG_VEmpty       0x3AU
#define MAX77658_FG_Power        0xB1U
#define MAX77658_FG_AvgPower     0xB3U
#define MAX77658_FG_IAlrtTh      0xB4U
#define MAX77658_FG_Config2      0xBBU

/*
 * Fuel Gauge - Measurement Registers
 */
#define MAX77658_FG_MR_Temp       0x08U
#define MAX77658_FG_MR_Vcell      0x09U
#define MAX77658_FG_MR_Current    0x0AU
#define MAX77658_FG_MR_AvgCurrent 0x0BU
#define MAX77658_FG_MR_AvgTA      0x16U
#define MAX77658_FG_MR_AvgVCell   0x19U
#define MAX77658_FG_MR_MaxMinTemp 0x1AU
#define MAX77658_FG_MR_MaxMinVolt 0x1BU
#define MAX77658_FG_MR_MaxMinCurr 0x1CU
#define MAX77658_FG_MR_AIN0       0x27U
#define MAX77658_FG_MR_Timer      0x3EU
#define MAX77658_FG_MR_TimerH     0xBEU

/*
 * Fuel Gauge -ModelGauge m5 Output Registers
 */
#define MAX77658_FG_M5_OUT_RepCap      0x05U
#define MAX77658_FG_M5_OUT_RepSOC      0x06U
#define MAX77658_FG_M5_OUT_AvSOC       0x0EU
#define MAX77658_FG_M5_OUT_FullCapRep  0x10U
#define MAX77658_FG_M5_OUT_TTE         0x11U
#define MAX77658_FG_M5_OUT_RCell       0x14U
#define MAX77658_FG_M5_OUT_Cycles      0x17U
#define MAX77658_FG_M5_OUT_AvCap       0x1FU
#define MAX77658_FG_M5_OUT_TTF         0x20U



#endif /* MAIN_COMPONENT_PMIC_MAX77658_DEFINES_H_ */
