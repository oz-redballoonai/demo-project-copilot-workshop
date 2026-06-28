#ifdef __cplusplus
extern "C"
{
#endif

#include "main.h"
#include "adt7410.h"

#ifdef __cplusplus
}
#endif

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

int main(void)
{
  /* USER CODE BEGIN 1 */
  /* USER CODE END 1 */

  HAL_Init();
  SystemClock_Config();

  MX_GPIO_Init();
  MX_I2C1_Init();

  /* USER CODE BEGIN 2 */
  adt7410_ctx_t sensor = {0};
  adt7410_status_t st = adt7410_init(&sensor, 0x48);
  (void)st;
  uint32_t last_read_tick = 0;
  /* USER CODE END 2 */

  while (1)
  {
    /* USER CODE BEGIN WHILE */
    uint32_t current_tick = HAL_GetTick();
    if ((current_tick - last_read_tick) >= 100)
    {
      int16_t temp_c_x100 = 0;
      (void)adt7410_read_temp_c_x100(&sensor, &temp_c_x100);
      last_read_tick = current_tick;
    }
    /* USER CODE END WHILE */
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */
