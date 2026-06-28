#ifdef __cplusplus
extern "C"
{
#endif
#include "adt7410.h"
#ifdef __cplusplus
}
#endif
// Source of truth for registers and format is docs/specs/adt7410_minimal.md

#define ADT7410_REG_TEMP_MSB (0x00u)
#define ADT7410_REG_TEMP_LSB (0x01u)
#define ADT7410_I2C_TIMEOUT_MS (10u)

adt7410_status_t adt7410_init(adt7410_ctx_t *ctx, uint8_t i2c_addr_7bit)
{
  if (!ctx)
    return ADT7410_ERR_INVALID_ARG;
  ctx->i2c_addr_7bit = i2c_addr_7bit;
  return ADT7410_OK;
}

adt7410_status_t adt7410_read_temp_c_x100(const adt7410_ctx_t *ctx, int16_t *out_temp_c_x100)
{
  if (!ctx || !out_temp_c_x100)
    return ADT7410_ERR_INVALID_ARG;

  uint8_t buf[2] = {0};
  uint8_t reg_addr = ADT7410_REG_TEMP_MSB;
  hal_status_t st = HAL_I2C_Mem_Read(ctx->i2c_addr_7bit, reg_addr, buf, sizeof(buf), ADT7410_I2C_TIMEOUT_MS);
  if (st != HAL_OK)
    return ADT7410_ERR_BUS;

  // Assemble 16-bit big-endian from MSB/LSB, then reinterpret as signed two's complement.
  uint16_t raw_u = ((uint16_t)buf[0] << 8u) | (uint16_t)buf[1];
  // Bit-pattern reinterpret: 0x8000-0xFFFF map to -32768 to -1 in two's complement (intentional for sensor data).
  int16_t raw = (int16_t)raw_u;
  // Convert sensor scale to output: temp(°C) = raw / 128 (from spec)
  // Output format: temp(°C) × 100 stored as int16_t
  // Math: (raw / 128) * 100 = (raw * 100) / 128 (safe: no overflow for valid raw)
  // Source: docs/specs/adt7410_minimal.md
  int32_t temp_x100 = ((int32_t)raw * 100) / 128;
  // Defensive: mathematically temp_x100 in [-25,600, +25,600] for valid raw int16_t,
  // but this catches sensor malfunction or spec deviation.
  if (temp_x100 < INT16_MIN || temp_x100 > INT16_MAX)
    return ADT7410_ERR_INVALID_ARG;
  *out_temp_c_x100 = (int16_t)temp_x100;

  return ADT7410_OK;
}
