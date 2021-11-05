/*
 * max77658_types.h
 *
 *  Created on: Oct 31, 2021
 *      Author: kai
 */

#ifndef MAIN_COMPONENT_PMIC_MAX77658_TYPES_H_
#define MAIN_COMPONENT_PMIC_MAX77658_TYPES_H_

/* Includes ----------------------------------------------------------- */
#include <stdint.h>
#include "max77658_defines.h"

/* Public defines ----------------------------------------------------- */
#define MAX1726X_TABLE_SIZE             32
#define MAX1726X_TABLE_SIZE_IN_BYTES    (2 * MAX1726X_TABLE_SIZE)

/* Model loading options */
#define MODEL_LOADING_OPTION1           1
#define MODEL_LOADING_OPTION2           2
#define MODEL_LOADING_OPTION3           3

/* Model lock/unlock */
#define MODEL_UNLOCK1   0X0059
#define MODEL_UNLOCK2   0X00C4
#define MODEL_LOCK1     0X0000
#define MODEL_LOCK2     0X0000

#define MODEL_SCALING        1

/* Public enumerate/structure ----------------------------------------- */

struct max1726x_platform_data{
    uint16_t designcap;
    uint16_t ichgterm;
    uint16_t vempty;
    int32_t vcharge;

    uint16_t learncfg;
    uint16_t relaxcfg;
    uint16_t config;
    uint16_t config2;
    uint16_t fullsocthr;
    uint16_t tgain;
    uint16_t toff;
    uint16_t curve;
    uint16_t rcomp0;
    uint16_t tempco;
    uint16_t qrtable00;
    uint16_t qrtable10;
    uint16_t qrtable20;
    uint16_t qrtable30;
    uint16_t cvhalftime;
    uint16_t cvmixcap;

    uint16_t dpacc;
    uint16_t modelcfg;

    uint16_t model_data[MAX1726X_TABLE_SIZE];
    uint16_t model_rcomp_seg;
    int32_t (*get_charging_status)(void);
    int32_t model_option;

    /*
     * rsense in miliOhms.
     * default 10 (if rsense = 0) as it is the recommended value by
     * the datasheet although it can be changed by board designers.
     */
    uint32_t rsense;
    int32_t volt_min;   /* in mV */
    int32_t volt_max;   /* in mV */
    int32_t temp_min;   /* in DegreC */
    int32_t temp_max;   /* in DegreeC */
    int32_t soc_max;    /* in percent */
    int32_t soc_min;    /* in percent */
    int32_t curr_max;   /* in mA */
    int32_t curr_min;   /* in mA */
};

enum max1726x_register{
    MAX1726X_STATUS_REG                 = 0x00,
    MAX1726X_VALRTTH_REG                = 0x01,
    MAX1726X_TALRTTH_REG                = 0x02,
    MAX1726X_SALRTTH_REG                = 0x03,
    MAX1726X_REPCAP_REG                 = 0x05,
    MAX1726X_REPSOC_REG                 = 0x06,
    MAX1726X_TEMP_REG                   = 0x08,
    MAX1726X_VCELL_REG                  = 0x09,
    MAX1726X_CURRENT_REG                = 0x0A,
    MAX1726X_AVGCURRENT_REG             = 0x0B,
    MAX1726X_REMCAP_REG                 = 0x0F,

    MAX1726X_FULLCAPREP_REG             = 0x10,
    MAX1726X_TTE_REG                    = 0X11,
    MAX1726X_QRTABLE00_REG              = 0x12,
    MAX1726X_FULLSOCTHR_REG             = 0x13,
    MAX1726X_CYCLES_REG                 = 0x17,
    MAX1726X_DESIGNCAP_REG              = 0x18,
    MAX1726X_AVGVCELL_REG               = 0x19,
    MAX1726X_MAXMINVOLT_REG             = 0x1B,
    MAX1726X_CONFIG_REG                 = 0x1D,
    MAX1726X_ICHGTERM_REG               = 0x1E,

    MAX1726X_TTF_REG                    = 0X20,
    MAX1726X_VERSION_REG                = 0x21,
    MAX1726X_QRTABLE10_REG              = 0x22,
    MAX1726X_FULLCAPNOM_REG             = 0x23,
    MAX1726X_LEARNCFG_REG               = 0x28,
    MAX1726X_RELAXCFG_REG               = 0x2A,
    MAX1726X_TGAIN_REG                  = 0x2C,
    MAX1726X_TOFF_REG                   = 0x2D,

