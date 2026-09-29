# Digital IC Design & Verification — Training Portfolio

**Author:** Asifa Siraj
**Programme:** Digital IC Design & Verification
**Track:** National Semiconductor HR Development Programme (NSHRDP – INSPIRE)

---

## About the Programme

A **fully funded training opportunity in Digital IC Design & Verification** under the Prime
Minister's **National Semiconductor HR Development Programme (NSHRDP – INSPIRE)**.

| | |
|---|---|
| **Implementing organisation** | NED University of Engineering & Technology |
| **Lead industry partner** | Pakistan Software Export Board (PSEB) |
| **Academic partners** | Sir Syed University of Engineering & Technology (SSUET), UIT University |
| **Duration** | 4 months, intensive |


**Highlights**

- 4-month intensive, hands-on, industry-relevant training
- Hands-on industry-relevant skills on real EDA tools and real FPGA hardware
- Dedicated mentorship and placement support

**Eligibility**

Engineering graduates and final-year students from Electronics, Electrical, Computer Systems
and related disciplines.

---

## What This Repository Is

This is the complete, consolidated record of the Digital IC Design & Verification training
portfolio — every lab, every project, and every design artefact produced during the
programme, organised into the six course tracks that make up the curriculum.

It is not a tutorial. It is the **evidence of the work**.

```
                                    ┌──────────────────────────────┐
                                    │   DIGITAL IC DESIGN &        │
                                    │      VERIFICATION            │
                                    │      PORTFOLIO               │
                                    └──────────────┬───────────────┘
                                                   │
        ┌──────────────┬───────────────┬───────────┴──────┬──────────────┬──────────────┐
        │              │               │                  │              │              │
   ┌────▼────┐    ┌────▼────┐    ┌─────▼─────┐      ┌─────▼─────┐   ┌────▼─────┐   ┌────▼─────┐
   │  RDV    │    │  PHE    │    │    SV     │      │    UVM    │   │   IPI    │   │  Extra   │
   │         │    │         │    │           │      │           │   │          │   │  Project │
   │ RTL &   │    │ C / C++ │    │ System    │      │ Universal │   │  AMBA    │   │ FPGA/SoC │
   │ Logic   │    │ for HW  │    │ Verilog   │      │  Verif.   │   │  AHB     │   │ &  Docs  │
   │ Design  │    │ Eng.    │    │           │      │  Method.  │   │  APB     │   │          │
   │         │    │         │    │ TB,cover, │      │           │   │  AXI     │   │          │
   │         │    │         │    │ asserts   │      │ Cadence   │   │          │   │          │
   └─────────┘    └─────────┘    └───────────┘      └───────────┘   └──────────┘   └──────────┘
   Gates → FSMs   Software →     APB / AXI BFMs    UVM 1.1d        Burst master  UART loopback
   → counters     SoC capstone   + SVA              YAPP UVC        + slaves      720p VGA
   → memories     on DE1-SoC     + coverage        + factory       + coverage    React doc site
```

### The arc of the training

The curriculum is deliberately sequenced so that each track hands off to the next. Nothing
here is an isolated exercise — **the same design is repeatedly re-implemented at a higher
level of abstraction**:

| Stage | Track | What the student stops doing and starts doing |
|---|---|---|
| 1 | **RDV** | Stops writing `assign` statements, starts *designing* gates/FSMs/memories and proving them with a self-checking testbench + waveform. |
| 2 | **PHE** | Stops thinking of C as a desktop language, starts writing *hardware-adjacent* software that drives real silicon (`/dev/mem`, `termios`, bare-metal). |
| 3 | **SV** | Stops writing testbenches as ad-hoc `initial` blocks, starts building *reusable, constrained, self-checking* class-based environments. |
| 4 | **UVM** | Stops hand-building environments, starts using a *standard methodology* — factory, sequence, agent, analysis port, drain time. |
| 5 | **IPI** | Stops verifying toy DUTs, starts verifying *real industry protocols* (AHB/APB/AXI) to a written requirements document, with functional coverage. |
| 6 | **Extra** | Stops simulating, starts *closing timing and programming a bitstream onto a physical board.* |

---

## Portfolio At A Glance

| Folder | Track | Artefacts | HDL / Code | Primary tools |
|---|---|---|---|---|
| [`RDV/`](RDV/) | RTL Design & Verification | 13 | Verilog-2001 | ModelSim / Questa, EDA Playground |
| [`PHE/`](PHE/) | Programming for Hardware Engineers | 6 | C, C++, Verilog | GCC/MinGW, MSVC, Quartus, Linux |
| [`SV/`](SV/) | SystemVerilog | 8 | SystemVerilog | ModelSim / Questa (vlib/vlog/vopt/vsim) |
| [`UVM/`](UVM/) | UVM Methodology | 8 | SystemVerilog + UVM | Cadence Xcelium 24.09, CDNS-1.1d UVM |
| [`IPI/`](IPI/) | Interface Protocols & IPs | 8 | SystemVerilog + Verilog | ModelSim, Quartus Prime 25.1 |
| [`ExtraProject/`](ExtraProject/) | FPGA / SoC Projects | 5 | Verilog-2001, C, TypeScript | Quartus Prime, Questa, Node.js/Vite |

**Totals**

- **48 tracked files**, ~**80 MB**, of which ~**154 HDL source files** (~**14,000 lines** of
  Verilog / SystemVerilog) and **14 C/C++ programs** (~**970 lines**)
- 5 lab reports in RDV, 4 SystemVerilog labs + a quiz, 7 UVM labs, 7 protocol projects,
  3 self-driven FPGA/SoC projects
- Every FPGA project carries a **completed Quartus compile with timing closure**

---

## 1 · RDV — RTL Design & Verification

The foundation. Verilog-2001 RTL from single gates all the way up to state machines,
memories and an FPGA video output, each one with a matching testbench, a printed
simulation log and a captured waveform.

**Evidence format:** `.docx` lab reports, each containing *source code → testbench →
console output → waveform screenshot* for every task. The `docx` files carry the waveform
images inline, which is why the file sizes are in the hundreds of kilobytes.

### 1.1 Combinational logic

| Design | Technique demonstrated |
|---|---|
| `logic_gates` | AND / NAND / OR / XOR, exhaustive 2-input truth-table drive |
| `full_adder` | `sum = a^b^cin`, `cout` carry majority — the cell every ALU is built from |
| `adder_subtractor_8bit` | **8 full adders chained through a `generate` loop**, two's-complement subtraction via `B ^ {8{add_sub}}`, `Cout = carry[8]`, `Overflow = carry[7] ^ carry[8]` |
| Multiplexers | 2:1, wider fan-in, behavioural and structural forms |
| Priority encoders | Priority resolution + valid flag |
| `hamming_encoder` / `hamming_decoder` | `(7,4)` Hamming code — data bits `d3 p6 d2 p4 d1 p2 d0 p0`, correct single-bit error recovery |
| `comparator_gt9` + `circuit_A` + `mux_4bit_2to1` | The classic **binary → BCD** decomposition: compare against 9, conditionally subtract 10, multiplex, and feed the MS digit straight into a seven-segment decoder |
| `seven_segment_decoder` | 2-to-4 input select driving the 7 segment outputs purely from a Boolean expression |
| `seven_segment_decoder_digit` | Full 0–9 `case` table with a blank `default` |
| `leading_zero_detector` | Priority-encoded zero detection for binary-to-BCD/display pipelines |
| Barrel shifter | Screenshot submission (`Barrel Shifter .jpg`) — 2-to-4 stage log-shift network |

### 1.2 Sequential logic

