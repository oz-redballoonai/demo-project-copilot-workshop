#ifndef ADT7410_ALERT_H
#define ADT7410_ALERT_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>

  enum class adt7410_alert_result : uint8_t
  {
    ok = 0,
    invalid_argument = 1,
    i2c_read_error = 2,
    i2c_write_error = 3,
    timeout = 4,
  };

  /**
   * Configure alert thresholds (high and low).
   *
   * @param low_threshold_c_x100 Low threshold in C*100 (e.g., 2500 = 25.00C)
   * @param high_threshold_c_x100 High threshold in C*100
   * @return status code
   */
  adt7410_alert_result adt7410_alert_configure_thresholds_c_x100(
      int16_t low_threshold_c_x100,
      int16_t high_threshold_c_x100);

  /**
   * Read the alert status register.
   *
   * @param raw_status Pointer to store status byte
   * @return status code
   */
  adt7410_alert_result adt7410_alert_read_status_raw(uint8_t *raw_status);

#ifdef __cplusplus
}
#endif

#endif // ADT7410_ALERT_H
