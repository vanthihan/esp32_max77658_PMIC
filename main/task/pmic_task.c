/*
 * pmic_task.c
 *
 *  Created on: Oct 10, 2021
 *      Author: kai
 */
/* Includes ----------------------------------------------------------- */
#include "pmic_task.h"

#include <esp_log.h>
#include "bsp.h"

/* Private defines ---------------------------------------------------- */
/* Private enumerate/structure ---------------------------------------- */
/* Private macros ----------------------------------------------------- */
/* Public variables --------------------------------------------------- */
/* Private variables -------------------------------------------------- */
static const char* TAG = "pmic TASK";

/* Private function prototypes ---------------------------------------- */
/* Function definitions ----------------------------------------------- */


void pmic_main_task()
{
   ESP_LOGI(TAG, "pmic_main_task() Started.");


   while(1)
   {
      ESP_LOGI(TAG, "pmic_main_task() Looping.");
      bsp_delay_ms(1000);
   }
}
//
//#include "mbed.h"
//#include "max17055.h"
//
//
//   //LED indication
//   DigitalOut rled(LED1);
//
//   //I2C communications
//   I2C i2cBus(P5_7, P6_0);
//
//   //Fuel Gauge
//   MAX17055 fuelGauge(i2cBus);
//   MAX17055::platform_data design_param;
//   MAX17055::saved_FG_params_t saved_param;
//
//   //MAX77650 PMIC
//   #define POWER_HOLD_ON 1
//   #define POWER_HOLD_OFF 0
//
//   DigitalOut pw_Hold(P2_2, POWER_HOLD_ON); //To enable battery operation from the PMIC
//
//   //Battery Parameters Storage from the Fuel Gauge MAX17055
//   union max17055_u {
//       struct battery {
//           uint8_t avg_soc_FG;     // in Battery Percent
//          float tte_FG;            // in seconds
//           float ttf_FG;           // in seconds
//           int avg_vcell_FG;       // in 78.125uV per bit
//           float avg_curr_FG;      // in uAmps
//           float curr_FG;          // in uAmps
//           int rep_cap;            // in mAh
//           int rep_SOC;            // in %
//       } battery;
//   } max17055_u;
//
//
//   int main(void)
//   {
//       rled = true;
//       //These are the calculated parameters for rsense 5mOhm found in the MAX32620FTHR and a 350mAh Li+ Cell.
//       design_param.designcap  = 0x015E;  //Design Battery Capacity mAh this can change depending on the batteries implemented see battery data sheet for details.
//       design_param.ichgterm  = 0x0070;  // Charge Termination Current for the Battery This is specified by the manufacturer.
//       design_param.vempty  = 0x9600;  // Battery Empty Voltage This is specified by design, but manufacturer has a min Empty voltage specification.
//       design_param.vcharge  = 4200;  // Battery Charge Voltage can be obtained from MAX77650 configuration
//       design_param.rsense = 5; //5mOhms for MAX32620, keep in mind the MAX17055EVKIT has a 10mOhm resistor. This is a design specific value. Used for calculation results.
//
//   //Saved Parameters
//   //saved_param.cycles = 0; //This value is used for the save parameters function
//
//   status = fuelGauge.init(design_param);
////    printf("Init FuelGauge Function Status= %X \r\n",status);
//
//   if (status == 0)
//       fuelGauge.save_Params(saved_param);
//
//   while (1) {
//       //This code is an example to illustrate the performance or the Fuel Gauge. This can change with the design requirements. Use this as a way to troubleshoot the FuelGauge.
//       rled = !rled;
//
//      max17055_u.battery.avg_vcell_FG = fuelGauge.get_avgVcell();
//      max17055_u.battery.avg_curr_FG  = fuelGauge.get_AvgCurrent(design_param);
//      max17055_u.battery.curr_FG      = fuelGauge.get_Current(design_param);
//      max17055_u.battery.rep_cap      = fuelGauge.get_battCAP(design_param);
//      max17055_u.battery.rep_SOC      = fuelGauge.get_SOC();
//
//       //This code works with Arduino Serial Plotter to visualize data
//       printf("%f " ,(max17055_u.battery.avg_vcell_FG/1000000.0)); //V
//       printf("%f " ,max17055_u.battery.avg_curr_FG);              //uA
//       printf("%f " ,max17055_u.battery.curr_FG);                  //uA
//       printf("%d " ,max17055_u.battery.rep_cap);                  //mAh
//       printf("%d " ,max17055_u.battery.rep_SOC);                  //%
//       printf("\n");
//       wait(1);
//    }
//}



