/*
 * pmic_task.c
 *
 *  Created on: Oct 10, 2021
 *      Author: kai
 */
/* Includes ----------------------------------------------------------- */
#include "pmic_task.h"
#include <stdio.h>
#include <esp_log.h>
#include "bsp.h"
#include "max77658_fg_types.h"
#include "max77658_fg.h"

/* Private defines ---------------------------------------------------- */
/* Private enumerate/structure ---------------------------------------- */
/* Private macros ----------------------------------------------------- */
/* Public variables --------------------------------------------------- */
/* Private variables -------------------------------------------------- */
static const char* TAG = "pmic TASK";
static saved_FG_params_t saved_param;
static max77658_fg_t *m_max77658_fg_t;

/* Private function prototypes ---------------------------------------- */
/* Function definitions ----------------------------------------------- */


void pmic_main_task()
{
   ESP_LOGI(TAG, "pmic_main_task() Started.");

   m_max77658_fg_t->device_address = 0x6C;
   m_max77658_fg_t->read_reg = bsp_i2c_read;
   m_max77658_fg_t->write_reg = bsp_i2c_write;

   //Battery Parameters Storage from the Fuel Gauge MAX17055
   union max17055_u {
       struct battery {
           uint8_t avg_soc_FG;     // in Battery Percent
          float tte_FG;            // in seconds
           float ttf_FG;           // in seconds
           int avg_vcell_FG;       // in 78.125uV per bit
           float avg_curr_FG;      // in uAmps
           float curr_FG;          // in uAmps
           int rep_cap;            // in mAh
           int rep_SOC;            // in %
       } battery;
   } max17055_u;

   //Saved Parameters
    //saved_param.cycles = 0; //This value is used for the save parameters function.

    int status; // stores return value of the status of setting up the MAX17055
    uint8_t array_addresses[7] = {MODELCFG_REG,
            DESIGNCAP_REG,
            FULLCAPNOM_REG,
            DPACC_REG,
            DQACC_REG,
            VEMPTY_REG,
            ICHGTERM_REG
           };

    status = max77658_fg_init(m_max77658_fg_t);
    printf("Init FuelGauge Function Status= %X \r\n",status); // Status shoudl retun Zero if the are no issues with the initialization.

    if (status == 0)
       max77658_fg_save_Params(m_max77658_fg_t, saved_param);

    //Read DesignCap, Ichagterm, Vempty, dqacc, dpacc, MODELCFG, FullCapNom to verify values correspond to the expected stored Values.
    // FullCapNom[mAh] = (dqacc[mAh]/dpacc[%])*100%
    uint16_t regValue[7];
    for(int i = 0 ; i < 7 ; i++) {
        regValue[i] = max77658_fg_get_regInfo(m_max77658_fg_t, array_addresses[i]);
        printf("%X"  ,regValue[i]);
        printf(" ");
    }

    bsp_delay_ms(2);

   while(1)
   {
      ESP_LOGI(TAG, "pmic_main_task() Looping.");
      m_max77658_fg_t->pdata->designcap  = 0x015E;  //Design Battery Capacity mAh this can change depending on the batteries implemented see battery data sheet for details.
      m_max77658_fg_t->pdata->ichgterm  = 0x0070;  // Charge Termination Current for the Battery This is specified by the manufacturer.
      m_max77658_fg_t->pdata->vempty  = 0x9600;  // Battery Empty Voltage This is specified by design, but manufacturer has a min Empty voltage specification.
      m_max77658_fg_t->pdata->vcharge  = 4200;  // Battery Charge Voltage can be obtained from MAX77650 configuration
      m_max77658_fg_t->pdata->rsense = 5; //5mOhms for MAX32620, keep in mind the MAX17055EVKIT has a 10mOhm resistor. This is a design specific value. Used for calculation results.

      max17055_u.battery.avg_vcell_FG = max77658_fg_get_avgVcell(m_max77658_fg_t);
      max17055_u.battery.avg_curr_FG  = max77658_fg_get_AvgCurrent(m_max77658_fg_t);
      max17055_u.battery.curr_FG      = max77658_fg_get_Current(m_max77658_fg_t);
      max17055_u.battery.rep_cap      = max77658_fg_get_battCAP(m_max77658_fg_t);
      max17055_u.battery.rep_SOC      = max77658_fg_get_SOC(m_max77658_fg_t);

      //This code works with Arduino Serial Plotter to visualize data
      printf("%f " ,(max17055_u.battery.avg_vcell_FG/1000000.0)); //V
      printf("%f " ,max17055_u.battery.avg_curr_FG);              //uA
      printf("%f " ,max17055_u.battery.curr_FG);                  //uA
      printf("%d " ,max17055_u.battery.rep_cap);                  //mAh
      printf("%d " ,max17055_u.battery.rep_SOC);                  //%
      printf("\n");

      bsp_delay_ms(1000);
   }
}

