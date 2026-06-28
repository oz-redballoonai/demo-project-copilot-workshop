# Inherited Driver - Scenario Files

> You've just joined the team and inherited this temperature-sensor **alert** module. It's intended for production, but the documentation is thin and the spec is incomplete. Your job (Module 3) is to triage it before it ships.

## What you have

### `adt7410_alert.h`
Public API for the alert-threshold module - configure thresholds, read alert status. Uses explicit error codes. Minimal documentation (as inherited).

### `adt7410_alert.cpp`
Implementation (C++). Talks to the sensor over I²C via HAL stubs. Contains inline assumptions marked with comments. No host-side tests exist yet.

### `adt7410_minimal.md`
Partial device spec. Covers the main temperature register only - alert registers are **not** described, the I²C address isn't confirmed, and timing constraints are missing.

### `hal_stub.h`
Minimal HAL interface (I²C read/write signatures + status codes). No hardware-behavior documentation.

## Key characteristics (by design)

- Looks plausible - not obviously broken
- Spec is incomplete (alert registers undefined)
- Assumptions are inline but not linked to evidence
- No dedicated tests
- Schedule pressure implied - someone expects it to "just work"

That gap between *plausible* and *proven* is the whole point of the exercise.
