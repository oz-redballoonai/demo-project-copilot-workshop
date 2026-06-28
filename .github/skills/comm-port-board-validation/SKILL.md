---
name: comm-port-board-validation
description: Generate validation artifacts for dedicated communication port boards and firmware bring-up, especially when the user mentions UART, USART, RS-232, RS-485, serial links, framing, parity, baud rate, DE/RE direction control, communication board verification, port bring-up, host-test stubs, bench-test plans, or deterministic firmware validation. Use this skill whenever the task is to review or validate a communication-port driver/board and produce bring-up checks, validation tests, failure cases, or test scaffolding, even if the user does not explicitly ask for a "validation skill."
compatibility:
  tools: Read, Write, Edit, Search
---

# Communication Port Board Validation

## Purpose

Use this skill to create deterministic validation artifacts for a dedicated communication port board and its firmware.

This skill is for UART, USART, RS-232, and RS-485 oriented work where the user needs practical validation outputs:

- bring-up checklists
- communication validation test cases
- host-test or bench-test stubs
- pass/fail criteria
- targeted code review findings tied to communication correctness

The goal is not to redesign the system. The goal is to help the user verify that the board and firmware can be brought up safely, tested deterministically, and reviewed with embedded constraints in mind.

## Core Constraints

Always preserve these constraints in both analysis and generated artifacts:

- No heap
- No exceptions
- No RTTI
- No blocking in ISR
- Deterministic behavior for bare-metal or RTOS systems
- No architectural rewrites
- No claims about electrical or protocol behavior without a spec reference

If the user asks for something that would violate these constraints, explain the issue and produce the closest safe alternative.

## When To Use

Use this skill when the user is working on any of the following:

- UART or USART board bring-up
- RS-232 or RS-485 communication firmware validation
- Serial framing, parity, baud-rate, timeout, or buffer-handling checks
- Direction-enable or transmit/receive turnaround handling for RS-485
- Bench validation for communication boards
- Host-test scaffolding for serial communication code
- Reviewing a communication driver for ISR safety, RTOS context correctness, buffer bounds, integer overflow, or error propagation
- Creating pass/fail criteria for firmware verification on a communication interface

## First Step

Before generating output, identify what inputs are available:

- driver source files
- public headers
- board schematic notes or connector notes
- protocol specification
- UART/RS-232/RS-485 electrical details
- RTOS usage context
- test environment details such as host harness, USB-UART adapter, logic analyzer, oscilloscope, or serial terminal

If important information is missing, do not invent it. Continue with a useful draft, but explicitly list the missing inputs as gaps or assumptions.

**Domain scope check**: Before producing output, check whether the input file contains any UART, USART, RS-232, or RS-485 API calls, type names, or peripheral references. If none are found, output the following notice at the top of the response:

> This file does not appear to be a UART/RS-232/RS-485 driver. Applying general defensive embedded checks only. Communication-specific sections: Not applicable.

Then continue with Bring-Up Checks and Failure Cases scoped to general defensive behavior only. Do not fabricate UART/RS-485 findings for files that have no communication peripheral usage.

## Required Behavior

Always do the following:

1. Determine the communication context.
2. Separate firmware concerns from board-level concerns.
3. Distinguish ISR context from task/thread context.
4. Check that generated validation steps are deterministic and realistic.
5. Prefer minimal code changes and validation hooks over broad refactors.
6. Tie protocol or electrical claims to a spec reference when one exists.
7. If code is referenced, cite it as `[file:line]`.

## What To Check

When reviewing code or creating validation artifacts, check these areas as applicable:

### ISR Safety

Check for:

- blocking calls in ISR
- logging or long loops in ISR
- non-ISR-safe queue or RTOS API usage
- shared buffer updates without a clear ownership or synchronization strategy
- interrupt handlers doing protocol parsing that should be deferred

### RTOS Context Correctness

Check for:

- task-only APIs used from ISR
- unclear handoff between ISR and task context
- timeout usage that is unsafe in the active context
- queue, semaphore, or ring-buffer usage that can race or starve

### UART / Serial Protocol Correctness

Check for:

- framing assumptions
- parity configuration assumptions
- stop-bit assumptions
- baud-rate mismatch handling
- receive timeout handling
- delimiter or packet-boundary assumptions
- buffer-overrun or truncation behavior
- half-duplex turnaround handling for RS-485

### RS-485 Direction Control

Check for:

- DE/RE pin sequencing
- turnaround timing assumptions
- transmit-complete vs transmit-buffer-empty confusion
- receive re-enable timing
- collision or bus-contention risk where applicable

### Testability

Check for:

- HAL or peripheral call sites that are direct (not injectable via function pointer or abstraction layer)
- if HAL calls are not injectable, flag this as a host-test validation gap: the driver cannot be unit-tested without link-time substitution or hardware access
- note whether the driver is structured for host-side testing at all

### Defensive Embedded Behavior

Check for:

- integer overflow in counters, lengths, time calculations, or ring-buffer math
- invalid pointer handling
- unchecked return values
- `HAL_BUSY` treated identically to `HAL_ERROR` without documentation - flag if the distinction matters for retry logic
- silent error swallowing
- retry behavior without bounds
- state-machine gaps during timeout or line-noise conditions