| Design | Technique demonstrated |
|---|---|
| `dff_asynchronous` / `dff_synchronous` | The fundamental reset-timing distinction, built and compared side by side |
| `d_ff_sync` | Synchronous-reset D flip-flop, `generate`-instantiated ×9 in the one-hot FSM |
| `jk_flipflop` | JK excitation table → logic, including illegal-state handling |
| `up_down_counter` | Bidirectional 3-bit counter, wrap in both directions, `up_down` select |
| `mod10_counter` | **Self-resetting counter** — a NAND derived from decoded count bits feeds an asynchronous clear back into the FF, so no external comparator is needed |
| `slow_counter` | Clock divider-by-N: a free-running `fast_count` with a decoded `enable` gating a second counter |
| `digital_clock` | Three-register cascade (seconds → minutes → hours) with **59/59/23 roll-over and synchronous reset** |
| `left_rotate` | Byte-wide character rotation on a 4-digit and a 6-digit display, index-limited |
| `shift_register` | **SISO / SIPO / PISO / PIPO** in one module, selected by a 2-bit mode input, with `$display` tracing of every mode transition |
| `ram_16x2` | 16×2 synchronous RAM, single `always` block, write-enable vs read on the same clock edge, with a `$display` table in the testbench |

### 1.3 Finite state machines

| FSM | States | Notes |
|---|---|---|
| `digital_access_control` | IDLE / CHECK / GRANT / DENY | Real control-flow logic: keypad-style code entry, compare against a secret, grant or deny with a lockout timer |
| `controller` (sequential multiplier) | `S_IDLE → S_START → S_CHECK → S_ADD → S_SHIFT → S_DONE` | A textbook **shift-and-add sequential multiplier**: a Mealy FSM issuing `LoadM / LoadQ / ClearA / Add / ShiftAQ / Count / Done` control signals to a separate datapath that holds `{A, Q}`, shifts and adds conditionally on `q0` |
| `lab3_fsm` | 9 states, **modified one-hot** | A full one-hot implementation done the hard way: nine explicit `d_ff_sync` flip-flops, each `Y[i]` next-state equation derived by hand from the state diagram, with `state_A = ~y[0]` because State A is encoded as all-zeros. Output `z = y[4] \| y[8]` |

The one-hot FSM work is the intellectual high point of the RDV stage. The source comment
block records the derivation:

```verilog
// To State B (y1): If w=0 and (State A OR State F,G,H,I)
assign Y[1] = ~w & (state_A | y[5] | y[6] | y[7] | y[8]);
```

### 1.4 FIFO and the modified one-hot assignment

A 16-deep × 8-bit synchronous FIFO with `full`/`empty` generation and commented-out
`(* ram_style = "block" *)` / `(* ram_style = "distributed" *)` attributes — the attributes
are left in place precisely so the reader can see the physical-implementation trade-off
between on-chip block RAM and LUT RAM was considered.

Also submitted as a scanned assignment: `Design and Simulate One hot assignment.pdf`.

### 1.5 VGA output on the DE1-SoC (EDA Playground)

`VGA_top` implements a complete 1024×768 @ 60 Hz video path for the Terasic DE1-SoC:

- A **mock 65 MHz PLL** — `always #7.7` in simulation, replaced by real PLL IP on hardware —
  so the design is simulatable in EDA Playground without vendor libraries
- A `vga_controller` sync generator with fully parameterised active/front-porch/sync/back-porch
  (1344 × 806 total) and generated `pixel_x` / `pixel_y`
- A `memory_interface` module driving the DE1-SoC's 20-bit `SRAM_ADDR` and **bidirectional
  16-bit `SRAM_DQ` bus** in read-only mode
- LED blink, 7-segment display, and PLL-lock LED bring-up
- A testbench with a **behavioural SRAM model** on the DQ bus, `wait(led_lock)` on the lock
  signal, and a bounded run (`repeat (2700) @(posedge clk_50)`) to stop exactly two video
  lines so the simulation terminates without a timeout

This is the first time RTL leaves the simulator and is pointed at real pins.

---

## 2 · PHE — Programming for Hardware Engineers

The bridge from software to silicon. Ordinary C and C++ first, then a **complete
System-on-Chip capstone** that runs on a real FPGA board.

> Full detail in [`PHE/README.md`](PHE/README.md).

### 2.1 C fundamentals (LAB 1)

Eleven separate programs, each with its source, its compiled `.exe`, and its `-S` assembly
listing so the compiler's actual output is inspectable:

| Program | Concept |
|---|---|
| `adder.c` | Arithmetic and `printf` formatting |
| `convert.c` | Type conversion / temperature-style conversion |
| `arrfunc.c` | **Insert / delete / search on an array with `size` passed by pointer** — the classic "array shrinks, caller must be told" contract |
| `count.c` | Digit counting by repeated `n /= 10` |
| `fac.c` | Factorial with a loop |
| `fibonacci.c` | Fibonacci series with a loop |
| `prime.c` | Primality test with early `break` on the first factor |
| `reverse.c` | Integer reversal: `reverse = reverse*10 + rem` |
| `palin.c` | String palindrome via a flag |
| `string.c` | `strlen` / `strcmp` / `strcat` — string reverse, compare and concatenate |
| `lab1.c` | The lab's own driver program (the only file the `Makefile` builds) |

### 2.2 Data types and format specifiers (LAB 2)

One program, one topic, done to completion: the five fundamental types and their `%`/`%lf`
specifiers — with deliberate attention to the two classic traps, the whitespace-skipping
behaviour of `%c` and why `scanf` needs `%lf` (not `%f`) for `double`.

### 2.3 C++ and OOP (LAB 3)

The same "read parameters, do something, print the result" task as LAB 2, re-expressed as a
`Transistor` class with `private` data and public methods — encapsulation, constructors, and
`std::string` replacing raw `char` arrays. (Documented in `PHE/README.md`; the `LAB3/`
folder is not in the current snapshot of this repository.)

### 2.4 Assignment work

**`PHE_Assignment_1.pdf`** — 17 pages, 10 numbered questions, each with source, code and a
captured console output:

1. Calculator using `switch`/`case` (`+ - * /`, with divide-by-zero guarded)
2. Factorial using a loop
3. Fibonacci series using a loop
4. Prime-number detection
5. Digit counting in a number
6. Number reversal
7. Array insert / delete / search
8. String reverse, compare, concatenate
9. Palindrome string detection
10. Decimal → octal and hexadecimal conversion

**`LinkedList Assignment.pdf`** — 14 pages covering both list types:

- **Singly linked list** (`struct Node`, `createNode`) — `insertBeginning`, `insertEnd`,
  `insertMiddle` (by position), `deleteBeginning`, `deleteEnd`, `deleteMiddle` (by
  position), `display`
- **Doubly linked list** (`struct Node { int data; Node *prev; Node *next; }` wrapped in a
  `DoublyLinkedList` class) — the same six operations plus **forward and backward traversal**,
  driven by a **9-option interactive menu** (`1`–`9`) in `main()`

The doubly-linked-list `deleteMiddle` handles the head and tail cases by delegating to
`deleteBeginning()` / `deleteEnd()` rather than duplicating the unlink logic, and
`insertMiddle` takes a *key* rather than a position — both are deliberate design choices
worth noticing.

### 2.5 Capstone — `snake_game`: a full SoC on the DE1-SoC

The PHE course's capstone, and the most complete single design in the portfolio. The split
is the whole point of the project: **the game logic lives in software, the pixel output lives
in hardware.**

```
  [sw/snake.c]                 [RTL, CLOCK_50 domain]        [RTL, pixel_clk domain]
  draws blocks into
  SDRAM framebuffer
  0x3800_0000 (320x240, 8bpp)
            │
            ▼
  vga_dma_master  ────────▶  async_fifo_dc  ────────▶  byte-unpack FSM  ────────▶  VGA pins
  Avalon-MM read            512 × 32-bit, CDC-safe      32b word → 4 pixels       R/G/B + HS/VS
  4 bytes/beat              dual-clock, Gray-coded      one pixel per pixel_clk
  up to 8 in flight
```

| Module | Role |
|---|---|
| `de1_soc_snake_top` | Top level; instantiates and wires everything |
| `vga_dma_master` | Avalon-MM read engine with back-pressure, address wraps at end of frame so it loops with no CPU involvement |
| `async_fifo_dc` | **512 × 32-bit dual-clock FIFO, Gray-coded pointers, 2-FF synchronisers** — bridges 50 MHz to 74.25 MHz |
| `video_timing_720p` | 1280×720 @ 60 Hz sync generator |
| `uart_rx` / `uart_tx` | 115200-baud serial link |
| `uart_protocol` | Framed command protocol: `0x55 · cmd · payload · checksum`, ACK `0xAA · cmd · payload · checksum`; bad checksum → silently drop and return to start-byte search |
| `pll_74p25_stub` | 50 → 74.25 MHz (stub — documented as such) |

