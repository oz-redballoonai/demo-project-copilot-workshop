---
name: firmware-unit-test
description: Generate deterministic embedded C++ unit test stubs for firmware functions, especially when the user asks for tests for drivers, HAL-facing code, ISR-safe behavior, timeout/error-path validation, or host-side test scaffolding. Use this skill whenever the task is to create embedded unit tests with no heap, no exceptions, static test data, and explicit HAL mocking via function pointers, even if the user does not explicitly ask for a "skill" or "unit test template."
compatibility:
  tools: Read, Write, Edit, Search
---

# Firmware Unit Test

## Purpose

Create deterministic unit test scaffolding for embedded C++ firmware functions.

This skill focuses on:

- no heap usage
- no exceptions
- static test data only
- HAL mocking via function pointers
- predictable, repeatable test execution
- explicit coverage of happy path, boundaries, HAL_ERROR, and HAL_TIMEOUT

The output must always include:

- one `.cpp` test file
- one `mock_hal.h` file with stub declarations

## Test Modes

This skill operates in one of three modes. Pick the mode from the inputs:

- **STANDARD mode** (default): an implementation `.cpp` exists. Generate tests that document and pin current behavior across happy path, boundaries, and HAL error/timeout paths. Use when a driver is already written and you want a regression net.
- **TDD mode**: only a header (and optional spec) exists, no implementation yet. Write tests that express the intended contract; they start "red" until the implementation satisfies them. See the TDD Mode section below.
- **COVERAGE mode**: an implementation exists and is already partially tested. Generate tests **only for functions that are not yet covered**, leaving existing tests untouched. Use when extending an existing suite or when an orchestrator requests gap-filling. See the COVERAGE Mode section below.

## When To Use

Use this skill whenever the user asks to:

- generate unit tests for embedded C++ functions
- test firmware drivers on host
- validate HAL-facing logic without link-time substitution
- scaffold tests for timeout and error paths
- add deterministic test stubs for edge cases and failure handling
- write tests before an implementation exists (TDD mode - see below)

## TDD Mode

Use TDD mode when the user provides a **header file and an optional spec**, but no implementation `.cpp` exists yet.

**How to detect TDD mode:**

- No implementation file is provided or referenced.
- User says "write tests first", "TDD", or "before I implement".
- Only a `.h` and/or spec file are given as input.

**TDD mode rules:**

1. Write tests that express the **intended contract**, not observed behavior. Tests will be in "red" state (failing) until the implementation satisfies them.
2. Derive contracts from:
   - Function signatures and return types in the header.
   - Status enum values declared in the header - every declared value should be reachable. If `ERR_TIMEOUT` is declared, `HAL_TIMEOUT` must map to it.
   - A spec file if provided. Cite it as `// Source: <file>` on each contract.
3. Replace all "documents current behavior" comments with "Contract:" comments.
4. Do not reference `.cpp` implementation details in comments.
5. Add a **TDD Contract Map** block at the top of the `.cpp` file listing each test and the spec requirement or header contract it enforces.
6. If a contract cannot be derived from the header or spec alone, add a `TODO: confirm contract` comment and leave the assertion as a placeholder.
7. All other constraints (no heap, static data, function-pointer mocks, AAA, naming) apply unchanged.

**TDD mode checklist additions** (append to Final Checklist):

- All `HAL_*` status codes present in the mock enum have a corresponding test
- Each test comment says "Contract:" not "Documents current behavior:"
- TDD Contract Map block is present at top of `.cpp`
- No test assertion is derived from reading an existing `.cpp` implementation

## COVERAGE Mode

Use COVERAGE mode when an implementation `.cpp` **and** an existing test file both exist, and the task is to fill gaps rather than start fresh.

**How to detect COVERAGE mode:**

- A driver implementation and an existing `<target>_tests.cpp` are both present.
- User says "cover the missing functions", "fill coverage gaps", or "only untested functions".
- An orchestrator requests tests for uncovered functions.

**COVERAGE mode rules:**

1. Enumerate the public functions in the target implementation.
2. Read the existing test file and determine which functions already have at least one test.
3. Generate tests **only** for functions with no existing coverage. Do not duplicate or rewrite existing tests.
4. For each newly covered function, still apply the full Test Scope Requirements (happy path, boundaries, HAL_ERROR, HAL_TIMEOUT, HAL_BUSY, partial-read).
5. Add a **Coverage Map** block at the top of the output listing each target function as `covered (existing)` or `added (this run)`.
6. All other constraints (no heap, static data, function-pointer mocks, AAA, naming) apply unchanged.

## Constraints

Always enforce:

- no dynamic allocation
- no exceptions
- no RTTI
- no blocking calls inside test bodies
- deterministic test setup and assertions
- static arrays for all test data buffers

If the source code appears to require unsupported runtime behavior, document the limitation and still generate the closest safe deterministic test scaffold.

