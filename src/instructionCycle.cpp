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
        case 0xC5:
            proc.cmp_zpg(&mem);
            break;
        case 0xD5:
            proc.cmp_zpgx(&mem);
            break;
        case 0xCD:
            proc.cmp_abs(&mem);
            break;
        case 0x98:
            proc.tya_impl(&mem);
            break;
        case 0x9A:
            proc.txs_impl(&mem);
            break;
        case 0x8A:
            proc.txa_impl(&mem);
            break;
        case 0x4C:
            proc.jmp_abs(&mem);
            break;
        case 0x6C:
            proc.jmp_idr(&mem);
            break;
        case 0xAA:
            proc.tax_impl(&mem);
            break;
        case 0xA8:
            proc.tay_impl(&mem);
            break;
        case 0xBA:
            proc.tsx_impl(&mem);
            break;
        case 0xE8:
            proc.inx_impl(&mem);
            break;
        case 0xC8:
            proc.iny_impl(&mem);
            break;
        case 0X18:
            proc.clc_impl(&mem);
            break;
        case 0xD8:
            proc.cld_impl(&mem);
            break;
        case 0x58:
            proc.cli_impl(&mem);
            break;
        case 0xB8:
            proc.clv_impl(&mem);
            break;

    }
}