`sw/snake.c` maps `/dev/mem` at `0x38000000`, renders 20×20-pixel blocks into the
framebuffer, and reads `W`/`A`/`S`/`D` from a raw `termios` terminal. `tb/` provides a
self-checking testbench for the DMA engine.

The README for this project does not hide its gaps. It lists six real, unfixed issues —
the stub PLL, two undefined macros in `snake.c`, unarbitrated dual input paths, unscaled
320×240 content on a 720p raster, a coarse 3/3/2 colour map, and missing testbenches for the
FIFO/timing/UART. **Documenting known issues precisely is treated as part of the deliverable,
not as an admission of failure.**

---

## 3 · SV — SystemVerilog for Verification

The move from procedural testbenches to *reusable constrained class-based* environments.

### 3.1 Lab 1 — APB bus functional environment

A complete APB environment built from scratch, one class per layer:

```
apb_top.sv
└── apb_test.sv
    └── apb_environment.sv
        ├── apb_generator.sv  ─┐
        ├── apb_driver.sv     ─┤ apb_if.sv (interface)
        ├── apb_monitor.sv    ─┘
        └── apb_scoreboard.sv
              apb_transaction.sv  (the sequence item)
apb_slave.sv                       (the responder)
filelist.f                         (ModelSim compile list)
```

### 3.2 Lab 2 — ALU verification

A 16-bit ALU with 13 opcodes and a complete OOP-style verification environment:

| Opcode | Operation | Opcode | Operation |
|---|---|---|---|
| `0` | `a + b` | `7` | `a - 1` (with borrow as carry) |
| `1` | `a - b` | `8` | `a << 1` |
| `2` | `a & b` | `9` | `a >> 1` |
| `3` | `a \| b` | `10` | `a == b` → `1` |
| `4` | `a ^ b` | `11` | `a > b` → `1` |
| `5` | `~a` | `12` | `a < b` → `1` |
| `6` | `a + 1` | | plus `carry` and `zero` status flags |

Environment: `alu_if`, `alu_pkg`, `alu_transaction`, `alu_driver`, `alu_generator`,
`alu_monitor`, `alu_scoreboard`, `alu_environment`, `tb_top.sv`, and a captured
`alu_tb.vcd`.

### 3.3 Lab 3 — APB with functional coverage

The same APB environment extended with `apb_coverage.sv` and a captured `apb_tb.vcd`,
closing the loop between *stimulus* and *coverage closure*.

### 3.4 Lab 4 — SVA: seven properties on a synchronous FIFO

The strongest verification artefact in the SV track. A parameterised 8-bit × 8-entry
synchronous FIFO (`fifo.sv`) with a dedicated checker module (`fifo_assertions.sv`) that
is attached with a **`bind` statement** — so internal signals (`wr_ptr`, `rd_ptr`) become
visible to the checker **without modifying the RTL port list**. That single technique is
the mark of a verification engineer who understands scope.

| # | Property | Statement | What it catches |
|---|---|---|---|
| 1 | `a_reset_empty` | `$rose(rst_n) \|-> empty` | FIFO not empty immediately after reset |
| 2 | `a_full_empty_mutex` | `disable iff(!rst_n) !(full && empty)` | Full and empty asserted together — a dead FIFO |
| 3 | `a_illegal_read_ignored` | `(rd_en && empty) \|=> (rd_ptr == $past(rd_ptr))` | Read pointer advancing while empty |
| 4 | `a_illegal_write_ignored` | `(wr_en && full) \|=> (wr_ptr == $past(wr_ptr))` | Write pointer advancing while full — silent data loss |
| 5 | `a_write_empty_to_nonempty` | `(wr_en && empty && !full) \|=> !empty` | A valid write that did not land |
| 6 | `a_read_full_to_nonfull` | `(rd_en && full && !empty) \|=> !full` | A valid read that did not free a slot |
| 7 | `a_data_order` | `expected_valid \|-> (dout == expected_data)` | **FIFO ordering violation**, checked against a golden `ref_q[$]` queue reference model with correct one-cycle registered-output latency |

Beyond the seven assertions the checker carries **eleven `cover property` statements**
(`cov_illegal_read`, `cov_illegal_write`, `cov_write_empty`, `cov_read_full`,
`cov_full_reached`, `cov_empty_reached`, `cov_valid_write`, `cov_valid_read`, …) whose
stated purpose is to *identify vacuous assertion successes* — a genuinely advanced point:
an assertion that never fires is not a pass.

**Result** — `assertion_report.txt`, all seven properties:

| Assertion | Failure Count | Pass Count | Status |
|---|---:|---:|---|
| `a_full_empty_mutex` | 0 | 1 | **pass** |
| `a_reset_empty` | 0 | 1 | **pass** |
| `a_illegal_read_ignored` | 0 | 1 | **pass** |
| `a_illegal_write_ignored` | 0 | 1 | **pass** |
| `a_write_empty_to_nonempty` | 0 | 1 | **pass** |
| `a_read_full_to_nonfull` | 0 | 1 | **pass** |
| `a_data_order` | 0 | 1 | **pass** |

A companion `assertion_report_verbose.txt` and a `wave.do` waveform script are included
alongside the run transcript:

```tcl
vlib work
vmap work work
vlog -sv -mfcu -cuname bind_unit fifo.sv fifo_assertions.sv fifo_bind.sv fifo_tb.sv
vopt +acc=npr work.fifo_tb -o fifo_tb_opt
vsim -assertdebug work.fifo_tb_opt -do wave.do
```

Note `-assertdebug` and `+acc=npr` — the flags you need to actually see assertion failures
and internal signal values rather than an optimised-away black box.

`fifo_tb.sv` supplies ten directed test cases, deliberately including the illegal
operations the assertions exist to catch: reset check, single write, single read,
consecutive writes, consecutive reads, fill-until-full, drain-until-empty, **write while
full**, **read while empty**, FIFO ordering verification, and a simultaneous
write+read to exercise the boundary transition.

### 3.5 SV Quiz — round-robin arbiter

A 4-request `round_robin_arbiter` with a rotating 2-bit `priority_ptr` and a fully
case-selected grant sequence, verified with its own class-based environment
(`arb_intf`, `transaction`, `generator`, `driver`, `monitor`, `scoreboard`, `environment`,
`test`, `top_tb`) plus a captured `arbiter.vcd` and `waveform.png`.

---

## 4 · UVM — Universal Verification Methodology

Run on **Cadence Xcelium 24.09** with **CDNS-1.1d UVM** on a Linux EDA host
(`/mnt/hgfs/uvm/`, `UVMHOME=/usr/Software/CadenceTools/XCELIUM2409/tools/methodology/UVM/CDNS-1.1d`),
following the Cadence *SystemVerilog Advanced Verification with UVM* training. The DUT is
the **YAPP (Yet Another PPP Protocol)** router.

### 4.1 Lab 1 — sequence items and constraint randomisation

`yapp_packet` extends `uvm_sequence_item` and is the cleanest illustration of constrained
randomisation in the portfolio:

```systemverilog
rand bit [1:0] addr;          // constrained inside {[0:3]}
rand bit [5:0] length;        // constrained inside {[1:63]}
rand bit [7:0] payload[];     // payload.size() == length
rand parity_type_e parity_type;
rand int packet_delay;        // inside {[1:20]}
```

- Full `uvm_object_utils_begin/end` field automation for printing and comparison
- A `parity_type_e` enum with a **weighted** `dist { GOOD_PARITY := 5, BAD_PARITY := 1 }`
  constraint, so the stimulus is biased toward legal traffic
- `calc_parity()` XORs `{6'b0, addr} ^ {2'b0, length}` and every payload byte
- `post_randomize()` calls `set_parity()` — parity is **derived, never random**

Verified with a `run.f` that compiles the package and prints five random packets.

### 4.2 Lab 2 — environment and test scaffolding

