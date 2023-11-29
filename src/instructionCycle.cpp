//
// Created by shobhit on 26/10/23.
//

#include "instructionCycle.hpp"
#include "processor.hpp"
#include "memory.hpp"
#include "dataView.hpp"

#include <iostream>

InstructionCycle::InstructionCycle() {
    proc.VMInit(&mem);

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

Processor* InstructionCycle::retProcessorObj() {
    Processor *procPtr = &proc;
    return procPtr;
}

Memory* InstructionCycle::retMemoryObj() {
    Memory *memPtr = &mem;
    return memPtr;
}

uint8_t InstructionCycle::IFetch() {
    uint8_t opc = mem.readMemVal(proc.PC);
    return opc;
}

void InstructionCycle::Execute(uint8_t opcode) {
    switch (opcode) {
        case 0xA9:
            proc.LDA_imdt(&mem);
            break;
        case 0xAD:
            proc.LDA_abs(&mem);
            break;
        case 0x8D:
            proc.STA_abs(&mem);
            break;
        case 0xC9:
            proc.CMP_imdt(&mem);
            break;
        case 0xCA:
            proc.DEX_impl(&mem);
            break;
        case 0x88:
            proc.DEY_impl(&mem);
            break;
        case 0x18:
            proc.CLC_impl(&mem);
            break;
        case 0xD8:
            proc.CLD_impl(&mem);
            break;
        case 0x58:
            proc.CLI_impl(&mem);
            break;
        case 0xB8:
            proc.CLV_impl(&mem);
            break;
        case 0xE8:
            proc.INX_impl(&mem);
            break;
        case 0xC8:
            proc.INY_impl(&mem);
            break;
        case 0xBA:
            proc.TSX_impl(&mem);
            break;
        case 0xA8:
            proc.TAY_impl(&mem);
            break;
        case 0xAA:
            proc.TAX_impl(&mem);
            break;
        case 0x8A:
            proc.TXA_impl(&mem);
            break;
        case 0x9A:
            proc.TXS_impl(&mem);
            break;
        case 0x98:
            proc.TYA_impl(&mem);
            break;
    }
}