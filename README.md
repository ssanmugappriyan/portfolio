# Engineering Portfolio

Personal collection of my technical projects — RTL/digital design (VHDL, Verilog), embedded firmware, C programming, and coursework — each built with working code and, where applicable, verification/testing proof.

I'm a final-year ECE student (graduating 2026) targeting entry-level RTL / Digital Design and embedded roles, working toward ASIC design long-term. This repo is my proof of hands-on work beyond coursework.

## Projects

| # | Project | Language | Skills Demonstrated | Status |
|---|---------|----------|----------------------|--------|
| 01 | [FSM Traffic Light Controller](https://github.com/ssanmugappriyan/portfolio/tree/main/VHDL/01-fsm-traffic-light) | VHDL | FSM design, sequential logic, testbench verification | ✅ Complete |
| 02 | [College Project — Smart Knee Monitor](https://github.com/ssanmugappriyan/portfolio/tree/main/College%20Project) | C (Arduino) + VHDL | Embedded firmware, sensor integration, hardware design, documentation | ✅ Complete |
| 03 | 8-bit ALU | VHDL | Combinational logic, structural design | 🔜 Planned |
| 04 | Async FIFO | VHDL | Clock domain crossing, synchronizer design | 🔜 Planned |
| 05 | UART Transceiver | VHDL | Serial protocol, timing-driven design | 🔜 Planned |
| 06 | FSM Traffic Light (Verilog rebuild) | Verilog | Cross-language RTL competence | 🔜 Planned |

> New folders (e.g. `C/`, `Embedded/`, `Python/`) will be added here as I take on more projects outside of RTL design.

## Repository Structure

```
portfolio/
├── College Project/          # Academic project: firmware + VHDL + documentation
│   ├── documentation/        # Report and presentation
│   ├── firmware/             # Arduino/C firmware
│   └── VHDL/                 # Hardware design modules
├── VHDL/                     # Standalone RTL design projects
│   └── 01-fsm-traffic-light/
│       ├── src/               # Synthesizable RTL source
│       ├── tb/                 # Self-checking testbench
│       ├── sim/                # Simulation log / waveform proof
│       └── README.md
└── README.md                  # This file
```

Each project folder generally includes:
- `src/` — source code (RTL or firmware)
- `tb/` — testbench, where applicable (assertions, not just waveform inspection)
- `sim/` — simulation log and/or waveform screenshot as proof of correct behavior
- `README.md` — what it does, how to build/simulate it, and design notes

## Tools

- **VHDL/Verilog:** [GHDL](https://ghdl.github.io/ghdl/) (open-source simulator) and GTKWave for waveform viewing
- **Embedded/Firmware:** Arduino IDE, C/C++
- **Schematic-level work:** OrCAD X Capture (see internship experience on [LinkedIn](https://www.linkedin.com/in/sanmugappriyan-s))

## Contact

Sanmugappriyan S — sanmugappriyan.ee@gmail.com — [LinkedIn](https://www.linkedin.com/in/sanmugappriyan-s)
