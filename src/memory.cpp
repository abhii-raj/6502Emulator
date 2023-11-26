//
// Created by shobhit on 26/10/23.
//

#include "memory.hpp"

#include <iostream>

// putting some instruction at few locations
// to be able to write execute routines till assembler is made
Memory::Memory() {

    // setting reset vector
    setMem(0xFFFC, 0x00);
    setMem(0xFFFD, 0x04);

    setMem(0x0400, 0xA9);
    setMem(0x0401, 0x23);
    setMem(0x0402, 0x8D);
    setMem(0x0403, 0x08);
    setMem(0x0404, 0x04);
    setMem(0x0405, 0xC9);
    setMem(0x0406, 0x24);

    // termination instruction for now
    setMem(0x0407, 0x69);
    // LDA #$01
    /***setMem(0x0400, 0xA9); // LDA
    setMem(0x0401, 0x01); // #$01

    // STA $0200
    setMem(0x0402, 0x8D); // STA
    setMem(0x0403, 0x00); // $0200
    setMem(0x0404, 0x02);

    // LDA #$05
    setMem(0x0405, 0xA9); // LDA
    setMem(0x0406, 0x05); // #$05

    // STA $0201
    setMem(0x0407, 0x8D); // STA
    setMem(0x0408, 0x01); // $0201
    setMem(0x0409, 0x02);

    // LDA #$08
    setMem(0x040A, 0xA9); // LDA
    setMem(0x040B, 0x08); // #$08

    // STA $0202
    setMem(0x040C, 0x8D); // STA
    setMem(0x040D, 0x02); // $0202
    setMem(0x040E, 0x02);***/
    //setMem(0x0407, 0x55);
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