//
// Created by shobhit on 26/10/23.
//

#ifndef INC_6502EMULATOR_INSTRUCTIONCYCLE_HPP
#define INC_6502EMULATOR_INSTRUCTIONCYCLE_HPP

#include "processor.hpp"
#include "memory.hpp"

class InstructionCycle {
    Processor proc;
    Memory mem;

    // table to store how many subsequent words(or bytes) is used by a particular instruction
    // first index is the high nibble value
    // second index is the low nibble value
    int InstrByteTable[16][16] = {
            {1,2,0,0,0,2,2,0,1,2,1,0,0,3,3,0},
            {2,2,0,0,0,2,2,0,1,3,0,0,0,3,3,0},
            {3,2,0,0,2,2,2,0,1,2,1,0,3,3,3,0},
            {2,2,0,0,0,2,2,0,1,3,0,0,0,3,3,0},
            {1,2,0,0,0,2,2,0,1,2,1,0,3,3,3,0},
            {2,2,0,0,0,2,2,0,1,3,0,0,0,3,3,0},
            {1,2,0,0,0,2,2,0,1,2,1,0,3,3,3,0},
            {2,2,0,0,0,2,2,0,1,3,0,0,0,3,3,0},
            {0,2,0,0,2,2,2,0,1,0,1,0,3,3,3,0},
            {2,2,0,0,2,2,2,0,1,3,1,0,0,3,0,0},
            {2,2,2,0,2,2,2,0,1,2,1,0,3,3,3,0},
            {2,2,0,0,2,2,2,0,1,3,1,0,3,3,3,0},
            {2,2,0,0,2,2,2,0,1,2,1,0,3,3,3,0},
            {2,2,0,0,0,2,2,0,1,3,0,0,0,3,3,0},
            {2,2,0,0,2,2,2,0,1,2,1,0,3,3,3,0},
            {2,2,0,0,0,2,2,0,1,3,0,0,0,3,3,0}
    };

    void LDA_imdt();  // LDA #oper
    void LDA_zpg();   // LDA oper
    void LDA_zpgx();  // LDA oper, X
    void LDA_abs();   // LDA oper
    void LDA_absx();  // LDA oper, X
    void LDA_absy();  // LDA oper, Y
    void LDA_ind_x(); // LDA (oper ,X)
    void LDA_ind_y(); // LDA (oper), Y .... verify addressing mode

public:
    InstructionCycle();
    uint8_t IFetch();
    //void IDecode();
    void Execute(uint8_t opcode);
    void UpdatePC(uint8_t opcode);
    Processor retProcessorObj();
    Memory retMemoryObj();
};


#endif //INC_6502EMULATOR_INSTRUCTIONCYCLE_HPP
