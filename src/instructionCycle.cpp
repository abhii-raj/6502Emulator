//
// Created by shobhit on 26/10/23.
//

#include "instructionCycle.hpp"
#include "processor.hpp"
#include "memory.hpp"
#include "dataView.hpp"

InstructionCycle::InstructionCycle() {
    proc.VMInit();

    uint8_t opcode;
    dataView dv;
    while((opcode = IFetch()) != 0x69) {
        dv.ADump_hex(proc);
        dv.PCDump_hex(proc);
        dv.FDump(proc);
        Execute(opcode);
        //UpdatePC(opc);
        //proc.updateClock(opc);
    }
    dv.ADump_hex(proc);
    dv.PCDump_hex(proc);
    dv.FDump(proc);
}

Processor InstructionCycle::retProcessorObj() {
    return proc;
}

Memory InstructionCycle::retMemoryObj() {
    return mem;
}

uint8_t InstructionCycle::IFetch() {
    uint8_t opc = mem.readMemVal(proc.PC);
    return opc;
}

void InstructionCycle::Execute(uint8_t opcode) {
    switch (opcode) {
        case 0xA9:
            LDA_imdt();
            break;
        case 0x8D:
            break;
    }
}

void InstructionCycle::UpdatePC(uint8_t opcode) {
    proc.PC += InstrByteTable[proc.highNibble(opcode)][proc.lowNibble(opcode)];
}

void InstructionCycle::LDA_imdt() {
    proc.A = mem.readMemVal(proc.PC + 1);
    if(proc.A == 0) {
        proc.setZeroBit();
    }
    // add negative condition

    //proc.updateClock(mem.readMemVal(proc.PC));
    proc.cpuClock += 1;
    //UpdatePC(mem.readMemVal(proc.PC));
    proc.PC += 2;
}

