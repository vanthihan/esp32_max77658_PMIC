/*
 * max77658.h
 *
 *  Created on: Nov 9, 2021
 *      Author: kai
 */

#ifndef MAIN_COMPONENT_PMIC_MAX77658_FG_H_
#define MAIN_COMPONENT_PMIC_MAX77658_FG_H_

// Include
#include <stdint.h>
#include "max77658_fg_types.h"

/* STATUS register bits */
#define MAX17055_STATUS_BST             (1 << 3)
#define MAX17055_STATUS_POR             (1 << 1)

/// Model loading options
#define MODEL_LOADING_OPTION1           1 //EZ Config

/*
 *
 *  Battery Recommendations based on sense Resistor Values (MAX32620FTHR comes with a 5 mOhm rsense resistor)\n
 *
 * | BATTERY FULL CAPACITY(mAh) | Sense Resistor | Current Register Resolution(uA) | Current Register Range(A) | Capacity Resolution(mAh) |\n
 * |----------------------------|----------------|---------------------------------|---------------------------|--------------------------|\n
 * | 1600 - 24576               | 5              | 312.5                           | +/- 10.24                 | 1                        |\n
 * | 8000 - 12288               | 10             | 156.25                          | +/- 5.12                  | 0.5                      |\n
 * | 400-6144                   | 20             | 78.125                          | +/- 2.56                  | 0.25                     |\n
 * | 160-2458                   | 50             | 31.25                           | +/- 1.024                 | 0.1                      |\n
 * | 40-614                     | 200            | 7.8125                          | +/- 0.256                 | 0.025                    |\n
 */

   /** @addtogroup  Interfaces_Functions
    * @brief       This section provide a set of functions used to read and
    *              write a generic register of the device.
    *              MANDATORY: return 0 -> no Error.*
    */
typedef int32_t (*dev_read_ptr)(uint8_t, uint8_t, uint8_t *, uint32_t);
typedef int32_t (*dev_write_ptr)(uint8_t, uint8_t, uint8_t *, uint32_t);

typedef struct
{
   uint8_t device_address;
   dev_read_ptr   read_reg;
   dev_write_ptr  write_reg;
   platform_data *pdata;
}max77658_fg_t;

/*
 * Helper function Read generic device register
 */
//int32_t readReg(Registers_e reg_addr, uint16_t &value);
int32_t max77658_fg_read_reg(max77658_fg_t *ctx, uint8_t reg_addr, uint16_t *value);

/*
 * Helper function write generic device register
 */
//int writeReg(const Registers_e reg_addr, uint16_t reg_data);
int32_t max77658_fg_write_reg(max77658_fg_t *ctx, uint8_t reg_addr, uint16_t reg_data);

/**
 * @brief      Poll Flag clear Function.
 */
int max77658_fg_poll_flag_clear(max77658_fg_t *ctx, uint8_t reg_addr, int mask, int timeout);

/**
 * @brief      Check POR function
 */
int max77658_fg_check_POR_func(max77658_fg_t *ctx);

/**
 * @brief        clear POR bit function
 */
int max77658_fg_clear_POR_bit(max77658_fg_t *ctx);

/**
 * @brief       Write and Verify a MAX17055 register
 */
int max77658_fg_write_and_verify_reg(max77658_fg_t *ctx, uint8_t reg_addr, uint16_t write_data);

/**
 * @brief       Initialization Function for MAX17055.
 */
int max77658_fg_init(max77658_fg_t *ctx);

/**
 * @brief       Get Temperature Function from the MAX17055 TEMP register.
 */
int max77658_fg_get_temperature();

/**
 * @brief       Forced Exit Hibernate Mode Function for MAX17055
 */
uint16_t max77658_fg_forcedExitHiberMode(max77658_fg_t *ctx);// Hibernate spelling

/**
 * @brief       EZ Config function
 */
uint16_t max77658_fg_config_option_1(max77658_fg_t *ctx);

/**
 * @brief       Config function option 2
 */
int32_t max77658_fg_config_option_2(max77658_fg_t *ctx);

/**
 * @brief       Config function option 3
 */
int32_t max77658_fg_config_option_3(max77658_fg_t *ctx);

/**
 * @brief       Get reported Battery Capacity Function from MAX17055 Fuel Gauge
 */
int max77658_fg_get_battCAP(max77658_fg_t *ctx);

/**
 * @brief       Get reported State Of Charge(SOC) Function from MAX17055 Fuel Gauge
 */
int max77658_fg_get_SOC(max77658_fg_t *ctx);

/**
 * @brief       Get at rate Average State Of Charge(SOC) Function from MAX17055 Fuel Gauge.
 */
int max77658_fg_get_atAvSOC(max77658_fg_t *ctx);

/**
 * @brief       Get the Time to Empty(TTE) Function form MAX17055 Fuel Gauge.
 */
float max77658_fg_get_TTE(max77658_fg_t *ctx);

/**
 * @brief       Get the at Time to Empty(atTTE) value Function for MAX17055 Fuel Gauge.
 */
float max77658_fg_get_atTTE(max77658_fg_t *ctx);

/**
 * @brief        Get mix State Of Charge(SOC) Function for MAX17055 Fuel Gauge.
 */
int max77658_fg_get_mixSOC(max77658_fg_t *ctx);

/**
 * @brief      Get the Time to Full(TTE) values Function for MAX17055 Fuel Gauge.
 */
float max77658_fg_get_TTF(max77658_fg_t *ctx);

/**
 * @brief       Get voltage of the cell Function for MAX17055 Fuel Gauge.
 */
int max77658_fg_get_Vcell(max77658_fg_t *ctx);

/**
 * @brief       Get average voltage of the cell Function for MAX17055 Fuel Gauge.
 */
int max77658_fg_get_avgVcell(max77658_fg_t *ctx);

/**
 * @brief       Get current Function for MAX17055 Fuel Gauge.
 */
float max77658_fg_get_Current(max77658_fg_t *ctx);

/**
 * @brief       Get average current Function for MAX17055 Fuel Gauge.
 */
float max77658_fg_get_AvgCurrent(max77658_fg_t *ctx);

/**
 * @brief        lsb_to_uvolts Conversion Function
 */
int max77658_fg_lsb_to_uvolts(uint16_t lsb);

/**
 * @brief        raw_current_to_uamp Conversion Function
 */
float max77658_fg_raw_current_to_uamps(uint32_t curr, int rsense_value);

/**
 * @brief        raw_cap_to_uAh Conversion Function
 */
int max77658_fg_raw_cap_to_uAh(uint32_t raw_cap, int rsense_value);

/**
 * @brief        Save Learned Parameters Function for battery Fuel Gauge model.
 */
int max77658_fg_save_Params(max77658_fg_t *ctx, saved_FG_params_t FG_params);

/**
 * @brief        Restore Parameters Function for battery Fuel Gauge model.
 */
int max77658_fg_restore_Params(max77658_fg_t *ctx, saved_FG_params_t FG_params);

/**
 * @brief        Function to Save Average Current to At Rate register.
 */
int max77658_fg_avCurr_2_atRate();

/**
 * @brief       Get specified register info Function for MAX17055 Fuel Gauge.
 */
int16_t max77658_fg_get_regInfo(max77658_fg_t *ctx, uint8_t reg_addr);


#endif /* MAIN_COMPONENT_PMIC_MAX77658_FG_H_ */
