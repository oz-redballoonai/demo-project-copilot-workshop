#ifdef __cplusplus
extern "C"
{
#endif
#include "temp_controller.h"
#ifdef __cplusplus
}
#endif

static temp_controller_status_t validate_inputs(
    int32_t hysteresis_c_x100,
    temp_controller_command_t *out_command)
{
  if (out_command == nullptr)
  {
    return TEMP_CONTROLLER_STATUS_ERR_NULL_PTR;
  }

  if (hysteresis_c_x100 < 0)
  {
    return TEMP_CONTROLLER_STATUS_ERR_INVALID_ARG;
  }

  return TEMP_CONTROLLER_STATUS_OK;
}

static temp_controller_command_t select_command(
    int32_t current_temp_c_x100,
    int32_t setpoint_c_x100,
    int32_t hysteresis_c_x100)
{
  const int32_t lower_edge_c_x100 = setpoint_c_x100 - hysteresis_c_x100;
  const int32_t upper_edge_c_x100 = setpoint_c_x100 + hysteresis_c_x100;

  if (current_temp_c_x100 < lower_edge_c_x100)
  {
    return TEMP_CONTROLLER_CMD_HEAT_ON;
  }

  if (current_temp_c_x100 > upper_edge_c_x100)
  {
    return TEMP_CONTROLLER_CMD_COOL_ON;
  }

  return TEMP_CONTROLLER_CMD_ALL_OFF;
}

temp_controller_status_t temp_controller_compute_command(
    int32_t current_temp_c_x100,
    int32_t setpoint_c_x100,
    int32_t hysteresis_c_x100,
    temp_controller_command_t *out_command)
{
  const temp_controller_status_t status = validate_inputs(hysteresis_c_x100, out_command);
  if (status != TEMP_CONTROLLER_STATUS_OK)
  {
    return status;
  }

  *out_command = select_command(current_temp_c_x100, setpoint_c_x100, hysteresis_c_x100);

  return TEMP_CONTROLLER_STATUS_OK;
}