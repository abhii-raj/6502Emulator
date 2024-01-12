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
    void setMem(uint16_t loc, uint8_t val);
    void readMem(uint16_t loc);
    uint8_t readMemVal(uint16_t loc);
    // inserts some random instruction at few locations
    Memory();

    // reads next two words(of 8 bits each) from memory and returns the effective 16 bit  number
    // uses little endian
    // less significant byte are at earlier location
    uint16_t readNextTwoWords(uint16_t startLoc);

    void resetMemory();
};


#endif //INC_6502EMULATOR_MEMORY_HPP
