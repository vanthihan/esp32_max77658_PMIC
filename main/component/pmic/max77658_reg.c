/*
 * max77658.c
 *
 *  Created on: Oct 31, 2021
 *      Author: kai
 */

/* Includes ----------------------------------------------------------- */
#include "max77658_reg.h"
#include <esp_log.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "bsp.h"

/* Private defines ---------------------------------------------------- */

/* STATUS register bits */
#define MAX1726X_STATUS_BST             (1 << 3)
#define MAX77658_STATUS_POR             (1 << 1)

/* MODELCFG register bits */
#define MAX77658_MODELCFG_REFRESH       (1 << 15)

/* FSTAT register bits */
#define MAX77658_FSTAT_DNR              (1)

/* TALRTTH register bits */
#define MIN_TEMP_ALERT                  0
#define MAX_TEMP_ALERT                  8

#define MAX1726X_VMAX_TOLERANCE     50 /* 50 mV */

/* Private enumerate/structure ---------------------------------------- */
/* Private macros ----------------------------------------------------- */
/* Public variables --------------------------------------------------- */
/* Private variables -------------------------------------------------- */
static const char *TAG = "MAX77658 REG";

/* Private function prototypes ---------------------------------------- */
//static void m_bsp_i2c_init(void);

/* Function definitions ----------------------------------------------- */

/**
  * @brief  Read generic device register
  *
  * @param  ctx   communication interface handler.(ptr)
  * @param  reg   first register address to read.
  * @param  data  buffer for data read.(ptr)
  * @param  len   number of consecutive register to read.
  * @retval       interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t max77658_read_reg(maxdev_ctx_t *ctx, uint8_t reg_address, uint16_t *val)
{
   uint16_t ret;
   uint8_t buff[2];
   uint8_t len = 16;

   ret = ctx->read_reg(ctx->device_address, reg_address, buff, len);
   if(ret > 0)
   {
      *val = buff[1];
      *val = (*val * 256U) +  buff[0];
   }

   return ret;
}

/**
  * @brief  Write generic device register
  *
  * @param  ctx   communication interface handler.(ptr)
  * @param  reg   first register address to write.
  * @param  data  the buffer contains data to be written.(ptr)
  * @param  len   number of consecutive register to write.
  * @retval       interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t max77658_write_reg(maxdev_ctx_t *ctx, uint8_t reg, uint16_t data)
{
   int32_t ret;
   uint8_t buff[2];
   uint8_t len = 16;

   buff[1] = (uint8_t)(data / 256U);
   buff[0] = (uint8_t)(data - (buff[1] * 256U));

   ret = ctx->write_reg(ctx->device_address, reg, buff, len);

   return ret;
}

static bool max77658_write_verify_reg(maxdev_ctx_t *ctx, uint8_t reg_address, uint16_t value_set)
{
   bool ret = false;
   int retry = 0;
   uint16_t value_get;

   do
   {
      max77658_write_reg(ctx, reg_address, value_set);
      bsp_delay_ms(1); //1ms
      max77658_read_reg(ctx, reg_address, &value_get);
   }
   while((value_set != value_get) && (retry++ < 3));

   ret = (value_set == value_get)?true:false;

   return ret;
}

static inline int max1726x_lsb_to_uvolts(int lsb)
{
   return lsb * 625 / 8; /* 78.125uV per bit */
}

static int max1726x_raw_current_to_uamps(maxdev_ctx_t *ctx, uint32_t curr)
{
    int res = curr;

    /* Negative */
    if (res & 0x8000)
        res |= 0xFFFF0000;

    res *= 1562500 / (ctx->pdata->rsense * 1000);
    return res;
}

static int32_t max77658_version_get(maxdev_ctx_t *ctx)
{
   int32_t ret;
   uint16_t version;

   ret = max77658_read_reg(ctx, MAX1726X_VERSION_REG, &version);

   if(ret > 0)
   {
      ESP_LOGI(TAG, "IC Version: 0x%04x\n", version);
   }

   return ret;
}