## Output Rules

Always group output exactly as:

# Bring-Up Checks

# Validation Tests

# Failure Cases

Do not replace these headings with alternatives.

If code is referenced, cite `[file:line]`.

For each item:

- describe the issue or validation goal
- explain the runtime impact
- give the minimal validation step or minimal code change
- include pass/fail criteria whenever possible

If a section has no items, write `None identified.` under that heading.

## Output Template

Always use this structure:

# Bring-Up Checks

- Title:
- Scope:
- Why it matters:
- Evidence:
- Minimal validation or code change:
- Pass criteria:
- Fail criteria:

# Validation Tests

- Title:
- Scope:
- Why it matters:
- Evidence:
- Test method:
- Minimal validation or code change:
- Pass criteria:
- Fail criteria:

# Failure Cases

- Title:
- Scope:
- Why it matters:
- Evidence:
- Failure mode:
- Minimal validation or code change:
- Pass criteria:
- Fail criteria:

## How To Build The Output

### If the user provides code

Read the code and produce:

- bring-up checks for initialization and configuration
- validation tests for nominal and boundary communication behavior
- failure cases for timeout, noise, overflow, framing, parity, and direction-control faults

### If the user provides a board or protocol spec

Use it to anchor:

- connector expectations
- electrical assumptions
- interface mode
- direction-control timing expectations
- framing rules
- timeout budgets

If the spec is incomplete, say what cannot be validated from it.

### If the user asks for test scaffolding

Generate host-test or bench-test stubs that are deterministic:

- no heap
- static buffers only
- explicit Arrange / Act / Assert structure if code is produced
- clear injection points for HAL error, timeout, framing faults, or line noise

## Validation Artifact Guidance

### Bring-Up Checks

Good bring-up checks usually cover:

- power and ground expectations for the communication interface
- correct UART/USART peripheral initialization
- GPIO mode and alternate-function setup where applicable
- RS-485 DE/RE default state
- idle-line behavior
- known-good baud, parity, and stop-bit configuration
- interrupt enable order
- receive path enablement before live traffic
- safe startup state if peer is already transmitting

### Validation Tests

Good validation tests usually cover:

- happy-path transmit and receive
- boundary-length frames
- zero-length or malformed frame handling
- parity mismatch behavior
- framing error handling
- receive timeout behavior
- baud mismatch detection or observed failure behavior
- sustained receive burst without buffer corruption
- RS-485 half-duplex turnaround
- repeated transmit/receive cycles
- task-context vs ISR-context separation behavior

### Failure Cases

Good failure cases usually cover:

- HAL timeout
- HAL error
- framing error
- parity error
- overrun
- noise-induced corruption
- stuck direction-enable
- stale state after error recovery
- unchecked return value leading to silent communication failure
- race conditions between ISR producer and task consumer

## Code Generation Rules

If generating code snippets, stubs, or scaffolding:

- use fixed-width integer types
- use static storage or stack storage only
- do not allocate dynamically
- do not add exceptions or RTTI-based patterns
- keep functions small and deterministic
- prefer explicit status returns
- avoid hidden control flow
- comment only where it explains why something matters

## Review Style

Be direct and specific.

Do not produce vague advice like:

- "improve error handling"
- "consider refactoring"
- "make this more robust"

Instead, say what to validate or change and why:

- which path can fail
- what runtime symptom would appear
- what minimal validation step would expose it
- what minimal code change would contain the risk

## Missing Information Policy

If key information is missing, add a short `Assumptions / Gaps` note before the main sections.

Typical missing items:

- voltage levels for RS-232 transceiver or RS-485 transceiver
- exact framing format
- DE/RE polarity
- interrupt model
- RTOS usage model
- receive buffer ownership
- timeout budget from spec

Do not stop unless the missing information makes the task impossible. Produce the most useful safe draft you can.

## Examples

### Example 1

Input:
Review this RS-485 UART driver and give me validation artifacts for bring-up.

Output shape:

- Bring-Up Checks covering DE/RE default state, UART init order, and interrupt enable sequence
- Validation Tests covering TX/RX, half-duplex turnaround, timeout handling, and line-noise injection
- Failure Cases covering stuck DE, unchecked timeout, and buffer overrun

### Example 2

Input:
Generate bench validation for a dedicated RS-232 board connected through a USB serial adapter.

Output shape:

- Bring-Up Checks covering board power, connector pin assumptions, UART settings, and known-good loopback setup
- Validation Tests covering baud/parity/stop-bit permutations and error observation
- Failure Cases covering framing mismatch, parity mismatch, and receive timeout recovery

### Example 3

Input:
Review this UART ISR and task handoff logic for race conditions and produce minimal fixes.

Output shape:

- Bring-Up Checks covering interrupt configuration and buffer initialization
- Validation Tests covering burst RX, queue handoff, and timeout behavior
- Failure Cases tied to `[file:line]` with minimal validation or minimal code changes

## Final Reminder

This skill is about validation quality, not feature expansion.

Prefer:

- practical bring-up steps
- deterministic tests
- explicit failure cases
- minimal corrective actions
- evidence tied to code and specs

Avoid:

- broad redesigns
- speculative electrical claims
- dynamic memory
- task/ISR confusion
- ambiguous pass/fail outcomes