    MAX1726X_QRTABLE20_REG              = 0x32,
    MAX1726X_RCOMP0_REG                 = 0x38,
    MAX1726X_TEMPCO_REG                 = 0x39,
    MAX1726X_VEMPTY_REG                 = 0x3A,
    MAX1726X_FSTAT_REG                  = 0x3D,

    MAX1726X_QRTABLE30_REG              = 0x42,
    MAX1726X_DQACC_REG                  = 0x45,
    MAX1726X_DPACC_REG                  = 0x46,
    MAX1726X_VFSOC0_REG                 = 0x48,
    MAX1726X_QH0_REG                    = 0x4C,
    MAX1726X_QH_REG                     = 0x4D,

    MAX1726X_VFSOC0_QH0_LOCK_REG        = 0x60,
    MAX1726X_LOCK1_REG                  = 0x62,
    MAX1726X_LOCK2_REG                  = 0x63,

    MAX1726X_MODELDATA_START_REG        = 0x80,
    MAX1726X_MODELDATA_RCOMPSEG_REG     = 0xAF,

    MAX1726X_IALRTTH_REG                = 0xB4,
    MAX1726X_CVMIXCAP_REG               = 0xB6,
    MAX1726X_CVHALFIME_REG              = 0xB7,
    MAX1726X_CURVE_REG                  = 0xB9,
    MAX1726X_HIBCFG_REG                 = 0xBA,
    MAX1726X_CONFIG2_REG                = 0xBB,

    MAX1726X_MODELCFG_REG               = 0xDB,

    MAX1726X_OCV_REG                    = 0xFB,
    MAX1726X_VFSOC_REG                  = 0xFF,
};

enum {
   POWER_SUPPLY_HEALTH_UNKNOWN = 0,
   POWER_SUPPLY_HEALTH_GOOD,
   POWER_SUPPLY_HEALTH_OVERHEAT,
   POWER_SUPPLY_HEALTH_DEAD,
   POWER_SUPPLY_HEALTH_OVERVOLTAGE,
   POWER_SUPPLY_HEALTH_UNSPEC_FAILURE,
   POWER_SUPPLY_HEALTH_COLD,
   POWER_SUPPLY_HEALTH_WATCHDOG_TIMER_EXPIRE,
   POWER_SUPPLY_HEALTH_SAFETY_TIMER_EXPIRE,
   POWER_SUPPLY_HEALTH_OVERCURRENT,
   POWER_SUPPLY_HEALTH_CALIBRATION_REQUIRED,
   POWER_SUPPLY_HEALTH_WARM,
   POWER_SUPPLY_HEALTH_COOL,
   POWER_SUPPLY_HEALTH_HOT,
};

enum {
   POWER_SUPPLY_STATUS_UNKNOWN = 0,
   POWER_SUPPLY_STATUS_CHARGING,
   POWER_SUPPLY_STATUS_DISCHARGING,
   POWER_SUPPLY_STATUS_NOT_CHARGING,
   POWER_SUPPLY_STATUS_FULL,
};

enum power_supply_property {
    POWER_SUPPLY_PROP_PRESENT,
    POWER_SUPPLY_PROP_CYCLE_COUNT,
    POWER_SUPPLY_PROP_VOLTAGE_MAX,
    POWER_SUPPLY_PROP_VOLTAGE_MIN_DESIGN,
    POWER_SUPPLY_PROP_VOLTAGE_NOW,
    POWER_SUPPLY_PROP_VOLTAGE_AVG,
    POWER_SUPPLY_PROP_VOLTAGE_OCV,
    POWER_SUPPLY_PROP_CAPACITY,
    POWER_SUPPLY_PROP_CHARGE_FULL,
    POWER_SUPPLY_PROP_CHARGE_NOW,
    POWER_SUPPLY_PROP_CHARGE_COUNTER,
    POWER_SUPPLY_PROP_TEMP,
    POWER_SUPPLY_PROP_TEMP_ALERT_MIN,
    POWER_SUPPLY_PROP_TEMP_ALERT_MAX,
    POWER_SUPPLY_PROP_HEALTH,
    POWER_SUPPLY_PROP_CURRENT_NOW,
    POWER_SUPPLY_PROP_CURRENT_AVG,
    POWER_SUPPLY_PROP_STATUS,
    POWER_SUPPLY_PROP_TIME_TO_EMPTY_AVG,
    POWER_SUPPLY_PROP_TIME_TO_FULL_NOW,
};

union power_supply_prop_val {
   int intval;
   const char *strval;
};

#endif /* MAIN_COMPONENT_PMIC_MAX77658_TYPES_H_ */
