## Purpose

This repository contains multiple student assignment implementations (C++) for an OS-style course. These instructions give a focused, practical guide for an AI coding agent to be immediately productive: build and run artifacts, understand common file/layout patterns, and follow local conventions.

## Quick start (build & run)
- Each assignment folder has its own Makefile. Typical workflow:
  - cd into the assignment directory, e.g. `assign3/` or `assign4/`
  - run `make` to build the provided targets
  - run produced executables (example names: `fcfs`, `rr`, `sjf`, `priority`) and compare output against `example_out.txt` or `*_out.txt` files in the same folder.

Examples:
```
cd assign3
make
./fcfs        # compare to example_out.txt

cd ../assign1
make          # builds test1/test2 where provided
./test1
```

If a Makefile target is missing, inspect `Makefile` in the assignment directory for expected compiler flags (repositories use plain g++/g++-compatible commands).

## Big-picture architecture / common boundaries
- This repo is a collection of independent assignments. Each assignment folder is self-contained and implements a small OS-like subsystem:
  - assign1: process control blocks and ready queues (`pcb.h`, `readyqueue.*`, `pcbtable.*`, tests `test1.cpp/test2.cpp`)
  - assign3: scheduler implementations. Driver programs named `driver_*.cpp` call scheduler implementations in `scheduler_*.cpp` and headers like `scheduler.h` and `pcb.h`.
  - assign4: a small buffer example (`buffer.cpp`, `buffer.h`, `main.cpp`).
  - assign5: page replacement/pagetable code (`replacement.*`, `pagetable.*`, `main.cpp`).

Reasoning: each folder isolates a single assignment's implementation and test harness. When making changes, keep edits scoped to the relevant `assignN/` folder unless the change is a global utility or README-only.

## Project-specific patterns & conventions
- File pairs: implementation and header pairs follow `name.cpp` + `name.h` (e.g., `readyqueue.cpp` / `readyqueue.h`, `scheduler_rr.cpp` / `scheduler_rr.h`).
- Driver/test separation: drivers are named `driver_*.cpp` or `test*.cpp`; compare produced output to `example_out.txt` or `*_out.txt` for correctness.
- Public submission snapshot: `assign1/Submitted100%/` contains a frozen snapshot — do not modify it.

## Integration points / cross-component communication
- Common header `pcb.h` is shared by many assignments; schedulers and drivers exchange `PCB` objects via these headers.
- Drivers link against scheduler implementations by including `scheduler.h` and compiling the matching `scheduler_*.cpp` file.

## Editing guidance (concrete examples)
- To add a new scheduling policy in `assign3`:
  - add `scheduler_newpolicy.cpp` and `scheduler_newpolicy.h` following the existing `scheduler_*` interface
  - update `driver_*` or `Makefile` in `assign3/` to build the new driver or binary
  - run `make` and compare output to `example_out.txt` if provided

## Tests & verification
- Many directories include `example_out.txt` or `test*_out.txt` files. Use exact text comparison (diff) against program output.
- There is no unified test runner at repo root — run tests per assignment folder.

## What not to change
- Do not alter files under `*/Submitted100%/` or test output files (`*_out.txt`) unless explicitly instructed.

## Where to look for context when stuck
- Read `Makefile` in the assignment folder to learn compile flags and targets.
- Inspect `driver_*.cpp` or `test*.cpp` to see expected program input/output and call patterns.

---
If any section is unclear or you'd like more detail (for example, adding sample diff checks, CI Makefile targets, or specific compiler flags used on the instructor's environment), tell me which area to expand and I will iterate.