`router_tb extends uvm_env` and `base_test extends uvm_test`, wired in `top.sv` with
`run_test()`. `+UVM_TESTNAME` and `+UVM_VERBOSITY` on the command line select the test and
verbosity; `uvm_top.print_topology()` in `end_of_elaboration_phase` dumps the hierarchy.

### 4.3 Lab 3 — building a UVC from scratch

A complete transmitter UVC assembled layer by layer, and the point where UVM stops being
framework trivia and starts being architecture:

| Class | Base | Responsibility |
|---|---|---|
| `yapp_tx_driver` | `uvm_driver #(yapp_packet)` | `get_next_item` → `send_to_dut` → `item_done` |
| `yapp_tx_sequencer` | `uvm_sequencer #(yapp_packet)` | Arbitrates between sequences |
| `yapp_tx_monitor` | `uvm_monitor` | Passive observation |
| `yapp_tx_agent` | `uvm_agent` | Bundles the three; `is_active == UVM_ACTIVE` gates driver+sequencer creation and the `seq_item_port ↔ seq_item_export` connection |
| `yapp_env` | `uvm_env` | Instantiates the agent |

The resulting topology, captured in the run log:

```
uvm_test_top   base_test
└── tb         router_tb
    └── yapp   yapp_env
        └── agent          yapp_tx_agent
            ├── monitor    yapp_tx_monitor
            ├── driver     yapp_tx_driver
            └── sequencer  yapp_tx_sequencer
```

The `yapp_5_packets` sequence is bound to the sequencer through configuration rather than
code, so the same environment runs a different stimulus without recompiling:

```systemverilog
uvm_config_wrapper::set(this,
                        "tb.yapp.agent.sequencer.run_phase",
                        "default_sequence",
                        yapp_5_packets::get_type());
```

`+SVSEED=random` in `run.f` makes every run a different random seed; `xrun -f run.f |
grep -c "YAPP_TX_DRIVER"` is used to confirm exactly five packets were driven.

### 4.4 Lab 4 — the factory, overrides and configuration

Three tests that exercise the three distinct extension mechanisms:

| Test | Mechanism | Effect |
|---|---|---|
| `base_test` | factory registration only | The nominal environment |
| `short_packet_test` | `yapp_packet::type_id::set_type_override(short_yapp_packet::get_type())` | Injects a derived `short_yapp_packet` (`length < 15`, `addr != 2`) **without touching the environment** |
| `set_config_test` | `uvm_config_int::set(this, "tb.yapp.agent", "is_active", UVM_PASSIVE)` | Flips the agent to passive at build time; the topology dump confirms driver and sequencer are *absent* and only the monitor remains |

Also demonstrated: `recording_detail`, `check_phase` + `check_config_usage()` to report
unconsumed configuration, and a `test2` child test registered with `uvm_component_utils`.

The captured transcript is a complete `xrun` run — compile, elaborate, hierarchy summary
(`Registers: 13,785`, `SV Class declarations: 202`, `Assertions: 2`), topology dump, report
summary and `$finish`. It also honestly preserves the tool's own warnings (a
`*W,DPIEXP: DPI export function in _sv_export.so not available` and the resulting
`IMPDLL` error) rather than hiding them.

### 4.5 Lab 5 — sequences and the objection mechanism

`yapp_base_seq` raises and drops the phase objection in `pre_body()` / `post_body()`, with
a `UVM_VERSION_1_2` conditional so the same code works on UVM 1.1d and 1.2:

```systemverilog
`ifdef UVM_VERSION_1_2
  phase = get_starting_phase();
`else
  phase = starting_phase;
`endif
```

This is the mechanism that decides when a UVM test is *allowed* to end. Getting it wrong is
the single most common cause of a test that "passes" without running anything.

### 4.6 Lab 6 — virtual interfaces and the analysis port

The lab where the verification code stops poking signals and starts *observing* them:

- `yapp_if.sv` — a real SystemVerilog `interface` with a `clocking` block and a
  `collect_packet` task
- `yapp_vif_config::get(this, "", "vif", vif)` — a resource-db lookup with a `NOVIF` error
  if the VIF was never set
- The monitor waits for `posedge vif.reset` then `negedge vif.reset` before starting
- `fork … join` of the collection task with `@(posedge vif.monstart)` triggers
  `begin_tr(pkt, "Monitor_YAPP_Packet")` / `end_tr(pkt)` — **transaction recording through
  the analysis port**
- The monitor re-derives `parity_type` from the *observed* parity, independently
  recomputing `calc_parity()` and classifying GOOD/BAD
- `report_phase` prints the total packet count collected
- `base_test::run_phase` sets `obj.set_drain_time(this, 200ns)` so packets in flight clear
  the router before the test ends

### 4.7 Lab 7

`AsifaSiraj_UVM_LAB7.rar` — the final lab of the Cadence UVM series. Stored as a RAR
archive; contents not extracted in this repository.

---

## 5 · IPI — Interface Protocols & IP

Where the training stops being about *your* designs and becomes about *industry-standard
buses*. The AHB project is driven from a written requirements document
(`AHB_REQUIRMENT.txt`) and every requirement is traced to the code that satisfies it.

### 5.1 AHB — the flagship project

A full **AHB master, RTL slave and behavioural slave BFM** implementing SINGLE, INCR4 and
open-ended INCR bursts, delivered across three revisions of the archive
(`AsifaSiraj_AHB.zip` → `AsifaSiraj_AHB _Updated.zip` → `AHB_With_Coverage.zip`) with the
compiled Cyclone V `.sof` bitstream and full timing reports inside.

#### The written requirements

| # | Requirement | How it is met |
|---|---|---|
| 1 | Implement an AHB master and an AHB slave in RTL | `ahb_master_burst.sv`, `ahb_slave_burst.sv` |
| 2 | Support SINGLE, INCR4 and INCR (undefined length) | `burst_i` = `2'b00` / `2'b01` / `2'b10` |
| 3 | Master must support **delayed `HREADY`** in the data phase | `pop_en` is AND-ed with `HREADY`, so a word is consumed only on the clean edge the FSM loads it |
| 4 | Master must **not** enter BUSY merely because the slave is not ready — only when **its own data buffer** says so | `if (is_write && is_incr && fifo_empty) HTRANS <= BUSY` in state `ADDR` |
| 5 | Restrict all INCR transfers to the **1 KB boundary** | `boundary = 9'd256 - addr[9:2]`; `max_beats = min(requested, boundary)` |
| 6 | Implement the **Error Response** mechanism | `HRESP[1]` checked every phase; the burst aborts, `err_o` is raised, and read data is discarded |
| 7 | Slave must support `HTRANS = BUSY` | `HTRANS == BUSY` ⇒ hold registered state, sample nothing |
| 8 | Configurable `BUSY_ENABLE_PARAM` and `DELAYED_READY_PARAM` | `tb_top` parameters `MASTER_BUSY`, `SLAVE_WAIT`, `USE_BFM`; slave `DELAY_READY`, `ERROR_EN`, `ERROR_ADDR` |
| 9 | **Thoroughly comment all code**, especially `if` statements and signal/register declarations | Every file opens with a header block and carries per-statement rationale |

#### Architecture

```
   user interface                    AHB bus                     slave
 start_i / write_i / burst_i  \                                  HSEL
 addr_i                       \   ahb_master_burst               HADDR
 data_valid_i / wdata_i        \  +--------------+   --------->  HWRITE
 data_last_i / data_ack_o  -------> |  FIFO (8)    |   --------->  HTRANS
 data_count_i                ------>|  transfer    |   --------->  HWDATA
 ready_o  <----------------   <-----|  FSM         |   <---------  HREADY
 rdata_o  <----------------   <-----|  boundary    |   <---------  HRESP
 err_o    <----------------   <-----|              |   <---------  HRDATA
                                   +--------------+
                                                    ahb_slave_burst  /  ahb_slave_bfm
```

- **FSM:** `IDLE → ADDR → (BUSY_ST) → DONE → IDLE`
- **Write-data FIFO:** 8 words, each slot carrying its own `data_last` flag
- **1 KB boundary arithmetic:** starting at word 252 (`0x3F0`) gives `boundary = 4`, so a
  request for 8 beats is correctly truncated to 4, and the 4 leftover buffered words are
  flushed in `DONE` so they cannot leak into the next transfer
