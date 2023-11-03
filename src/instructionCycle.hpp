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

public:
    InstructionCycle();
    /***void IFetch();
    void IDecode();
    void Execute();
    void UpdatePC();****/
    Processor retProcessorObj();
    Memory retMemoryObj();
};


#endif //INC_6502EMULATOR_INSTRUCTIONCYCLE_HPP
