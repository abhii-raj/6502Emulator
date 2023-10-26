//
// Created by shobhit on 26/10/23.
//

#ifndef INC_6502EMULATOR_INSTRUCTIONCYCLE_HPP
#define INC_6502EMULATOR_INSTRUCTIONCYCLE_HPP


class InstructionCycle {
    InstructionCycle();
    void IFetch();
    void IDecode();
    void Execute();
    void UpdatePC();
};


#endif //INC_6502EMULATOR_INSTRUCTIONCYCLE_HPP
