# Hands-On Exercise Guide
## AI-Native Embedded Firmware Development Workshop

**Time:** 60 minutes  
**Tool:** GitHub Copilot in VS Code  
**Repo:** the workshop project folder (this folder)

> ⚠️ **Please don't run these prompts before the workshop.** Half the value is discovering the results live and comparing what everyone gets. Set up using `PRE_FLIGHT.md`, but save the exercises for the session.

> **How to read this guide:** Each module has a **core part** (must-do) and optional **extensions** for fast movers. Move at the core pace  -  don't wait on extensions before moving on.

---

## Before You Start

Open this folder as your workspace root in VS Code (`File > Open Folder` → select the workshop project folder, i.e. the repo root). Confirm the Copilot status bar icon is active (bottom-right, no error). Open **Copilot Chat**: click the chat icon in the top toolbar, or open the **View** menu and choose **Chat** (it may be listed as **Copilot Chat**).

> **Chat mode matters:** keep Copilot Chat in **Ask** mode for Modules 1-4 (the small dropdown at the bottom-left of the chat box). Switch to **Agent** mode only for Module 5. Agent mode automatically reads your repo files, which would spoil the Module 1 demo.

---

## Module 1  -  Guardrails & Context
**Core: 10 minutes**

The repo contains `.github/copilot-instructions.md`. Copilot reads it automatically before every interaction  -  your no-malloc, ISR, and diff rules, always active.

### 1A  -  Verify rules load *(3 min)*

```
Summarize the coding constraints defined for this repository.
List: memory rules, ISR constraints, refactoring discipline, and where these rules are defined.
```

**If Copilot gives a generic answer** that doesn't cite this repo's specific rules, your workspace root is wrong  -  reopen at the repo root and retry.

---

### 1B  -  The hallucination trap *(7 min)*

Send this **without attaching any file:**

```
From your own general knowledge only - do not open, read, or search any files in this workspace.
List the exact I2C register addresses for the ADT7410 temperature sensor:
- temperature register
- configuration register
- high-limit threshold register
Give specific hex values for each.
```

**Write down what you get**  -  you'll check it against the real spec in Module 2.

---

> **Extension (fast movers):** Ask Copilot `Is it allowed to use malloc in this project? Explain why.`  -  confirm it says NO and cites the instructions file, not just generic embedded wisdom.

---

## Module 2  -  Spec-Driven Code Generation
**Core: 10 minutes**

### 2A  -  Generate from spec and compare *(7 min)*

Open `docs/specs/adt7410_minimal.md` in the editor, then:

```
Using only #file:docs/specs/adt7410_minimal.md, generate C constants for all register addresses defined in the spec.

Constraints:
- Do not guess missing values.
- If a value is not in the spec, list it as missing and stop.
- Add a // Source: docs/specs/adt7410_minimal.md comment to each constant.
```

**Compare with what you wrote down in Module 1B.** What's different between the two?

---

### 2B  -  Push the limit *(3 min)*

Still with the spec in context:

```
Using only #file:docs/specs/adt7410_minimal.md, what is the I2C clock stretch timeout in milliseconds for the ADT7410?
```

**Then check:** is that value actually anywhere in the spec file?

---

> **Extension:** Generate a full `adt7410_regs.h` header: all register constants, include guard, source comment at the top, no invented values.

---

## Module 3  -  Production Risk Review
**Core: 12 minutes**

You've inherited a driver. Triage it before it ships.

Open in the editor:
- `inherited/adt7410_alert.cpp`
- `inherited/adt7410_alert.h`
- `inherited/adt7410_minimal.md`
- `inherited/hal_stub.h`

### 3A  -  Triage *(8 min)*

```
You just joined a firmware team.

Inherited code:
- driver: #file:inherited/adt7410_alert.cpp
- public API: #file:inherited/adt7410_alert.h
- partial spec: #file:inherited/adt7410_minimal.md
- HAL assumptions: #file:inherited/hal_stub.h

Do NOT modify code yet.

Task:
1. List every production risk visible immediately
2. Separate: code defects / spec gaps / verification gaps
3. State: safe to merge today? YES or NO
4. Justify in 5-10 bullets

Do not guess hardware behavior.
```

**Note the three categories**  -  you'll see these again in Module 5.

---

### 3B  -  ISR safety check *(4 min)*

```
Is #file:inherited/adt7410_alert.cpp safe to call from ISR context? Justify.
If not: describe what would need to change, without modifying the code.
```

