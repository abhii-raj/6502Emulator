//
// Created by shobhit on 26/10/23.
//

#include "processor.hpp"
#include "memory.hpp"
#include <iostream>

void Processor::VMInit() {
    PC = 0x0400; // for now assume that PC starts from 0x0400
    A = 0;
    X = 0;
    Y = 0;

    // values initialised with reference to 6502 specifications
    // unused 5th bit(5th bit) and Interrupt bit(2nd bit) is set as 1
    // N V - B D I Z C
    FR = 0b00100100;

    // stack pointer register initialisation
    // stack starts from (SP + 0x100)
    // stack register is initialised from 0xff because 8 bit register can't store 0x1ff
    SP = 0xFF;
}

// increments the clock tick by the parameter value
void Processor::updateClock(uint8_t opcode) {
    cpuClock += InstrTicksTable[lowNibble(opcode)][highNibble(opcode)];
}

// gives the location of top of the stack
int Processor::retStackTopLoc() {
    return (SP + 0x100);
}

uint8_t Processor::lowNibble(uint8_t opcode) {
    return (opcode % 16);
}
uint8_t Processor::highNibble(uint8_t opcode) {
    opcode = opcode / 16;
    return (opcode % 16);
}

void Processor::UpdatePC(uint8_t opcode) {
    PC += InstrByteTable[highNibble(opcode)][lowNibble(opcode)];
}

void Processor::setNegativeBit() {
    FR = FR|0b10000000;
}
void Processor::setOverflowBit() {
    FR = FR|0b01000000;
}
void Processor::setBreakBit() {
    FR = FR|0b00010000;
}
void Processor::setDecimalBit() {
    FR = FR|0b00001000;
}
void Processor::setInterruptDisableBit() {
    FR = FR|0b00000100;
}
void Processor::setZeroBit() {
    FR = FR|0b00000010;
}
void Processor::setCarryBit() {
    FR = FR|0b00000001;
}

void Processor::LDA_imdt(Memory *mem) {
    A = mem->readMemVal(PC + 1);
    if(A == 0) {
        setZeroBit();
    }
    if((A & 0b10000000) == 0b10000000) {
        setNegativeBit();
    }

    updateClock(mem->readMemVal(PC));
    UpdatePC(mem->readMemVal(PC));
}

void Processor::LDA_abs(Memory *mem) {
    uint16_t nextTwoWordsAddr = mem->readNextTwoWords(PC + 1);
    A = mem->readMemVal(nextTwoWordsAddr);

    if(A == 0) {
        setZeroBit();
    }
    if((A & 0b10000000) == 0b10000000) {
        setNegativeBit();
    }
    updateClock(mem->readMemVal(PC));
    UpdatePC(mem->readMemVal(PC));
}

void Processor::STA_abs(Memory *mem) {
    uint16_t nextTwoWordsAddr = mem->readNextTwoWords(PC + 1);
    mem->setMem(nextTwoWordsAddr, A);

    //no flag affected
    
    updateClock(mem->readMemVal(PC));
    UpdatePC(mem->readMemVal(PC));
}
