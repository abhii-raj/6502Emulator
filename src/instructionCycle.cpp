//
// Created by shobhit on 26/10/23.
//

#include "instructionCycle.hpp"
#include "processor.hpp"
#include "memory.hpp"
#include "dataView.hpp"

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
    dataView dv;
    while(mem.readMemVal(proc.PC) != 0x69) {
        opc = mem.readMemVal(proc.PC);
        dv.ADump_hex(proc);
        dv.PCDump_hex(proc);
        dv.FDump(proc);
        Execute(opc);
        //UpdatePC(opc);
        //proc.updateClock(opc);
    }
    dv.ADump_hex(proc);
    dv.PCDump_hex(proc);
    dv.FDump(proc);
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

