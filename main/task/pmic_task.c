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
#include "max77658_defines.h"
#include "max77658_pm.h"
#include "esp_sntp.h"


/* Private defines ---------------------------------------------------- */
/* Private enumerate/structure ---------------------------------------- */
/* Private macros ----------------------------------------------------- */
/* Public variables --------------------------------------------------- */
/* Private variables -------------------------------------------------- */
static const char* TAG = "pmic TASK";
static saved_FG_params_t saved_param;
max77658_fg_t m_max77658_fg_t;
max77658_pm_t m_max77658_pm_t;


uint8_t butLst;

//GERRY MOD
//enum { None, SingleClick, DoubleClick };
enum { None, SingleClick, DoubleClick, YesSingle};

/* Private function prototypes ---------------------------------------- */
/* Function definitions ----------------------------------------------- */
static int chkButton (uint8_t input);



void pmic_main_task()
{
   ESP_LOGI(TAG, "pmic_main_task() Started.");

   bsp_hw_init();

   m_max77658_fg_t.device_address = 0x6C;
   m_max77658_fg_t.read_reg = bsp_i2c_read;
   m_max77658_fg_t.write_reg = bsp_i2c_write;

   //Battery Parameters Storage from the Fuel Gauge MAX17055
   union max17055_u {
        struct battery {
        int8_t avg_soc_FG;     // in Battery Percent
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
   uint8_t array_addresses[7] = 
   {
      MODELCFG_REG,
      DESIGNCAP_REG,
      FULLCAPNOM_REG,
      DPACC_REG,
      DQACC_REG,
      VEMPTY_REG,
      ICHGTERM_REG
   };

   status = max77658_fg_init(&m_max77658_fg_t);
   printf("Init FuelGauge Function Status= %X \r\n",status); // Status shoudl retun Zero if the are no issues with the initialization.

   if(status == 0)
   {
      max77658_fg_save_Params(&m_max77658_fg_t, saved_param);
   }

   //Read DesignCap, Ichagterm, Vempty, dqacc, dpacc, MODELCFG, FullCapNom to verify values correspond to the expected stored Values.
   // FullCapNom[mAh] = (dqacc[mAh]/dpacc[%])*100%
   uint16_t regValue[7];
   for(int i = 0 ; i < 7 ; i++) 
   {
      regValue[i] = max77658_fg_get_regInfo(&m_max77658_fg_t, array_addresses[i]);
      printf("%X", regValue[i]);
      printf(" ");
   }

   bsp_delay_ms(2);

   while(1)
   {
      ESP_LOGI(TAG, "pmic_main_task() Looping.");

      max17055_u.battery.avg_vcell_FG = max77658_fg_get_avgVcell(&m_max77658_fg_t);
      max17055_u.battery.avg_curr_FG  = max77658_fg_get_AvgCurrent(&m_max77658_fg_t);
      max17055_u.battery.curr_FG      = max77658_fg_get_Current(&m_max77658_fg_t);
      max17055_u.battery.rep_cap      = max77658_fg_get_battCAP(&m_max77658_fg_t);
      max17055_u.battery.rep_SOC      = max77658_fg_get_SOC(&m_max77658_fg_t);

      //This code works with Arduino Serial Plotter to visualize data
      ESP_LOGI(TAG, "pmic_main_task() Battery Information");
      printf("---avg_vcell_FG:---%f V \n", (max17055_u.battery.avg_vcell_FG/1000000.0)); //V
      printf("---avg_curr_FG:----%f uA \n", max17055_u.battery.avg_curr_FG);              //uA
      printf("---curr_FG:--------%f uA \n", max17055_u.battery.curr_FG);                  //uA
      printf("---rep_cap:--------%d mAh \n", max17055_u.battery.rep_cap);                  //mAh
      printf("---rep_SOC:--------%d %% \n", max17055_u.battery.rep_SOC);                  //%
      printf("\n");

      bsp_delay_ms(1000);
   }
}

static int32_t get_current_time() 
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000LL + (tv.tv_usec / 1000LL));
}


