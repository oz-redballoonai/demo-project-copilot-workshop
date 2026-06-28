#ifndef HAL_STUB_H
#define HAL_STUB_H

#include <stdint.h>
#include <stddef.h>

typedef enum
{
  HAL_OK = 0,
  HAL_ERROR = 1,
  HAL_BUSY = 2,
  HAL_TIMEOUT = 3
} hal_status_t;

void HAL_Init(void);
void HAL_Delay(uint32_t ms);
uint32_t HAL_GetTick(void);

hal_status_t HAL_I2C_Mem_Read(uint8_t dev_addr_7bit, uint8_t mem_addr, uint8_t *data, size_t len, uint32_t timeout_ms);
hal_status_t HAL_I2C_Mem_Write(uint8_t dev_addr_7bit, uint8_t mem_addr, const uint8_t *data, size_t len, uint32_t timeout_ms);

#endif /* HAL_STUB_H */