static int32_t max77568_POR_status_get(maxdev_ctx_t *ctx)
{
   int32_t ret;
   uint16_t data;

   /* Step 0: Check for POR */
   /* Skip load model if POR bit is cleared */
   ret = max77658_read_reg(ctx, MAX1726X_STATUS_REG, &data);
   /* Skip load custom model */
   if(ret > 0)
   {
      if (!(data & MAX77658_STATUS_POR)){
          ESP_LOGW(TAG, "POR is not set. Skipping initialization...\n");
          ret = -1;
      }
   }

   return ret;
}

static int32_t max77658_flag_polling(maxdev_ctx_t *ctx, uint8_t reg_address, int32_t mask, int32_t timeout)
{
   uint16_t data;
   int ret = 0;

   do{
      bsp_delay_ms(10);
      if(max77658_read_reg(ctx, reg_address, &data) < 0)
      {
         ret = -1;
         break;
      }

      if(!(data & mask))
      {
         ret = 0;
         break;
      }
      timeout -= 10;
   } while(timeout > 0);

   if(timeout < 0)
      ret = -1;

   return ret;
}

static int32_t max77568_config_option_1(maxdev_ctx_t *ctx, uint16_t hibcfg)
{
   int32_t ret;

   /* Step 2.1: Option 1 EZ Config */
   ret = max77658_write_reg(ctx, MAX1726X_DESIGNCAP_REG, ctx->pdata->designcap);
   ret = max77658_write_reg(ctx, MAX1726X_ICHGTERM_REG, ctx->pdata->ichgterm);
   ret = max77658_write_reg(ctx, MAX1726X_VEMPTY_REG, ctx->pdata->vempty);

   if(ctx->pdata->vcharge > 4275)
   {
      ret = max77658_write_reg(ctx, MAX1726X_MODELCFG_REG, 0x8400);
   }
   else
   {
      ret = max77658_write_reg(ctx, MAX1726X_MODELCFG_REG, 0x8000);
   }

   /* Poll ModelCFG.ModelRefresh bit for clear */
   ret = max77658_flag_polling(ctx, MAX1726X_MODELCFG_REG, MAX77658_MODELCFG_REFRESH, 500);
   if(ret < 0)
   {
       ESP_LOGE(TAG, "Option1 model refresh not completed!\n");
       return ret;
   }

   ret = max77658_write_reg(ctx, MAX1726X_HIBCFG_REG, hibcfg); // Restore Original HibCFG value

   return ret;
}

static int32_t max77568_config_option_2(maxdev_ctx_t *ctx, uint16_t hibcfg)
{
   int32_t ret;

   /* Step 2.2: Option 2 Custom Short INI without OCV Table */
   ret = max77658_write_reg(ctx, MAX1726X_DESIGNCAP_REG, ctx->pdata->designcap);
   ret = max77658_write_reg(ctx, MAX1726X_ICHGTERM_REG, ctx->pdata->ichgterm);
   ret = max77658_write_reg(ctx, MAX1726X_VEMPTY_REG, ctx->pdata->vempty);
   max77658_write_verify_reg(ctx, MAX1726X_LEARNCFG_REG, ctx->pdata->learncfg); /* Optional */
   max77658_write_verify_reg(ctx, MAX1726X_FULLSOCTHR_REG, ctx->pdata->fullsocthr); /* Optional */

   ret = max77658_write_reg(ctx, MAX1726X_MODELCFG_REG, ctx->pdata->modelcfg);

   /* Poll ModelCFG.ModelRefresh bit for clear */
   ret = max77658_flag_polling(ctx, MAX1726X_MODELCFG_REG, MAX77658_MODELCFG_REFRESH, 500);
   if(ret < 0)
   {
      ESP_LOGE(TAG, "Option2 model refresh not completed!\n");
      return ret;
   }

   ret = max77658_write_reg(ctx, MAX1726X_RCOMP0_REG, ctx->pdata->rcomp0);
   ret = max77658_write_reg(ctx, MAX1726X_TEMPCO_REG, ctx->pdata->tempco);
   ret = max77658_write_reg(ctx, MAX1726X_QRTABLE00_REG, ctx->pdata->qrtable00);
   ret = max77658_write_reg(ctx, MAX1726X_QRTABLE10_REG, ctx->pdata->qrtable10);
   ret = max77658_write_reg(ctx, MAX1726X_QRTABLE20_REG, ctx->pdata->qrtable20);  /* Optional */
   ret = max77658_write_reg(ctx, MAX1726X_QRTABLE30_REG, ctx->pdata->qrtable30);  /* Optional */

   ret = max77658_write_reg(ctx, MAX1726X_HIBCFG_REG, hibcfg); // Restore Original HibCFG value

   return ret;
}