- **Two slaves, one protocol:** `ahb_slave_burst.sv` (synthesizable) and `ahb_slave_bfm.sv`
  (behavioural) are interchangeable because they share the exact bus behaviour — the
  verification layers do not need to know which is connected (`USE_BFM` selects)

#### Verification stack

| Layer | File | What it does |
|---|---|---|
| Interface | `ahb_if.sv` | Bundles the user side and the bus side into one `virtual ahb_if` handle, plus a `wait_clocks(n)` task |
| Package | `ahb_pkg.sv` | `ahb_op_e` (6 ops), `ahb_transaction`, `ahb_beat`, `ERROR_WORD_INDEX = 8'h3F` |
| Generator | `ahb_pkg.sv` | 16 fixed-but-varied transactions: SINGLE ×4, INCR4 ×4, INCR 5-beat, INCR 8-beat, ERROR write/read, boundary-truncated write/read |
| Driver | `ahb_pkg.sv` | `push_word(w, last)` implements the real `data_valid_i / data_ack_o` back-pressure handshake — pre-loading up to 8 words before `start_i` |
| Monitor | `ahb_pkg.sv` | Registers each NONSEQ/SEQ address phase as pending; a **BUSY cycle extends the pending beat and samples nothing** |
| Scoreboard | `ahb_pkg.sv` | Reference-memory model keyed by full address; ERROR beats skipped; PASS/FAIL counters |
| Coverage | `ahb_pkg.sv` | `ahb_bus_coverage` (HTRANS, HBURST, HWRITE, HREADY, **HRESP with the new ERROR bin**, beat position, 3 crosses), `ahb_txn_coverage` (6 op bins), `ahb_cfg_coverage` (config-combination bins) |
| Environment | `ahb_pkg.sv` | Builds mailboxes, forks monitor/scoreboard/coverage tasks, prints the summary |
| Layered top | `tb_top.sv` | Per-cycle bus trace, 100 µs watchdog against hangs, `ERROR_WORD` defaulted from the package so the two can never drift |

#### The 15-test directed map

| Test | Scenario | Checks |
|---:|---|---|
| 1 | INCR4 write `0x10`, base `0xAA` | `mem[4..7] == 0xAA..0xAD` |
| 2 | INCR4 read-back | 4 beat values + `rdata_o` |
| 3 | SINGLE write `0x20 = 0xDEADBEEF` | `mem[8]` |
| 4 | SINGLE read-back | `rdata_o` |
| 5 | INCR4 write `0x00`, base `0x0A` | `mem[0..3]` |
| 6 | INCR4 read-back | beats + last |
| 7 | **INCR write, 5 beats** `0x30` | `mem[12..16]` |
| 8 | **INCR read, 5 beats** | beats + last |
| 9 | **INCR write, 8 beats** `0x60` | `mem[24..31]` |
| 10 | **INCR read, 8 beats** | beats + last |
| 11 | **ERROR write** to word 63 (`0xFC`) | `err_o` asserted **and `mem[63]` still 0** — proves the aborted write never committed |
| 12 | **ERROR read** from `0xFC` | `err_o` asserted |
| 13 | **1 KB boundary write** at `0x3F0`, 8 requested | only 4 beats written |
| 14 | **1 KB boundary read** at `0x3F0` | only 4 beats returned |
| 15 | **Buffer-starved INCR write** at `0x80` | ≥1 `HTRANS=BUSY` cycle observed, data intact |

Test 15 is the one that validates requirement 4 specifically: the driver pre-loads only
word 0 and then withholds word 1, so the three `BUSY` cycles in the trace
(`NONSEQ, SEQ, BUSY, BUSY, BUSY, SEQ, …`) are produced *purely* by `fifo_empty` — not by
the slave.

#### Two pieces of written engineering documentation

- **`README_CODE_GUIDE.md`** (346 lines) — a file-by-file, line-referenced explanation of the
  whole design: system architecture, the AHB protocol essentials the code relies on, a deep
  dive into every FSM state, **three worked timing traces** (5-beat INCR write, buffer
  starvation, 1 KB boundary), the slave's wait-state generator, all seven verification
  layers, and a closing table mapping **each requirement to the line numbers that satisfy it**.
- **`README_CHANGES.md`** — the change record across the three revisions, including the
  `HREADY` gating fix that resolved a `SLAVE_WAIT=1` hang.

#### Hardware realisation

The AHB master was taken all the way to a Cyclone V SoC (`5CSEMA5F31C6`) bitstream: the
compiled `ahb_master_burst.sof`, the full `asm/fit/map/sta/eda` report set, the ModelSim
`ahb_burst.vcd`, and a `regression_cov.do` coverage regression script are all committed.

### 5.2 APB

A second full class-based APB environment (`ipi/AsifaSiraj_APB.zip`) with the addition of
`apb_coverage.sv` — an early appearance of the functional-coverage discipline that later
dominates the UVM work.

### 5.3 AXI4-Lite

A complete AXI4-Lite environment (`AsifaSiraj_AXI.zip`) — `axi_agent`, `axi_driver`,
`axi_environment`, `axi_generator`, `axi_if`, `axi_monitor`, `axi_pkg`, `axi_scoreboard`,
`axi_slave`, `axi_test`, `axi_transaction`, `tb_top.sv` — plus `axi_coverage.sv`:

```systemverilog
cp_op    : coverpoint tr.is_write { bins wr = {1}; bins rd = {0}; }
cp_addr  : coverpoint tr.addr    { bins addr_bins[] = {[0:31]}; }
cp_wdata : coverpoint tr.wdata   { bins zero = {32'h0}; bins others = default; }
cp_rdata : coverpoint tr.rdata   { bins zero = {32'h0}; bins others = default; }
cp_bresp : coverpoint tr.bresp   { bins okay = {RESP_OKAY}; bins err = default; }
cp_rresp : coverpoint tr.rresp   { bins okay = {RESP_OKAY}; bins err = default; }
cx_op_addr  : cross cp_op, cp_addr;
cx_op_bresp : cross cp_op, cp_bresp;
cx_op_rresp : cross cp_op, cp_rresp;
```

with a `mon2cov` mailbox decoupling the monitor from the covergroup, a `run()` task that
samples forever, and a `report()` that prints the overall coverage percentage.

### 5.4 AXI dual-port memory and AXI FIFO

- **`AXI_DualPort.zip`** — `axi_master.sv` driving `axi_dp_mem.sv`, a **true dual-port memory**
  with independent read and write channels, verified by `tb_axi.sv`. Dual-port memories are
  the building block of register files, FIFO buffers and BRAM inference.
- **`AXI_FIFO.zip`** — `axi_fifo.sv` behind an AXI interface with `axi_fifo_tb.sv`, a
  `Makefile.txt` build script and a captured `axi_fifo_wave.vcd`.

### 5.5 Protocol waveform study

`WAVEFORM_PROTOCOL.docx` — a screenshot-driven study of real AXI protocol waveforms
(`HSEL`, `HREADY`, `HRESP`, address/data phase pipelining, wait states, burst boundaries),
i.e. reading a bus off an actual bus rather than only from a specification.

---

## 6 · ExtraProject — Self-Initiated FPGA & SoC Work

The projects that go beyond the brief: designs chosen, specified, built, **timed closed and
programmed onto a physical board**. Documented in full detail in
[`ExtraProject/README.md`](ExtraProject/README.md).

### 6.1 UART loopback — timing-closed on Cyclone V GX

A hand-written, parameterised 115200-baud 8-N-1 UART wired as a loopback, with internal
state exposed on the LEDs for hardware debugging.

| Parameter | Value |
|---|---|
| Clock | 50 MHz `CLOCK_50` |
| `CLKS_PER_BIT` | 434 (`50_000_000 / 115200`) |
| `HALF_BIT` | 217 |
| Data / parity / stop | 8, none, 1 |
| Reset | asynchronous, active-low, from `KEY[0]` |
| Bit period / byte on wire | ≈ 8.68 µs / ≈ 86.8 µs |

