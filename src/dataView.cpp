//
// Created by shobhit on 3/11/23.
//

#include "dataView.hpp"
#include "processor.hpp"

#include <iostream>

void dataView::PCDump_hex(Processor P) {
    std::cout << std::hex << P.PC << std::endl;
}

void dataView::ADump_hex(Processor P) {
    std::cout << std::hex << (unsigned)P.A << std::endl;
}

void dataView::XDump_hex(Processor P) {
    std::cout << std::hex << P.X << std::endl;
}

void dataView::YDump_hex(Processor P) {
    std::cout << std::hex << P.Y << std::endl;
}

void dataView::ADump_bin(Processor P) {
    uint8_t tempA = P.A;
    uint8_t t = 0b00000001;
    for(int idx = 0; idx < 8; idx++) {
        std::cout << (tempA & t)  << " ";
        tempA = tempA>>1;
    }
    std::cout << std::endl;
}

void dataView::XDump_bin(Processor P) {
    uint8_t tempX = P.X;
    uint8_t t = 0b00000001;
    for(int idx = 0; idx < 8; idx++) {
        std::cout << (tempX & t)  << " ";
        tempX = tempX>>1;
    }
    std::cout << std::endl;
}

void dataView::YDump_bin(Processor P) {
    uint8_t tempY = P.Y;
    uint8_t t = 0b00000001;
    for(int idx = 0; idx < 8; idx++) {
        std::cout << (tempY & t)  << " ";
        tempY = tempY>>1;
    }
    std::cout << std::endl;
}


// outputs the individual bits of the flag register
// from 7th bit to 0th bit
void dataView::FDump(Processor P) {
    uint8_t tempF = P.FR;
    uint8_t t = 0b00000001;
    for(int idx = 0; idx < 8; idx++) {
        std::cout << (tempF & t)  << " ";
        tempF = tempF>>1;
    }
    std::cout << std::endl;
}
