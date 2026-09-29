# ExtraProject

A collection of standalone FPGA / embedded-systems projects. Every project here targets a
Terasic development board, uses Verilog-2001 RTL, and is built with an Intel/Altera or
Xilinx FPGA toolchain.

Each sub-project has its own `README.md` with the full file-by-file breakdown, module
descriptions, pin tables, build instructions, and design notes.

---

## Repository layout

```
ExtraProject/
├── README.md                              ← you are here
│
├── 720p-snake-game-verilog/               ← React documentation site (Vite + TS + Tailwind)
│   └── README.md
│
├── uart/                                  ← UART loopback for Cyclone V boards
│   ├── README.md
│   └── uart_z/
│       └── README.md                      ← Quartus project (UART.qpf / UART.qsf)
│
├── vga_controller with image/             ← 720p VGA controller w/ Block-ROM image
│   ├── README.md
│   └── vga_controller with image/
│       └── README.md                      ← Quartus project (vga_controller.qpf / .qsf)
│
├── Znake-master.zip                        ← reference design (Xilinx Zynq / Zedboard)
└── Siemens_Questa_Advanced_Simulator_2024.1-*.zip   ← simulator installer
```

---

## Project index

| # | Project | What it is | Target board | Toolchain | RTL files | README |
|---|---------|-----------|--------------|-----------|-----------|--------|
| 1 | [`720p-snake-game-verilog/`](720p-snake-game-verilog/) | Interactive browser-based documentation site for a 720p SoC-FPGA snake-game RTL reference. Contains full source of every Verilog module as embedded, copyable, syntax-highlighted source. | DE1-SoC (Cyclone V SoC) | Vite 7 + React 19 + TypeScript 5.9 + Tailwind 4 | 6 modules embedded as strings | [→](720p-snake-game-verilog/README.md) |
| 2 | [`uart/`](uart/) | Parameterised 115200-baud UART transmitter + receiver wired as a **loopback**, with LEDs exposing internal state for hardware debug. | Cyclone V GX Starter Kit + DE1-SoC variant | Quartus Prime (18.1 Lite / 25.1) + ModelSim | 3 hand-written | [→](uart/README.md) · [uart_z/](uart/uart_z/README.md) |
| 3 | [`vga_controller with image/`](vga_controller%20with%20image/) | VESA 1280×720@60 video timing generator plus two pixel sources: an on-chip Block-ROM image, and an Avalon-MM DMA master that streams an 8bpp frame buffer out of DDR3 through a dual-clock FIFO. | DE1-SoC `5CSEMA5F31C6` | Quartus Prime 25.1 Lite + Questa | 8 hand-written + 2 generated | [→](vga_controller%20with%20image/README.md) · [inner](vga_controller%20with%20image/vga_controller%20with%20image/README.md) |
| 4 | `Znake-master.zip` | Third-party reference implementation of a Zynq snake game (block design + AXI IPs + C software). **Archive only — not extracted.** | Xilinx Zedboard (Zynq-7000) | Vivado 2017.4 | Inside archive | — |
| 5 | `Siemens_Questa_Advanced_Simulator_2024.1-*.zip` | Vendor installer for Siemens Questa Advanced Simulator 2024.1, referenced by the `simulation/questa/` folders in project 3. **Archive only — not extracted.** | n/a | n/a | n/a | — |

---

## Shared design constants

Two of the three active projects target the same board and the same display, so they
share a common set of video constants:

