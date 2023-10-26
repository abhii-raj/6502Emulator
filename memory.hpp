//
// Created by shobhit on 26/10/23.
//

#ifndef INC_6502EMULATOR_MEMORY_HPP
#define INC_6502EMULATOR_MEMORY_HPP

#include <cstdint>

class Memory {
    // has 2^16 addressable memory locations
    // each memory location has 8 bits
    uint8_t addrLoc[65536];
};


#endif //INC_6502EMULATOR_MEMORY_HPP
