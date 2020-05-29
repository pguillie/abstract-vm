# abstract-vm

---

### 42 | C++
_The purpose of this project is to create a simple virtual machine that can
interpret programs written in a basic assembly language._
[Subject](abstract-vm.en.pdf)

---

## Overview

This virtual machine offers a small [instruction set](#instructions) to make operations on
numbers. The operands can have different types and are handled polymorphically
in a stack.

## Invocation

The program reads the source code from the file specified on the command line,
or from `stdin` if no argument is given.  When reading from `stdin`, you may
enter `;;` on a single line to inform the program that it can process your
input.

An `--interactive` mode will process each line without waiting for the whole
source to be read.  A `--verbose` mode will explain what is being done.

## Stack



## Documentation

### Instructions

The following instructions are available:

`push`
Push values at the top of the stack.

`pop`
Remove values from the stack.

`dump`
Display the stack (from more recent to oldest).

`assert`
Assert the values at the top of the stack are equal to the parameters.
