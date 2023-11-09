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

void InstructionCycle::IFetch() {
    uint8_t opc;
    while((opc = mem.readMemVal(proc.PC)) != 0x69) {

        Execute(opc);
        //UpdatePC(opc);
        //proc.updateClock(opc);
    }
}

void InstructionCycle::Execute(uint8_t opcode) {
    switch (opcode) {
        case 0xA9:
            //LDA_imdt();
            break;
        case 0x8D:
            break;
    }
}

void InstructionCycle::UpdatePC(uint8_t opcode) {
    proc.PC += InstrByteTable[proc.highNibble(opcode)][proc.lowNibble(opcode)];
}


