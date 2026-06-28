# AI-Native Embedded Firmware Workshop

A VS Code-first workspace for the hands-on portion of the workshop. It mimics a real STM32CubeMX-style project - an STM32F103 reading an ADT7410 I²C temperature sensor - with a stubbed HAL so nothing needs real hardware.

## Start here

1. **Before the workshop:** follow [`PRE_FLIGHT.md`](PRE_FLIGHT.md) to confirm VS Code + GitHub Copilot are working. It takes ~10 minutes and saves the whole room from setup delays on the day.
2. **At the workshop:** open [`WORKSHOP.md`](WORKSHOP.md) for the 2-minute setup re-check, then work through [`workshop_exercises.md`](workshop_exercises.md).

> Please don't run the exercise prompts before the session - discovering the results live (and comparing what everyone gets) is half the point.

## What we'll do (5 short modules)

1. **Guardrails & Context** - how Copilot reads this repo's rules automatically
2. **Spec-Driven Generation** - generating code from a spec, and catching hallucinations
3. **Production Risk Review** - triaging an inherited driver before it ships
4. **Skills** - reusable, structured prompt packages (`/firmware-unit-test`)
5. **Agents** - a multi-step review orchestrator with a gated verdict

## Folder overview

- `Core/Inc`, `Core/Src` - application code (drivers, `main`)
- `Drivers/STM32_HAL_stub/` - minimal HAL-like stubs (no hardware needed)
- `docs/specs/` - short markdown specs used as the single source of truth
- `inherited/` - the "inherited driver" scenario for Module 3
- `.github/` - Copilot guardrails, skills, and agents
- `tests/host/` - placeholder where you'll generate host-side tests
- `stm32f103c8.pdf` - the real STM32F103 datasheet, for reference

No compilation or hardware required.
