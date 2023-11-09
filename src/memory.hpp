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
public:
    void setMem(int loc, int val);
    void readMem(int loc);
    uint8_t readMemVal(int loc);
    // inserts some random instruction at few locations
    Memory();
};


#endif //INC_6502EMULATOR_MEMORY_HPP
