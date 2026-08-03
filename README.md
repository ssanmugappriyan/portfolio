# RTL Design Portfolio

Personal collection of RTL/digital design projects in VHDL (and Verilog, where noted), each built with a self-checking testbench and simulation proof — not just code, but verified working designs.

I'm a final-year ECE student (graduating 2026) targeting entry-level RTL / Digital Design roles, working toward ASIC design long-term. This repo is my proof of hands-on work beyond coursework.

## Projects

| # | Project | Language | Skills Demonstrated | Status |
|---|---------|----------|---------------------|--------|
| 01 | [FSM Traffic Light Controller](./01-fsm-traffic-light) | VHDL | FSM design, sequential logic, testbench verification | ✅ Complete |
| 02 | 8-bit ALU | VHDL | Combinational logic, structural design | 🔜 Planned |
| 03 | Async FIFO | VHDL | Clock domain crossing, synchronizer design | 🔜 Planned |
| 04 | UART Transceiver | VHDL | Serial protocol, timing-driven design | 🔜 Planned |
| 05 | FSM Traffic Light (Verilog rebuild) | Verilog | Cross-language RTL competence | 🔜 Planned |

## How each project is structured

Every project folder contains:
- `src/` — synthesizable RTL source
- `tb/` — self-checking testbench (assertions, not just waveform inspection)
- `sim/` — simulation log and/or waveform screenshot as proof of correct behavior
- `README.md` — what it does, how to simulate it, and design notes

## Tools

Simulated using [GHDL](https://ghdl.github.io/ghdl/) (open-source VHDL simulator) and GTKWave for waveform viewing. OrCAD X Capture used separately for schematic-level work (see internship experience on [LinkedIn](https://www.linkedin.com/in/sanmugappriyan-s)).

## Contact

Sanmugappriyan S — sanmugappriyan.ee@gmail.com — [LinkedIn](https://www.linkedin.com/in/sanmugappriyan-s)
