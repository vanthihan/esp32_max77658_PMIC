#include <max77658.h>
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "sdkconfig.h"
#include "esp_log.h"
#include "bsp.h"
#include "pmic_task.h"

static const char *TAG = "MAIN APP";


void app_main()
{
    ESP_LOGI(TAG, "=======BEGIN======");

    xTaskCreate(&pmic_task, "pmic_task", (5 * 1024), NULL, 1, NULL);

   // while(1)
   // {
   //    ESP_LOGI(TAG, "Looping");
   //    bsp_delay_ms(1000);
   // }
}
