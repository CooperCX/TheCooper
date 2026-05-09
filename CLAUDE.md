# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Overview

This is a personal technical knowledge base and coding workspace. It contains study notes, algorithm implementations, interview prep material, and a few small projects — not a single application.

## Build & Run

**LeetCode/algorithm solutions:**
```
cd leetcode/FindOffer && bash build.sh && ./main
```
The `main.cpp` includes whichever algorithm header is being tested. Edit it to switch problems. All solutions are header-only in `methods/`. Build uses `g++ main.cpp -o main -std=gnu++11`.

**Cover generator (newapp_cover_gen):**
```
cd newapp_cover_gen && mkdir -p build && cd build && cmake .. && make
```
Requires Homebrew-installed pango, cairo, glib, harfbuzz, fontconfig, icu4c. Paths in CMakeLists.txt are hardcoded to specific Homebrew versions — update if brew upgrades packages. The project renders Chinese text onto book cover images.

**Scripts:**
```
python3 Scripts/version_cvt.py
```

## Code Style

- clang-format configured: Google style, 4-space indent, 120 column limit, pointer alignment left
- C++ standard: varies — gnu++11 for leetcode, C++17 for cover_gen
- No formatter, linter, or test framework is enforced across the repo

## Repository Layout

| Directory | Content |
|-----------|---------|
| `leetcode/FindOffer/methods/` | ~100 algorithm solutions, each in a self-contained `.h` file (e.g. `42-接雨水.h`) |
| `leetcode/FindOffer/include/` | Custom data structure headers (SharedPtr, Singleton, vector, string, stack, array) |
| `C++/` | Study notes on C++: STL, memory model, new features, interview Q&A |
| `OperationSystem/` | Study notes on OS concepts + small C++ demos (mutex vs atomic, nonblock I/O, IPC) |
| `AI_Infra/` | Deep-dive notes on llama.cpp internals (GGUF, mmap, KV cache, quantization, compute graphs, backends, samplers), CUDA basics, a Q4_0 quantization example |
| `Linux/` | Notes on CMake, GDB, Git, I/O, gcc, Makefiles, libraries + an `ls -l` implementation |
| `CV/` | Computer vision interview notes + define.h |
| `newapp_cover_gen/` | C++17 cover image generator using Cairo/Pango + cppjieba for Chinese text segmentation |
| `my-theme/` | VS Code theme extension |
| `Scripts/` | Small utility scripts |

## Key Conventions

- Algorithm solutions in `leetcode/FindOffer/methods/` follow naming: `<problem-number>-<Chinese-name>.h`. Each is self-contained with a class-based solution. Drive execution by including the header in `main.cpp`.
- The repo is a personal workspace — notes are in Chinese, code comments are sparse, there is no CI/CD, no formal test suite, and no package management.
- `.gitignore` excludes build artifacts, model files, media files, and IDE dotfiles.
