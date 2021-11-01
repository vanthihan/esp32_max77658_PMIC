/**
 * @file       bsp.c
 * @brief      Board Support Package (BSP)
 * 
 * @note       None
 * @example    None
 */

/* Includes ----------------------------------------------------------- */
#include "bsp.h"
#include "i2c_bus.h"
#include "freertos/task.h"
#include "driver/gpio.h"


#define LOG_LOCAL_LEVEL ESP_LOG_VERBOSE
#include "esp_log.h"

/* Private defines ---------------------------------------------------- */
#define BLINK_GPIO GPIO_NUM_2

/* Private enumerate/structure ---------------------------------------- */
/* Private macros ----------------------------------------------------- */
/* Public variables --------------------------------------------------- */
/* Private variables -------------------------------------------------- */
static const char *TAG = "BSP";

static i2c_bus_handle_t m_i2c_0_hdl;
static gpio_num_t I2C_SDA_PIN = GPIO_NUM_21;
static gpio_num_t I2C_SCL_PIN = GPIO_NUM_22;

/* Private function prototypes ---------------------------------------- */
static void m_bsp_i2c_init(void);

/* Function definitions ----------------------------------------------- */
void bsp_hw_init(void)
{
   ESP_LOGI(TAG, "bsp_hw_init()");
   m_bsp_i2c_init();

   gpio_pad_select_gpio(BLINK_GPIO);
   /* Set the GPIO as a push/pull output */
   gpio_set_direction(BLINK_GPIO, GPIO_MODE_OUTPUT);
}

int bsp_i2c_write(uint8_t slave_addr, uint8_t reg_addr, uint8_t *p_data, uint32_t len)
{
   int ret;
   ret = i2c_bus_write_bytes(m_i2c_0_hdl, slave_addr, &reg_addr, sizeof(reg_addr), p_data, len);

   if (ret != 0)
   {
      ESP_LOGI(TAG, "I2C 0 error: %d. Restart I2C", ret);
      i2c_bus_delete(m_i2c_0_hdl);
      m_bsp_i2c_init();
      ret = i2c_bus_write_bytes(m_i2c_0_hdl, slave_addr, &reg_addr, sizeof(reg_addr), p_data, len);
   }

   return ret;
}

int bsp_i2c_read(uint8_t slave_addr, uint8_t reg_addr, uint8_t *p_data, uint32_t len)
{
   int ret;
   ret = i2c_bus_read_bytes(m_i2c_0_hdl, slave_addr, &reg_addr, sizeof(reg_addr), p_data, len);

   if (ret != 0)
   {
      ESP_LOGE(TAG, "I2C 0 error: %d. Restart I2C", ret);
      i2c_bus_delete(m_i2c_0_hdl);
      m_bsp_i2c_init();
      ret = i2c_bus_read_bytes(m_i2c_0_hdl, slave_addr, &reg_addr, sizeof(reg_addr), p_data, len);
   }

   return ret;
}

void bsp_delay_ms(uint32_t ms)
{
   vTaskDelay(ms / portTICK_PERIOD_MS);
}

void bsp_gpio_write(uint8_t pin , uint8_t state)
{
   ESP_LOGD(TAG, "bsp_gpio_write() Pin: %d, level: %d", pin, state);
   gpio_set_level(pin, state);
}

/* Private function definitions ---------------------------------------- */
/**
 * @brief         I2C init
 *
 * @param[in]     None
 *
 * @attention     None
 *
 * @return        None
 */
void m_bsp_i2c_init(void)
{
   ESP_LOGI(TAG, "m_bsp_i2c_init()");
   i2c_config_t es_i2c_cfg =
   {
      .mode             = I2C_MODE_MASTER,
      .sda_io_num       = I2C_SDA_PIN,
      .scl_io_num       = I2C_SCL_PIN,
      .sda_pullup_en    = GPIO_PULLUP_ENABLE,
      .scl_pullup_en    = GPIO_PULLUP_ENABLE,
      .master.clk_speed = 400000
   };

   m_i2c_0_hdl = i2c_bus_create(I2C_NUM_0, &es_i2c_cfg);
   i2c_set_timeout(I2C_NUM_0, 0xfffff);
}

/* End of file -------------------------------------------------------- */
