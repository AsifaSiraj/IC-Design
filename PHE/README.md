# PHE — Programming for Hardware Engineers

## What is this folder about?

`PHE` is the course workspace for **PHE (Programming for Hardware Engineers)**. It contains four
independent lab submissions, each in its own folder, ordered roughly by difficulty:

| Folder | Language | Topic | Hardware required |
| --- | --- | --- | --- |
| [`LAB1/`](LAB1/) | C | C fundamentals — data types, control flow, arrays, strings, functions | none |
| [`LAB2/`](LAB2/) | C | Data types and `scanf`/`printf` format specifiers in depth | none |
| [`LAB3/`](LAB3/) | C++ | OOP — classes, encapsulation, modelling a transistor | none |
| [`snake_game/`](snake_game/) | Verilog + C | Full SoC design — DMA video pipeline, VGA, async FIFO, UART | **DE1-SoC FPGA board** |

## The progression

The course moves from **host software** to **hardware description** to a **complete system**:

```
LAB1  C basics, many small programs          ─┐
                                               ├─►  software only, runs on your PC
LAB2  one concept, in depth                   │
LAB3  C++ / OOP                                ─┘

snake_game  Verilog RTL + Linux userspace C   ──►  runs on an FPGA board
```

LAB1–LAB3 are ordinary console programs: you compile with `gcc` (or `cl.exe` for LAB3) and run them on
Windows. `snake_game` is the first thing in the repository that is actual hardware — it synthesises into
a Cyclone V FPGA and streams a framebuffer to a VGA monitor.

Every folder has its own README with a detailed walkthrough of the code, design decisions, and known
issues. Start there.

## Loose files

| File | Description |
| --- | --- |
| `OOPS lecture notes.pdf` | Lecture notes for the Object-Oriented Programming portion of the course — the material behind LAB3. |
| `snake_game.zip` | An archived copy of `snake_game/`. Kept as a submission snapshot; the live version is the `snake_game/` folder. If they ever diverge, the folder is the working copy. |

## Quick start

### LAB1 / LAB2 — with GCC or MinGW

```sh
cd LAB1
gcc -Wall -o convert convert.c
./convert
```

`LAB1/Makefile` builds only `lab1.c`; every other program is compiled by hand.

To regenerate the assembly listings that sit next to each source file:

```sh
gcc -Wall -S -o convert.s convert.c
```

### LAB3 — with MSVC

```bat
cd LAB3
cl /EHsc /nologo lab3.cpp
lab3.exe
```

Or open the folder in VS Code and press `Ctrl+Shift+B` — `.vscode/tasks.json` is already configured.

With GCC it also works: `g++ -Wall -o lab3 lab3.cpp`.

### snake_game — with Quartus

See [`snake_game/README.md`](snake_game/README.md). Requires Intel Quartus, and physically a Terasic
DE1-SoC board to do anything interesting. There are currently three blocking issues in that project
(PLL is a stub, `sw/snake.c` is missing two `#define`s, and the 320x240 framebuffer is not scaled to the
720p video timing) — all documented in that README.

## Toolchain summary

| Tool | Used by | Notes |
| --- | --- | --- |
| **GCC / MinGW-w64** | LAB1, LAB2, snake_game/sw | Produces the `.exe` and `.s` files in LAB1/LAB2 |
| **MSVC (`cl.exe`)** | LAB3 | Produces `.exe`, `.obj`, `.pdb`, `.ilk` |
| **Intel Quartus** | snake_game/rtl, snake_game/qsf | Cyclone V `5CSEMA5F31C6` |
| **Icarus Verilog / ModelSim** | snake_game/tb | Optional, for running the testbench |
| **Linux + GCC** | snake_game/sw | Runs on the board, needs root for `/dev/mem` |

## Repository conventions worth knowing

- **`.s` files are compiler output**, not hand-written assembly. They are the `-S` listings of the
  matching `.c` files, kept so you can see what the compiler generated. Do not edit them.
- **`.exe` / `.obj` / `.pdb` / `.ilk` are build artefacts.** All safe to delete; the compiler regenerates
  them. `LAB3` is ~19 MB mostly because of two `.pdb` debug symbol files.
- **`.qsf` files are configuration**, not generated output. The one in `snake_game/qsf/` is
  hand-maintained.
- The LAB1/LAB2 `Makefile`s use a Unix-style `clean` target (`rm -rf *.exe`), so they only work in
  Git Bash / MSYS2 / WSL, not PowerShell or cmd.

## Quick reference — what each lab teaches

**LAB1** — reading input correctly (`scanf(" %c", ...)` with the leading space), `switch`-based
calculator, insert/delete/search on an array with `size` passed by pointer, digit counting, factorial,
Fibonacci, primality, integer reversal, and `strlen`/`strcmp`/`strcat`.

**LAB2** — one program, one topic: the five fundamental data types and their format specifiers. The two
things it exists to nail down are the whitespace-skipping behaviour of `%c` and why `scanf` needs `%lf`
(not `%f`) for `double`.

**LAB3** — the same "read parameters, do something, print it" task as LAB2, but as a `Transistor` class
with `private` data and public methods. Demonstrates encapsulation, constructors, and `std::string`
replacing raw `char` arrays.

**snake_game** — a full SoC design in four folders: `rtl/` (7 Verilog modules), `sw/` (the game),
`tb/` (a DMA testbench), `qsf/` (pin assignments). Software renders into an SDRAM framebuffer; hardware
streams it out over Avalon-MM through an asynchronous FIFO to a 720p VGA output. An optional UART
channel sends direction commands with a checksummed packet protocol.