| Constant | Value | Notes |
|----------|-------|-------|
| Pixel clock | **74.25 MHz** | Synthesised by a PLL IP from the 50 MHz onboard `CLOCK_50` |
| Resolution | **1280 × 720** | VESA 720p, 60 Hz |
| Horizontal total | **1650** pixel clocks | 1280 active + 110 front porch + 40 sync + 220 back porch |
| Vertical total | **750** lines | 720 active + 5 front porch + 5 sync + 20 back porch |
| Sync polarity | **Active-HIGH** | 720p requirement — *opposite* of 480p |
| Frame rate | **60 Hz** | 1650 × 750 × 60 Hz = 74.25 MHz |
| Colour format | **RGB332** | `R[7:5]` (3 b) / `G[4:2]` (3 b) / `B[1:0]` (2 b) |
| Frame buffer | **921 600 bytes** (`0xE1000`) | 1280 × 720 × 1 byte |
| DDR3 frame buffer base | **`0x38000000`** | Via the `f2h_sdram_master` Avalon-MM bridge |
| Device | `5CSEMA5F31C6` | Cyclone V SoC, FBGA-896, speed grade 6 |

---

## The 720p data path (projects 1 and 3)

Both VGA projects implement the same conceptual pipeline; they differ only in where the
pixel bytes come from.

```
             ┌──────────────────────┐
 DDR3  ─────▶│  Avalon-MM read      │      project 3 (avalon_dma_master.v)
 0x38000000  │  master (f2h_sdram)  │      32-bit words, 4 pixels per word
             └───────────┬──────────┘
                         │ am_readdatavalid
                         ▼
             ┌──────────────────────┐
             │  Dual-clock FIFO     │      project 1: async_fifo.v (Gray-coded pointers)
             │  (CDC boundary)      │      project 3: video_fifo.v (dcfifo megafunction)
             └───────────┬──────────┘
                         │ 4 × 8-bit pixels per word
                         ▼
             ┌──────────────────────┐
 image.hex ─▶│  image_rom (M10K)    │◀── project 3 only — on-chip Block ROM
             └───────────┬──────────┘
                         │
                         ▼
             ┌──────────────────────┐
             │  720p timing gen     │      vga_timing.v / vga_controller.v
             │  pixel_x / pixel_y   │      74.25 MHz, active-HIGH sync
             └───────────┬──────────┘
                         ▼
             ┌──────────────────────┐
             │  RGB332 → RGB888    │      bit-replication expansion
             └───────────┬──────────┘
                         ▼
             ADV7123 VGA DAC  →  VGA_R/G/B[7:0] + HS / VS / BLANK_N
```

---

## Build tooling requirements

| Tool | Version used | Needed for |
|------|--------------|-----------|
| Node.js | 18+ (any modern LTS) | project 1 |
| npm | 9+ | project 1 |
| Quartus Prime Lite | 18.1 (UART) / 25.1std (VGA) | projects 2, 3 |
| ModelSim-Altera / Questa Altera FPGA | bundled with Quartus or standalone | projects 2, 3 |
| Vivado | 2017.4+ | project 4 (`Znake-master.zip`) |
| USB-Blaster II | any | programming `.sof` onto the boards |

---

## Conventions used across all projects

* **Verilog-2001** only — no SystemVerilog, no `always_ff`/`always_comb`, no packed
  structs. Every module is written in the classic procedural style with explicit
  `always @(posedge clk or negedge rst_n)` blocks.
* **Reset styles differ per project** and are intentional. The VGA project uses a
  *synchronous, active-high* reset produced by `reset_sync.v`; the UART project uses
  *asynchronous, active-low* resets; the snake-game documentation RTL documents both
  an asynchronous `rst_n` and synchronous resets depending on module.
* **Comments are unusually verbose.** They record *why* a design decision was made —
  timing failures that were diagnosed, Quartus inference pitfalls that were worked
  around, and race conditions that were fixed. Read them; they are the most valuable
  part of the source.
* **`.bak` files are kept deliberately.** Each `.v.bak` is the previous revision of the
  corresponding source file, retained as a record of what changed between iterations.
  Do not add them to the Quartus project file list — they are not compiled.
* **`db/`, `incremental_db/`, `output_files/`, `simulation/`** are tool-generated
  directories. They are committed so the exact state of each build is recoverable, but
  they can be deleted and regenerated at any time by re-running the compilation.