**Receiver** — a 4-state FSM (`IDLE / START / DATA / STOP`) that counts `HALF_BIT` clocks
into the start bit, re-checks that the line is still low (rejecting a false start), and then
samples every `CLKS_PER_BIT` clocks. Because counting restarts from the *middle* of the start
bit, every subsequent sample lands in the middle of its own bit and no bit-by-bit
re-alignment is needed.

**Transmitter** — a 10-bit shift register preloaded with `{1'b1, tx_data, 1'b0}` (stop bit,
data with LSB at bit 0, start bit) so the register walks out start → data[0..7] → stop with
no special casing.

**Metastability** — the asynchronous RX line passes through a **2-flop synchroniser** before
the FSM ever samples it, both flops reset to idle-high.

**Rate decoupling** — a single-entry buffer between RX and TX in the top level, so a
partially-completed transmit is never corrupted by a newly arrived byte.

#### Verified results

Compiled clean; **0.000 ns total negative slack in all four speed/corner models**:

| Corner | Setup slack | Hold slack | Min pulse width |
|---|---:|---:|---:|
| Slow 1100 mV 85 °C | **+1.442 ns** | +0.234 ns | +9.093 ns |
| Slow 1100 mV 0 °C | +1.414 ns | +0.213 ns | +8.999 ns |
| Fast 1100 mV 85 °C | +5.446 ns | +0.127 ns | +9.412 ns |
| Fast 1100 mV 0 °C | +5.663 ns | +0.115 ns | +9.398 ns |

| Resource | Used / Available | % |
|---|---:|---:|
| Logic (ALMs) | 56 / 29,080 | < 1 % |
| Registers | 112 | — |
| Pins | 17 / 364 | 5 % |
| RAM / DSP / PLL | 0 | 0 % |

**A real timing failure that was diagnosed and fixed** is preserved in `uart_rx.v.bak`.
The original receiver used 16× oversampling with majority voting, but the population counter
created a huge combinational path (`bit_index` → multiplier → adders → comparators →
`rx_samples`) that was **failing setup timing by ~9 ns**. The fix attempted in the `.bak`
revision replaced the `bit_index * CLKS_PER_BIT` multiplier with a running `bit_start` adder.
The active `uart_rx.v` then simplified to a single middle-of-bit sample, and the source
carries a warning to whoever re-enables oversampling: *keep the adder — do not reintroduce
the multiply.*

### 6.2 VGA controller with image — 720p from Block RAM and from DDR3

A complete, hardware-verified Quartus Prime project driving the DE1-SoC at
**VESA 1280×720 @ 60 Hz** from a **74.25 MHz** pixel clock, with two pixel sources.

| Parameter | Value |
|---|---|
| Device | `5CSEMA5F31C6` — Cyclone V SoC, FBGA-896, speed grade 6 |
| Input clock | 50 MHz `CLOCK_50` (PIN_AF14) |
| Pixel clock | 74.25 MHz from an Integer-N `pll_74p25` |
| Horizontal total | 1650 px = 1280 active + 110 FP + 40 sync + 220 BP |
| Vertical total | 750 lines = 720 active + 5 FP + 5 sync + 20 BP |
| Sync polarity | **active-HIGH** (720p requirement — the *opposite* of 480p) |
| Colour | **RGB332** — `R[7:5]` / `G[4:2]` / `B[1:0]`, expanded to 8/8/8 |
| Frame buffer | 921,600 bytes (`0xE1000`) at `0x38000000` |
| Quartus | 25.1std.0 Build 1129, SC Lite Edition |

The timing arithmetic checks out exactly: `1650 × 750 × 60 Hz = 74.25 MHz`.

**Path A — on-chip image (the compiled top level).** A 320×240 RGB332 bitmap
(`image.hex`, 76,800 bytes, `$readmemh`-initialised into an M10K Block ROM) rendered
centred on a black 720p field. **No CPU, no DDR3.**

**Path B — DDR3 via Avalon-MM DMA.** `avalon_dma_master.v` autonomously streams the frame
buffer out of HPS DDR3 as 32-bit words (4 pixels per beat) through a dual-clock
`dcfifo` (`video_fifo.v`, 512 × 32) into `pixel_unpacker.v`. A self-checking testbench
`tb_avalon_dma_master.v` reports `=== TESTBENCH PASSED: N requests accepted, 0 errors ===`.

The 720p data path in one picture:

```
            ┌──────────────────┐      ┌──────────────────────┐      ┌────────────────────┐
 DDR3       │  Avalon-MM read  │      │   Dual-clock FIFO    │      │   720p timing gen  │
 0x38000000 │  master (f2h_sdram)      │  (CDC boundary)      │      │  pixel_x / pixel_y │
            │  32-bit, 4 px/word   ────▶  4 × 8-bit pixels/word ──▶  74.25 MHz, act-HIGH
            └──────────────────┘      └──────────────────────┘      └─────────┬──────────┘
                                                                               │
                                                        RGB332 → RGB888 ────▶  ADV7123 VGA DAC
```

#### Verified results

| Resource | Used / Available | % |
|---|---:|---:|
| Logic (ALMs) | 75 / 32,070 | < 1 % |
| Registers | 36 | — |
| Pins | 31 / 457 | 7 % |
| Block memory | 76 / 397 (614,400 bits) | 19 % |
| PLLs | 1 / 6 | — |

Worst-case setup slack **+3.779 ns** (slow 1100 mV 0 °C). Timing closed.

#### Four real problems diagnosed and recorded

1. **`quartus_map.exe` ran out of memory (5,168 MB).** Root cause: Quartus's RAM-inference
   pattern matcher does not always recognise a *parameter-computed* array bound such as
   `mem[0:IMG_WIDTH*IMG_HEIGHT-1]` as block RAM, so it falls back to flip-flops plus a huge
   combinational address decoder. **Fix applied:** the array depth is hardcoded as the literal
   `mem [0:76799]`. The captured `serv_req_info.txt` crash log is kept as evidence.
2. **JVM heap exhaustion** — four `hs_err_pid*.log` files from the Quartus GUI hitting the
   machine's RAM limit during large analyses, with their matching HotSpot `replay_pid*.log`
   companions. Diagnosed as diagnostic artefacts, safe to delete.
3. **NativeLink simulation failure** — `POSIX EACCES: permission denied` on
   `msim_transcript`, because a Questa process still held the file open from a previous run.
   Eleven accumulated `.do.bak1` … `.do.bak11` NativeLink script backups document the repeated
   attempts.
4. **An orphaned duplicate top level.** `de1soc_vga720p_top.v` still declared
   `module de1soc_vga720p_onchip_top` — the *same* module name as the real top level, so
   adding it to the QSF would be a duplicate-module error — and it parameterised `image_rom`,
   which the OOM fix in (1) deliberately removed.

Plus: the `pll_74p25` IP was generated for `5CEBA2F17A7` while the project targets
`5CSEMA5F31C6` (same family, correct divider ratios, compiles and meets timing — but should
be regenerated); and the DDR3/Avalon path is *present but not compiled* in the current QSF,
which is why the fitter reports 0 DSP blocks and the `0x38000000` base address is dead code
in that build.

### 6.3 Interactive RTL documentation site

`720p-snake-game-verilog.zip` is a **documentation website**, not a Verilog project — and
building it is a legitimate part of an IC design engineer's job.

A single-page React application presenting a complete Verilog-2001 RTL reference for the
720p VGA frame-buffer pipeline, with all six Verilog modules embedded as typed template
literals and rendered with a line-numbered, copy-to-clipboard code viewer.

| Layer | Choice |
|---|---|
| Build tool | Vite 7.3.2 |
| UI | React 19.2.6 |
| Language | TypeScript 5.9.3 — `strict`, `noUnusedLocals`, `noUnusedParameters` all on |
| Styling | Tailwind CSS 4.1.17 (CSS-first, no config file) |
| Icons | `lucide-react`, 11 tree-shaken icons |
| Bundling | `vite-plugin-singlefile` — the build inlines JS and CSS into **one self-contained `dist/index.html`** that can be opened from disk or emailed as a single attachment |

