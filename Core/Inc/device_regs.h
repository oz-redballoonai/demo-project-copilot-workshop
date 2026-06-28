// STM32F103C8 Hardware Register Definitions
// Generated from: STM32F103C8 Firmware Specification (DS5319 Rev 20, July 2025)
// Device: STM32F103C8 (Medium-density, 64 KB Flash, 20 KB SRAM)
// Core: ARM Cortex-M3 @ 72 MHz
//
// WARNING: This file contains ONLY values explicitly documented in the spec.
// Complete register definitions require the STM32F10xxx Reference Manual.

#ifndef STM32F103C8_DEVICE_REGS_H
#define STM32F103C8_DEVICE_REGS_H

#include <cstdint>

// ============================================================================
// Memory Map Base Addresses (Section 1)
// ============================================================================

// Flash and SRAM
constexpr uint32_t FLASH_BASE = 0x00000000U; // Flash memory (aliased, BOOT-dependent)
constexpr uint32_t SRAM_BASE = 0x20000000U;  // Embedded SRAM (20 KB)
constexpr uint32_t SRAM_END = 0x20004FFFU;
constexpr uint32_t PERIPH_BASE = 0x40000000U;    // APB/AHB Peripherals (~144 KB)
constexpr uint32_t CORTEX_M3_BASE = 0xE0000000U; // Cortex-M3 Internal

// ============================================================================
// Peripheral Base Addresses (Section 1)
// ============================================================================

// APB1 Peripherals
constexpr uint32_t TIM2_BASE = 0x40000000U;
constexpr uint32_t TIM3_BASE = 0x40000400U;
constexpr uint32_t TIM4_BASE = 0x40000800U;
constexpr uint32_t RTC_BASE = 0x40002800U;
constexpr uint32_t WWDG_BASE = 0x40003000U;
constexpr uint32_t IWDG_BASE = 0x40003400U;
constexpr uint32_t SPI2_BASE = 0x40003800U;
constexpr uint32_t USART2_BASE = 0x40004800U;
constexpr uint32_t USART3_BASE = 0x40004C00U;
constexpr uint32_t I2C1_BASE = 0x40005400U;
constexpr uint32_t I2C2_BASE = 0x40005800U;
constexpr uint32_t USB_BASE = 0x40005C00U;
constexpr uint32_t CAN_BASE = 0x40006000U;
constexpr uint32_t BKP_BASE = 0x40006800U;
constexpr uint32_t PWR_BASE = 0x40007000U;

// APB2 Peripherals
constexpr uint32_t EXTI_BASE = 0x40010800U;
constexpr uint32_t GPIOA_BASE = 0x40010C00U; // Port A
constexpr uint32_t GPIOB_BASE = 0x40011000U; // Port B
constexpr uint32_t GPIOC_BASE = 0x40011400U; // Port C
constexpr uint32_t GPIOD_BASE = 0x40011800U; // Port D
constexpr uint32_t ADC1_BASE = 0x40012800U;
constexpr uint32_t ADC2_BASE = 0x40012C00U;
constexpr uint32_t TIM1_BASE = 0x40013000U;
constexpr uint32_t SPI1_BASE = 0x40013400U;
constexpr uint32_t USART1_BASE = 0x40013C00U;

// AHB Peripherals
constexpr uint32_t FLASH_IF_BASE = 0x40022000U; // Flash Interface
constexpr uint32_t RCC_BASE = 0x40023000U;
constexpr uint32_t CRC_BASE = 0x40023400U;

// ============================================================================
// System Clock Constraints (Section 2)
// ============================================================================

constexpr uint32_t CPU_FREQ_MAX_HZ = 72000000U; // Max CPU frequency

// External High-Speed Clock (HSE)
constexpr uint32_t HSE_FREQ_MIN_HZ = 4000000U;  // Crystal min
constexpr uint32_t HSE_FREQ_MAX_HZ = 16000000U; // Crystal max

// Internal Clocks
constexpr uint32_t HSI_FREQ_HZ = 8000000U; // Internal RC (factory-trimmed)
constexpr uint32_t LSI_FREQ_HZ = 40000U;   // Watchdog, RTC backup
constexpr uint32_t LSE_FREQ_HZ = 32000U;   // RTC crystal (optional)

// Peripheral Bus Clocks
constexpr uint32_t APB1_FREQ_MAX_HZ = 36000000U; // APB1 max (I2C, SPI2, USART2/3, TIM2-4)
constexpr uint32_t APB2_FREQ_MAX_HZ = 72000000U; // APB2 max (ADC, SPI1, USART1, TIM1)

// ADC Clock Constraints
constexpr uint32_t ADC_FREQ_MIN_HZ = 600000U;   // 0.6 MHz
constexpr uint32_t ADC_FREQ_MAX_HZ = 14000000U; // 14 MHz (optimal)
constexpr uint32_t ADC_FREQ_OPT_HZ = 14000000U; // Recommended for 1 µs conversion

// ============================================================================
// GPIO Configuration (Section 3)
// ============================================================================

