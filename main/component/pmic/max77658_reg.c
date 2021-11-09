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
/* POR Mask */
#define MAX17055_POR_MASK               (0xFFFD)
#define MAX17055_CYCLE_MASK             (0x0002)

/* STATUS register bits */
#define STATUS_BST             (1 << 3)
#define MAX77658_STATUS_POR             (1 << 1)

/* MODELCFG register bits */
#define MAX77658_MODELCFG_REFRESH       (1 << 15)

/* FSTAT register bits */
#define MAX77658_FSTAT_DNR              (1)

/* TALRTTH register bits */
#define MIN_TEMP_ALERT                  0
#define MAX_TEMP_ALERT                  8

#define VMAX_TOLERANCE     50 /* 50 mV */

/* Private enumerate/structure ---------------------------------------- */
/* Private macros ----------------------------------------------------- */
/* Public variables --------------------------------------------------- */
/* Private variables -------------------------------------------------- */
static const char *TAG = "MAX77658 REG";

/* Private function prototypes ---------------------------------------- */
//static void m_bsp_i2c_init(void);

/* Function definitions ----------------------------------------------- */

/**
 * @brief      Reads from MAX17055 register.
 *
 * @param[in]  reg_addr  The register address
 * @param      value     The value
 *
 * @retval     0 on success
 * @retval     non-0 for errors
 */
int32_t max77658_read_reg(maxdev_ctx_t *ctx, uint8_t reg_addr, uint16_t *value)
{
   int32_t ret;
   uint16_t mask = 0x00FF;
   uint8_t read_data[2];

   ret = ctx->read_reg(ctx->device_address, reg_addr, read_data, 2);
   if(ret == 0)
   {
      *value = (((read_data[1] & mask) << 8) + (read_data[0]));
   }

   return ret;
}

/**
 * @brief      Writes a register.
 *
 * @param[in]  reg_addr  The register address
 * @param[in]  reg_data  The register data
 *
 * @retval     0 on success
 * @retval     non-0 for errors
 */
int32_t max77658_write_reg(maxdev_ctx_t *ctx, uint8_t reg_addr, uint16_t reg_data)
{
   int32_t ret;
   uint16_t mask = 0x00FF;
   uint8_t dataLSB;
   uint8_t dataMSB;

   dataLSB = reg_data & mask;
   dataMSB = (reg_data >> 8) & mask;
   uint8_t buff[2] = {dataLSB, dataMSB};

   ret = ctx->write_reg(ctx->device_address, reg_addr, buff, 2);

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

static inline int lsb_to_uvolts(int lsb)
{
   return lsb * 625 / 8; /* 78.125uV per bit */
}

static int raw_current_to_uamps(maxdev_ctx_t *ctx, uint32_t curr)
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

   ret = max77658_read_reg(ctx, VERSION_REG, &version);

   if(ret > 0)
   {
      ESP_LOGI(TAG, "IC Version: 0x%04x\n", version);
   }

   return ret;
}

