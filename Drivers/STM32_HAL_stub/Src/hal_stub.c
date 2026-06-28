#include "hal_stub.h"

void HAL_Init(void) {}

void HAL_Delay(uint32_t ms) { (void)ms; }

uint32_t HAL_GetTick(void)
{
  static uint32_t tick = 0;
  return tick++;
}

hal_status_t HAL_I2C_Mem_Read(uint8_t dev_addr_7bit, uint8_t mem_addr, uint8_t *data, size_t len, uint32_t timeout_ms)
{
  (void)dev_addr_7bit;
  (void)mem_addr;
  (void)timeout_ms;

  if (!data || len == 0)
    return HAL_ERROR;

  // Dummy raw temp: 25.00C -> raw = 25 * 128 = 3200 = 0x0C80
  if (len >= 2)
  {
    data[0] = 0x0C;
    data[1] = 0x80;
  }
  else
  {
    data[0] = 0x0C;
  }

  return HAL_OK;
}

hal_status_t HAL_I2C_Mem_Write(uint8_t dev_addr_7bit, uint8_t mem_addr, const uint8_t *data, size_t len, uint32_t timeout_ms)
{
  (void)dev_addr_7bit;
  (void)mem_addr;
  (void)timeout_ms;

  if (!data || len == 0)
    return HAL_ERROR;

  return HAL_OK;
}
