//
// Created by shobhit on 26/10/23.
//

#include "instructionCycle.hpp"
#include "processor.hpp"
#include "memory.hpp"
#include "dataView.hpp"

#include <iostream>
#include <unistd.h>

// continuous run
// this function continuously executes instructions till BRK is not found
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

// step run
// this function executes instructions step wise
// and waits for signal from input
// to determine if to execute instruction stepwise or continuously or break
InstructionCycle::InstructionCycle(int modeFlag) {
    proc.VMInit(&mem);
    uint8_t opcode = IFetch();
    dataView dv;
    int stopFlag = 1;
    while(stopFlag) {
        std::cout << "step : 1\ncontinue: 2\nbreak: 3" << std::endl;
        std::cin >> modeFlag;
        if(modeFlag == 1) {
            dv.ADump_hex(proc);
            dv.PCDump_hex(proc);
            dv.FDump(proc);
            Execute(opcode);
        }
        else if(modeFlag == 2) {
            int c = proc.cpuClock;
            int x = c;
            while((opcode = IFetch()) != 0x00) {
                c = proc.cpuClock;
                x = c-x;
                dv.ADump_hex(proc);
                dv.PCDump_hex(proc);
                dv.FDump(proc);
                printf("Time :%d\n", x);
                Execute(opcode);
                sleep(x);
                x = x;
            }
        }
        else
            break;

        // stopFlag is set to 0 when first 0x00 is encountered
        if( (opcode = IFetch()) == 0x00 )
            stopFlag = 0;
    }
    if(modeFlag == 1 || modeFlag == 2) {
        dv.ADump_hex(proc);
        dv.PCDump_hex(proc);
        dv.FDump(proc);
    }
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
        case 0xA2:
            proc.LDX_imdt(&mem);
            break;
        case 0xAE:
            proc.LDX_abs(&mem);
            break;
        case 0xBE:
            proc.LDX_absy(&mem);
            break;
        case 0xA6:
            proc.LDX_zpg(&mem);
            break;
        case 0xB6:
            proc.LDX_zpgy(&mem);
            break;
        case 0xA0:
            proc.LDY_imdt(&mem);
            break;
        case 0xAC:
            proc.LDY_abs(&mem);
            break;
        case 0xBC:
            proc.LDY_absx(&mem);
            break;
        case 0xA4:
            proc.LDY_zpg(&mem);
            break;
        case 0xB4:
            proc.LDY_zpgx(&mem);
            break;
        case 0x09:
            proc.ORA_imdt(&mem);
            break;
        case 0x05:
            proc.ORA_zpg(&mem);
            break;
        case 0x15:
            proc.ORA_zpgx(&mem);
            break;
        case 0x0D:
            proc.ORA_abs(&mem);
            break;
        case 0x1D:
            proc.ORA_absx(&mem);
            break;
        case 0x19:
            proc.ORA_absy(&mem);
            break;
        case 0x01:
            proc.ORA_idrx(&mem);
            break;
        case 0x11:
            proc.ORA_idry(&mem);
            break;
        case 0x49:
            proc.EOR_imdt(&mem);
            break;
        case 0x45:
            proc.EOR_zpg(&mem);
            break;
        case 0x55:
            proc.EOR_zpgx(&mem);
            break;
        case 0x4D:
            proc.EOR_abs(&mem);
            break;
        case 0x5D:
            proc.EOR_absx(&mem);
            break;
        case 0x59:
            proc.EOR_absy(&mem);
            break;
        case 0x41:
            proc.EOR_idrx(&mem);
            break;
        case 0x51:
            proc.EOR_idry(&mem);
            break;
        case 0x29:
            proc.AND_imdt(&mem);
            break;
        case 0x25:
            proc.AND_zpg(&mem);
            break;
        case 0x35:
            proc.AND_zpgx(&mem);
            break;
        case 0x2D:
            proc.AND_abs(&mem);
            break;
        case 0x3D:
            proc.AND_absx(&mem);
            break;
        case 0x39:
            proc.AND_absy(&mem);
            break;
        case 0x21:
            proc.AND_idrx(&mem);
            break;
        case 0x31:
            proc.AND_idry(&mem);
            break;



    }
}