# Workshop: AI-Powered Embedded Firmware Development

Welcome. This repo is your workspace for the hands-on portion of today's workshop.

> **Did you do the pre-flight?** You should have completed `PRE_FLIGHT.md` a few days ago and confirmed Copilot works. If you did, this setup is just a quick re-check. If you didn't, do it now and flag a facilitator.

## Setup (do this now)

1. **Open this folder as your VS Code workspace root**  
   `File > Open Folder` → select the workshop project folder (the repo root)  
   (not a subfolder  -  the root matters for Copilot to find the instructions file)

2. **Confirm Copilot is active**  
   Look for the Copilot icon in the bottom-right status bar. It should not show an error.

3. **Open Copilot Chat**  
   `View > Copilot Chat`  or  `Ctrl+Alt+I` (Windows/Linux)  /  `Cmd+Ctrl+I` (Mac)

4. **Verify the instructions are loaded**  -  send this in Copilot Chat:
   ```
   Summarize the coding constraints for this repository.
   ```
   You should see rules about no malloc, ISR constraints, and minimal diffs.

---

## Key Files for Today's Exercises

| File | Used in |
|------|---------|
| `.github/copilot-instructions.md` | Exercise 1  -  the guardrails file Copilot reads automatically |
| `docs/specs/adt7410_minimal.md` | Exercise 2  -  partial sensor spec for code generation |
| `inherited/adt7410_alert.cpp` | Exercise 3  -  inherited driver to triage |
| `inherited/adt7410_alert.h` | Exercise 3 |
| `inherited/adt7410_minimal.md` | Exercise 3 |
| `inherited/hal_stub.h` | Exercise 3 |
| `Core/Src/adt7410.cpp` | Exercise 4  -  target for the `/firmware-unit-test` skill |
| `.github/skills/firmware-unit-test/SKILL.md` | Exercise 4  -  the skill definition you inspect |
| `.github/agents/firmware-review-orchestrator.agent.md` | Exercise 5  -  the agent you read and (optionally) run |

---

## Your Exercise Guide

Follow `workshop_exercises.md` in this folder. It has all the prompts  -  copy and paste them exactly as written.

---

## What This Repo Is

A VS Code-first training workspace mimicking a real STM32 project layout:
- `Core/Inc`, `Core/Src`  -  application code
- `Drivers/`  -  stubbed HAL (no real hardware needed)
- `docs/specs/`  -  spec files used as context for prompts
- `inherited/`  -  the "inherited driver" scenario

No compilation or hardware required for today's exercises.