The build output is the requirement. A hardware design handed to a client has to be
*readable*, and this is a demonstration of being able to produce that artefact.

### 6.4 1280×720 host-side game application

`SnakeGame_With_VGAController.c` — a 471-line Linux userspace application, the software half
of the 720p pipeline:

- `mmap()`s `/dev/mem` at `PIXEL_BUF_BASE 0x38000000`, spanning 921,600 bytes
  (`1280 × 720 × 1 byte`)
- An RGB332 palette expressed directly as `(R<<5)|(G<<2)|B` — `BLACK`, `RED 0xE0`,
  `GREEN 0x1C`, `WHITE 0xFF`, `BLUE 0x03`, `YELLOW 0xFC`, `CYAN 0x1F`, `MAGENTA 0xE3`
- A 20×20-pixel cell grid, snake length up to 512, and separate `direction` /
  `next_direction` variables so a key press cannot reverse the snake into itself mid-tick
- `termios` raw mode (`ICANON | ECHO` cleared, `VMIN 0`, `VTIME 0`) for a
  non-blocking, non-echoing keyboard with `atexit`-style terminal restore
- The game's state lives in software; the framebuffer in DDR3 is scanned out by the FPGA —
  the CPU never touches a pixel on its way to the monitor

---

## Skills Demonstrated

### Design (RTL)

Combinational and sequential logic · Boolean-expression derivation · half/full adder
construction · ripple-carry and overflow-flag arithmetic · 7-segment decoding ·
binary-to-BCD conversion · Hamming encode/decode · RAM and dual-port memory ·
SISO/SIPO/PISO/PIPO shift registers · self-resetting counters · clock dividers ·
BCD/decimal cascades · priority encoders and multiplexers · up/down counters ·
Mealy state machines · one-hot and modified one-hot FSM encoding by hand ·
sequential (shift-and-add) multiplication with a separate datapath/controller split ·
FIFO design with full/empty generation · Gray-coded asynchronous FIFOs and CDC ·
PLL-based clock generation · reset synchronisation (async→sync conversion) ·
VESA video timing generation · RGB332↔RGB888 colour mapping · clock-domain-crossing
boundaries

### Verification

Self-checking testbenches · `$dumpfile`/`$dumpvars` VCD generation and waveform review ·
`$monitor`/`$display` trace-driven debugging · directed + constrained-random stimulus ·
layered class-based environments (generator / driver / monitor / scoreboard / environment) ·
interface-based and virtual-interface connectivity · active/passive agents ·
reference-model scoreboards with PASS/FAIL accounting · SVA: `assert property`,
`cover property`, `$past`, `|->`, `|=>`, `disable iff`, concurrent assertion, `bind`-based
checking, **vacuous-pass detection** · functional coverage: covergroups, coverpoints,
`bins`, `default`, `cross`, mailbox decoupling, coverage reporting · UVM: sequence items,
constraints (including `dist` weighting), `post_randomize`, packages, `uvm_env`,
`uvm_test`, `uvm_driver`, `uvm_monitor`, `uvm_agent`, `uvm_sequencer`, factories and
`set_type_override`, `uvm_config_int` / `uvm_config_wrapper` / resource DB, phase
objections, `set_drain_time`, analysis-port transaction recording, `print_topology`,
`check_config_usage`, UVM 1.1d ↔ 1.2 portability conditionals · bus functional models ·
protocol error injection and error-response checking · coverage-driven regression

### Protocols

**AMBA** — AHB (SINGLE / INCR4 / INCR, pipelined address & data phases, wait states,
`HTRANS=BUSY`, 1 KB boundary rule, ERROR response), APB (setup/access phase), AXI4-Lite
(five independent channels, `OKAY`/`SLVERR` responses), Avalon-MM (pipelined reads,
outstanding requests, wait states) · VESA 1280A-720@60 video timing · UART 8-N-1 framing ·
Hamming (7,4) error correction

### Software & Platforms

C (pointers, arrays-as-parameters, `char` arrays, `printf`/`scanf` format specifiers) ·
C++ (classes, encapsulation, constructors, `std::string`) · data structures (singly and
doubly linked lists, dynamic allocation, interactive menu-driven programs) · Linux
userspace (`mmap` on `/dev/mem`, `termios` raw mode, `fcntl`, `unistd`, `time`) ·
cross-platform toolchain work (GCC/MinGW on Windows, MSVC `cl.exe`, Linux GCC on the board) ·
TypeScript / React 19 / Vite / Tailwind 4

### EDA Tools & Flows

| Tool | Used for |
|---|---|
| **Intel Quartus Prime** (18.1 Lite / 25.1std) | Cyclone V synthesis, fit, STA, bitstream generation, pin planning, `.qsf`/`.qip`/`.sdc` management |
| **ModelSim-Altera / Questa Altera FPGA** | `vlib`/`vlog`/`vopt`/`vsim` flows, `vsim.wlf` waveform databases, TCL regression scripts |
| **Cadence Xcelium 24.09** | UVM simulation, `xrun -f run.f`, `worklib` snapshots, `qaLog.txt` |
| **Cadence UVM CDNS-1.1d** | The verification methodology library |
| **TimeQuest STA** | SDC constraints, four-corner timing analysis, slack reporting |
| **EDA Playground** | Vendor-library-free simulation of the DE1-SoC VGA design |
| **GTKWave / EPWave** | VCD waveform inspection |
| **Node.js / npm / Vite** | Building the RTL documentation site |

### Engineering Practice

- **Requirements traceability** — the AHB project maintains a table mapping each written
  requirement to the exact line numbers that satisfy it, and the test map is keyed to the
  same requirement list
- **Revision discipline** — `.bak` files are kept deliberately as a record of what changed
  between iterations, and the *reason* for each change is recorded in the surviving comments
  (the ~9 ns setup failure, the OOM fix, the permission failure)
- **Honest status reporting** — every project README carries an explicit, itemised
  *Known issues* section listing real unresolved defects (stub PLL, undefined macros,
  unscaled framebuffer, missing testbenches, wrong PLL device, duplicate module name,
  naming mismatches). Nothing is presented as finished when it is not
- **Debugging discipline** — crash logs, transcripts, wave1/wave2 screenshots, `transcript`
  files, `msim_transcript`, and `xrun.log` are all retained as the evidence trail
- **Git discipline** — 20 commits, authored consistently, with submission snapshots taken at
  each stage

---

## Verified Results Summary

| Project | Metric | Result |
|---|---|---|
| **UART loopback** | Worst setup slack | **+1.442 ns**, 0.000 ns TNS across 4 corners |
| | Logic | 56 / 29,080 ALMs (< 1 %) |
| **VGA controller 720p** | Worst setup slack | **+3.779 ns** |
| | Logic / memory / PLL | 75 / 32,070 ALMs, 76 / 397 RAM blocks, 1 / 6 PLLs |
| **AHB burst master** | Cyclone V `.sof` bitstream | compiled, full `asm`/`fit`/`sta` report set committed |
| **SVA FIFO** | Assertions | **7 / 7 pass**, 0 failures |
| | Cover properties | 11, targeting vacuous-pass detection |
| **UVM environment** | Test types | `base_test`, `test2`, `short_packet_test`, `set_config_test` |
| | Report summary | 0 errors, 0 warnings, 0 fatals in the captured run |
| **AXI4-Lite coverage** | Coverpoints / crosses | 6 coverpoints, 3 crosses, with a printed coverage report |
| **AHB directed testbench** | Test cases | 15, covering all 3 burst types, both error paths, the 1 KB boundary and buffer starvation |

---

## Repository Layout