* **Standard industrial pin frames.** Both FPGA projects apply `set_false_path` on the
  asynchronous button resets and relaxed I/O timing on the LEDs and UART lines, which is
  the correct way to tell TimeQuest that these are not synchronous interfaces.

---

## Quick start

Each project is independent — no top-level build script ties them together.

```bash
# Project 1 — documentation site
cd 720p-snake-game-verilog
npm install
npm run dev            # http://localhost:5173

# Project 2 — UART loopback
# Open uart/uart_z/UART.qpf in Quartus Prime, then Ctrl+L (Start Compilation)
# Then: Tools → Programmer → load output_files/UART.sof → Start

# Project 3 — VGA controller
# Open vga_controller with image/vga_controller with image/vga_controller.qpf
# in Quartus Prime, then Ctrl+L, then program output_files/vga_controller.sof
```

Simulation-only runs (no hardware needed):

```bash
# Project 3 — Avalon-MM DMA master testbench
vlib work
vlog avalon_dma_master.v tb_avalon_dma_master.v
vsim tb_avalon_dma_master
run -all
# expect: "=== TESTBENCH PASSED: N requests accepted, 0 errors ==="
```

---

## Verified results

Both hardware projects have completed a full Quartus compile with timing closure.

| Project | Logic (ALMs) | Registers | Pins | RAM blocks | PLLs | Worst setup slack |
|---------|-------------:|----------:|-----:|-----------:|-----:|-----------------:|
| UART loopback | 56 / 29 080 (< 1 %) | 112 | 17 / 364 (5 %) | 0 | 0 | +1.442 ns (slow 1100 mV 85 °C) |
| VGA controller | 75 / 32 070 (< 1 %) | 36 | 31 / 457 (7 %) | 76 / 397 (19 %), 614 400 bits | 1 / 6 | +3.779 ns (slow 1100 mV 0 °C) |

The UART project compiles clean on `CLOCK_50` with no timing violations and zero
negative slack across all four device speed/corner models.

---

## Known issues and troubleshooting notes

These are recorded because they cost real debugging time and are easy to hit again.

### 1. `quartus_map.exe` runs out of memory (VGA project)

`serv_req_info.txt` in the VGA project captures a real crash:

```
*** Fatal Error: Out of memory in module quartus_map.exe (5168 megabytes used)
  sub_system: MEM
```

**Root cause:** Quartus's RAM-inference pattern matcher does not always recognise a
*parameter-computed* array bound (e.g. `mem[0:IMG_WIDTH*IMG_HEIGHT-1]`) as block RAM.
It falls back to building the memory out of flip-flops plus a huge combinational address
decoder, which explodes memory usage during analysis.

**Fix already applied in `image_rom.v`:** the array depth is hardcoded as the literal
`mem [0:76799]` instead of being derived from parameters. Keep it that way.

### 2. Java heap exhaustion (`hs_err_pid*.log`)

Four `hs_err_pid*.log` files sit in the VGA project folder, each reporting:

```
There is insufficient memory for the Java Runtime Environment to continue.
Native memory allocation (malloc) failed to allocate 248336 bytes for Chunk::new
```

These are JVM crash logs from the Quartus GUI hitting the machine's RAM limit while
running large analyses. The matching `replay_pid*.log` files are HotSpot replay logs
that can be opened in `-XX:+ReplayCompiles` mode to identify the exact compiler
hotspot. **These are safe to delete** — they are diagnostic artefacts, not sources.

### 3. NativeLink simulation fails with a permission error

`vga_controller_nativelink_simulation.rpt` records:

```
Warning: File vga_controller_run_msim_rtl_verilog.do already exists -
         backing up current file as vga_controller_run_msim_rtl_verilog.do.bak7
error deleting "msim_transcript": permission denied
Error: NativeLink simulation flow was NOT successful
```

