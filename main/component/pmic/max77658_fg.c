/*
 * max77658.c
 *
 *  Created on: Nov 9, 2021
 *      Author: kai
 */

#ifndef MAIN_COMPONENT_PMIC_MAX77658_C_
#define MAIN_COMPONENT_PMIC_MAX77658_C_

#include "max77658_fg.h"
#include "esp_log.h"
#include "bsp.h"

static const char *TAG = "MAX_FG";

/* POR Mask */
#define MAX17055_POR_MASK               (0xFFFD)
#define MAX17055_CYCLE_MASK             (0x0002)


/* MODELCFG register bits */
#define MAX17055_MODELCFG_REFRESH       (1 << 15)


/* FSTAT register bits */
#define MAX17055_FSTAT_DNR              (1)

/* LIBRARY FUNCTION SUCCESS*/
#define F_SUCCESS_0  0

/* LIBRARY FUNCTION ERROR CODES */
#define F_ERROR_1 -1    //-1 if I2C read/write errors exist
#define F_ERROR_2 -2    //-2 if device is not present
#define F_ERROR_3 -3    //-3 if function error
#define F_ERROR_4 -4    //-4 if other error
#define F_ERROR_5 -5    //-5 if POR not detected

//8-bit write address
//static const uint8_t I2C_W_ADRS = 0x6C;
//8-bit read address
//static const uint8_t I2C_R_ADRS = 0x6D;

platform_data pdata;

/**
 * @brief      Reads from MAX17055 register.
 *
 * @param[in]  reg_addr  The register address
 * @param      value     The value
 *
 * @retval     0 on success
 * @retval     non-0 for errors
 */