static int32_t max77568_config_option_3(maxdev_ctx_t *ctx, uint16_t hibcfg)
{
   int32_t ret;
   /* Step 2.3: Option 3 Custom Full INI with OCV Table */
   /* Steps 2.3.1-3: Unlock model access, write/read/verify custom model,
                                     lock model access */

//   ret = max1726x_load_model(priv);
//   if(ret){
//   dev_err(priv->dev, "Option3 model table write unsuccessful!\n");
//   return ret;
//   }
//
//   /* Steps 2.3.4: Verify that model access is locked */
//   ret = max1726x_verify_model_lock(priv);
//   if(ret){
//   dev_err(priv->dev, "Option3 model unlock unsuccessful!\n");
//   return ret;
//   }
//
//   /* Step 2.3.5 Write custom paramaters */
//   regmap_write(regmap, MAX1726X_REPCAP_REG, 0x0);
//   regmap_write(regmap, MAX1726X_DESIGNCAP_REG, pdata->designcap);
//   regmap_write(regmap, MAX1726X_DPACC_REG, 0xC80);
//   regmap_write(regmap, MAX1726X_ICHGTERM_REG, pdata->ichgterm);
//   regmap_write(regmap, MAX1726X_VEMPTY_REG, pdata->vempty);
//   regmap_write(regmap, MAX1726X_RCOMP0_REG, pdata->rcomp0);
//   regmap_write(regmap, MAX1726X_TEMPCO_REG, pdata->tempco);
//   regmap_write(regmap, MAX1726X_QRTABLE00_REG, pdata->qrtable00);
//   regmap_write(regmap, MAX1726X_QRTABLE10_REG, pdata->qrtable10);
//   regmap_write(regmap, MAX1726X_QRTABLE20_REG, pdata->qrtable20);  /* Optional */
//   regmap_write(regmap, MAX1726X_QRTABLE30_REG, pdata->qrtable30);  /* Optional */
//
//   /* Optional */
//   max1726x_write_verify_reg(regmap, MAX1726X_LEARNCFG_REG, pdata->learncfg);
//   regmap_write(regmap, MAX1726X_RELAXCFG_REG, pdata->relaxcfg);
//   regmap_write(regmap, MAX1726X_CONFIG_REG, pdata->config);
//   regmap_write(regmap, MAX1726X_CONFIG2_REG, pdata->config2);
//   regmap_write(regmap, MAX1726X_FULLSOCTHR_REG, pdata->fullsocthr);
//   regmap_write(regmap, MAX1726X_TGAIN_REG, pdata->tgain);
//   regmap_write(regmap, MAX1726X_TOFF_REG, pdata->toff);
//   regmap_write(regmap, MAX1726X_CURVE_REG, pdata->curve);
//
//   /* Step 2.3.6 Initiate model loading */
//   regmap_read(regmap, MAX1726X_CONFIG2_REG, &reg);
//   regmap_write(regmap, MAX1726X_CONFIG2_REG, reg | MAX1726X_CONFIG2_LDMDL); /* Set Config2.LdMdl bit */
//
//   /* Step 2.3.7 Poll the Config2.LdMdl=0 */
//   ret = max1726x_poll_flag_clear(regmap, MAX1726X_CONFIG2_REG, MAX1726X_CONFIG2_LDMDL, 5000);
//   if(ret < 0){
//      dev_err(priv->dev, "Option3 LdMdl not completed!\n");
//      return ret;
//   }
//
//   /* Step 2.3.8 Update QRTable20 and QRTable30*/
//   max1726x_write_verify_reg(regmap, MAX1726X_QRTABLE20_REG, pdata->qrtable20);
//   max1726x_write_verify_reg(regmap, MAX1726X_QRTABLE30_REG, pdata->qrtable30);
//
//   /* Step 2.3.9 Restore original HibCfg */
//   regmap_write(regmap, MAX1726X_HIBCFG_REG, hibcfg);

   return ret;
}

