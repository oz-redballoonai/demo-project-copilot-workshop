# Pre-Flight Checklist - Read & Do Before the Workshop

**Please complete this 2-3 days before the session and reply with one screenshot of Step 6.**

This 10-minute setup is the difference between a smooth workshop and spending the first 15 minutes fixing tools instead of doing the cool stuff. Everything that tends to break - licenses, network, workspace setup - is easy to fix now and painful to fix live. Do it on the **same laptop and network** you'll use during the workshop.

If anything below fails, reply to the invite and we'll sort it out before the day - not on the clock.

---

## What you need ready

### 1. VS Code installed
Current version. Download: https://code.visualstudio.com/

### 2. GitHub Copilot - enabled AND licensed
- Recent versions of VS Code include **GitHub Copilot and Copilot Chat built-in** - just make sure VS Code is up to date and you likely won't need to install anything. (On older VS Code, install the **GitHub Copilot Chat** extension from the Extensions panel.)
- Sign in with a GitHub account that has an **active Copilot license**.
- ⚠️ Most common silent failure: the seat was *requested* but never *assigned*. Confirm Copilot actually works (Step 6 below), don't assume.

### 3. The workshop repo, cloned locally
```
git clone <repo-url>
```
(or download the zip and unzip it). You just need the workshop project folder on your machine.

### 4. Network check - on your real workshop network
Copilot needs outbound internet access. Corporate VPNs and proxies sometimes block it.
- Test on the **network you'll actually be on during the workshop** (office wifi / VPN), not only home wifi.
- If Step 6 fails on that network, it's almost always a proxy/firewall issue - flag it to us early.

### 5. Open the repo as the **workspace root**
`File > Open Folder` → select the workshop project folder itself (the repo root).
**Not** a subfolder. The root matters - Copilot reads the instructions file from there.

### 6. ✅ The green-check self-test (do this and screenshot it)
1. Open Copilot Chat (`Ctrl+Alt+I` on Windows/Linux, `Cmd+Ctrl+I` on Mac).
2. Send exactly:
   ```
   Summarize the coding constraints for this repository.
   ```
3. **Expected:** Copilot mentions rules like **no malloc/free**, **ISR constraints**, and **minimal diffs**, and points to `.github/copilot-instructions.md`.
   - ✅ You see those rules → **you're ready. Screenshot this and reply to the invite.**
   - ❌ You get a generic answer with no mention of those rules → your workspace root is wrong (Step 5). Reopen at the repo root and try again.

---

## Optional - only if you want to run the Module 5 agent live
Module 5 ends with an autonomous review agent. You can fully follow along by reading and discussing it - **this is optional and not required.** If you'd like to run it live yourself, set up **one** of the following.

**Option A - Copilot agent mode (easiest, you already have Copilot)**
1. Update VS Code and the **GitHub Copilot Chat** extension to the latest version (`Code > Check for Updates`, and update the extension in the Extensions panel).
2. Open Copilot Chat: click the **chat icon** in the top toolbar of VS Code (a speech-bubble icon), or open the **View** menu in the top menu bar and choose **Chat** (it may be listed as **Copilot Chat**).
3. At the **bottom-left of the chat input box** there's a small dropdown that says **Ask** - click it and choose **Agent**.
4. **Don't see "Agent" in that dropdown?** You need to turn on one setting:
   - In the top menu bar, choose **Code > Settings > Settings** (on Windows/Linux: **File > Preferences > Settings**). A Settings tab opens.
   - In the search box at the top of that Settings tab, type `chat.agent.enabled`, then tick the checkbox that appears under it.
   - Reload VS Code: open the **View** menu, choose **Command Palette**, type `Developer: Reload Window`, and press Enter.
5. Verify: in Agent mode, the custom agents in `.github/agents/` become selectable once the project is open at its root.

**Option B - Claude Code (terminal-based)**
1. Install Node.js 18+ if you don't have it: https://nodejs.org/
2. Install Claude Code: `npm install -g @anthropic-ai/claude-code`
3. Sign in: run `claude` in a terminal and follow the browser login prompt (Claude account or API key).
4. Verify: `claude --version` prints a version number.

If you skip both, you'll still see the agent demonstrated. No need to set it up just for the workshop.

---

## TL;DR
Open the repo at its root in VS Code, ask Copilot Chat *"Summarize the coding constraints for this repository,"* and if it cites the no-malloc / ISR rules → you're set. Screenshot it and reply. That's the whole job.
