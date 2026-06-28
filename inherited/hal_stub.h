#ifndef HAL_STUB_H
#define HAL_STUB_H

#include <stdint.h>

/**
 * HAL status codes (stub)
 * In a real project, these come from vendor HAL (e.g., stm32f1xx_hal.h)
 */
typedef enum
{
  HAL_OK = 0,
  HAL_ERROR = 1,
  HAL_BUSY = 2,
  HAL_TIMEOUT = 3,
} hal_status_t;

/**
 * I2C handle (opaque in this stub)
 * In a real project, this holds hardware state and config.
 */
typedef void *I2C_HandleTypeDef;

/**
 * Read from I2C memory.
 *
 * @param i2c_addr 7-bit I2C device address
 * @param mem_addr Memory address to read from
 * @param buf Output buffer
 * @param bufsize Number of bytes to read
 * @param timeout Timeout in milliseconds
 * @return HAL_OK on success, HAL_ERROR / HAL_TIMEOUT on failure
 *
 * NOTE: This is a highly simplified stub.
 * Real HAL_I2C_Mem_Read typically requires an I2C_HandleTypeDef as first parameter.
 * Adjust signature for your actual HAL.
 */
hal_status_t HAL_I2C_Mem_Read(
    uint8_t i2c_addr,
    uint8_t mem_addr,
    uint8_t *buf,
    uint16_t bufsize,
    uint32_t timeout);

/**
 * Write to I2C memory.
 *
 * @param i2c_addr 7-bit I2C device address
 * @param mem_addr Memory address to write to
 * @param buf Input buffer
 * @param bufsize Number of bytes to write
 * @param timeout Timeout in milliseconds
 * @return HAL_OK on success, HAL_ERROR / HAL_TIMEOUT on failure
 */
hal_status_t HAL_I2C_Mem_Write(
    uint8_t i2c_addr,
    uint8_t mem_addr,
    uint8_t *buf,
    uint16_t bufsize,
    uint32_t timeout);

#endif // HAL_STUB_H