static void max77658_set_alert_thresholds(maxdev_ctx_t *ctx)
{
    struct max1726x_platform_data *pdata = ctx->pdata;
    uint16_t val;

    /* Set VAlrtTh */
    val = (pdata->volt_min / 20);
    val |= ((pdata->volt_max / 20) << 8);
    max77658_write_reg(ctx, MAX1726X_VALRTTH_REG, val);

    /* Set TAlrtTh */
    val = pdata->temp_min & 0xFF;
    val |= ((pdata->temp_max & 0xFF) << 8);
    max77658_write_reg(ctx, MAX1726X_TALRTTH_REG, val);

    /* Set SAlrtTh */
    val = pdata->soc_min;
    val |= (pdata->soc_max << 8);
    max77658_write_reg(ctx, MAX1726X_SALRTTH_REG, val);

    /* Set IAlrtTh */
    val = (pdata->curr_min * pdata->rsense / 400) & 0xFF;
    val |= (((pdata->curr_max * pdata->rsense / 400) & 0xFF) << 8);
    max77658_write_reg(ctx, MAX1726X_IALRTTH_REG, val);
}

static int max1726x_get_temperature(maxdev_ctx_t *ctx, int *temp)
{
    int ret;
    uint16_t data;

    ret = max77658_read_reg(ctx, MAX1726X_TEMP_REG, &data);
    if (ret < 0)
        return ret;

    *temp = data;
    /* The value is signed. */
    if (*temp & 0x8000)
        *temp |= 0xFFFF0000;

    /* The value is converted into centigrade scale */
    /* Units of LSB = 1 / 256 degree Celsius */
    *temp >>= 8;

    return 0;
}

static int max1726x_get_temperature_limit(maxdev_ctx_t *ctx, int *temp, int shift)
{
    int ret;
    uint16_t data;

    ret = max77658_read_reg(ctx, MAX1726X_TALRTTH_REG, &data);
    if (ret < 0)
        return ret;

    *temp = data >> shift;
    /* The value is signed */
    if(*temp & 0x80)
        *temp |= 0xFFFFFF00;

    /* LSB is 1DegreeC */
    return 0;
}

static int32_t max77568_initialize_config(maxdev_ctx_t *ctx)
{
   int32_t ret;
   uint16_t reg;
   uint16_t hibcfg;

   max77658_version_get(ctx);
   max77568_POR_status_get(ctx);
   max77658_flag_polling(ctx,MAX1726X_FSTAT_REG, MAX77658_FSTAT_DNR, 500);

   max77658_read_reg(ctx, MAX1726X_HIBCFG_REG, &hibcfg);    //Store original HibCFG value
   max77658_write_reg(ctx, 0x60, 0x90);                     // Exit Hibernate Mode step 1
   max77658_write_reg(ctx, 0xBA, 0x0);                      // Exit Hibernate Mode step 2
   max77658_write_reg(ctx, 0x60, 0x0);                      // Exit Hibernate Mode step 3

   /* Step 2: Initialize configuration */
   switch(ctx->pdata->model_option)
   {
      case MODEL_LOADING_OPTION1:
      {
         /* Step 2.1: Option 1 EZ Config */
         ret = max77568_config_option_1(ctx, hibcfg);
         break;
      }
      case MODEL_LOADING_OPTION2:
      {
         /* Step 2.2: Option 2 Custom Short INI without OCV Table */
         ret = max77568_config_option_2(ctx, hibcfg);
         break;
      }
      case MODEL_LOADING_OPTION3:
      {
         /* Step 2.3: Option 3 Custom Full INI with OCV Table */
         ret = max77568_config_option_3(ctx, hibcfg);
         break;
      }
      default:
      {
         break;
      }
   }

   /* Optional step - alert threshold initialization */
   max77658_set_alert_thresholds(ctx);

   /* Clear Status.POR */
   max77658_read_reg(ctx, MAX1726X_STATUS_REG, &reg);
   max77658_write_verify_reg(ctx, MAX1726X_STATUS_REG, reg & ~MAX77658_STATUS_POR);

   return ret;
}

