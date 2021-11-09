/*
 * max77658_types.h
 *
 *  Created on: Oct 31, 2021
 *      Author: kai
 */

#ifndef MAIN_COMPONENT_PMIC_MAX77658_FG_TYPES_H_
#define MAIN_COMPONENT_PMIC_MAX77658_FG_TYPES_H_

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


/**
* @brief      Saved Platform Data for Fuel Gauge Model
* @details    Struct with fuel Gauge Platform Data for Fuel Gauge Model based on the final design.
*/
typedef struct {
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
} platform_data;

enum {
   STATUS_REG                 = 0x00,
   VALRTTH_REG                = 0x01,
   TALRTTH_REG                = 0x02,
   SALRTTH_REG                = 0x03,
   ATRATE_REG                 = 0x04, /*!< 0x04 write negative 2s comp of a 16-bit theoretical load */
   REPCAP_REG                 = 0x05,
   REPSOC_REG                 = 0x06,
   TEMP_REG                   = 0x08,
   VCELL_REG                  = 0x09,
   CURRENT_REG                = 0x0A,
   AVGCURRENT_REG             = 0x0B,
   MIXSOC_REG                 = 0x0D, /*!< 0x0D */
   AVSOC_REG                  = 0x0E, /*!< 0x0E */
   REMCAP_REG                 = 0x0F,
   MIXCAP_REG                 = 0x0F, /*!< 0x0F */

   FULLCAPREP_REG             = 0x10,
   TTE_REG                    = 0X11,
   QRTABLE00_REG              = 0x12,
   FULLSOCTHR_REG             = 0x13,
   CYCLES_REG                 = 0x17,
   DESIGNCAP_REG              = 0x18,
   AVGVCELL_REG               = 0x19,
   MAXMINVOLT_REG             = 0x1B,
   CONFIG_REG                 = 0x1D,
   ICHGTERM_REG               = 0x1E,

   TTF_REG                    = 0X20,
   VERSION_REG                = 0x21,
   QRTABLE10_REG              = 0x22,
   FULLCAPNOM_REG             = 0x23,
   LEARNCFG_REG               = 0x28,
   RELAXCFG_REG               = 0x2A,
   TGAIN_REG                  = 0x2C,
   TOFF_REG                   = 0x2D,

   QRTABLE20_REG              = 0x32,
   RCOMP0_REG                 = 0x38,
   TEMPCO_REG                 = 0x39,
   VEMPTY_REG                 = 0x3A,
   FSTAT_REG                  = 0x3D,

   QRTABLE30_REG              = 0x42,
   DQACC_REG                  = 0x45,
   DPACC_REG                  = 0x46,
   VFSOC0_REG                 = 0x48,
   QH0_REG                    = 0x4C,
   QH_REG                     = 0x4D,

   VFSOC0_QH0_LOCK_REG        = 0x60,
   LOCK1_REG                  = 0x62,
   LOCK2_REG                  = 0x63,

   MODELDATA_START_REG        = 0x80,
   MODELDATA_RCOMPSEG_REG     = 0xAF,

   IALRTTH_REG                = 0xB4,
   CVMIXCAP_REG               = 0xB6,
   CVHALFIME_REG              = 0xB7,
   CURVE_REG                  = 0xB9,
   HIBCFG_REG                 = 0xBA,
   CONFIG2_REG                = 0xBB,

   MODELCFG_REG               = 0xDB,
   ATTTE_REG                  = 0xDD, /*!< 0xDD */
   ATAVSOC_REG                = 0xDE, /*!< 0xDE */

   OCV_REG                    = 0xFB,
   VFSOC_REG                  = 0xFF,
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

/**
 * @brief      Saved Fuel Gauge Parameters
 * @details    It is recommended to save the learned capacity parameters
 *             every time bit 2 of the Cycles register toggles (so that it
 *             is saved every 64% change in the battery) so that if power is
 *             lost the values can easily be restored.
 */
typedef struct {
   int rcomp0;              /**< The RComp0 is the characterization information critical to computing the open-circuit voltage of a cell under loaded conditions. */
   int temp_co;             /**< The TempCo value is the temperature compensation information based on the RComp0 value*/
   int full_cap_rep;        /**< The full capacity in relation with RepCap for reporting to the GUI. A new full-capacity value is calculated at the end of every charge cycle in the application. */
   int cycles;              /**< The Cycles value maintains a total count of the number of charge/discharge cycles of the cell that have occurred */
   int full_cap_nom;        /**< This is the calculated full capacity of the cell, not including temperature and empty compensation. A new full-capacity nominal value
                              is calculated each time a cell relaxation event is detected. This values is used to generate other outputs of the ModelGauge m5 algorithm. */
} saved_FG_params_t;

#endif /* MAIN_COMPONENT_PMIC_MAX77658_FG_TYPES_H_ */
