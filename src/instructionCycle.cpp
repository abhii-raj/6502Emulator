//
// Created by shobhit on 26/10/23.
//

#include "instructionCycle.hpp"
#include "processor.hpp"
#include "memory.hpp"
#include "dataView.hpp"

#include <iostream>

InstructionCycle::InstructionCycle() {
    proc.VMInit();

    uint8_t opcode;
    dataView dv;
    while((opcode = IFetch()) != 0x69) {
        dv.ADump_hex(proc);
        dv.PCDump_hex(proc);
        dv.FDump(proc);
        Execute(opcode);
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
        case 0xAD:
            LDA_abs();
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
    if((proc.A & 0b10000000) == 0b10000000) {
        proc.setNegativeBit();
    }

    proc.updateClock(mem.readMemVal(proc.PC));
    UpdatePC(mem.readMemVal(proc.PC));
}

void InstructionCycle::LDA_abs() {
    uint16_t nextTwoWordsAddr = mem.readNextTwoWords(proc.PC + 1);
    proc.A = mem.readMemVal(nextTwoWordsAddr);

    if(proc.A == 0) {
        proc.setZeroBit();
    }
    if((proc.A & 0b10000000) == 0b10000000) {
        proc.setNegativeBit();
    }

    proc.updateClock(mem.readMemVal(proc.PC));
    UpdatePC(mem.readMemVal(proc.PC));
}

