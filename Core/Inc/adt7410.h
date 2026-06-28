#ifndef ADT7410_H
#define ADT7410_H

#include <stdint.h>
#include "hal_stub.h"

typedef enum
{
  ADT7410_OK = 0,
  ADT7410_ERR_INVALID_ARG = 1,
  ADT7410_ERR_BUS = 2,
  ADT7410_ERR_TIMEOUT = 3
} adt7410_status_t;

typedef struct
{
  uint8_t i2c_addr_7bit;
} adt7410_ctx_t;

/**
 * @brief  Initialize ADT7410 temperature sensor context.
 * @param  ctx Pointer to sensor context structure (must not be NULL).
 * @param  i2c_addr_7bit 7-bit I2C slave address.
 * @return ADT7410_OK on success, or error code on failure.
 */
adt7410_status_t adt7410_init(adt7410_ctx_t *ctx, uint8_t i2c_addr_7bit);

/**
 * @brief  Read temperature from ADT7410 sensor.
 * @param  ctx Pointer to initialized sensor context (must not be NULL).
 * @param  out_temp_c_x100 Pointer to store temperature in degrees Celsius × 100 (must not be NULL).
 *         Example: 2550 → 25.50°C, -1050 → -10.50°C.
 * @return ADT7410_OK on success, ADT7410_ERR_BUS on I2C communication failure,
 *         ADT7410_ERR_INVALID_ARG on NULL pointer or out-of-range value.
 */
adt7410_status_t adt7410_read_temp_c_x100(const adt7410_ctx_t *ctx, int16_t *out_temp_c_x100);

#endif /* ADT7410_H */
