# P-18
# Virtual Machine Simulating a 6502-Like Processor
## Project Overview
This project aims to develop a simple Virtual Machine (VM) that simulates a 6502-like processor, complete with CPU, memory, and I/O device emulation. The VM can execute instructions, and store and retrieve data functioning like a real computer.

## Introduction
A Virtual Machine (VM) is a software program that simulates a computer system, including a CPU, memory, and other hardware components. VMs are used for various purposes, such as secure code execution, legacy software support, and platform portability. In this project, we focus on creating a VM that simulates a simplified 6502-like processor, in contrast to complex modern VMs like VMWare, VirtualBox, or Qemu.

### Why Use a VM?
**1. Reproducing Behaviour** - It can reproduce the behaviour of some specific computer which are not in production anymore. 
It can be used to run legacy software (including retro games, older applications) which can’t run on modern processors.

**2. Hardware Prototyping** – Design and architecture modifications can be tested before actually producing the hardware.

**3. As a learning tool** – Our VM also acts as a tool to understand and appreciate the working of the fundamentals of modern processors in general and the specifics of 6502 in particular.

## Project Scope
The project encompasses the following key aspects:

- **Functionalities**: Determine the functionalities to be implemented in the VM.
- **Software Development**: Write the code to implement the VM's functionalities.
- **Testing**: Conduct extensive testing to ensure the VM meets the project's objectives.
- **Sample Programs**: Run basic programs and verify the status of registers and components.
- **Documentation**: Create detailed documentation for reference.

## Design

  ### 1. Processor
  * #### Registers: 
    The CPU includes various registers:
     - Accumulator register(A)
     - Index register(X and Y)
     - Flag register
     - Program counter
     - Stack pointer register
  * #### ALU: 
    The Arithmetic Logic Unit performs arithmetic and logical operations.

  * #### Clock
    The clock signal controls the timing of instruction execution, ensuring proper order and speed for each instruction.

  ### 2. Memory
  Emulate memory for storing instructions and data.

  ### 3. Mechanism of Loading Instructions to Memory
