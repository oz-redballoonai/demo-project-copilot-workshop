# Copilot Instructions - Firmware Training Repo (STM32 style layout, VS Code)

You assist with an embedded C codebase that follows STM32CubeMX-style conventions (Core/Src, Core/Inc),
but this repository is used for training in VS Code. Your output must be safe, deterministic, and reviewable.

## Non negotiable constraints

- No dynamic memory: DO NOT use malloc/free/new/delete.
- Avoid recursion.
- Keep diffs minimal and local. Prefer surgical edits.
- Do not add blocking calls in time critical paths.
- In ISR context: no blocking calls, no logging/printf, no long loops, no heap.

## Language and style

- Primary language: C++ (use modern C++ but keep it embedded-friendly).
- Avoid exceptions and RTTI unless the repo explicitly uses them.
- Avoid the C++ standard library on target unless explicitly allowed (no iostream).
- Prefer deterministic code. Keep allocations and hidden costs out of hot paths.

## RTOS context rules

- Distinguish contexts:
  - ISR context: no blocking calls, no heap, no logging, minimal work.
  - Task context: blocking may be allowed only when explicitly stated.
- Do not call task-only APIs from ISR.
- Use ISR-safe RTOS APIs when in ISR (e.g., \*FromISR variants).
- Be explicit about thread-safety: protect shared state with mutex/critical sections or message passing.

## Code documentation and comments

- Prefer short, high-signal comments that explain "why", not "what".
- Do not write comments that simply restate the code.
- Avoid speculative comments. Do not claim hardware behavior unless referenced by a spec file.
- When a constant, register, bitfield, timing value, or formula comes from a spec, add a source reference:
  // Source: docs/specs/<file>.md
- Use Doxygen-style comments only when asked, or when adding a new public API in a header.
- Keep comments stable and maintainable:
  - No long paragraphs
  - No marketing language
  - No excessive bullet lists inside code

## Public API documentation (headers)

- For functions in Core/Inc/\*.h, add a short Doxygen block:
  - Purpose
  - Parameters (only non-obvious details)
  - Return value
  - Important constraints (ISR-safe, blocking, units)
- Include units in documentation when applicable (e.g., temp in C\*100).
- Do not document undefined behavior; enforce it via input validation in code.

## Logging policy

- Do NOT use printf, sprintf, snprintf directly.
- Do NOT introduce stdio-based logging.
- Do NOT log inside ISR or time-critical paths.
- If logging is required, use a project-defined macro (e.g., APP_LOG_INFO, APP_LOG_ERROR).
- Assume logging may be compiled out in production.
- Logging must never block execution or allocate memory.

## Generated vs user code rules

- Treat everything outside USER CODE blocks as "generated style" and do not rewrite it unless explicitly asked.
- Only add or modify logic within blocks like:
  - /_ USER CODE BEGIN <tag> _/
  - /_ USER CODE END <tag> _/

## Hardware correctness: NO GUESSING

- Do NOT invent register addresses, bitfields, timing values, scaling constants, or protocol details.
- If a value depends on a datasheet/spec, require a reference under docs/specs.
- If information is missing, ask 1-3 targeted questions and stop.

## Types and defensive programming

- Use fixed width integer types: uint8_t/uint16_t/uint32_t/int16_t, etc.
- Validate bounds and pointer usage.
- Handle return codes explicitly. Prefer small enums/status codes.
- Be explicit about endianness when assembling multi-byte values.

## Output expectations

- Before changing code: summarize intent and affected files/functions.
- Provide minimal patches and explain changes briefly.
- If asked to refactor, propose a short plan first, then implement after approval.