The `POSIX EACCES {permission denied}` occurs because the Questa process still holds
`msim_transcript` open from a previous run. The eleven `.do.bak1` … `.do.bak11` files
in `simulation/questa/` are the accumulated NativeLink script backups from repeated
failed attempts.

**Fix:** close any running ModelSim/Questa GUI or console session, delete
`simulation/questa/msim_transcript`, `simulation/questa/vsim.wlf` and the `rtl_work/`
directory, then re-launch. Do the same if the `.do` script needs regenerating.

### 4. Camera / video-in files are vestigial

`vga_controller.qsf` contains the complete DE1-SoC board pin assignment including the
video-in decoder pins (`TD_CLK27`, `TD_DATA[7:0]`, `TD_HS`, `TD_VS`, `TD_RESET_N`).
The design does not use them — they are simply part of the board-wide
`pin_assignment_DE1_SoC.tcl` assignment that gets applied wholesale.

---

## File-type glossary

Appears hundreds of times across the `db/` and `output_files/` directories. These are
all produced by the Quartus Prime compilation flow and are safe to regenerate.

| Extension / suffix | Full form | What it is |
|-------------------|-----------|-----------|
| `.qpf` | Quartus Project File | Project container. Lists revision name and Quartus version. |
| `.qsf` | Quartus Settings File | All project settings *and* per-pin assignments. Auto-generated by the GUI. |
| `.qws` | Quartus Workspace | Per-user GUI workspace state (window positions, open panes). Not portable. |
| `.sdc` | Standard Delay Constraints | TimeQuest constraints (`create_clock`, `set_input_delay`, `set_false_path`). |
| `.qip` | Quartus IP File | Lists an IP core's source files for inclusion in the project. |
| `.sip` | System IP File | IP variant that also registers simulation model libraries. |
| `.spd` | SignalWeb/Diamond IP Definition | IP Compiler's parameter/specification database. |
| `.bsf` | Bus Spec File | Legacy per-signal bus declarations (type + width). |
| `.ppf` | Pin Preferences File | Legacy pin-order file. |
| `.cmp` | Component Declaration | VHDL component/entity declaration for black-box IP. |
| `.vo` | VHDL Output | Precompiled simulation model (older naming). |
| `.sft` | Signal Flow Trace | Quartus post-fit timing-analysis intermediate file. |
| `.sof` | SRAM Object File | **Bitstream** to program an Altera/Intel FPGA. |
| `.pof` | Parallel Object File | Programming file for parallel/flash programming. |
| `.jdi` / `.jditmp` | JTAG Debug Information | Debug session metadata for SignalTap. |
| `.cdf` | Configuration Device File | Flash/active-serial configuration descriptor. |
| `.sld` | System-Level Design | Platform Designer system description. |
| `.pin` | Pin Report | Fitter's post-fit pin assignment output. |
| `.flow.rpt` | Flow Report | Per-stage compilation log (Analysis & Synthesis → Fitter → STA). |
| `.map.rpt` | Map Report | Analysis & Synthesis results, resource usage, warnings. |
| `.fit.rpt` / `.fit.summary` | Fitter Report | Placement/routing result + utilisation summary. |
| `.asm.rpt` | Assembler Report | Final bitstream assembly results. |
| `.sta.rpt` / `.sta.summary` | TimeQuest Report | Timing closure results per speed/corner corner. |
| `.eda.rpt` | EDA Tool Report | Third-party (ModelSim/Questa) invocation log. |
| `.done` | — | Touch marker signalling a stage completed successfully. |
| `.summary` | — | Condensed one-screen version of the matching `.rpt`. |
| `.smsg` | — | Severity-tagged warning/error summary. |
| `.qmsg` | — | Quartus message database for the matching stage. |
| `.cnf.cdb` / `.cnf.hdb` | — | Pin location / I/O buffer post-fit databases. |
| `.rdb` / `.hdb` / `.cdb` | Routed DB / Heap DB / Circuit DB | Internal relational post-fit databases (placement, routing, timing graph). |
| `.logdb` | Log Database | Internal per-stage log database. |
| `.tiscmp.*.ddb` | Timing-Specific Comparison | Per-corner timing analysis databases (fast/slow, 0 °C/85 °C). |
| `.sta_cmp.*.tdb` | Static Timing Comparison | Worst-case setup slack comparison vs. previous run. |
| `.hsd` | HotSpot Data | Altera I/O simulation cache (`.ff_` fast, `.ii_`/`tt_` input/typical). |
| `.tdf` | Timing-Driven Fitting | Per-primitive placement guidance records. |
| `.hbdb.*` | Hierarchical Block DB | Partition/compiled-partition boundary databases. |
| `.ammdb` | Altera Metastability/Memory DB | Post-fit metadata for memory and metastability analysis. |
| `.pplq.rdb` | Post-P&L Routing DB | Additional routing records. |
| `.cbx.xml` | Component Box | GUI component-box placement state. |
| `.sci` | System Component Index | Qsys/Platform Designer component metadata. |
| `.tbw` / `.tcl` | — | Testbench window / TCL automation scripts. |
| `.vcd` | Value Change Dump | Simulation waveform dump (open in GTKWave). |
| `.wlf` | ModelSim Wave Log | Questa/ModelSim native waveform database. |
| `.do` | ModelSim Script | Command script that drives a `vsim` run. |
| `.msim_transcript` | — | ModelSim invocation log. |
| `nl_common.txt`, `*_setup.tcl`, `*_libs.txt` | NativeLink | Generated third-party simulator library-include scripts. |
| `.tcl` | Tcl Script | `pin_assignment_DE1_SoC.tcl` is the Terasic board pin-assignment script. |
| `.hex` | Intel HEX | Raw image data loaded by `$readmemh` into `image_rom`. |
| `.mif` | Memory Initialisation File | Quartus-generated alternative to `.hex` for RAM init. |
| `.bak` | Backup | Previous revision of a source file, kept for reference. Not compiled. |
| `.log` | Log | Tool-generated log. `hs_err_*` is a JVM crash log; `replay_*` is its HotSpot replay companion. |
| `.zip` | Archive | `Znake-master.zip` (Xilinx reference design), Questa installer. |

