// STM32F103C8 Device Helper Functions
// Generated from: STM32F103C8 Firmware Specification (DS5319 Rev 20, July 2025)
//
// Provides inline helper functions for common calculations and conversions
// documented in the firmware specification.

#ifndef STM32F103C8_DEVICE_HELPERS_H
#define STM32F103C8_DEVICE_HELPERS_H

#include "device_regs.h"
#include <cstdint>

// ============================================================================
// ADC Conversion Helpers (Section 6)
// ============================================================================

// Convert 12-bit ADC digital value to millivolts
// Formula from spec: V_measured = (D × V_REF) / 2^12
// Source: Section 6 - Conversion Formula
inline constexpr uint32_t adc_digital_to_mv(uint16_t digital_value, uint32_t vref_mv)
{
  return (static_cast<uint32_t>(digital_value) * vref_mv) >> ADC_RESOLUTION_BITS;
}

// Convert millivolts to 12-bit ADC digital value
// Inverse formula: D = (V_measured × 2^12) / V_REF
inline constexpr uint16_t adc_mv_to_digital(uint32_t voltage_mv, uint32_t vref_mv)
{
  if (vref_mv == 0U)
    return 0U;
  const uint32_t digital = (voltage_mv << ADC_RESOLUTION_BITS) / vref_mv;
  return (digital > ADC_MAX_VALUE) ? ADC_MAX_VALUE : static_cast<uint16_t>(digital);
}

// ============================================================================
// Timer Helpers (Section 7)
// ============================================================================

// Calculate timer counter value for microsecond delay @ 72 MHz
// Formula: counter = (µs × f_TIMxCLK) / 1,000,000
// Source: Section 7 - Timer resolution time (13.9 ns @ 72 MHz)
inline constexpr uint16_t tim_us_to_count(uint32_t microseconds, uint32_t timer_freq_hz)
{
  const uint32_t count = (microseconds * timer_freq_hz) / 1000000U;
  return (count > TIM_MAX_COUNT) ? TIM_MAX_COUNT : static_cast<uint16_t>(count);
}

// Calculate microseconds from timer counter value
// Formula: µs = (counter × 1,000,000) / f_TIMxCLK
inline constexpr uint32_t tim_count_to_us(uint16_t counter, uint32_t timer_freq_hz)
{
  if (timer_freq_hz == 0U)
    return 0U;
  return (static_cast<uint32_t>(counter) * 1000000U) / timer_freq_hz;
}

// ============================================================================
// Clock Validation Helpers (Section 2)
// ============================================================================

// Check if APB1 frequency is valid for I2C standard mode (100 kHz)
// Source: Section 2 - I2C Requirements
inline constexpr bool is_valid_i2c_std_clock(uint32_t apb1_freq_hz)
{
  return apb1_freq_hz >= I2C_PCLK_MIN_STD_HZ && apb1_freq_hz <= APB1_FREQ_MAX_HZ;
}

// Check if APB1 frequency is valid for I2C fast mode (400 kHz)
// Source: Section 2 - I2C Requirements
inline constexpr bool is_valid_i2c_fast_clock(uint32_t apb1_freq_hz)
{
  return apb1_freq_hz >= I2C_PCLK_MIN_FAST_HZ && apb1_freq_hz <= APB1_FREQ_MAX_HZ;
}

// Check if ADC clock frequency is within valid range
// Source: Section 2 - ADC Requirements (0.6-14 MHz)
inline constexpr bool is_valid_adc_clock(uint32_t adc_freq_hz)
{
  return adc_freq_hz >= ADC_FREQ_MIN_HZ && adc_freq_hz <= ADC_FREQ_MAX_HZ;
}

// ============================================================================
// SPI Prescaler Calculation (Section 5)
// ============================================================================

// Calculate SPI BR[2:0] bits for desired SCK frequency
// Returns SPI_BR_DIVx value or 0xFF if frequency not achievable
// Source: Section 5 - SPI Clock Prescaler (PCLK / 2^(BR+1))
uint8_t spi_calculate_prescaler(uint32_t pclk_hz, uint32_t desired_sck_hz);

// ============================================================================
// Voltage Range Validation (Section 9)
// ============================================================================

// Check if VDD voltage is within operating range
// Source: Section 9 - Operating Voltage Range
inline constexpr bool is_valid_vdd(uint32_t vdd_mv)
{
  return vdd_mv >= VDD_MIN_MV && vdd_mv <= VDD_MAX_MV;
}

// Check if VDDA (ADC supply) voltage is within range
// Source: Section 9 - Operating Voltage Range
inline constexpr bool is_valid_vdda(uint32_t vdda_mv)
{
  return vdda_mv >= VDDA_MIN_MV && vdda_mv <= VDDA_MAX_MV;
}

#endif // STM32F103C8_DEVICE_HELPERS_H