```
IC-Design/
├── README.md                    ← you are here
│
├── RDV/                         RTL Design & Verification
│   ├── ASIFA SIRAJ - Lab Tasks_1.docx          10 combinational + sequential tasks
│   ├── ASIFA SIRAJ - LAB-TASK-1.docx           7-segment + binary-to-BCD
│   ├── ASIFA SIRAJ - LAB-TASK-2.docx           8-bit adder-subtractor
│   ├── ASIFA SIRAJ - LAB-TASK-3.docx           digital access control FSM
│   ├── ASIFA SIRAJ - LAB-TASK-4.docx           4×4 + sequential multiplier
│   ├── ASIFA SIRAJ - LAB 2.docx                RAM, mod-10, rotate, slow counter, Hamming
│   ├── ASIFA SIRAJ LAB1 MISS ARHAM.docx        FIFO, one-hot FSM, VGA/SRAM
│   ├── ASIFA SIRAJ - SISO, SIPO, PISO, PIPO.docx
│   ├── ASIFA SIRAJ - Up and Down Counter.docx
│   ├── ASIFA SIRAJ - Digital Clock.docx
│   ├── Design and Simulate One hot assignment.pdf
│   ├── Barrel Shifter .jpg
│   └── README.md
│
├── PHE/                         Programming for Hardware Engineers
│   ├── README.md
│   ├── LAB1.zip                 11 C programs + Makefile + assembly listings
│   ├── LAB2.zip                 data types & format specifiers
│   ├── PHE_Assignment_1.pdf     10 questions with code + output
│   ├── LinkedList Assignment.pdf  singly + doubly linked lists
│   └── snake_game.zip           SoC capstone: 7 RTL modules + snake.c + TB + pins
│
├── SV/                          SystemVerilog
│   ├── AsifaSiraj_Lab1_SV.zip   APB environment
│   ├── AsifaSiraj_Lab2_SV.zip   ALU + environment + alu_tb.vcd
│   ├── AsifaSiraj_Lab3_SV.zip   APB + functional coverage + apb_tb.vcd
│   ├── AsifaSiraj_Lab4_SV.zip   SVA on FIFO: fifo.sv, fifo_assertions.sv,
│   │                            fifo_bind.sv, fifo_tb.sv, assertion reports, wave.do
│   ├── Asifa Siraj - Assertion Assignment.docx
│   ├── assertion_report.txt    7 / 7 assertions pass
│   ├── SVQUIZ.zip               round-robin arbiter + environment + waveform
│   └── README.md
│
├── UVM/                         Universal Verification Methodology
│   ├── Asifa Siraj_UVM_Lab 1.docx    sequence items & constraint randomisation
│   ├── Asifa Siraj_UVM_Lab 2 .docx   env + test scaffolding
│   ├── Asifa Siraj_UVM_Lab 3.docx    building a UVC
│   ├── Asifa Siraj_UVM_Lab 4 .docx    factories, overrides, configuration
│   ├── AsifaSiraj_UVVM_LAB5.zip       sequences & objections
│   ├── AsifaSiraj_UVM_LAB6.zip        virtual interfaces & analysis port
│   ├── AsifaSiraj_UVM_LAB7.rar        final lab
│   └── README.md
│
├── IPI/                         Interface Protocols & IP
│   ├── AHB_REQUIRMENT.txt       the written requirements
│   ├── AsifaSiraj_AHB.zip
│   ├── AsifaSiraj_AHB _Updated.zip
│   ├── AHB_With_Coverage.zip    + README_CODE_GUIDE.md, README_CHANGES.md
│   ├── AsifaSiraj_APB.zip       + apb_coverage.sv
│   ├── AsifaSiraj_AXI.zip       + axi_coverage.sv
│   ├── AXI_DualPort.zip         true dual-port memory
│   ├── AXI_FIFO.zip
│   └── WAVEFORM_PROTOCOL.docx   AXI waveform study
│
└── ExtraProject/                Self-Initiated FPGA & SoC Work
    ├── README.md                full architecture, specs, results, known issues
    ├── uart.zip                 115200 UART loopback, timing-closed
    ├── vga_controller with image.zip   720p, Block ROM + Avalon-MM DMA, timing-closed
    ├── 720p-snake-game-verilog.zip     React/TS documentation site
    └── SnakeGame_With_VGAController.c  1280×720 host-side game, 471 lines
```

Each `README.md` inside `PHE/`, `ExtraProject/` and the top level is written as a
standalone document with file-by-file breakdowns, module descriptions, pin tables, build
instructions and a *Known issues* section. The `RDV/`, `SV/` and `UVM/` `README.md` files
are placeholders pending the same treatment.

---

## Reproducing the Work

### Software (PHE)

```sh
cd PHE && mkdir -p LAB1 && cd LAB1 && unzip ../LAB1.zip
gcc -Wall -o convert convert.c && ./convert
gcc -Wall -S -o convert.s convert.c      # regenerate the assembly listing
```

The `LAB1`/`LAB2` `Makefile`s use a Unix-style `clean` target (`rm -rf *.exe`), so they work
in Git Bash / MSYS2 / WSL, not PowerShell or cmd.

### RTL and SystemVerilog simulation

```tcl
# RDV / SV — ModelSim or Questa
vlib work
vmap work work
vlog -sv fifo.sv fifo_assertions.sv fifo_bind.sv fifo_tb.sv
vopt +acc=npr work.fifo_tb -o fifo_tb_opt
vsim -assertdebug work.fifo_tb_opt -do wave.do
```

```sh
# AHB
cd ahb && vlog -sv *.sv && vsim work.tb_ahb_burst -do "run -all"
# or the committed coverage regression
do regression_cov.do
```

### UVM

```sh
cd tb
xrun -f run.f                              # uses +UVM_TESTNAME from run.f
xrun -f run.f +UVM_TESTNAME=short_packet_test +SVSEED=random
xrun -f run.f | grep -c "YAPP_TX_DRIVER"   # expect 5
```

### FPGA

```bash
# Compile
quartus_sh --flow compile vga_controller

# Program over USB-Blaster
quartus_pgm -m jtag -o "P;vga_controller/output_files/vga_controller.sof"

# Or open the .qpf in the Quartus GUI, Ctrl+L, then Tools → Programmer
```

### Documentation site

```bash
cd 720p-snake-game-verilog
npm install
npm run dev        # http://localhost:5173
npm run build      # single self-contained dist/index.html
```

---

## Honest Status

A portfolio that claims everything works is not a portfolio, it is marketing. Current state:

| Item | Status |
|---|---|
| RDV labs | Complete — source, testbench, console output and waveform for every task |
| PHE LAB 1 / LAB 2 | Complete, with assembly listings |
| PHE LAB 3 (C++ OOP) | Documented in `PHE/README.md`; the `LAB3/` folder is not in this snapshot |
| `snake_game` | RTL and software complete; **3 blocking issues** (stub PLL, two undefined macros, unscaled 320×240 on 720p) documented in `PHE/README.md` |
| SV Labs 1–4 + quiz | Complete, all 7 assertions passing |
| UVM Labs 1–6 | Complete, with captured run logs and topologies |
| UVM Lab 7 | RAR archive, not extracted |
| AHB master/slave | Complete, three revisions, bitstream compiled, fully documented |
| AXI / APB / dual-port / FIFO | Environments complete, coverage collectors included |
| UART loopback | **Complete, timing closed, programmed to hardware** |
| VGA controller | **Complete, timing closed**; DDR3 path present but not in the compiled file list |
| `SnakeGame_With_VGAController.c` | Complete; depends on the 720p DMA path being enabled |
| Documentation site | Complete; single-file build |

---

## About This README

This document was generated by reading every folder, archive, lab report and source tree in
the repository — including text and code extracted from the `.docx` lab reports, the
contents of all 21 `.zip` archives, and the source of the C, Verilog, SystemVerilog and UVM
files inside them. Every number, module name, test name, slack figure and resource count
above is taken from the artefacts themselves rather than from a course description.

Where the repository is inconsistent with its own documentation, the documentation is
noted. Where a project has unresolved defects, the defects are listed.

---

<div align="center">

### Digital IC Design & Verification
**NSHRDP – INSPIRE** · NED University of Engineering & Technology · Pakistan Software Export Board
In academic partnership with Sir Syed University of Engineering & Technology and UIT University

**4-month fully funded intensive training · PKR 10,000/month stipend · Mentorship & placement support**

📋 **Apply now → <https://lnkd.in/dfaPiFiy>**

*Open to engineering graduates and final-year students in Electronics, Electrical, Computer
Systems and related disciplines.*

</div>
