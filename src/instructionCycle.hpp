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
    // for text based operation
    InstructionCycle(int a);

    // for GUI based operation
    InstructionCycle(int a, int *f_argc, char ***f_argv);

    uint8_t IFetch();
    //void IDecode();
    void Execute(uint8_t opcode);
    Processor* retProcessorObj();
    Memory* retMemoryObj();
};


#endif //INC_6502EMULATOR_INSTRUCTIONCYCLE_HPP
