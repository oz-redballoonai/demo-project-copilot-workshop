#ifndef MAIN_H
#define MAIN_H

#include <stdint.h>
#include "hal_stub.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* USER CODE BEGIN Defines */

/* USER CODE END Defines */

/**
 * @brief  Configure the system clock.
 */
void SystemClock_Config(void);

/**
 * @brief  Initialize GPIO peripheral.
 */
void MX_GPIO_Init(void);

/**
 * @brief  Initialize I2C1 peripheral for sensor communication.
 */
void MX_I2C1_Init(void);

#endif /* MAIN_H */