---

> **Extension:** Run the MISRA simulation: `Review #file:inherited/adt7410_alert.cpp as if running MISRA C:2012 / static analysis. List all violations or risks. Do not modify  -  report only.`

---

## Module 4  -  Skills in Action
**Core: 10 minutes**

Skills are reusable prompt packages. Invoke with a slash command. Consistent, structured output every time.

### 4A  -  Run the unit test skill *(8 min)*

Open `Core/Src/adt7410.cpp` in the editor. In Copilot Chat:

```
/firmware-unit-test

Target: #file:Core/Src/adt7410.cpp
Function: adt7410_read_temp_c_x100

Generate tests for: happy path, HAL_ERROR return, HAL_TIMEOUT return, and boundary values.
Constraints: no heap, no exceptions, static test data only, HAL mocking via function pointers.
```

**Check your output:**
- Did it cover HAL_ERROR and HAL_TIMEOUT, or just the happy path?
- Any `new` / `malloc` anywhere?
- How did it mock the HAL?
- Did it produce a second file alongside the tests?

---

### 4B  -  Inspect the skill definition *(2 min)*

Open `.github/skills/firmware-unit-test/SKILL.md`. Ask:

```
Based on #file:.github/skills/firmware-unit-test/SKILL.md, what are the three test modes this skill supports and when should each be used?
```

This is how skills encode expertise so you don't re-prompt every time.

> **Going further:** these skills are just markdown files  -  you can author your own with `/skill-creator`. We don't cover skill-authoring today, but that's the natural next step.

---

> **Extension:** Try `/comm-port-board-validation`  -  same skill pattern, different domain. Generates a bring-up checklist for hardware interface validation.

---

## Module 5  -  Agentic Taste
**Core: 8 minutes**

Agents execute multi-step tasks autonomously  -  with sub-agent handoffs and gated verdicts.

### 5A  -  Understand the orchestrator *(4 min)*

Open `.github/agents/firmware-review-orchestrator.agent.md`. Send:

```
Based on #file:.github/agents/firmware-review-orchestrator.agent.md, explain:
1. What this agent does end-to-end
2. What sub-agents it hands off to and in what order
3. What the three possible verdicts mean (PASS / REVIEW REQUIRED / BLOCKED)
4. What conditions trigger a BLOCKED verdict
```

---

### 5B  -  Run or discuss *(4 min)*

**If agent mode is available** (Copilot agent mode or Claude Code):

```
Run firmware-review-orchestrator on:
- driver_file_path: inherited/adt7410_alert.cpp

Use inherited/adt7410_minimal.md for spec validation.
Generate tests under tests/host/.
Report the final verdict with justification.
```

Watch the handoffs: Read → Firmware Review → Spec Validation → Test Generation → Gated Verdict.

> **Going further:** the orchestrator and its sub-agents are just `.agent.md` files you can write yourself  -  building your team's own review pipeline is a deeper topic for another session.

**If not available**  -  discuss as a group:
- Module 3 triage output: how long did it take?
- The orchestrator runs that review **plus** spec validation **plus** test generation automatically.
- When does a single prompt beat an agent? When does an agent win?

---

## Wrap-Up
**Before you close:**

Three questions worth answering:

1. **Which file on your real project** would you run production triage on this week?
2. **Which single prompt** from today is most immediately useful to you?
3. **What rule would you add** to `.github/copilot-instructions.md` for your actual project?

---

## Prompt Cheat Sheet

Take this with you for daily use.

**Spec-Driven Generation**
```
Using only #file:<spec>, generate <output>.
Do not guess. If missing, list gaps and stop.
Add // Source: <spec> to each constant.
```

**Production Triage**
```
List every production risk. Separate: code defects / spec gaps / verification gaps.
State: safe to merge? YES or NO. Justify. Do not guess hardware behavior.
```

**ISR Safety Check**
```
Is this safe to call from ISR context? Justify.
If not: describe what needs to change, without modifying the code.
```

**MISRA Simulation**
```
Review as if running MISRA C:2012 / static analysis.
List all violations or risks. Do not modify  -  report only.
```

**Controlled Refactor**
```
Refactor ONLY the selected function.
Constraints: minimal diff, no behavior change, no malloc, no API change.
If context is missing, ask and stop.
```

**Unit Test Skill**
```
/firmware-unit-test
Target: #file:<driver>
Generate tests for: <function list>
Constraints: no heap, HAL mocking via function pointers.
```