static int max1726x_get_battery_health(maxdev_ctx_t *ctx, int *health)
{
    int temp, vavg, vbatt, ret;
    uint16_t val;

    ret = max77658_read_reg(ctx, MAX1726X_AVGVCELL_REG, &val);
    if (ret < 0)
        goto health_error;

    /* bits [0-3] unused */
    vavg = max1726x_lsb_to_uvolts(val);
    /* Convert to millivolts */
    vavg /= 1000;

    ret = max77658_read_reg(ctx, MAX1726X_VCELL_REG, &val);
    if (ret < 0)
        goto health_error;

    /* bits [0-3] unused */
    vbatt = max1726x_lsb_to_uvolts(val);
    /* Convert to millivolts */
    vbatt /= 1000;

    if (vavg < ctx->pdata->volt_min) {
        *health = POWER_SUPPLY_HEALTH_DEAD;
        goto out;
    }

    if (vbatt > ctx->pdata->volt_max + MAX1726X_VMAX_TOLERANCE) {
        *health = POWER_SUPPLY_HEALTH_OVERVOLTAGE;
        goto out;
    }

    ret = max1726x_get_temperature(ctx, &temp);
    if (ret < 0)
        goto health_error;

    if (temp <= ctx->pdata->temp_min) {
        *health = POWER_SUPPLY_HEALTH_COLD;
        goto out;
    }

    if (temp >= ctx->pdata->temp_max) {
        *health = POWER_SUPPLY_HEALTH_OVERHEAT;
        goto out;
    }

    *health = POWER_SUPPLY_HEALTH_GOOD;

out:
    return 0;

health_error:
    return ret;
}

static int max1726x_get_property(maxdev_ctx_t *ctx,
                   enum power_supply_property psp,
                   union power_supply_prop_val *val)
{
   struct max1726x_platform_data *pdata = ctx->pdata;
   uint16_t reg;
   int ret;

