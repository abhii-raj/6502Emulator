//
// Created by shobhit on 26/10/23.
//

#include "memory.hpp"

#include <iostream>

// putting some instruction at few locations
// to be able to write execute routines till assembler is made
Memory::Memory() {
    resetMemory();
}

void Memory::setMem(uint16_t loc, uint8_t val) {
    addrLoc[loc] = val;
}

void Memory::readMem(uint16_t loc) {
    std::cout << std::hex << (int)addrLoc[loc] << std::endl;
}

uint8_t Memory::readMemVal(uint16_t loc) {
    return addrLoc[loc];
}

// reads next two words(of 8 bits each) from memory and returns the effective 16-bit  number
// uses little endian
// less significant byte are at earlier location
uint16_t Memory::readNextTwoWords(uint16_t startLoc) {
    uint16_t lsB = (uint16_t)readMemVal(startLoc);
    uint16_t msB = (uint16_t)readMemVal(startLoc + 1);
    msB = (msB << 8);
    uint16_t effVal = lsB + msB;

    return effVal;
}

void Memory::resetMemory() {
    // sets all word as 0x00
    for(int i=0; i<65536; i++) {
        setMem(i, 0x00);
    }
    // setting reset vector
    setMem(0xFFFC, 0x00);
    setMem(0xFFFD, 0x04);
}