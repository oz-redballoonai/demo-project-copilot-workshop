# ADT7410 Sensor Specification (Partial)

**Status**: Work in Progress - Do NOT assume complete

## Overview

- Device: Analog Devices ADT7410 Temperature Sensor
- Interface: I2C
- Address: 0x48 (7-bit, verify strapping on your board)

## Temperature Register

### Address 0x00-0x01

16-bit two's complement value.

**Format**:

- MSB at 0x00
- LSB at 0x01
- Default resolution: 13-bit
- Scale: 0.0625°C per LSB
  - Formula: temp(°C) = raw / 128
  - Scaled: temp(°C) × 100 = raw × 100 / 128

---

## Conversion Examples

| Raw Value | Temperature |
| --------- | ----------- |
| 128       | 1.00°C      |
| 2560      | 20.00°C     |
| 3200      | 25.00°C     |

---

## Error Handling

- If I2C read/write fails, return explicit error code (do not retry silently)
- Timeout value for I2C operation: TBD (assume 10ms for now)

---

## **NOT YET SPECIFIED** (Open Questions)

- [ ] Alert threshold registers (addresses? format?)
- [ ] Alert status register (address? bit meanings?)
- [ ] Configuration register details
- [ ] Interrupt behavior (if any)
- [ ] Resolution modes (13-bit vs 16-bit)
- [ ] Power-on reset behavior
- [ ] I2C clock speed requirements
- [ ] Board-specific strapping confirm (address pins)

---

## Reference

Consult the ADT7410 datasheet from Analog Devices for complete behavior.
This spec is derived from preliminary information only.