   switch (psp)
   {
      case POWER_SUPPLY_PROP_PRESENT:
      {
         ret = max77658_read_reg(ctx, MAX1726X_STATUS_REG, &reg);
         if (ret < 0)
         return ret;
         if (reg & MAX1726X_STATUS_BST)
         val->intval = 0;
         else
         val->intval = 1;
         break;
      }
      case POWER_SUPPLY_PROP_CYCLE_COUNT:
      {
         ret = max77658_read_reg(ctx, MAX1726X_CYCLES_REG, &reg);
         if (ret < 0)
         return ret;

         val->intval = reg;
         break;
      }
      case POWER_SUPPLY_PROP_VOLTAGE_MAX:
      {
         ret = max77658_read_reg(ctx, MAX1726X_MAXMINVOLT_REG, &reg);
         if (ret < 0)
         return ret;

         val->intval = reg >> 8;
         val->intval *= 20000; /* Units of LSB = 20mV */
         break;
      }
      case POWER_SUPPLY_PROP_VOLTAGE_MIN_DESIGN:
      {
         ret = max77658_read_reg(ctx, MAX1726X_VEMPTY_REG, &reg);
         if (ret < 0)
         return ret;

         val->intval = reg >> 7;
         val->intval *= 10000; /* Units of LSB = 10mV */
         break;
      }
      case POWER_SUPPLY_PROP_STATUS:
      {
         if (pdata && pdata->get_charging_status)
         val->intval = pdata->get_charging_status();
         else
         val->intval = POWER_SUPPLY_STATUS_UNKNOWN;
         break;
      }
      case POWER_SUPPLY_PROP_VOLTAGE_NOW:
      {
         ret = max77658_read_reg(ctx, MAX1726X_VCELL_REG, &reg);
         if (ret < 0)
         return ret;

         val->intval = max1726x_lsb_to_uvolts(reg);
         break;
      }
      case POWER_SUPPLY_PROP_VOLTAGE_AVG:
      {
         ret = max77658_read_reg(ctx, MAX1726X_AVGVCELL_REG, &reg);
         if (ret < 0)
         return ret;

         val->intval = max1726x_lsb_to_uvolts(reg);
         break;
      }
      case POWER_SUPPLY_PROP_VOLTAGE_OCV:
      {
         ret = max77658_read_reg(ctx, MAX1726X_OCV_REG, &reg);
         if (ret < 0)
         return ret;

         val->intval = max1726x_lsb_to_uvolts(reg);
         break;
      }
      case POWER_SUPPLY_PROP_CAPACITY:
      {
         ret = max77658_read_reg(ctx,MAX1726X_REPSOC_REG, &reg);
         if (ret < 0)
         return ret;

         val->intval = reg >> 8; /* RepSOC LSB: 1/256 % */
         break;
      }
      case POWER_SUPPLY_PROP_CHARGE_FULL:
      {
         ret = max77658_read_reg(ctx, MAX1726X_FULLCAPREP_REG, &reg);
         if (ret < 0)
         return ret;

         val->intval = (reg * 1000) >> 1; /* FullCAPRep LSB: 0.5 mAh */
         break;
      }
      case POWER_SUPPLY_PROP_CHARGE_COUNTER:
      {
         ret = max77658_read_reg(ctx, MAX1726X_QH_REG, &reg);
         if (ret < 0)
         return ret;

         val->intval = ((int16_t)reg * 1000) >> 1; /* QH LSB: 0.5 mAh */
         break;
      }
      case POWER_SUPPLY_PROP_CHARGE_NOW:
      {
         ret = max77658_read_reg(ctx, MAX1726X_REPCAP_REG, &reg);
         if (ret < 0)
         return ret;

         val->intval = (reg * 1000) >> 1; /* RepCAP LSB: 0.5 mAh */
         break;
      }
      case POWER_SUPPLY_PROP_TEMP:
      {
         ret = max1726x_get_temperature(ctx, &val->intval);
         if (ret < 0)
         return ret;

         val->intval *= 10; /* Convert 1DegreeC LSB to 0.1DegreeC LSB */
         break;
      }
      case POWER_SUPPLY_PROP_TEMP_ALERT_MIN:
      {
         ret = max1726x_get_temperature_limit(ctx, &val->intval, MIN_TEMP_ALERT);
         if (ret < 0)
         return ret;

         val->intval *= 10; /* Convert 1DegreeC LSB to 0.1DegreeC LSB */
         break;
      }
      case POWER_SUPPLY_PROP_TEMP_ALERT_MAX:
      {
         ret = max1726x_get_temperature_limit(ctx, &val->intval, MAX_TEMP_ALERT);
         if (ret < 0)
         return ret;

         val->intval *= 10; /* Convert 1DegreeC LSB to 0.1DegreeC LSB */
         break;
      }
      case POWER_SUPPLY_PROP_HEALTH:
      {
         ret = max1726x_get_battery_health(ctx, &val->intval);
         if (ret < 0)
         return ret;
         break;
         case POWER_SUPPLY_PROP_CURRENT_NOW:
         ret = max77658_read_reg(ctx, MAX1726X_CURRENT_REG, &reg);
         if (ret < 0)
         return ret;

         val->intval = max1726x_raw_current_to_uamps(ctx, reg);
         break;
      }
      case POWER_SUPPLY_PROP_CURRENT_AVG:
      {
         ret = max77658_read_reg(ctx, MAX1726X_AVGCURRENT_REG, &reg);
         if (ret < 0)
         return ret;

         val->intval = max1726x_raw_current_to_uamps(ctx, reg);
         break;
      }
      case POWER_SUPPLY_PROP_TIME_TO_EMPTY_AVG:
      {
         ret = max77658_read_reg(ctx, MAX1726X_TTE_REG, &reg);
         if (ret < 0)
         return ret;

         val->intval = (reg * 45) >> 3; /* TTE LSB: 5.625 sec */
         break;
      }
      case POWER_SUPPLY_PROP_TIME_TO_FULL_NOW:
      {
         ret = max77658_read_reg(ctx, MAX1726X_TTF_REG, &reg);
         if (ret < 0)
         return ret;

         val->intval = (reg * 45) >> 3; /* TTE LSB: 5.625 sec */
         break;
      }
      default:
      {
         return -1;
      }
   }
   return 0;
}

