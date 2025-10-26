# Rex

Rex is a small, low-level programming language that compiles straight to native code. The goal is to make something fast, simple, and predictable without all the high-level fluff. It uses a custom IR (intermediate representation) as a middle layer before generating assembly for each architecture.

---

## what it does

Rex takes your code, turns it into an AST, lowers it to Rex IR, and then spits out assembly that actually runs on your CPU.

```
source -> AST -> Rex IR -> assembly -> executable
```

---

## structure

```
frontend/
  lexer/        token stuff
  parser/       builds AST
  diagnostics/  errors and reports

middle_end/
  sema/         type checking and symbols
  ir/           Rex IR and optimization passes

backend/
  codegen/      generates assembly (x86_64, ARM64, etc)
  assembler/    handles registers and writes .asm files
  linker/       makes the final binary
```

---

## Rex IR

Rex IR is a simple three-address format. It’s low enough to translate to any CPU but still readable.

```
LOAD_CONST r1, 10
LOAD_CONST r2, 20
ADD r3, r1, r2
CALL print, r3
```

---

## building

not ready yet but it should look something like:

```
make rex
./rex hello.rx
```

should output a .asm file and a binary when done.

---

## goals

* cross platform native compilation
* no hidden behavior
* clean compiler structure
* explicit memory control
* maybe a JIT later

---

## license

MIT License, see LICENSE.md

