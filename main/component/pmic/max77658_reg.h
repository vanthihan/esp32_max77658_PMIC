/*
 * max77658_reg.h
 *
 *  Created on: Oct 31, 2021
 *      Author: kai
 */

#ifndef MAIN_COMPONENT_PMIC_MAX77658_REG_H_
#define MAIN_COMPONENT_PMIC_MAX77658_REG_H_

#include <stdint.h>

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
} dev_ctx_t;


#endif /* MAIN_COMPONENT_PMIC_MAX77658_REG_H_ */
