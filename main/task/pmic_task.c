/*
 * pmic_task.c
 *
 *  Created on: Oct 10, 2021
 *      Author: kai
 */

#include "pmic_task.h"

#include <esp_log.h>
#include "bsp.h"

static const char* TAG = "pmic TASK";

void pmic_main_task()
{
   ESP_LOGI(TAG, "pmic_main_task() Started.");


   while(1)
   {
      ESP_LOGI(TAG, "pmic_main_task() Looping.");
      bsp_delay_ms(1000);
   }
}