// GPIO_CRx MODEx[1:0] bitfield values (speed configuration)
// Note: Spec does not provide bit positions, only that MODEx[1:0] controls speed
constexpr uint32_t GPIO_MODE_INPUT = 0b00U; // Input mode (inferred from 2-bit field)
constexpr uint32_t GPIO_MODE_10MHZ = 0b01U; // 10 MHz output
constexpr uint32_t GPIO_MODE_2MHZ = 0b10U;  // 2 MHz output
constexpr uint32_t GPIO_MODE_50MHZ = 0b11U; // 50 MHz output (Table 38, MODE=11)

// GPIO Timing Constraints (Section 3) - 50 MHz mode @ 2.7-3.6V
constexpr uint32_t GPIO_RISE_TIME_30PF_NS = 5U; // Rise time @ 30 pF
constexpr uint32_t GPIO_RISE_TIME_50PF_NS = 8U; // Rise time @ 50 pF
constexpr uint32_t GPIO_FALL_TIME_30PF_NS = 5U; // Fall time @ 30 pF
constexpr uint32_t GPIO_FALL_TIME_50PF_NS = 8U; // Fall time @ 50 pF
constexpr uint32_t GPIO_MAX_FREQ_MHZ = 30U;     // Max output frequency (50 pF load)

// ============================================================================
// I2C Configuration (Section 4)
// ============================================================================

// I2C Clock Requirements
constexpr uint32_t I2C_PCLK_MIN_STD_HZ = 2000000U;  // Min clock for 100 kHz I2C
constexpr uint32_t I2C_PCLK_MIN_FAST_HZ = 4000000U; // Min clock for 400 kHz I2C

// I2C_CCR Register Values (Table: PCLK1 = 36 MHz, R_P = 4.7 kΩ)
constexpr uint16_t I2C_CCR_400KHZ = 0x801EU; // Fast mode, 400 kHz
constexpr uint16_t I2C_CCR_300KHZ = 0x8028U; // Fast mode, 300 kHz
constexpr uint16_t I2C_CCR_200KHZ = 0x803CU; // Standard mode, ~200 kHz (±5%)
constexpr uint16_t I2C_CCR_100KHZ = 0x00B4U; // Standard mode, 100 kHz
constexpr uint16_t I2C_CCR_50KHZ = 0x0168U;  // Standard mode, 50 kHz
constexpr uint16_t I2C_CCR_20KHZ = 0x0384U;  // Standard mode, 20 kHz

// I2C Timing Constraints (Section 4) - extracted from Table 41
// Standard Mode (100 kHz)
constexpr uint32_t I2C_SCLL_STD_US = 4700U;     // SCL low time (ns converted to ps for precision: 4.7 µs)
constexpr uint32_t I2C_SCLH_STD_US = 4000U;     // SCL high time (4.0 µs)
constexpr uint32_t I2C_SDA_SETUP_STD_NS = 250U; // SDA setup time
constexpr uint32_t I2C_SDA_HOLD_STD_NS = 3450U; // SDA hold time (if no clock stretch)

// Fast Mode (400 kHz)
constexpr uint32_t I2C_SCLL_FAST_US = 1300U;     // SCL low time (1.3 µs)
constexpr uint32_t I2C_SCLH_FAST_US = 600U;      // SCL high time (0.6 µs)
constexpr uint32_t I2C_SDA_SETUP_FAST_NS = 100U; // SDA setup time
constexpr uint32_t I2C_SDA_HOLD_FAST_NS = 900U;  // SDA hold time (if no clock stretch)

// ============================================================================
// SPI Configuration (Section 5)
// ============================================================================

// SPI_CR1 BR[2:0] Clock Prescaler Values
constexpr uint32_t SPI_BR_DIV2 = 0b000U;   // PCLK / 2
constexpr uint32_t SPI_BR_DIV4 = 0b001U;   // PCLK / 4
constexpr uint32_t SPI_BR_DIV8 = 0b010U;   // PCLK / 8
constexpr uint32_t SPI_BR_DIV16 = 0b011U;  // PCLK / 16
constexpr uint32_t SPI_BR_DIV32 = 0b100U;  // PCLK / 32
constexpr uint32_t SPI_BR_DIV64 = 0b101U;  // PCLK / 64
constexpr uint32_t SPI_BR_DIV128 = 0b110U; // PCLK / 128
constexpr uint32_t SPI_BR_DIV256 = 0b111U; // PCLK / 256

// SPI Timing Constraints
constexpr uint32_t SPI_SCK_MAX_MHZ = 18U; // Max SCK frequency (master/slave)

// ============================================================================
// ADC Configuration (Section 6)
// ============================================================================

// ADC Supply Voltage Range
constexpr uint32_t ADC_VDD_MIN_MV = 2400U;  // V_DDA min (mV)
constexpr uint32_t ADC_VDD_MAX_MV = 3600U;  // V_DDA max (mV)
constexpr uint32_t ADC_VREF_MIN_MV = 2400U; // V_REF+ min (mV)

// ADC Resolution
constexpr uint32_t ADC_RESOLUTION_BITS = 12U;
constexpr uint32_t ADC_MAX_VALUE = 4095U; // 2^12 - 1