void pmic_task()
{
   ESP_LOGI(TAG, "pmic_task() Started.");

   bsp_hw_init();

   m_max77658_pm_t.device_address = 0x90;
   m_max77658_pm_t.read_reg = bsp_i2c_read;
   m_max77658_pm_t.write_reg = bsp_i2c_write;

   //Baseline Initialization following rules printed in MAX77650 Programmres Guide Chapter 4 Page 5
   max77658_pm_base_line_init(&m_max77658_pm_t);

   //Limit output of SBB0 to 333mA
   max77658_pm_set_IP_SBB0(&m_max77658_pm_t, 0b11);
   //Set output Voltage of SBB0 to 3.3V
   max77658_pm_set_TV_SBB0(&m_max77658_pm_t, 0b1110000);
   //Disable Active Discharge at SBB0 Output
   max77658_pm_set_ADE_SBB0(&m_max77658_pm_t, 0b0);
   //Enable SBB0 is on irrespective of FPS whenever the on/off controller is in its "On via Software" or "On via On/Off Controller" states
   max77658_pm_set_EN_SBB0(&m_max77658_pm_t, 0b110);

   float SBB0_value = max77658_pm_get_TV_SBB0(&m_max77658_pm_t) * 0.025 + 0.5;
   printf("SBB0 Output voltage: %f V\n", SBB0_value);

   uint8_t interrupt_REG0 = max77658_pm_get_INT_GLBL0(&m_max77658_pm_t);  //read global interrupt register to clear it
   ESP_LOGI(TAG, "pmic_main_task() interrupt_REG0: %d", interrupt_REG0);


   uint8_t is_nEN_rising = 0x00;
   uint8_t is_nEN_falling = 0x00;
   uint8_t global_0_status = 0x00;



   while(1)
   {
      global_0_status = max77658_pm_get_INT_GLBL0(&m_max77658_pm_t);
      is_nEN_rising = max77658_pm_get_bit(global_0_status, 3);  //nEN Rising Interrupt

      //In both push-button mode and slide-switch mode, the on/off controller looks for a falling edge on the nEN input to initiate a power-up sequence
      is_nEN_falling = max77658_pm_get_bit(global_0_status, 2);  //nEN Falling Interrupt

      // ESP_LOGI(TAG, "pmic_main_task() global_0_status: %d, nEn Rising: %d, Falling: %d", global_0_status, is_nEN_rising, is_nEN_falling);

      if(is_nEN_falling)
      {
         ESP_LOGI(TAG, "pmic_main_task() nEN falling detected %d", is_nEN_falling);
      }

      switch(chkButton(is_nEN_falling))
      {
         case SingleClick:
         {
            printf("Press detected\n");
            break;
         }
         case DoubleClick:
         {
            printf("Double presses detected\n");
            break;
         }
         //GERRY MOD
         case YesSingle:
         {
            printf("Single press detected\n");
            break;
         }
      }
   }
}

// -----------------------------------------------------------------------------
static int chkButton (uint8_t input)
{
   const  unsigned long ButTimeout  = 300;
   static unsigned long msecLst;
   unsigned long msec = get_current_time();
   //GERRY MOD
   const int debDuration = 30;
   static unsigned long  debStartTime = 0;

   if (msecLst && (msec - msecLst) > ButTimeout)
   {
      msecLst = 0;
      //GERRY MOD
      //return SingleClick;	
      return YesSingle;
   }

   uint8_t but = input;
   if (butLst != but)
   {
      //GERRY MOD
      if (get_current_time() - debStartTime < debDuration) {
      return None;
      }
      debStartTime = get_current_time();

      butLst = but;

      if (0x01 == but)
      {   // press
         if (msecLst)
         { // 2nd press
            msecLst = 0;
            return DoubleClick;
         }
         else
         {
            msecLst = 0 == msec ? 1 : msec;
            //GERRY MOD
            return SingleClick; //SINGLE?
         }
      }
   }

  return None;
}


