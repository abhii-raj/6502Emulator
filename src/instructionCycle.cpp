//
// Created by shobhit on 26/10/23.
//

#include "instructionCycle.hpp"
#include "processor.hpp"
#include "memory.hpp"
#include "dataView.hpp"
#include "codeLoad.hpp"

#include <iostream>
#include <unistd.h>

// continuous run
// this function continuously executes instructions till BRK is not found

// update this function to 'InstructionCycleFunc ()' when required
/***InstructionCycle::InstructionCycle() {
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
}***/

// step run
// this function executes instructions step wise
// and waits for signal from input
// to determine if to execute instruction stepwise or continuously or break
void InstructionCycle::InstructionCycleFunc(int modeFlag) {
    proc.VMInit(&mem);
    load.CodeLoadFromFile("../OPCODE INPUT/opcodeInput1.txt",
                          0x0400, &mem);

    uint8_t opcode = IFetch();
    dataView dv;
    int stopFlag = 1;
    while(stopFlag) {
        std::cout << mem.readMemVal(0x0400) << std::endl;
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
        case 0xA5:
            proc.LDA_zpg(&mem);
            break;
        case 0xB5:
            proc.LDA_zpgx(&mem);
            break;
        case 0xAD:
            proc.LDA_abs(&mem);
            break;
        case 0xBD:
            proc.LDA_absx(&mem);
            break;
        case 0xB9:
            proc.LDA_absy(&mem);
            break;
        /***case 0xA1:
            proc.LDA_ind_x(&mem);
            break; ***/
      /***  case 0xB1:
            proc.LDA_ind_y(&mem);
            break; ***/
        case 0x85:
            proc.STA_zpg(&mem);
            break;
        case 0x95:
            proc.STA_zpgx(&mem);
            break;
        case 0x8D:
            proc.STA_abs(&mem);
            break;
         case 0x9D:
            proc.STA_absx(&mem);
            break;
        case 0x99:
            proc.STA_absy(&mem);
            break;
        /***case 0x81:
            proc.STA_ind_x(&mem);
            break; ***/
        /**case 0x91:
            proc.STA_ind_Y(&mem);
            break; ***/
        case 0xC9:
            proc.CMP_imdt(&mem);
            break;
         case 0xC5:
            proc.CMP_zpg(&mem);
            break;
         case 0xD5:
            proc.CMP_zpgx(&mem);
            break;
         case 0xCD:
            proc.CMP_abs(&mem);
            break;
        case 0x4C:
            proc.JMP_abs(&mem);
            break;
         case 0x6C:
            proc.JMP_idr(&mem);
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
         case 0x84:
            proc.STY_zpg(&mem);
            break;
        case 0x94:
            proc.STY_zpgx(&mem);
            break;
        case 0x8C:
            proc.STY_abs(&mem);
            break;
         case 0x86:
            proc.STX_zpg(&mem);
            break;
        case 0x96:
            proc.STX_zpgx(&mem);
            break;
        case 0x8E:
            proc.STX_abs(&mem);
            break;
        case 0x78:
            proc.SEI_impl(&mem);
            break;
        case 0xF8:
            proc.SED_impl(&mem);
            break;
        case 0x38:
            proc.SEC_impl(&mem);
            break;     
        case 0xE6:
            proc.INC_zpg(&mem);
            break;
        case 0xF6:
            proc.INC_zpgx(&mem);
            break;
        case 0xEE:
            proc.INC_abs(&mem);
            break;
        case 0xFE:
            proc.INC_absx(&mem);
            break; 
        case 0xEA:
            proc.NOP_impl(&mem);
            break;
        case 0x20:
            proc.JSR_abs(&mem);
            break;
        case 0x48:
            proc.PHA_impl(&mem);
            break;
        case 0x08:
            proc.PHP_impl(&mem);
            break;
        case 0x68:
            proc.PLA_impl(&mem);
            break;
        case 0x28:
            proc.PLP_impl(&mem);
            break;
        case 0xA2:
            proc.LDX_imdt(&mem);
            break;
        case 0xAE:
            proc.LDX_abs(&mem);
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
        case 0x01:
            proc.ORA_idrx(&mem);
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
        case 0x41:
            proc.EOR_idrx(&mem);
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
        case 0x21:
            proc.AND_idrx(&mem);
            break;
       case 0xC6:
            proc.DEC_zpg(&mem);
            break;
       case 0xD6:
            proc.DEC_zpgx(&mem);
            break;   
       case 0xCE:
            proc.DEC_abs(&mem);
            break;  
       case 0xDE:
            proc.DEC_absx(&mem);
            break; 
        case 0xE0:
            proc.CPX_imdt(&mem);
            break;
       case 0xE4:
            proc.CPX_zpg(&mem);
            break;
        case 0xEC:
            proc.CPX_abs(&mem);
            break;
       case 0xC0:
            proc.CPY_imdt(&mem);
            break; 
        case 0xC4:
            proc.CPY_zpg(&mem);
            break;
        case 0xCC:
            proc.CPY_abs(&mem);
            break;
        case 0x2A:
            proc.ROL_A(&mem);
            break; 
        case 0x26:
            proc.ROL_zpg(&mem);
            break;
        case 0x36:
            proc.ROL_zpgx(&mem);
            break;
        case 0x2E:
            proc.ROL_abs(&mem);
            break;
        case 0x3E:
            proc.ROL_absx(&mem);
            break;
        case 0x6A:
            proc.ROL_A(&mem);
            break;
         case 0x66:
            proc.ROR_zpg(&mem);
            break;
        case 0x76:
            proc.ROR_zpgx(&mem);
            break;
        case 0x6E:
            proc.ROR_abs(&mem);
            break; 
         case 0x7E:
            proc.ROR_absx(&mem);
            break; 
       case 0x0A:
            proc.ASL_A(&mem);
            break;
        case 0x06:
            proc.ASL_zpg(&mem);
            break;
        case 0x16:
            proc.ASL_zpgx(&mem);
            break;
        case 0x0E:
            proc.ASL_abs(&mem);
            break; 
         case 0x1E:
            proc.ASL_absx(&mem);
            break;  
         case 0x69:
            proc.ADC_imdt(&mem);
            break;
        /***case 0x65:
            proc.ADC_zpg(&mem);
            break; ***/
       /*** case 0x75:
            proc.ADC_zpgx(&mem);
            break; ***/
        /***case 0x6D:
            proc.ADC_abs(&mem);
            break; ***/
        /*** case 0x61:
            proc.ADC_idrx(&mem);
            break; ***/
       case 0x90:
            proc.BCC_rel(&mem);
            break;
        case 0xB0:
            proc.BCS_rel(&mem);
            break;
        case 0xF0:
            proc.BEQ_rel(&mem);
            break;
        case 0xD0:
            proc.BNE_rel(&mem);
            break;
        case 0x30:
            proc.BMI_rel(&mem);
            break;
        case 0x10:
            proc.BPL_rel(&mem);
            break;
        case 0x50:
            proc.BVC_rel(&mem);
            break;
        case 0x70:
            proc.BVS_rel(&mem);
            break; 
    }
}