---

## Data-file formats

### `image.hex` — VGA project

76 800 lines, one hex byte per line (`00`–`FF`), loaded into `image_rom.v` at
**elaboration time** by `$readmemh("image.hex", mem)`.

* Geometry: **320 × 240**, 1 byte per pixel = 76 800 bytes exactly.
* Packing: RGB332 — `bits[7:5]` = red, `bits[4:2]` = green, `bits[1:0]` = blue.
* Ordering: row-major, top-left pixel at line 1.
* Registered in the Quartus project as `set_global_assignment -name HEX_FILE image.hex`.
* Backing M10K usage: 614 400 bits = 76 800 bytes of storage plus 17 address bits of
  depth headroom (the ROM is declared 17 bits wide, covering 0–131 071).

The first lines of the shipped file are all `ff` (white), which is why the centred image
appears as a white rectangle on a black 720p field.

---

## Relationship between the three active projects

```
720p-snake-game-verilog  ── documents ──▶  (the vga_controller design)
   (React reference site)                    vga_timing.v, avalon_dma_master.v,
                                             async_fifo.v, vga_top.v …

vga_controller with image ── implements ──▶  720p timing + on-chip image + DDR3 DMA
   (Quartus project, verified on hardware)

uart ── independent peripheral, no shared code
   (shares only the board, the Quartus flow, and the pin-frame conventions)
```

The React site is the **specification**; the VGA project is the **hardware
implementation** of that specification. The timing numbers, pin assignments, memory map,
and DMA FSM rules in the site's data tables match the VGA project's RTL one-for-one.
