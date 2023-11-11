//
// Created by shobhit on 26/10/23.
//

#include "memory.hpp"

#include <iostream>

// putting some instruction at few locations
// to be able to write execute routines till assembler is made
Memory::Memory() {
    // LDA #$01
    setMem(0x0400, 0xA9); // LDA
    setMem(0x0401, 0x01); // #$01

    // STA $0200
    /***setMem(0x0402, 0x8D); // STA
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
    setMem(0x040E, 0x02);****/

    // termination instruction for now
    setMem(0x0402, 0x69);
}

void Memory::setMem(int loc, int val) {
    addrLoc[loc] = val;
}

void Memory::readMem(int loc) {
    std::cout << std::hex << (int)addrLoc[loc] << std::endl;
}

uint8_t Memory::readMemVal(int loc) {
    return addrLoc[loc];
}