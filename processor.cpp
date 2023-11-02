//
// Created by shobhit on 26/10/23.
//

#include "processor.hpp"

void Processor::VMInit() {
    PC = 0b0000000000000000;
    A = 0;
    X = 0;
    Y = 0;

    // values initialised with reference to 6502 specifications
    // unused 5th bit(5th bit) and Interrupt bit(2nd bit) is set as 1
    FR = 0b00100100;
}