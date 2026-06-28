# ADT7410 Minimal Firmware Spec

## Source
- Datasheet: Analog Devices ADT7410 (use the exact revision used by your team)

## Interface
- Bus: I2C
- Address: 0x48 (example 7-bit address; verify board strapping)

## Temperature register
- Address 0x00: Temperature MSB
- Address 0x01: Temperature LSB
- Combined: 16-bit two's complement
- Default resolution: 13-bit, scale = 0.0625 C per LSB
  - Equivalent: temp(C) = raw / 128

## Conversion
- raw: int16_t
- temp(C) = raw / 128
- temp(C)*100 = raw*100/128

## Error handling expectations
- If I2C read fails, return an explicit error code.
- Do not guess register values or scaling if spec differs.

## Missing info / open questions
- Confirm I2C address for your hardware.
- Confirm resolution mode configuration (13-bit vs 16-bit).
