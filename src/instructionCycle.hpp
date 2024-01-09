//
// Created by shobhit on 26/10/23.
//

#ifndef INC_6502EMULATOR_INSTRUCTIONCYCLE_HPP
#define INC_6502EMULATOR_INSTRUCTIONCYCLE_HPP

#include "processor.hpp"
#include "memory.hpp"
#include "codeLoad.hpp"

class InstructionCycle {
    Processor proc;
    Memory mem;
    CodeLoad load;
public:
    // for text based operation
    void InstructionCycleFunc(int modeFlag);

    uint8_t IFetch();
    //void IDecode();
    void Execute(uint8_t opcode);
    Processor* retProcessorObj();
    Memory* retMemoryObj();
};


#endif //INC_6502EMULATOR_INSTRUCTIONCYCLE_HPP