// ADC Sampling Time Cycles (from External Input Impedance table)
constexpr uint32_t ADC_SMPR_1_5 = 0b000U;  // 1.5 cycles
constexpr uint32_t ADC_SMPR_7_5 = 0b001U;  // 7.5 cycles
constexpr uint32_t ADC_SMPR_13_5 = 0b010U; // 13.5 cycles
constexpr uint32_t ADC_SMPR_28_5 = 0b011U; // 28.5 cycles
constexpr uint32_t ADC_SMPR_41_5 = 0b100U; // 41.5 cycles
constexpr uint32_t ADC_SMPR_55_5 = 0b101U; // 55.5 cycles
// Note: Bit patterns inferred from 3-bit field encoding 6 values
// Additional cycles (71.5, 239.5) exist but not mapped to bit values in spec

// ADC Timing Constants (@ 14 MHz)
constexpr uint32_t ADC_CONV_MIN_US = 1U;  // Min total conversion time
constexpr uint32_t ADC_CONV_MAX_US = 18U; // Max total conversion time
constexpr uint32_t ADC_SAR_CYCLES = 12U;  // SAR conversion cycles (12.5 rounded)

// ============================================================================
// Timer Configuration (Section 7)
// ============================================================================

// Timer Resolution
constexpr uint32_t TIM_RESOLUTION_BITS = 16U;
constexpr uint32_t TIM_MAX_COUNT = 65536U; // 2^16

// Timer Timing @ 72 MHz
constexpr uint32_t TIM_RES_NS = 14U;          // Resolution: 13.9 ns (rounded)
constexpr uint32_t TIM_COUNTER_MAX_US = 910U; // Max 16-bit period @ 72 MHz
constexpr uint32_t TIM_MAX_COUNT_MS = 59600U; // Max count: 59.6 s @ 72 MHz

// ============================================================================
// Reset and Power Control (Section 8)
// ============================================================================

// NRST Pin Thresholds
constexpr uint32_t NRST_VIL_MAX_MV = 800U;  // Input low max (0.8 V)
constexpr uint32_t NRST_VIH_MIN_MV = 2000U; // Input high min (2.0 V)
constexpr uint32_t NRST_VHYS_TYP_MV = 200U; // Schmitt hysteresis typ (200 mV)
constexpr uint32_t NRST_RPU_MIN_KOHM = 30U; // Pull-up resistance min (30 kΩ)
constexpr uint32_t NRST_RPU_TYP_KOHM = 40U; // Pull-up resistance typ (40 kΩ)
constexpr uint32_t NRST_RPU_MAX_KOHM = 50U; // Pull-up resistance max (50 kΩ)
constexpr uint32_t NRST_FILTER_NS = 100U;   // Filtered pulse width max (100 ns)
constexpr uint32_t NRST_UNFILTER_NS = 300U; // Unfiltered pulse width min (300 ns)

// Recommended NRST decoupling
constexpr uint32_t NRST_CAP_NF = 100U; // 100 nF to ground

// ============================================================================
// Electrical Supply (Section 9)
// ============================================================================

// Operating Voltage Range
constexpr uint32_t VDD_MIN_MV = 2000U; // Main supply min (2.0 V)
constexpr uint32_t VDD_TYP_MV = 3300U; // Main supply typ (3.3 V)
constexpr uint32_t VDD_MAX_MV = 3600U; // Main supply max (3.6 V)

constexpr uint32_t VDDA_MIN_MV = 2400U; // ADC supply min (2.4 V)
constexpr uint32_t VDDA_TYP_MV = 3300U; // ADC supply typ (3.3 V)
constexpr uint32_t VDDA_MAX_MV = 3600U; // ADC supply max (3.6 V)

constexpr uint32_t VBAT_MIN_MV = 1800U; // RTC backup min (1.8 V)
constexpr uint32_t VBAT_TYP_MV = 3300U; // RTC backup typ (3.3 V)
constexpr uint32_t VBAT_MAX_MV = 3600U; // RTC backup max (3.6 V)

// Recommended Decoupling
constexpr uint32_t VDD_CAP_CNT = 5U;  // 5× 100 nF capacitors
constexpr uint32_t VDD_CAP_NF = 100U; // 100 nF per VDD pin
constexpr uint32_t VDD_BULK_UF = 4U;  // 1× 4.7 µF bulk (rounded to 4)

// ============================================================================
// USART/UART (Section 10)
// ============================================================================

constexpr uint32_t USART_BAUD_MAX = 2250000U; // Max baud rate: 2.25 Mbps

// ============================================================================
// USB (Section 11)
// ============================================================================

constexpr uint32_t USB_SPEED_MBPS = 12U;  // Full-speed: 12 Mbps
constexpr uint32_t USB_SRAM_BYTES = 512U; // Shared SRAM with CAN

// ============================================================================
// Memory Sizes
// ============================================================================

constexpr uint32_t FLASH_SIZE_KB = 64U; // 64 KB Flash
constexpr uint32_t SRAM_SIZE_KB = 20U;  // 20 KB SRAM

#endif // STM32F103C8_DEVICE_REGS_H
