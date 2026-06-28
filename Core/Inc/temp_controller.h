#ifndef TEMP_CONTROLLER_H
#define TEMP_CONTROLLER_H

#include <stdint.h>

typedef enum
{
  TEMP_CONTROLLER_CMD_ALL_OFF = 0,
  TEMP_CONTROLLER_CMD_HEAT_ON = 1,
  TEMP_CONTROLLER_CMD_COOL_ON = 2
} temp_controller_command_t;

typedef enum
{
  TEMP_CONTROLLER_STATUS_OK = 0,
  TEMP_CONTROLLER_STATUS_ERR_NULL_PTR = 1,
  TEMP_CONTROLLER_STATUS_ERR_INVALID_ARG = 2
} temp_controller_status_t;

temp_controller_status_t temp_controller_compute_command(
    int32_t current_temp_c_x100,
    int32_t setpoint_c_x100,
    int32_t hysteresis_c_x100,
    temp_controller_command_t *out_command);

#endif /* TEMP_CONTROLLER_H */