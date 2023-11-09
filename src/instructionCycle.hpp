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
            {},
            {},
            {},
            {},
            {},
            {},
            {},
            {},
            {},
            {},
            {},
            {},
            {},
            {},
            {},
            {}
    };

public:
    InstructionCycle();
    void IFetch();
    //void IDecode();
    void Execute(uint8_t opcode);
    void UpdatePC(uint8_t opcode);
    Processor retProcessorObj();
    Memory retMemoryObj();
};


#endif //INC_6502EMULATOR_INSTRUCTIONCYCLE_HPP
