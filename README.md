# Virtual Machine Simulating a 6502-Like Processor
## Project Overview
This project aims to develop a simple Virtual Machine (VM) that simulates a 6502-like processor, complete with CPU, memory, and I/O device emulation. The VM can execute instructions, store and retrieve data, and interact with the external world, functioning like a real computer.

## Introduction
A Virtual Machine (VM) is a software program that simulates a computer system, including a CPU, memory, and other hardware components. VMs are used for various purposes, such as secure code execution, legacy software support, and platform portability. In this project, we focus on creating a VM that simulates a simplified 6502-like processor, in contrast to complex modern VMs like VMWare, VirtualBox, or Qemu.

### Why Use a VM?
1. Security and Isolation: VMs allow code execution in a secure and isolated environment, protecting the host system.
2. Legacy Software: VMs can replicate the behavior of older computers, enabling the execution of legacy applications on modern systems.
3. Portability: VMs offer a standardized platform, ensuring portability across different environments.

## Project Scope
The project encompasses the following key aspects:

- Functionalities: Determine the functionalities to be implemented in the VM.
- Software Development: Write the code to implement the VM's functionalities.
- Testing: Conduct extensive testing to ensure the VM meets the project's objectives.
- Sample Programs: Run basic programs and verify the status of registers and components.
- Documentation: Create detailed documentation for reference.


## Design
![image](https://github.com/dragon540/6502Emulator/assets/149693065/b682fa85-5f4f-4165-b44c-e98b34bfe5a1)


### Processor
 - Registers: The CPU includes various registers:
 - General-purpose registers
 - Flag register
 - Program counter
 - Stack pointer register
ALU: The Arithmetic Logic Unit performs arithmetic and logical operations.
Stack Memory: Emulate a stack using Last In First Out (LIFO) access.

## Clock
The clock signal controls the timing of instruction execution, ensuring proper order and speed for each instruction.

## Memory
Emulate memory for storing instructions and data.

## Mechanism of Loading Instructions to Memory
Describe how instructions are loaded into memory for execution.

## Usage
Explain how to use the VM, including any setup instructions, running programs, and interacting with the VM.

## Getting Started
Provide instructions on setting up the development environment, dependencies, and building the project.

## Testing
Explain how to run tests on the VM to ensure its functionality.

## License
Indicate the project's license (e.g., MIT, Apache, or your choice) and any licensing terms.

## Contribution
Guide potential contributors on how to participate in the project, including code contributions, reporting issues, and submitting pull requests.

## Acknowledgments
Mention any sources, libraries, or inspirations you used for the project.

## Contact
Provide contact information or links to relevant communication channels for questions and support.

## Additional Documentation
Link to additional documents, if any, such as technical specifications or design details.
