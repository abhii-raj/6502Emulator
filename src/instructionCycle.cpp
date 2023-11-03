//
// Created by shobhit on 26/10/23.
//

#include "instructionCycle.hpp"
#include "processor.hpp"
#include "memory.hpp"

InstructionCycle::InstructionCycle() {
    proc.VMInit();
}

Processor InstructionCycle::retProcessorObj() {
    return proc;
}

Memory InstructionCycle::retMemoryObj() {
    return mem;
}