int32_t max77658_fg_read_reg(max77658_fg_t *ctx, uint8_t reg_addr, uint16_t *value)
{
   int32_t ret;
   uint16_t mask = 0x00FF;
   uint8_t read_data[2];

   ret = ctx->read_reg(ctx->device_address, reg_addr, &read_data, 2);
   if(ret == F_SUCCESS_0)
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
int max77658_fg_write_reg(max77658_fg_t *ctx, uint8_t reg_addr, uint16_t reg_data)
{

   int32_t ret;
   uint16_t mask = 0x00FF;
   uint8_t dataLSB;
   uint8_t dataMSB;

   dataLSB = reg_data & mask;
   dataMSB = (reg_data >> 8) & mask;
   uint8_t buff[2] = {dataLSB, dataMSB};

   ret = (F_SUCCESS_0 == ctx->write_reg(ctx->device_address, reg_addr, buff, 2))?F_SUCCESS_0:F_ERROR_1;

   return ret;
}

/**
 * @brief      Reads an specified register from the MAX17055 register.
 *
 * @param[in]  reg_addr  The register address
 * @param      value     The value
 *
 * @retval     reg_data register data
 * @retval     statusRead non-0 for errors
 */

int16_t max77658_fg_get_regInfo(max77658_fg_t *ctx, uint8_t reg_addr)
{
    uint16_t read_data;
    int status;

    status = max77658_fg_read_reg(ctx, reg_addr, &read_data);
    if (status != F_SUCCESS_0)
        return status;
    else
        return read_data;
}

/**
 * @brief        Write and Verify a MAX17055 register
 * @par          Details
 *               This function writes and verifies if the writing process was successful
 *
 * @param[in]    reg_addr     - register address
 * @param[out]   reg_data     - the variable that contains the data to write
 *                               to the register address
 *
 * @retval       0 on success
 * @retval       non-0 for errors
 */
int max77658_fg_write_and_verify_reg(max77658_fg_t *ctx, uint8_t reg_addr, uint16_t write_data)
{
   int retries = 0;
   int read_status;
   int write_status;
   uint16_t read_data;

   do
   {
      write_status = max77658_fg_write_reg(ctx, reg_addr, write_data);
      if(write_status != F_SUCCESS_0)
      {
         return F_ERROR_1;
      }

      bsp_delay_ms(1);
      read_status = max77658_fg_read_reg(ctx, reg_addr, &read_data);
      if(read_status != F_SUCCESS_0)
      {
         return F_ERROR_1;
      }
   } while (write_data != read_data && retries++<3);

   return F_SUCCESS_0;
}

/**
 * @brief       Initialization Function for MAX17055.
 * @par         Details
 *              This function initializes the MAX17055 for the implementation of the EZconfig model.\n
 *              The library needs to be customized for the implementation of customize model.\n
 *
 * @retval      0 on success
 * @retval      non-0 for errors
 */
int max77658_fg_init(max77658_fg_t *ctx)
{
   int ret;
   int time_out = 10;
   int32_t status;
   uint16_t hibcfg_value;
   uint16_t version;

   pdata.designcap  = 0x015E;  //Design Battery Capacity mAh this can change depending on the batteries implemented see battery data sheet for details.
   pdata.ichgterm  = 0x0070;  // Charge Termination Current for the Battery This is specified by the manufacturer.
   pdata.vempty  = 0x9600;  // Battery Empty Voltage This is specified by design, but manufacturer has a min Empty voltage specification.
   pdata.vcharge  = 4200;  // Battery Charge Voltage can be obtained from MAX77650 configuration
   pdata.rsense = 10; //5mOhms for MAX32620, keep in mind the MAX17055EVKIT has a 10mOhm resistor. This is a design specific value. Used for calculation results.

   ESP_LOGI(TAG, "max77658_fg_init() Read Address = %X",ctx->device_address);

   status = max77658_fg_read_reg(ctx, VERSION_REG, &version);
   if (status != F_SUCCESS_0)
      return status;

   ESP_LOGI(TAG, "max77658_fg_init() version: %d", version);
    

   ///STEP 0. Check for POR (Skip load model if POR bit is cleared)

   if (max77658_fg_check_POR_func(ctx) == F_ERROR_5)
      return F_ERROR_5;  //POR not detected. Skip Initialization.

   ///STEP 1. Check if FStat.DNR == 0 (Do not continue until FSTAT.DNR == 0)
   ret = max77658_fg_poll_flag_clear(ctx, FSTAT_REG, MAX17055_FSTAT_DNR, time_out);
   if (ret < F_SUCCESS_0) {
      return ret;
   }

   ///STEP 1.2. Force exit from hibernate
   hibcfg_value = max77658_fg_forcedExitHiberMode(ctx);
   ESP_LOGI(TAG, "max77658_fg_init() hibcfg_value: %d", hibcfg_value);

   ///STEP 2. Initialize configuration
   ///STEP 2.1. Load EZ Config
   max77658_fg_config_option_1(ctx);

   ///STEP 2.2. Poll ModelCFG.ModelRefresh bit for clear
   ret = max77658_fg_poll_flag_clear(ctx, MODELCFG_REG, MAX17055_MODELCFG_REFRESH, time_out);
   if(ret < F_SUCCESS_0) {
      return ret;
   }
   ///STEP3. Restore original HibCfg
   max77658_fg_write_reg(&ctx, HIBCFG_REG, hibcfg_value);


   /* Clear Status.POR */
   ret = max77658_fg_clear_POR_bit(ctx);
   if (ret < F_SUCCESS_0)
      return ret; //See errors

   return F_SUCCESS_0;
}

/**
 * @brief      Check POR function
 * @par Details
 *     This function check is there was a power on reset event for the
 *     MAX17055
 *
 * @retval    0 on success (POR detected)
 * @retval    non-0 for errors (POR not detected)
 *
 */
int max77658_fg_check_POR_func(max77658_fg_t *ctx)
{
    uint16_t read_data;

    max77658_fg_read_reg(ctx, STATUS_REG, &read_data);
//    printf("STATUS REF = %X \r\n", read_data);
    if (!(read_data & MAX17055_STATUS_POR ) ) {
        return F_ERROR_5;  //POR not detected.
    } else
        return F_SUCCESS_0;
}

/**
 * @brief        clear POR bit function
 * @par          Details
 *               This function clear the indicating bit for POR - MAX17055
 *
 * @retval       0 for Success
 * @retval      non-0 for errors
 */
int max77658_fg_clear_POR_bit(max77658_fg_t *ctx)
{
    int status;
    uint16_t read_data;


    status = max77658_fg_read_reg(ctx, STATUS_REG, &read_data);
    if (status != F_SUCCESS_0)
        return F_ERROR_2;  //Device is not present in the i2c Bus
    status = max77658_fg_write_and_verify_reg(ctx, STATUS_REG, (read_data & MAX17055_POR_MASK));
    if (status != F_SUCCESS_0)
        return F_ERROR_1; //read or write error
    else
        return F_SUCCESS_0;
}

/**
 * @brief      Poll Flag clear Function.
 * @par Details
 *     This function clears status flags for the MAX17055
 *
 * @param[in]  reg_addr  - register address
 * @param[in]  mask      - register address
 * @param[in]  timeout   - register data
 *
 * @retval     0 on success
 * @retval    non-0 negative for errors
 */
int max77658_fg_poll_flag_clear(max77658_fg_t *ctx, uint8_t reg_addr, int mask, int timeout)
{
    uint16_t data;
    int ret;

    do {
        bsp_delay_ms(50);
        ret = max77658_fg_read_reg(ctx, reg_addr, &data);
//        printf("read reg %X\r\n", data);
//        printf("mask %X\r\n", mask);
        if(ret < F_SUCCESS_0)
            return F_ERROR_1;


        if(!(data & mask))
            return F_SUCCESS_0;

        timeout -= 10;
//        printf("end timeout %d \r\n", timeout);
    } while(timeout > 0);

    return F_ERROR_4;
}

/**
 * @brief        Get Temperature Function from the MAX17055 TEMP register.
 * @par          Details
 *               This function sends a request to access the TEMP register
 *               of the MAX17055, which reflects the temperature measured for the fuel gauge.
 *               The temperature values will reflect the Config Register (0x1D) selections for Tsel bit (D15).
 *               For this library the setting are for die temperature.
 *               The MAX32620FTHR thermistor bias pin is not connected. The biasing of the thermistor is
 *               done by the MAX77650. See MAX77650 library for how to enable the thermistor biasing.
 *
 *
 * @retval      temp - Temperature value from TEMP register in &deg;C
 * @retval      non-0 negative values check for errors
 */
int max77658_fg_get_temperature(max77658_fg_t *ctx)
{

    int ret;
    uint16_t temp;

    ret = max77658_fg_read_reg(ctx, TEMP_REG, &temp);
    if (ret < F_SUCCESS_0)
        return ret;

    /* The value is signed. */
    if (temp & 0x8000)
        temp |= 0xFFFF0000;

    /* The value is converted into centigrade scale */
    /* Units of LSB = 1 / 256 degree Celsius */
    temp >>= 8;

    return temp;
}

/**
 * @brief        Forced Exit Hibernate Mode Function for MAX17055
 * @par          Details
 *               This function executes a force exit from hibernate mode.
 *
 * @retval       HibCFG original value before forced Exit Hibernate mode *
 */
uint16_t max77658_fg_forcedExitHiberMode(max77658_fg_t *ctx)
{
    uint16_t hibcfg;

    /* Force exit from hibernate */
    //STEP 0: Store original HibCFG value
    max77658_fg_read_reg(ctx, HIBCFG_REG, &hibcfg);

    //STEP 1: Write to Soft-Wakeup Command Register
    max77658_fg_write_reg(ctx, VFSOC0_QH0_LOCK_REG, 0x90); //Soft-Wakeup from hibernate

    //STEP 2: Write to Hibernate Configuration register
    max77658_fg_write_reg(ctx, HIBCFG_REG, 0x0); //disable hibernate mode

    //STEP 3:Write to Soft-Wakeup Command Register
    max77658_fg_write_reg(ctx, VFSOC0_QH0_LOCK_REG, 0x0); //Clear All commands

    return hibcfg;
}

/**
 * @brief        EZ Config function
 * @par          Details
 *               This function implements the steps for the EZ config m5 FuelGauge
 * @param[in]    des_data - Plataform_data struct with information about the design.
 * @retval       0 on success
 * @retval       non-zero for errors
 */
uint16_t max77658_fg_config_option_1(max77658_fg_t *ctx)
{
   ESP_LOGI(TAG, "max77658_fg_config_option_1() Read Address = %X",ctx->device_address);

    //STEP 2.1.1 EZ config values suggested by manufacturer.
    const int charger_th = 4275;
    const int chg_V_high = 51200; // scaling factor high voltage charger
    const int chg_V_low = 44138;
    const int param_EZ_FG1 = 0x8400; // Sets config bit for the charge voltage for the m5
    const int param_EZ_FG2 = 0x8000;
    uint16_t dpacc, ret;
    const int DIV_32 = 5;//DesignCap divide by 32 for EZ config
    //    const int DIV_16 = 4;//DesignCap divide by 16 only for custom ini files

    //STEP 2.1.2 Store the EZ Config values into the appropriate registers.
    ret = max77658_fg_write_reg(ctx, DESIGNCAP_REG, pdata.designcap);
    ret = max77658_fg_write_reg(ctx, DQACC_REG, pdata.designcap >> DIV_32);
    ret = max77658_fg_write_reg(ctx, ICHGTERM_REG, pdata.ichgterm);
    ret = max77658_fg_write_reg(ctx, VEMPTY_REG, pdata.vempty);

    if (pdata.vcharge > charger_th) {
        dpacc = (pdata.designcap >> DIV_32) * chg_V_high / pdata.designcap;
        ret = max77658_fg_write_reg(ctx, DPACC_REG, dpacc);
        ret = max77658_fg_write_reg(ctx, MODELCFG_REG, param_EZ_FG1); //
    } else {
        dpacc = (pdata.designcap >> DIV_32) * chg_V_low / pdata.designcap;
        ret = max77658_fg_write_reg(ctx, DPACC_REG, dpacc);
        ret = max77658_fg_write_reg(ctx, MODELCFG_REG, param_EZ_FG2);
    }
    return ret;
}

/**
 * @brief        Config function option 2
 * @par          Details
 *               This function implements the steps for the EZ config m5 FuelGauge
 * @param[in]    des_data - Plataform_data struct with information about the design.
 * @retval       0 on success
 * @retval       non-zero for errors
 */
int32_t max77658_fg_config_option_2(max77658_fg_t *ctx)
{
   int32_t ret;

   /* Step 2.2: Option 2 Custom Short INI without OCV Table */
   ret = max77658_fg_write_reg(ctx, DESIGNCAP_REG, pdata.designcap);
   ret = max77658_fg_write_reg(ctx, ICHGTERM_REG, pdata.ichgterm);
   ret = max77658_fg_write_reg(ctx, VEMPTY_REG, pdata.vempty);
   max77658_fg_write_and_verify_reg(ctx, LEARNCFG_REG, pdata.learncfg); /* Optional */
   max77658_fg_write_and_verify_reg(ctx, FULLSOCTHR_REG, pdata.fullsocthr); /* Optional */

   ret = max77658_fg_write_reg(ctx, MODELCFG_REG, pdata.modelcfg);

   /* Poll ModelCFG.ModelRefresh bit for clear */
   ret = max77658_fg_poll_flag_clear(ctx, MODELCFG_REG, MAX17055_MODELCFG_REFRESH, 500);
   if(ret < 0)
   {
//      ESP_LOGE(TAG, "Option2 model refresh not completed!\n");
      return ret;
   }

   ret = max77658_fg_write_reg(ctx, RCOMP0_REG, pdata.rcomp0);
   ret = max77658_fg_write_reg(ctx, TEMPCO_REG, pdata.tempco);
   ret = max77658_fg_write_reg(ctx, QRTABLE00_REG, pdata.qrtable00);
   ret = max77658_fg_write_reg(ctx, QRTABLE10_REG, pdata.qrtable10);
   ret = max77658_fg_write_reg(ctx, QRTABLE20_REG, pdata.qrtable20);  /* Optional */
   ret = max77658_fg_write_reg(ctx, QRTABLE30_REG, pdata.qrtable30);  /* Optional */

   return ret;
}

/**
 * @brief        Config function option 3
 * @par          Details
 *               This function implements the steps for the EZ config m5 FuelGauge
 * @param[in]    des_data - Plataform_data struct with information about the design.
 * @retval       0 on success
 * @retval       non-zero for errors
 */
int32_t max77658_fg_config_option_3(max77658_fg_t *ctx)
{
//   int32_t ret;
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

   return 0;
}

/**
 * @brief        Get reported Battery Capacity Function from MAX17055 Fuel Gauge
 * @par          Details
 *               This function sends a request to access the RepCAP register
 *               of the MAX17055. RepCAP is the reported Battery Capacity in mAh of the battery based on the calculation by the Fuel Gauge algorithm.
 *
 * @retval      repcap_data - Reported SOC data from the RepSOC register in % value.
 * @retval      non-0 negative values check for errors
 */

int max77658_fg_get_battCAP(max77658_fg_t *ctx)
{
    int ret, design_rsense;
    uint16_t repcap_data;

    ret = max77658_fg_read_reg(ctx, REPCAP_REG, &repcap_data);
    if (ret < F_SUCCESS_0)
        return ret;
    else
        design_rsense = pdata.rsense;
    ret = max77658_fg_raw_cap_to_uAh((uint32_t)repcap_data, design_rsense);
    if (ret < F_SUCCESS_0)
        return ret;
    else
        return ret;
}

/**
 * @brief        Get reported State Of Charge(SOC) Function from MAX17055 Fuel Gauge.
 * @par          Details
 *               This function sends a request to access the RepSOC register
 *               of the MAX17055. RepSOC is the reported state-of-charge percentage output of the fuel gauge.
 *
 * @retval      soc_data - Reported SOC data from the RepSOC register in % value.
 * @retval      non-0 negative values check for errors
 */
int max77658_fg_get_SOC(max77658_fg_t *ctx)
{

    int ret;
    uint16_t soc_data;

    ret = max77658_fg_read_reg(ctx, REPSOC_REG, &soc_data);
    if (ret < F_SUCCESS_0)
        return ret;

    soc_data = soc_data >> 8; /* RepSOC LSB: 1/256 % */

    return soc_data;
}

/**
 * @brief       Get at rate Average State Of Charge(SOC) Function from MAX17055 Fuel Gauge.
 * @par          Details
 *               This function sends a request to access the atAvSOC register of the MAX17055.
 *               The AvSOC registers hold the calculated available capacity and percentage of the
 *               battery based on all inputs from the ModelGauge m5 algorithm including empty
 *               compensation. These registers provide unfiltered results. Jumps in the reported
 *               values can be caused by abrupt changes in load current or temperature.
 *
 * @retval       atAvSOC_data - Average SOC data from the atAVSOC register in % value.
 * @retval       non-0 negative values check for errors
 */
int max77658_fg_get_atAvSOC(max77658_fg_t *ctx)
{
    int ret;
    uint16_t atAvSOC_data;

    ret = max77658_fg_read_reg(ctx, AVSOC_REG, &atAvSOC_data);
    if (ret < F_SUCCESS_0)
        return ret; //Check errors if data is not correct

    atAvSOC_data = atAvSOC_data >> 8; /* avSOC LSB: 1/256 % */

    return atAvSOC_data;
}

/**
 * @brief        Get mix State Of Charge(SOC) Function for MAX17055 Fuel Gauge.
 * @par          Details
 *               This function sends a request to access mixSOC register
 *               of the MAX17055. The MixSOC registers holds the calculated
 *               remaining capacity and percentage of the cell before any empty compensation
 *               adjustments are performed.
 *
 * @retval       mixSOC_data - Mixed SOC register values from the mixSOC register in % value.
 * @retval       non-0 for errors
 */
int max77658_fg_get_mixSOC(max77658_fg_t *ctx)
{
    int ret;
    uint16_t mixSOC_data;

    ret = max77658_fg_read_reg(ctx, MIXSOC_REG, &mixSOC_data);
    if (ret < F_SUCCESS_0)
        return ret;

    mixSOC_data = mixSOC_data >> 8; /* RepSOC LSB: 1/256 % */

    return mixSOC_data;
}

/**
 * @brief       Get the Time to Empty(TTE) Function form MAX17055 Fuel Gauge.
 * @par         Details
 *              This function sends a request to access the TTE register
 *              of the MAX17055
 *              The TTE register holds the estimated time to empty for the
 *              application under present temperature and load conditions. The TTE value is
 *              determined by relating AvCap with AvgCurrent. The corresponding AvgCurrent
 *              filtering gives a delay in TTE, but provides more stable results.
 *
 * @retval      tte_data - Time to Empty data from the TTE register in seconds.
 * @retval      non-0 negative values check for errors
 */
float max77658_fg_get_TTE(max77658_fg_t *ctx)
{

    int ret;
    uint16_t tte_data;
    float f_tte_data;

    ret = max77658_fg_read_reg(ctx, TTE_REG, &tte_data);
    if (ret < F_SUCCESS_0)
        return ret;
    else
        f_tte_data = ((float)tte_data * 5.625); /* TTE LSB: 5.625 sec */

    return f_tte_data;
}

/**
 * @brief       Get the at Time to Empty(atTTE) value Function for MAX17055 Fuel Gauge.
 * @par         Details
 *              This function sends a request to access the internal register
 *              of the MAX17055
 *
 * @retval      atTTE_data - Time to Empty data from the atTTE register in seconds.
 * @retval      non-0 negative values check for errors
 */
float max77658_fg_get_atTTE(max77658_fg_t *ctx)
{

    int ret;
    uint16_t atTTE_data;
    float f_atTTE_data;

    ret = max77658_fg_read_reg(ctx, ATTTE_REG, &atTTE_data);
    if (ret < F_SUCCESS_0)
        return ret; //Check for errors
    else
        f_atTTE_data = ((float)atTTE_data * 5.625); /* TTE LSB: 5.625 sec */

    return  f_atTTE_data;
}

/**
 * @brief      Get the Time to Full(TTE) values Function for MAX17055 Fuel Gauge.
 * @par        Details
 *             This function sends a request to access the internal register of the MAX17055
 *             The TTF register holds the estimated time to full for the application
 *             under present conditions. The TTF value is determined by learning the
 *             constant current and constant voltage portions of the charge cycle based
 *             on experience of prior charge cycles. Time to full is then estimate
 *             by comparing present charge current to the charge termination current.
 *             Operation of the TTF register assumes all charge profiles are consistent in the application.
 *
 * @retval     ttf_data - Time to Full data from the TTF register in seconds.
 * @retval     non-0 negative values check for errors
 */
float max77658_fg_get_TTF(max77658_fg_t *ctx)
{

    int ret;
    uint16_t ttf_data;
    float f_ttf_data;

    ret = max77658_fg_read_reg(ctx, TTF_REG, &ttf_data);
    if (ret < F_SUCCESS_0)
        return ret;
    else
        f_ttf_data = ((float)ttf_data * 5.625); /* TTE LSB: 5.625 sec */

    return  f_ttf_data;
}

/**
 * @brief       Get voltage of the cell Function for MAX17055 Fuel Gauge.
 * @par         Details
 *              This function sends a request to access the VCell Register
 *              of the MAX17055 to read the measured voltage from the cell.
 *
 * @retval      vcell_data  - vcell data from the VCELL_REG register in uVolts.
 * @retval      non-0 negative values check for errors
 */
int max77658_fg_get_Vcell(max77658_fg_t *ctx)
{
   int ret;
   uint16_t vcell_data;

   ret = max77658_fg_read_reg(ctx, VCELL_REG, &vcell_data);
   if (ret < F_SUCCESS_0)
   {
      return ret;
   }
   else
   {
      ret = max77658_fg_lsb_to_uvolts(vcell_data);
   }
   return ret;
}

/**
 * @brief       Gets Average voltage of the cell Function for MAX17055 Fuel Gauge.
 * @par         Details
 *              This function sends a request to access the AvgVCell Register
 *              of the MAX17055 to read the measured voltage from the cell.
 *
 * @retval      avgVcell_data  - avgvcell data from the AVGVCELL_REG register in uVolts.
 * @retval      non-0 negative values check for errors
 */
double max77658_fg_get_avgVcell(max77658_fg_t *ctx)
{

    double ret;
    uint16_t avgVcell_data;

    ret = max77658_fg_read_reg(ctx, AVGVCELL_REG, &avgVcell_data);
    if (ret < F_SUCCESS_0)
        return ret;
    else
        ret = max77658_fg_lsb_to_uvolts(avgVcell_data);
    return ret;
}

/**
 * @brief       Get current Function for MAX17055 Fuel Gauge.
 * @par         Details
 *              This function sends a request to access the CURRENT register
 *              of the MAX17055 to read the current readings.
 *
 * @param[in]   des_data - Plataform_data struct with information about the design.
 *
 * @retval      curr_data  - current data from the CURRENT register in uAmps.
 * @retval      non-0 negative values check for errors.
 */
float max77658_fg_get_Current(max77658_fg_t *ctx)
{

    int ret,design_rsense;
    uint16_t curr_data;
    float f_ret;

    ret = max77658_fg_read_reg(ctx, CURRENT_REG, &curr_data);
    if (ret < F_SUCCESS_0)
        return ret;
    else
        design_rsense = pdata.rsense;
    f_ret = max77658_fg_raw_current_to_uamps((uint32_t)curr_data, design_rsense);
    return f_ret;
}

/**
 * @brief       Get average current Function for MAX17055 Fuel Gauge.
 * @par         Details
 *              This function sends a request to access the aveCURRENT register
 *              of the MAX17055 to read the average current readings.
 *
 * @param[in]   des_data - Plataform_data struct with information about the design.
 *
 * @retval      aveCurr_data - current data from the AVGCURRENT register in uAmps.
 * @retval      non-0 negative values check for errors.
 */
float max77658_fg_get_AvgCurrent(max77658_fg_t *ctx)
{
    int ret, design_rsense;
    uint16_t data;
    float avgCurr_data;

    ret = max77658_fg_read_reg(ctx, AVGCURRENT_REG, &data);
    if (ret < F_SUCCESS_0)
        return ret;
    else
        avgCurr_data = data;
    design_rsense = pdata.rsense;
    avgCurr_data = max77658_fg_raw_current_to_uamps((uint32_t)data, design_rsense);
    return avgCurr_data;
}

/**
 * @brief        lsb_to_uvolts Conversion Function
 * @par          Details
 *               This function takes the lsb value of the register and convert it
 *               to uvolts
 *
 * @param[in]   lsb - value of register lsb
 * @retval      conv_2_uvolts - value converted lsb to uvolts
 */
int max77658_fg_lsb_to_uvolts(uint16_t lsb)
{
    int conv_2_uvolts;
    conv_2_uvolts = (lsb * 625) / 8; /* 78.125uV per bit */
    return conv_2_uvolts;
}

/**
 * @brief        raw_current_to_uamp Conversion Function
 * @par          Details
 *               This function takes the raw current value of the register and
 *               converts it to uamps
 *
 * @param[in]   curr - raw current value of register
 * @retval      res  - converted raw current to uamps (Signed 2's complement)
 */
float max77658_fg_raw_current_to_uamps(uint32_t curr, int rsense_value)
{
    int res = curr;
    float final_res;
    /* Negative Check*/
    if (res & 0x8000){
        res |= 0xFFFF0000;
    }
    final_res = (float)res;
    final_res *= 1562500 /(float)(rsense_value*10000);

    return final_res;
}

/**
 * @brief        raw_cap_to_uAh Conversion Function
 * @par          Details
 *               This function takes the raw battery capacity value of the register and
 *               converts it to uAh
 *
 * @param[in]   raw_cap - raw capacity value of register
 * @retval      res  - converted raw capacity to uAh
 */
int max77658_fg_raw_cap_to_uAh(uint32_t raw_cap, int rsense_value)
{
    int res = raw_cap ;
    res *=  5000000/(rsense_value * 1000000);
    return res;
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
int max77658_fg_save_Params(max77658_fg_t *ctx, saved_FG_params_t FG_params)
{
    int ret;
    uint16_t data[5], value;
    ///STEP 1. Checks if the cycle register bit 2 has changed.
    ret = max77658_fg_read_reg(ctx, CYCLES_REG, &data[3]);
    value = data[3];
    if (ret < F_SUCCESS_0)
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
        ret = max77658_fg_read_reg(ctx, RCOMP0_REG, &data[0]);
        if (ret < F_SUCCESS_0)
            return ret;
        else
            FG_params.rcomp0 = data[0];

        ret = max77658_fg_read_reg(ctx, TEMPCO_REG, &data[1]);
        if (ret < F_SUCCESS_0)
            return ret;
        else
            FG_params.temp_co = data[1];

        ret = max77658_fg_read_reg(ctx, FULLCAPREP_REG, &data[2]);
        if (ret < F_SUCCESS_0)
            return ret;
        else
            FG_params.full_cap_rep = data[2];

        FG_params.cycles = data[3];

        ret = max77658_fg_read_reg(ctx, FULLCAPNOM_REG, &data[4]);
        if (ret < F_SUCCESS_0)
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
int max77658_fg_restore_Params(max77658_fg_t *ctx, saved_FG_params_t FG_params)
{
    int ret;
    uint16_t temp_data, fullcapnom_data, mixCap_calc, dQacc_calc;
    uint16_t dPacc_value = 0x0C80;//Set it to 200%

    ///STEP 1. Restoring capacity parameters
    max77658_fg_write_and_verify_reg(ctx, RCOMP0_REG, FG_params.rcomp0);
    max77658_fg_write_and_verify_reg(ctx, TEMPCO_REG, FG_params.temp_co);
    max77658_fg_write_and_verify_reg(ctx, FULLCAPNOM_REG, FG_params.full_cap_nom);

    bsp_delay_ms(350);//check the type of wait

    ///STEP 2. Restore FullCap
    ret = max77658_fg_read_reg(ctx, FULLCAPNOM_REG, &fullcapnom_data);
    if (ret < F_SUCCESS_0)
        return ret;

    ret = max77658_fg_read_reg(ctx, MIXSOC_REG, &temp_data);
    if (ret < F_SUCCESS_0)
        return ret;

    mixCap_calc = (temp_data*fullcapnom_data)/25600;

    max77658_fg_write_and_verify_reg(ctx, MIXCAP_REG, mixCap_calc);
    max77658_fg_write_and_verify_reg(ctx, FULLCAPREP_REG, FG_params.full_cap_rep);

    ///STEP 3. Write DQACC to 200% of Capacity and DPACC to 200%
    dQacc_calc = (FG_params.full_cap_nom/ 16) ;

    max77658_fg_write_and_verify_reg(ctx, DPACC_REG, dPacc_value);
    max77658_fg_write_and_verify_reg(ctx, DQACC_REG, dQacc_calc);

    bsp_delay_ms(350);

    ///STEP 4. Restore Cycles register
    ret = max77658_fg_write_and_verify_reg(ctx, CYCLES_REG, FG_params.cycles);
    if (ret < F_SUCCESS_0)
        return ret;
    return ret;
}

/**
 * @brief        Function to Save Average Current to At Rate register.
 * @par          Details
 *               For User friendliness display of atTTE, atAvSOC, atAvCAP
 *               write the average current to At Rate registers every 10sec
 *               when the battery is in use.
 *               NOTE: do not use this function when the Battery is charging.
 *
 * @retval      0 for success
 * @retval      non-0 negative for errors
 */
int max77658_fg_avCurr_2_atRate(max77658_fg_t *ctx)
{
    int ret;
    uint16_t avCurr_data;

    ret = max77658_fg_read_reg(ctx, AVGCURRENT_REG, &avCurr_data);
    if (ret < F_SUCCESS_0) {
        return ret = -3;
    }

    //Write avCurrent to atRate Register
    ret = max77658_fg_write_reg(ctx, ATRATE_REG, avCurr_data);
    if (ret < F_SUCCESS_0) {
        return ret;
    }
    return F_SUCCESS_0;
}

#endif /* MAIN_COMPONENT_PMIC_MAX77658_C_ */
