/*
 * max77658_reg.h
 *
 *  Created on: Oct 31, 2021
 *      Author: kai
 */

#ifndef MAIN_COMPONENT_PMIC_MAX77658_REG_H_
#define MAIN_COMPONENT_PMIC_MAX77658_REG_H_

/* Includes ----------------------------------------------------------- */
#include <stdint.h>
#include "max77658_defines.h"
#include "max77658_types.h"

/* Public defines ----------------------------------------------------- */

/* Model loading options */
#define MODEL_LOADING_OPTION1           1
#define MODEL_LOADING_OPTION2           2
#define MODEL_LOADING_OPTION3           3

/* Public enumerate/structure ----------------------------------------- */

/** @addtogroup  Interfaces_Functions
  * @brief       This section provide a set of functions used to read and
  *              write a generic register of the device.
  *              MANDATORY: return 0 -> no Error.
  * @{
  *
  */
typedef int32_t (*dev_write_ptr)(uint8_t, uint8_t, uint8_t *, uint32_t);
typedef int32_t (*dev_read_ptr)(uint8_t, uint8_t, uint8_t *, uint32_t);

typedef struct
{
   uint8_t device_address;
   dev_read_ptr   read_reg;
   dev_write_ptr  write_reg;
   struct max1726x_platform_data *pdata;
}maxdev_ctx_t;

/*
 * Helper function Read generic device register
 */
int32_t max77658_read_reg(maxdev_ctx_t *ctx, uint8_t reg, uint16_t *val);
/*
 * Helper function write generic device register
 */
int32_t max77658_write_reg(maxdev_ctx_t *ctx, uint8_t reg, uint16_t data);


#endif /* MAIN_COMPONENT_PMIC_MAX77658_REG_H_ */

