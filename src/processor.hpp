//
// Created by shobhit on 26/10/23.
//

#ifndef INC_6502EMULATOR_PROCESSOR_HPP
#define INC_6502EMULATOR_PROCESSOR_HPP


#include <cstdint>

class Processor {
public:
    uint16_t PC; // 16 bit Program Counter register
    uint8_t A;   // 8 bit Accumulator register
    uint8_t X;   // 8 bit Index register X specific to 6502
    uint8_t Y;   // 8 bit Index register Y specific to 6502
    uint8_t SP;  // 8 bit Stack Pointer register

    // 8 bit Flag Status register
    // from 7th to 0th bit
    // negative(N), overflow(O), reserved, break(B), decimal(D), interrupt disable(I), zero(Z), and carry(C) bit
    uint8_t FR;

    // Initialises the values of relevant registers before instruction fetch
    void VMInit();
};


#endif //INC_6502EMULATOR_PROCESSOR_HPP
