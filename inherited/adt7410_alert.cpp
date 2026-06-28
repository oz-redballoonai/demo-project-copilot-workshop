#include "adt7410_alert.h"
#include "hal_stub.h"

// Alert register addresses (not confirmed in spec yet)
#define ADT7410_REG_THIGH_MSB (0x02u)
#define ADT7410_REG_THIGH_LSB (0x03u)
#define ADT7410_REG_TLOW_MSB (0x04u)
#define ADT7410_REG_TLOW_LSB (0x05u)
#define ADT7410_REG_STATUS (0x0Fu)

#define ADT7410_I2C_ADDR (0x48u)
#define ADT7410_I2C_TIMEOUT_MS (10u)

adt7410_alert_result adt7410_alert_configure_thresholds_c_x100(
    int16_t low_threshold_c_x100,
    int16_t high_threshold_c_x100)
{
  if (low_threshold_c_x100 > high_threshold_c_x100)
    return adt7410_alert_result::invalid_argument;

  // Convert temp to raw using 1/128 scale from temperature register
  int32_t raw_high = ((int32_t)high_threshold_c_x100 * 128) / 100;
  int32_t raw_low = ((int32_t)low_threshold_c_x100 * 128) / 100;

  // Bounds check before cast
  if (raw_high < INT16_MIN || raw_high > INT16_MAX ||
      raw_low < INT16_MIN || raw_low > INT16_MAX)
    return adt7410_alert_result::invalid_argument;

  uint16_t raw_high_u = (uint16_t)(int16_t)raw_high;
  uint16_t raw_low_u = (uint16_t)(int16_t)raw_low;

  // Write high threshold (big-endian)
  uint8_t buf_high[2] = {
      (uint8_t)((raw_high_u >> 8u) & 0xFFu),
      (uint8_t)(raw_high_u & 0xFFu)};
  hal_status_t st = HAL_I2C_Mem_Write(
      ADT7410_I2C_ADDR,
      ADT7410_REG_THIGH_MSB,
      buf_high,
      sizeof(buf_high),
      ADT7410_I2C_TIMEOUT_MS);
  if (st != HAL_OK)
    return adt7410_alert_result::i2c_write_error;

  // Write low threshold (big-endian)
  uint8_t buf_low[2] = {
      (uint8_t)((raw_low_u >> 8u) & 0xFFu),
      (uint8_t)(raw_low_u & 0xFFu)};
  st = HAL_I2C_Mem_Write(
      ADT7410_I2C_ADDR,
      ADT7410_REG_TLOW_MSB,
      buf_low,
      sizeof(buf_low),
      ADT7410_I2C_TIMEOUT_MS);
  if (st != HAL_OK)
    return adt7410_alert_result::i2c_write_error;

  return adt7410_alert_result::ok;
}

adt7410_alert_result adt7410_alert_read_status_raw(uint8_t *raw_status)
{
  if (!raw_status)
    return adt7410_alert_result::invalid_argument;

  uint8_t buf[1] = {0};
  hal_status_t st = HAL_I2C_Mem_Read(
      ADT7410_I2C_ADDR,
      ADT7410_REG_STATUS,
      buf,
      sizeof(buf),
      ADT7410_I2C_TIMEOUT_MS);
  if (st != HAL_OK)
    return adt7410_alert_result::i2c_read_error;

  *raw_status = buf[0];
  return adt7410_alert_result::ok;
}
