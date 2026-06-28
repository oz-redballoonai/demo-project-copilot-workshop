// STM32F103C8 Device Helper Functions - Implementation
// Generated from: STM32F103C8 Firmware Specification (DS5319 Rev 20, July 2025)

#include "device_helpers.h"

// ============================================================================
// SPI Prescaler Calculation (Section 5)
// ============================================================================

// Calculate SPI BR[2:0] bits for desired SCK frequency
// Returns SPI_BR_DIVx value or 0xFF if frequency not achievable
// Source: Section 5 - SPI Clock Prescaler (PCLK / 2^(BR+1))
uint8_t spi_calculate_prescaler(uint32_t pclk_hz, uint32_t desired_sck_hz)
{
  // SPI prescaler values: 2, 4, 8, 16, 32, 64, 128, 256
  // Formula: SCK = PCLK / (2 ^ (BR + 1))
  // Rearranged: BR = log2(PCLK / SCK) - 1

  // Check max frequency constraint (18 MHz from Section 5)
  const uint32_t max_sck_hz = SPI_SCK_MAX_MHZ * 1000000U;
  if (desired_sck_hz > max_sck_hz)
  {
    return 0xFFU; // Invalid: exceeds maximum
  }

  if (desired_sck_hz == 0U)
    return 0xFFU;
  // Calculate required divisor
  const uint32_t divisor = pclk_hz / desired_sck_hz;

  // Map divisor to BR bits (logarithmic search)
  if (divisor <= 2U)
  {
    return SPI_BR_DIV2; // BR = 000 (div by 2)
  }
  else if (divisor <= 4U)
  {
    return SPI_BR_DIV4; // BR = 001 (div by 4)
  }
  else if (divisor <= 8U)
  {
    return SPI_BR_DIV8; // BR = 010 (div by 8)
  }
  else if (divisor <= 16U)
  {
    return SPI_BR_DIV16; // BR = 011 (div by 16)
  }
  else if (divisor <= 32U)
  {
    return SPI_BR_DIV32; // BR = 100 (div by 32)
  }
  else if (divisor <= 64U)
  {
    return SPI_BR_DIV64; // BR = 101 (div by 64)
  }
  else if (divisor <= 128U)
  {
    return SPI_BR_DIV128; // BR = 110 (div by 128)
  }
  else if (divisor <= 256U)
  {
    return SPI_BR_DIV256; // BR = 111 (div by 256)
  }
  else
  {
    return 0xFFU; // Invalid: divisor too large
  }
}