## Required Output

Always output exactly two files:

1. `<target>_tests.cpp`
2. `mock_hal.h`

Do not output only one file.
Do not replace `mock_hal.h` with another header name unless the user explicitly asks.

## Test Scope Requirements

For each target function, include tests for:

- happy path
- boundary conditions
- HAL_ERROR path
- HAL_TIMEOUT path
- HAL_BUSY path - document whether it is treated as retriable or as a hard error
- partial-read case - for any HAL read function that accepts a `len` parameter, include a test where the mock supplies fewer bytes than requested, and assert the driver handles or rejects the short read

Use naming format exactly:

- `test_<function>_<condition>_<expected>`

## Test Style

Use AAA structure in each test:

- Arrange
- Act
- Assert

Keep each test small and explicit.
Do not hide setup in complex fixtures unless requested.

## Mocking Rules

Mock HAL functions through function pointers only.
Do not use link-time substitution.
Do not use runtime patching frameworks.
Expose clear injectable function pointers in test scope or a simple mock layer header.

**Include order**: `mock_hal.h` must be included before any driver header that transitively includes the real HAL header. The mock must define the real HAL header's include guard (e.g., `#define HAL_STUB_H`) at the top of `mock_hal.h` to prevent double-definition conflicts when the driver header is included afterward.

## Safety and Context Checks

When generating tests, include checks relevant to embedded firmware correctness:

- argument validation
- buffer bounds
- integer overflow-sensitive paths
- status propagation behavior
- ISR-related non-blocking expectations where applicable

If ISR-specific behavior cannot be executed in host tests, simulate inputs and validate contract-level behavior.

## Output Template

Use this exact structure in your response.

### File 1: `<target>_tests.cpp`

- Include minimal includes.
- Include `mock_hal.h`.
- Define static test data arrays.
- Define deterministic mock state.
- Provide tests using AAA comments.
- Use required test naming pattern.

### File 2: `mock_hal.h`

- Define status enum values used by tests.
- Declare mockable HAL function pointer types.
- Declare mock function pointers.
- Declare helper reset/config functions for test setup.

## Implementation Guidance

Prefer:

- fixed-width integer types
- explicit return checks
- static constexpr constants for boundaries
- minimal helper functions for readability

Avoid:

- dynamic containers
- hidden global coupling
- random or time-based behavior
- ambiguous assertions

## Handling Missing Context

If function signatures or HAL contracts are missing:

- infer minimally from available code
- state assumptions briefly
- still produce compilable stubs with clear TODO markers
- keep assumptions narrow and test-oriented

## Examples

### Example 1

Input:
Generate host unit test stubs for this UART read function with timeout and bus errors.

Output shape:

- one `uart_read_tests.cpp` containing deterministic AAA tests
- one `mock_hal.h` defining mock function pointers for HAL read calls
- test names like `test_uart_read_timeout_returns_hal_timeout`

### Example 2

Input:
Create deterministic tests for this ADC conversion helper and include HAL failure paths.

Output shape:

- boundary tests for min/max input and clamping behavior
- HAL_ERROR and HAL_TIMEOUT tests through function pointer mocks
- static arrays only for fixtures and sample buffers

### Example 3

Input:
Build firmware unit tests for this driver with static buffers and no heap.

Output shape:

- tests covering happy path, boundaries, and error propagation
- no dynamic allocation, no exceptions, no RTTI
- clear AAA layout in every test body

## Examples

### Example 4 (TDD mode)

Input:
Here is `sensor.h` and `docs/specs/sensor_spec.md`. No implementation exists yet. Write the tests first.

Output shape:

- TDD Contract Map at top of `sensor_tests.cpp` mapping each test to a spec requirement or header contract
- `HAL_TIMEOUT` test asserts `SENSOR_ERR_TIMEOUT` because the header declares that enum value
- `HAL_BUSY` test asserts `SENSOR_ERR_BUS` with a `// Contract: HAL_BUSY treated as hard error, no retry` comment
- All assertions derived from header declarations and spec - no implementation file referenced
- All tests start failing (`red`) until the implementation satisfies the contracts

## Final Checklist Before Output

Confirm all are true before finalizing:

- Two files are present: `.cpp` and `mock_hal.h`
- Test names match `test_<function>_<condition>_<expected>`
- AAA structure is visible in each test
- Static arrays are used for test data
- HAL mocking uses function pointers
- Happy path, boundary, HAL_ERROR, HAL_TIMEOUT are covered
- No blocking calls in test bodies

**Additionally, if in TDD mode:**

- All `HAL_*` status codes in the mock enum have a corresponding test
- Each test comment says "Contract:" not "Documents current behavior:"
- TDD Contract Map block is present at top of `.cpp`
- No assertion is derived from reading an existing `.cpp` implementation
