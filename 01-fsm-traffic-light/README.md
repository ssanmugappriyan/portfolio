# FSM Traffic Light Controller (VHDL)

A Moore finite state machine implementing a traffic light controller with configurable timing, verified with a self-checking testbench.

## Design

**States:** `RED -> GREEN -> YELLOW -> RED` (repeats)

**Timing (generics, configurable per instantiation):**
| State | Default duration |
|-------|-------------------|
| RED | 4 clock cycles |
| GREEN | 3 clock cycles |
| YELLOW | 2 clock cycles |

**Type:** Moore FSM — outputs depend only on current state, not inputs, which keeps the outputs glitch-free relative to input changes.

**Reset:** Synchronous, active-high. Forces the FSM to `RED` with counter cleared.

## Files
```
src/traffic_light_fsm.vhd       -- RTL source
tb/traffic_light_fsm_tb.vhd     -- self-checking testbench
sim/                             -- simulation log / waveform screenshot
```

## Verification approach

The testbench isn't just a stimulus generator — it self-checks three properties on every run:

1. **Reset correctness** — asserts RED is forced immediately after reset
2. **Sequence correctness** — asserts each state transitions to the correct next state after the correct number of cycles (checked against `RED_TIME`, `GREEN_TIME`, `YELLOW_TIME`)
3. **One-hot output property** — a continuous assertion running every clock cycle confirms exactly one of `red_light` / `yel_light` / `grn_light` is active at any time (a design where two lights are on simultaneously is a real, dangerous bug class)

On success, the simulation prints `TEST RESULT: ALL CHECKS PASSED`. On failure, it reports exactly which check failed and why.

## How to simulate

**EDA Playground:** paste `src/` file into Design, `tb/` file into Testbench, run with GHDL or any VHDL-2008 simulator.

**GHDL (local):**
```bash
ghdl -a src/traffic_light_fsm.vhd
ghdl -a tb/traffic_light_fsm_tb.vhd
ghdl -e traffic_light_fsm_tb
ghdl -r traffic_light_fsm_tb --wave=sim/wave.ghw
```

## What I'd improve with more time

- Add configurable pedestrian-crossing state with a button input
- Parameterize for multiple intersections with a shared clock and mutually-exclusive green phases
- Port to Verilog as a cross-language exercise (see repo root for planned Verilog rebuild)