static int32_t max77658_POR_status_get(maxdev_ctx_t *ctx)
{
   int32_t ret;
   uint16_t data;

   /* Step 0: Check for POR */
   /* Skip load model if POR bit is cleared */
   ret = max77658_read_reg(ctx, STATUS_REG, &data);
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

static int32_t max77658_config_option_1(maxdev_ctx_t *ctx, uint16_t hibcfg)
{
   int32_t ret;

   /* Step 2.1: Option 1 EZ Config */
   ret = max77658_write_reg(ctx, DESIGNCAP_REG, ctx->pdata->designcap);
   ret = max77658_write_reg(ctx, ICHGTERM_REG, ctx->pdata->ichgterm);
   ret = max77658_write_reg(ctx, VEMPTY_REG, ctx->pdata->vempty);

   if(ctx->pdata->vcharge > 4275)
   {
      ret = max77658_write_reg(ctx, MODELCFG_REG, 0x8400);
   }
   else
   {
      ret = max77658_write_reg(ctx, MODELCFG_REG, 0x8000);
   }

   /* Poll ModelCFG.ModelRefresh bit for clear */
   ret = max77658_flag_polling(ctx, MODELCFG_REG, MAX77658_MODELCFG_REFRESH, 500);
   if(ret < 0)
   {
       ESP_LOGE(TAG, "Option1 model refresh not completed!\n");
       return ret;
   }

   ret = max77658_write_reg(ctx, HIBCFG_REG, hibcfg); // Restore Original HibCFG value

   return ret;
}

static int32_t max77658_config_option_2(maxdev_ctx_t *ctx, uint16_t hibcfg)
{
   int32_t ret;

   /* Step 2.2: Option 2 Custom Short INI without OCV Table */
   ret = max77658_write_reg(ctx, DESIGNCAP_REG, ctx->pdata->designcap);
   ret = max77658_write_reg(ctx, ICHGTERM_REG, ctx->pdata->ichgterm);
   ret = max77658_write_reg(ctx, VEMPTY_REG, ctx->pdata->vempty);
   max77658_write_verify_reg(ctx, LEARNCFG_REG, ctx->pdata->learncfg); /* Optional */
   max77658_write_verify_reg(ctx, FULLSOCTHR_REG, ctx->pdata->fullsocthr); /* Optional */

   ret = max77658_write_reg(ctx, MODELCFG_REG, ctx->pdata->modelcfg);

   /* Poll ModelCFG.ModelRefresh bit for clear */
   ret = max77658_flag_polling(ctx, MODELCFG_REG, MAX77658_MODELCFG_REFRESH, 500);
   if(ret < 0)
   {
      ESP_LOGE(TAG, "Option2 model refresh not completed!\n");
      return ret;
   }

   ret = max77658_write_reg(ctx, RCOMP0_REG, ctx->pdata->rcomp0);
   ret = max77658_write_reg(ctx, TEMPCO_REG, ctx->pdata->tempco);
   ret = max77658_write_reg(ctx, QRTABLE00_REG, ctx->pdata->qrtable00);
   ret = max77658_write_reg(ctx, QRTABLE10_REG, ctx->pdata->qrtable10);
   ret = max77658_write_reg(ctx, QRTABLE20_REG, ctx->pdata->qrtable20);  /* Optional */
   ret = max77658_write_reg(ctx, QRTABLE30_REG, ctx->pdata->qrtable30);  /* Optional */

   ret = max77658_write_reg(ctx, HIBCFG_REG, hibcfg); // Restore Original HibCFG value

   return ret;
}

static int32_t max77568_fg_config_option_3(maxdev_ctx_t *ctx, uint16_t hibcfg)
{
   int32_t ret;
   /* Step 2.3: Option 3 Custom Full INI with OCV Table */
   /* Steps 2.3.1-3: Unlock model access, write/read/verify custom model,
                                     lock model access */

//   ret = load_model(priv);
//   if(ret){
//   dev_err(priv->dev, "Option3 model table write unsuccessful!\n");
//   return ret;
//   }
//
//   /* Steps 2.3.4: Verify that model access is locked */
//   ret = verify_model_lock(priv);
//   if(ret){
//   dev_err(priv->dev, "Option3 model unlock unsuccessful!\n");
//   return ret;
//   }
//
//   /* Step 2.3.5 Write custom paramaters */
//   regmap_write(regmap, REPCAP_REG, 0x0);
//   regmap_write(regmap, DESIGNCAP_REG, pdata->designcap);
//   regmap_write(regmap, DPACC_REG, 0xC80);
//   regmap_write(regmap, ICHGTERM_REG, pdata->ichgterm);
//   regmap_write(regmap, VEMPTY_REG, pdata->vempty);
//   regmap_write(regmap, RCOMP0_REG, pdata->rcomp0);
//   regmap_write(regmap, TEMPCO_REG, pdata->tempco);
//   regmap_write(regmap, QRTABLE00_REG, pdata->qrtable00);
//   regmap_write(regmap, QRTABLE10_REG, pdata->qrtable10);
//   regmap_write(regmap, QRTABLE20_REG, pdata->qrtable20);  /* Optional */
//   regmap_write(regmap, QRTABLE30_REG, pdata->qrtable30);  /* Optional */
//
//   /* Optional */
//   write_verify_reg(regmap, LEARNCFG_REG, pdata->learncfg);
//   regmap_write(regmap, RELAXCFG_REG, pdata->relaxcfg);
//   regmap_write(regmap, CONFIG_REG, pdata->config);
//   regmap_write(regmap, CONFIG2_REG, pdata->config2);
//   regmap_write(regmap, FULLSOCTHR_REG, pdata->fullsocthr);
//   regmap_write(regmap, TGAIN_REG, pdata->tgain);
//   regmap_write(regmap, TOFF_REG, pdata->toff);
//   regmap_write(regmap, CURVE_REG, pdata->curve);
//
//   /* Step 2.3.6 Initiate model loading */
//   regmap_read(regmap, CONFIG2_REG, &reg);
//   regmap_write(regmap, CONFIG2_REG, reg | CONFIG2_LDMDL); /* Set Config2.LdMdl bit */
//
//   /* Step 2.3.7 Poll the Config2.LdMdl=0 */
//   ret = poll_flag_clear(regmap, CONFIG2_REG, CONFIG2_LDMDL, 5000);
//   if(ret < 0){
//      dev_err(priv->dev, "Option3 LdMdl not completed!\n");
//      return ret;
//   }
//
//   /* Step 2.3.8 Update QRTable20 and QRTable30*/
//   write_verify_reg(regmap, QRTABLE20_REG, pdata->qrtable20);
//   write_verify_reg(regmap, QRTABLE30_REG, pdata->qrtable30);
//
//   /* Step 2.3.9 Restore original HibCfg */
//   regmap_write(regmap, HIBCFG_REG, hibcfg);

   return ret;
}

static void max77658_set_alert_thresholds(maxdev_ctx_t *ctx)
{
    platform_data *pdata = ctx->pdata;
    uint16_t val;

    /* Set VAlrtTh */
    val = (pdata->volt_min / 20);
    val |= ((pdata->volt_max / 20) << 8);
    max77658_write_reg(ctx, VALRTTH_REG, val);

    /* Set TAlrtTh */
    val = pdata->temp_min & 0xFF;
    val |= ((pdata->temp_max & 0xFF) << 8);
    max77658_write_reg(ctx, TALRTTH_REG, val);

    /* Set SAlrtTh */
    val = pdata->soc_min;
    val |= (pdata->soc_max << 8);
    max77658_write_reg(ctx, SALRTTH_REG, val);

    /* Set IAlrtTh */
    val = (pdata->curr_min * pdata->rsense / 400) & 0xFF;
    val |= (((pdata->curr_max * pdata->rsense / 400) & 0xFF) << 8);
    max77658_write_reg(ctx, IALRTTH_REG, val);
}

static int get_temperature(maxdev_ctx_t *ctx, int *temp)
{
    int ret;
    uint16_t data;

    ret = max77658_read_reg(ctx, TEMP_REG, &data);
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

static int get_temperature_limit(maxdev_ctx_t *ctx, int *temp, int shift)
{
    int ret;
    uint16_t data;

    ret = max77658_read_reg(ctx, TALRTTH_REG, &data);
    if (ret < 0)
        return ret;

    *temp = data >> shift;
    /* The value is signed */
    if(*temp & 0x80)
        *temp |= 0xFFFFFF00;

    /* LSB is 1DegreeC */
    return 0;
}

static int32_t max77568_fg_initialize_config(maxdev_ctx_t *ctx)
{
   int32_t ret;
   uint16_t reg;
   uint16_t hibcfg;

   max77658_version_get(ctx);
   max77658_POR_status_get(ctx);
   max77658_flag_polling(ctx,FSTAT_REG, MAX77658_FSTAT_DNR, 500);

   max77658_read_reg(ctx, HIBCFG_REG, &hibcfg);    //Store original HibCFG value
   max77658_write_reg(ctx, 0x60, 0x90);                     // Exit Hibernate Mode step 1
   max77658_write_reg(ctx, 0xBA, 0x0);                      // Exit Hibernate Mode step 2
   max77658_write_reg(ctx, 0x60, 0x0);                      // Exit Hibernate Mode step 3

   /* Step 2: Initialize configuration */
   switch(ctx->pdata->model_option)
   {
      case MODEL_LOADING_OPTION1:
      {
         /* Step 2.1: Option 1 EZ Config */
         ret = max77658_config_option_1(ctx, hibcfg);
         break;
      }
      case MODEL_LOADING_OPTION2:
      {
         /* Step 2.2: Option 2 Custom Short INI without OCV Table */
         ret = max77658_config_option_2(ctx, hibcfg);
         break;
      }
      case MODEL_LOADING_OPTION3:
      {
         /* Step 2.3: Option 3 Custom Full INI with OCV Table */
         ret = max77568_fg_config_option_3(ctx, hibcfg);
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
   max77658_read_reg(ctx, STATUS_REG, &reg);
   max77658_write_verify_reg(ctx, STATUS_REG, reg & ~MAX77658_STATUS_POR);

   return ret;
}

static int get_battery_health(maxdev_ctx_t *ctx, int *health)
{
    int temp, vavg, vbatt, ret;
    uint16_t val;

    ret = max77658_read_reg(ctx, AVGVCELL_REG, &val);
    if (ret < 0)
        goto health_error;

    /* bits [0-3] unused */
    vavg = lsb_to_uvolts(val);
    /* Convert to millivolts */
    vavg /= 1000;

    ret = max77658_read_reg(ctx, VCELL_REG, &val);
    if (ret < 0)
        goto health_error;

    /* bits [0-3] unused */
    vbatt = lsb_to_uvolts(val);
    /* Convert to millivolts */
    vbatt /= 1000;

    if (vavg < ctx->pdata->volt_min) {
        *health = POWER_SUPPLY_HEALTH_DEAD;
        goto out;
    }

    if (vbatt > ctx->pdata->volt_max + VMAX_TOLERANCE) {
        *health = POWER_SUPPLY_HEALTH_OVERVOLTAGE;
        goto out;
    }

    ret = get_temperature(ctx, &temp);
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

static int get_property(maxdev_ctx_t *ctx,
                   enum power_supply_property psp,
                   union power_supply_prop_val *val)
{
   platform_data *pdata = ctx->pdata;
   uint16_t reg;
   int ret;

   switch (psp)
   {
      case POWER_SUPPLY_PROP_PRESENT:
      {
         ret = max77658_read_reg(ctx, STATUS_REG, &reg);
         if (ret < 0)
         return ret;
         if (reg & STATUS_BST)
         val->intval = 0;
         else
         val->intval = 1;
         break;
      }
      case POWER_SUPPLY_PROP_CYCLE_COUNT:
      {
         ret = max77658_read_reg(ctx, CYCLES_REG, &reg);
         if (ret < 0)
         return ret;

         val->intval = reg;
         break;
      }
      case POWER_SUPPLY_PROP_VOLTAGE_MAX:
      {
         ret = max77658_read_reg(ctx, MAXMINVOLT_REG, &reg);
         if (ret < 0)
         return ret;

         val->intval = reg >> 8;
         val->intval *= 20000; /* Units of LSB = 20mV */
         break;
      }
      case POWER_SUPPLY_PROP_VOLTAGE_MIN_DESIGN:
      {
         ret = max77658_read_reg(ctx, VEMPTY_REG, &reg);
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
         ret = max77658_read_reg(ctx, VCELL_REG, &reg);
         if (ret < 0)
         return ret;

         val->intval = lsb_to_uvolts(reg);
         break;
      }
      case POWER_SUPPLY_PROP_VOLTAGE_AVG:
      {
         ret = max77658_read_reg(ctx, AVGVCELL_REG, &reg);
         if (ret < 0)
         return ret;

         val->intval = lsb_to_uvolts(reg);
         break;
      }
      case POWER_SUPPLY_PROP_VOLTAGE_OCV:
      {
         ret = max77658_read_reg(ctx, OCV_REG, &reg);
         if (ret < 0)
         return ret;

         val->intval = lsb_to_uvolts(reg);
         break;
      }
      case POWER_SUPPLY_PROP_CAPACITY:
      {
         ret = max77658_read_reg(ctx,REPSOC_REG, &reg);
         if (ret < 0)
         return ret;

         val->intval = reg >> 8; /* RepSOC LSB: 1/256 % */
         break;
      }
      case POWER_SUPPLY_PROP_CHARGE_FULL:
      {
         ret = max77658_read_reg(ctx, FULLCAPREP_REG, &reg);
         if (ret < 0)
         return ret;

         val->intval = (reg * 1000) >> 1; /* FullCAPRep LSB: 0.5 mAh */
         break;
      }
      case POWER_SUPPLY_PROP_CHARGE_COUNTER:
      {
         ret = max77658_read_reg(ctx, QH_REG, &reg);
         if (ret < 0)
         return ret;

         val->intval = ((int16_t)reg * 1000) >> 1; /* QH LSB: 0.5 mAh */
         break;
      }
      case POWER_SUPPLY_PROP_CHARGE_NOW:
      {
         ret = max77658_read_reg(ctx, REPCAP_REG, &reg);
         if (ret < 0)
         return ret;

         val->intval = (reg * 1000) >> 1; /* RepCAP LSB: 0.5 mAh */
         break;
      }
      case POWER_SUPPLY_PROP_TEMP:
      {
         ret = get_temperature(ctx, &val->intval);
         if (ret < 0)
         return ret;

         val->intval *= 10; /* Convert 1DegreeC LSB to 0.1DegreeC LSB */
         break;
      }
      case POWER_SUPPLY_PROP_TEMP_ALERT_MIN:
      {
         ret = get_temperature_limit(ctx, &val->intval, MIN_TEMP_ALERT);
         if (ret < 0)
         return ret;

         val->intval *= 10; /* Convert 1DegreeC LSB to 0.1DegreeC LSB */
         break;
      }
      case POWER_SUPPLY_PROP_TEMP_ALERT_MAX:
      {
         ret = get_temperature_limit(ctx, &val->intval, MAX_TEMP_ALERT);
         if (ret < 0)
         return ret;

         val->intval *= 10; /* Convert 1DegreeC LSB to 0.1DegreeC LSB */
         break;
      }
      case POWER_SUPPLY_PROP_HEALTH:
      {
         ret = get_battery_health(ctx, &val->intval);
         if (ret < 0)
         return ret;
         break;
         case POWER_SUPPLY_PROP_CURRENT_NOW:
         ret = max77658_read_reg(ctx, CURRENT_REG, &reg);
         if (ret < 0)
         return ret;

         val->intval = raw_current_to_uamps(ctx, reg);
         break;
      }
      case POWER_SUPPLY_PROP_CURRENT_AVG:
      {
         ret = max77658_read_reg(ctx, AVGCURRENT_REG, &reg);
         if (ret < 0)
         return ret;

         val->intval = raw_current_to_uamps(ctx, reg);
         break;
      }
      case POWER_SUPPLY_PROP_TIME_TO_EMPTY_AVG:
      {
         ret = max77658_read_reg(ctx, TTE_REG, &reg);
         if (ret < 0)
         return ret;

         val->intval = (reg * 45) >> 3; /* TTE LSB: 5.625 sec */
         break;
      }
      case POWER_SUPPLY_PROP_TIME_TO_FULL_NOW:
      {
         ret = max77658_read_reg(ctx, TTF_REG, &reg);
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


/**
 * @brief        Save Learned Parameters Function for battery Fuel Gauge model.
 * @par          Details
 *               It is recommended to save the learned capacity parameters every
 *               time bit 2 of the Cycles register toggles
 *               (so that it is saved every 64% change in the battery)
 *               so that if power is lost the values can easily be restored. Make sure
 *               the data is saved on a non-volatile memory. Call this function after first initialization for reference in future function calls.
 *               Max number of cycles is 655.35 cycles with a LSB of 1% for the cycles register.
 *
 * @param[in]   FG_params Fuel Gauge Parameters based on design details.
 *
 * @retval      0 for success
 * @retval      non-0 negative for errors
 */
static int max77658_fg_save_Params(maxdev_ctx_t *ctx, saved_FG_params_t FG_params)
{
    int ret;
    uint16_t data[5], value;
    ///STEP 1. Checks if the cycle register bit 2 has changed.
    ret = max77658_read_reg(ctx, CYCLES_REG, &data[3]);
    value = data[3];
    if (ret < 0)
        return ret;
    //Check if the stored cycles value is different from the read Cycles_reg value
    else if (FG_params.cycles == value)
        return ret; //exits the function without saving, when initializing or value did not change (calculate when the function is called in you application).
    else {
        value = FG_params.cycles^value;
        //check with mask
        value = (value & MAX17055_POR_MASK);

        if (value == 0)
            return ret;

        ///STEP 2. Save the capacity parameters for the specific battery.
        ret = max77658_read_reg(ctx, RCOMP0_REG, &data[0]);
        if (ret < 0)
            return ret;
        else
            FG_params.rcomp0 = data[0];

        ret = max77658_read_reg(ctx, TEMPCO_REG, &data[1]);
        if (ret < 0)
            return ret;
        else
            FG_params.temp_co = data[1];

        ret = max77658_read_reg(ctx, FULLCAPREP_REG, &data[2]);
        if (ret < 0)
            return ret;
        else
            FG_params.full_cap_rep = data[2];

        FG_params.cycles = data[3];

        ret = max77658_read_reg(ctx, FULLCAPNOM_REG, &data[4]);
        if (ret < 0)
            return ret;
        else
            FG_params.full_cap_nom = data[4];
        return ret;
    }
}

/**
 * @brief        Restore Parameters Function for battery Fuel Gauge model.
 * @par          Details
 *               If power is lost, then the capacity information
 *               can be easily restored with this function.
 *
 * @param[in]   FG_params Struct for Fuel Gauge Parameters
 * @retval      0 for success
 * @retval      non-0 negative for errors
 */
static int max77658_restore_Params(maxdev_ctx_t *ctx, saved_FG_params_t FG_params)
{
    int ret;
    uint16_t temp_data, fullcapnom_data, mixCap_calc, dQacc_calc;
    uint16_t dPacc_value = 0x0C80;//Set it to 200%

    ///STEP 1. Restoring capacity parameters
    max77658_write_verify_reg(ctx, RCOMP0_REG, FG_params.rcomp0);
    max77658_write_verify_reg(ctx, TEMPCO_REG, FG_params.temp_co);
    max77658_write_verify_reg(ctx, FULLCAPNOM_REG, FG_params.full_cap_nom);

    bsp_delay_ms(350);//check the type of wait

    ///STEP 2. Restore FullCap
    ret = max77658_read_reg(ctx, FULLCAPNOM_REG, &fullcapnom_data);
    if (ret < 0)
        return ret;

    ret = max77658_read_reg(ctx, MIXSOC_REG, &temp_data);
    if (ret < 0)
        return ret;

    mixCap_calc = (temp_data*fullcapnom_data)/25600;

    max77658_write_verify_reg(ctx, MIXCAP_REG, mixCap_calc);
    max77658_write_verify_reg(ctx, FULLCAPREP_REG, FG_params.full_cap_rep);

    ///STEP 3. Write DQACC to 200% of Capacity and DPACC to 200%
    dQacc_calc = (FG_params.full_cap_nom/ 16) ;

    max77658_write_verify_reg(ctx, DPACC_REG, dPacc_value);
    max77658_write_verify_reg(ctx, DQACC_REG, dQacc_calc);

    bsp_delay_ms(350);

    ///STEP 4. Restore Cycles register
    ret = max77658_write_verify_reg(ctx, CYCLES_REG, FG_params.cycles);
    if (ret < 0)
        return ret;
    return ret;
}


