//
// Created by shobhit on 26/10/23.
//

#include "processor.hpp"
#include "memory.hpp"
#include "codeLoad.hpp"

#include <iostream>
#include <math.h>

void Processor::VMInit(Memory *mem) {
    // read 0xFFFC and 0xFFFD(reset vector) to get the address to initialise PC to
    uint16_t PCResetAddress = mem->readNextTwoWords(0xFFFC);
    PC = PCResetAddress;
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

void Processor::resetNegativeBit() {
    FR = FR&0b01111111;
}
void Processor::resetOverflowBit() {
    FR = FR&0b10111111;
}
void Processor::resetBreakBit() {
    FR = FR&0b11101111;
}
void Processor::resetDecimalBit() {
    FR = FR&0b11110111;
}
void Processor::resetInterruptDisableBit() {
    FR = FR&0b11111011;
}
void Processor::resetZeroBit() {
    FR = FR&0b11111101;
}
void Processor::resetCarryBit() {
    FR = FR&0b11111110;
}

void Processor::LDA_imdt(Memory *mem) {
    A = mem->readMemVal(PC + 1);
    if(A == 0) setZeroBit();
    else resetZeroBit();
    
    if((A & 0b10000000) == 0b10000000) setNegativeBit();
    else resetNegativeBit();

    updateClock(mem->readMemVal(PC));
    UpdatePC(mem->readMemVal(PC));
}

void Processor::LDA_abs(Memory *mem) {
    uint16_t nextTwoWordsAddr = mem->readNextTwoWords(PC + 1);
    A = mem->readMemVal(nextTwoWordsAddr);

    if(A == 0) setZeroBit();
    else resetZeroBit();
    
    if((A & 0b10000000) == 0b10000000) setNegativeBit();
    else resetNegativeBit();
    
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

void Processor::STA_zpg(Memory *mem) {
    uint8_t nextWordAddr = mem->readMemVal(PC + 1);
    mem->setMem((uint16_t)nextWordAddr, A);

    updateClock(mem->readMemVal(PC));
    UpdatePC(mem->readMemVal(PC));
}

void Processor::STA_zpgx(Memory *mem) {
    uint8_t nextWordAddr = mem->readMemVal(PC + 1);
    nextWordAddr += mem->readMemVal(PC + 2);

    mem->setMem((uint16_t)nextWordAddr, A);
    updateClock(mem->readMemVal(PC));
    UpdatePC(mem->readMemVal(PC));
}

void Processor::STA_absx(Memory *mem) {
    uint16_t nextTwoWordsAddr = mem->readNextTwoWords(PC + 1);
    nextTwoWordsAddr += X;

    mem->setMem(nextTwoWordsAddr, A);
    updateClock(mem->readMemVal(PC));
    UpdatePC(mem->readMemVal(PC));
}

void Processor::STA_absy(Memory *mem) {
    uint16_t nextTwoWordsAddr = mem->readNextTwoWords(PC + 1);
    nextTwoWordsAddr += Y;

    mem->setMem(nextTwoWordsAddr, A);
    updateClock(mem->readMemVal(PC));
    UpdatePC(mem->readMemVal(PC));
}

void Processor::CMP_imdt(Memory *mem) {
    uint8_t memoryVal = mem->readMemVal(PC + 1);
    int temp = A - memoryVal;
    //std::cout << "memVal - " << (unsigned)memoryVal << std::endl;
    //std::cout << "temp - " << temp << std::endl;
    if(temp == 0) setZeroBit();
    else resetZeroBit();
    
    if(temp < 0) setNegativeBit();
    else resetNegativeBit();
    
    if(temp >= 0) setCarryBit();
    else resetCarryBit();

    updateClock(mem->readMemVal(PC));
    UpdatePC(mem->readMemVal(PC));
}

void Processor::CMP_zpg(Memory *mem) {
    uint16_t effAddrToRead = mem->readMemVal(PC + 1);
    uint8_t effVal = mem->readMemVal(effAddrToRead);
    int temp = A - effVal;
    if(temp == 0) setZeroBit();
    else resetZeroBit();
    
    if(temp < 0) setNegativeBit();
    else resetNegativeBit();
    
    
    if(temp >= 0) setCarryBit();
    else resetCarryBit();

    updateClock(mem->readMemVal(PC));
    UpdatePC(mem->readMemVal(PC));
}

void Processor::CMP_zpgx(Memory *mem) {
    uint8_t effAddrToRead = mem->readMemVal(PC + 1);
    effAddrToRead += X;

    uint8_t effValFetched = mem->readMemVal((uint16_t)effAddrToRead);
    int temp = A - effValFetched;
    if(temp == 0) setZeroBit();
    else resetZeroBit();
    
    if(temp < 0) setNegativeBit();
    else resetNegativeBit();

    if(temp >= 0) setCarryBit();
    else resetCarryBit();
    
    updateClock(mem->readMemVal(PC));
    UpdatePC(mem->readMemVal(PC));
}

void Processor::CMP_abs(Memory *mem) {
    uint16_t nextTwoWordsAddr = mem->readNextTwoWords(PC + 1);
    int temp = A - mem->readMemVal(nextTwoWordsAddr);

    if(temp == 0) setZeroBit();
    else resetZeroBit();

    if(temp < 0) setNegativeBit();
    else resetNegativeBit();
    
    if(temp >= 0) setCarryBit();
    else resetCarryBit();
    
    updateClock(mem->readMemVal(PC));
    UpdatePC(mem->readMemVal(PC));
}

void Processor::TYA_impl(Memory *mem) {
    A = Y;

    if(A==0) setZeroBit();
    else resetZeroBit();
    
    if(A<0) setNegativeBit();
    else resetNegativeBit();
    

    updateClock(mem->readMemVal(PC));
    UpdatePC(mem->readMemVal(PC));
}

void Processor::TXS_impl(Memory *mem) {
    SP = X;
    updateClock(mem->readMemVal(PC));
    UpdatePC(mem->readMemVal(PC));
}

void Processor::TXA_impl(Memory *mem) {
    A = X;

    if(A==0) setZeroBit();
    else resetZeroBit();
    
    if(A<0) setNegativeBit();
    else resetNegativeBit();

    updateClock(mem->readMemVal(PC));
    UpdatePC(mem->readMemVal(PC));
}

void Processor::JMP_abs(Memory *mem) {
    uint16_t nextTwoWordsAddr = mem->readNextTwoWords(PC + 1);

    // no flag bit set

    updateClock(mem->readMemVal(PC));
    PC = nextTwoWordsAddr;
}

void Processor::JMP_idr(Memory *mem) {
    // address of the actual address to which to jump to
    uint16_t nextTwoWordsAddr = mem->readNextTwoWords(PC + 1);

    uint16_t addrToJmpTo = mem->readNextTwoWords(mem->readMemVal(nextTwoWordsAddr));

    // no flag bit set

    updateClock(mem->readMemVal(PC));
    PC = addrToJmpTo;
}

void Processor::TAX_impl(Memory *mem) {
    X = A;

    if(X==0) setZeroBit();
    else resetZeroBit();
    
    if(X<0) setNegativeBit();
    else resetNegativeBit();

    updateClock(mem->readMemVal(PC));
    UpdatePC(mem->readMemVal(PC));
}

void Processor::TAY_impl(Memory *mem) {
    Y = A;

    if(Y==0) setZeroBit();
    else resetZeroBit();

    if(Y<0) setNegativeBit();
    else resetNegativeBit();
    

    updateClock(mem->readMemVal(PC));
    UpdatePC(mem->readMemVal(PC));
}

void Processor::TSX_impl(Memory *mem) {
    X = SP;

    if(X==0) setZeroBit();
    else resetZeroBit();
    
    if(X<0) setNegativeBit();
    else setNegativeBit();
    

    updateClock(mem->readMemVal(PC));
    UpdatePC(mem->readMemVal(PC));
}

void Processor::INX_impl(Memory *mem) {
    X++;

    if(X==0) setZeroBit();
    else resetZeroBit();
    
    if(X<0) setNegativeBit();
    else resetNegativeBit();

    updateClock(mem->readMemVal(PC));
    UpdatePC(mem->readMemVal(PC));
}

void Processor::INY_impl(Memory *mem) {
    Y++;
    
    if(Y==0) setZeroBit();
    else resetZeroBit();

    if(Y<0) setNegativeBit();
    else resetNegativeBit();

    updateClock(mem->readMemVal(PC));
    UpdatePC(mem->readMemVal(PC));
}

void Processor::DEX_impl(Memory *mem) {
    X--;

    if(X==0) setZeroBit();
    else setZeroBit();
    
    if(X<0) setNegativeBit();
    else resetNegativeBit();   
    

    updateClock(mem->readMemVal(PC));
    UpdatePC(mem->readMemVal(PC));
}

void Processor::DEY_impl(Memory *mem) {
    Y--;

    if(Y==0) setZeroBit();
    else resetZeroBit();

    if(Y<0) setNegativeBit();
    else resetNegativeBit();
    
    
    updateClock(mem->readMemVal(PC));
    UpdatePC(mem->readMemVal(PC));
}

void Processor::CLC_impl(Memory *mem) {
    FR = FR & 0b11111110;

    updateClock(mem->readMemVal(PC));
    UpdatePC(mem->readMemVal(PC));
}

void Processor::CLI_impl(Memory *mem) {
    FR = FR & 0b11111011;

    updateClock(mem->readMemVal(PC));
    UpdatePC(mem->readMemVal(PC));
}

void Processor::CLD_impl(Memory *mem) {
    FR = FR & 0b11110111;

    updateClock(mem->readMemVal(PC));
    UpdatePC(mem->readMemVal(PC));
}

void Processor::CLV_impl(Memory *mem) {
    FR = FR & 0b10111111;

    updateClock(mem->readMemVal(PC));
    UpdatePC(mem->readMemVal(PC));
}

void Processor::STY_zpg(Memory *mem) {
    uint16_t effAddrToRead = mem->readMemVal(PC + 1);
    uint8_t effVal = mem->readMemVal(effAddrToRead);
    mem->setMem(effVal, Y);
    
    updateClock(mem->readMemVal(PC));
    UpdatePC(mem->readMemVal(PC));
}

void Processor::STY_zpgx(Memory *mem) {
    uint8_t effAddrToRead = mem->readMemVal(PC + 1);
    effAddrToRead += X;

    uint8_t effValFetched = mem->readMemVal((uint16_t)effAddrToRead);
     mem->setMem(effValFetched, Y);
    
    updateClock(mem->readMemVal(PC));
    UpdatePC(mem->readMemVal(PC));
}

void Processor::STY_abs(Memory *mem) {
    uint16_t nextTwoWordsAddr = mem->readNextTwoWords(PC + 1);
    mem->setMem(nextTwoWordsAddr, Y);

    updateClock(mem->readMemVal(PC));
    UpdatePC(mem->readMemVal(PC));
}

void Processor::STX_zpg(Memory *mem) {
    uint16_t effAddrToRead = mem->readMemVal(PC + 1);
    uint8_t effVal = mem->readMemVal(effAddrToRead);
    mem->setMem(effVal, X);
    
    updateClock(mem->readMemVal(PC));
    UpdatePC(mem->readMemVal(PC));
}

void Processor::STX_zpgx(Memory *mem) {
    uint8_t effAddrToRead = mem->readMemVal(PC + 1);
    effAddrToRead += X;

    uint8_t effValFetched = mem->readMemVal((uint16_t)effAddrToRead);
     mem->setMem(effValFetched, X);
    
    updateClock(mem->readMemVal(PC));
    UpdatePC(mem->readMemVal(PC));
}

void Processor::STX_abs(Memory *mem) {
    uint16_t nextTwoWordsAddr = mem->readNextTwoWords(PC + 1);
    mem->setMem(nextTwoWordsAddr, X);

    updateClock(mem->readMemVal(PC));
    UpdatePC(mem->readMemVal(PC));
}

void Processor::SEI_impl(Memory *mem) {
    setInterruptDisableBit();

    updateClock(mem->readMemVal(PC));
    UpdatePC(mem->readMemVal(PC));
}

void Processor::SED_impl(Memory *mem) {
    setDecimalBit();

    updateClock(mem->readMemVal(PC));
    UpdatePC(mem->readMemVal(PC));
}

void Processor::SEC_impl(Memory *mem) {
    setCarryBit();

    updateClock(mem->readMemVal(PC));
    UpdatePC(mem->readMemVal(PC));
}

void Processor::INC_zpg(Memory *mem) {
    uint8_t nextAddr = mem->readMemVal(PC + 1);
    uint8_t temp = mem->readMemVal((uint16_t)nextAddr);
    temp++;
    mem->setMem((uint16_t)nextAddr, temp);

    if(temp==0) setZeroBit();
    else resetZeroBit();
    
    if(temp<0) setNegativeBit();
    else resetNegativeBit();
    

    updateClock(mem->readMemVal(PC));
    UpdatePC(mem->readMemVal(PC));
}
/***
void Processor::INC_zpgx(Memory *mem) {
    uint16_t nextAddr = mem->readMem(PC + 1);
    nextAddr += X;
    uint8_t temp = mem->readMem((uint16_t)nextAddr);
    temp++;
    mem->setMem((uint16_t)nextAddr, temp);

    if(temp==0) {
        setZeroBit();
    }
    if(temp<0) {
        setNegativeBit();
    }

    updateClock(mem->readMemVal(PC));
    UpdatePC(mem->readMemVal(PC));
}****/

void Processor::NOP_impl(Memory *mem) {
    updateClock(mem->readMemVal(PC));
    UpdatePC(mem->readMemVal(PC));
}

// Jump to New Location Saving Return Address
void Processor::JSR_abs(Memory *mem) {
    // effective address of the topmost free location in stack
    uint16_t effStackAddr = 0x0100 + SP;

    // push PC + 3 to the stack
    mem->setMem(effStackAddr, PC+3);

    // update stack pointer
    // decreasing by 1 word
    SP--;

    // new location where control is shifted to
    uint16_t newLoc = mem->readNextTwoWords(PC + 1);

    updateClock(mem->readMemVal(PC));
    PC = newLoc;
}

void Processor::PHA_impl(Memory *mem) {
    uint16_t effStackAddr = 0x0100 + SP;

    // push A to stack
    mem->setMem(effStackAddr, A);

    //update SP
    SP--;

    updateClock(mem->readMemVal(PC));
    UpdatePC(mem->readMemVal(PC));
}

void Processor::PHP_impl(Memory *mem) {
    uint16_t effStackAddr = 0x0100 + SP;

    // push A to stack
    mem->setMem(effStackAddr, FR);

    //update SP
    SP--;

    updateClock(mem->readMemVal(PC));
    UpdatePC(mem->readMemVal(PC));
}

void Processor::PLA_impl(Memory *mem) {
    uint16_t effStackAddr = 0x0100 + SP;

    // store top most word of the stack into 'A' register
    A = mem->readMemVal(effStackAddr);

    //update SP
    SP++;

    // update flag bits
    if(A==0) setZeroBit();
    else resetZeroBit();
    
    if(A<0) setNegativeBit();
    else resetNegativeBit();
    

    updateClock(mem->readMemVal(PC));
    UpdatePC(mem->readMemVal(PC));
}

void Processor::PLP_impl(Memory *mem) {
    uint16_t effStackAddr = 0x0100 + SP;

    // store top most word of the stack into a temporary variable
    uint8_t tempVal = mem->readMemVal(effStackAddr);

    //update SP
    SP++;

    // update flag bit
    // ignore 4th and 54th bits
    // 4th and 5th bit of tempVal does not affect flag register
    for(int i=0;i<8;i++) {
        int bitVal = tempVal % 2;
        tempVal = tempVal/2;
        int toOR_edWith = bitVal * pow(2, i);
        if( i!=4 && i!=5) {
            FR = FR | toOR_edWith;
        }
    }

    updateClock(mem->readMemVal(PC));
    UpdatePC(mem->readMemVal(PC));
}

void Processor::LDX_imdt(Memory *mem) {
    X = mem->readMemVal(PC + 1);
    if(X == 0) setZeroBit();
    else resetZeroBit();
    
    if((X & 0b10000000) == 0b10000000) setNegativeBit();
    else resetNegativeBit();
    

    updateClock(mem->readMemVal(PC));
    UpdatePC(mem->readMemVal(PC));
}

void Processor::LDX_abs(Memory *mem) {
    uint16_t nextTwoWordsAddr = mem->readNextTwoWords(PC + 1);
    X = mem->readMemVal(nextTwoWordsAddr);

    if(X == 0) setZeroBit();
    else resetZeroBit();

    if((X & 0b10000000) == 0b10000000) setNegativeBit();
    else resetNegativeBit();
    
    updateClock(mem->readMemVal(PC));
    UpdatePC(mem->readMemVal(PC));
}

void Processor::LDX_zpg(Memory *mem){
    uint8_t zeroPageAddr = mem->readMemVal(PC + 1);

    // Load the value from the zero-page address into the X register
    X = mem->readMemVal(zeroPageAddr);
    if(X == 0 ) setZeroBit();
    else resetZeroBit();
    
    if((X & 0b10000000) == 0b10000000) setNegativeBit();
    else resetNegativeBit();

    updateClock(mem->readMemVal(PC));
    UpdatePC(mem->readMemVal(PC));
}

void Processor::LDX_zpgy(Memory *mem) {
    uint8_t zpgAddrX = mem->readMemVal(PC+1);
    zpgAddrX += Y;

    X = mem->readMemVal(zpgAddrX);
    if(X== 0)setZeroBit();
    else resetZeroBit();

    if((X & 0b10000000) == 0b10000000) setNegativeBit();
    else resetNegativeBit();

    updateClock(mem->readMemVal(PC));
    UpdatePC(mem->readMemVal(PC));
}

void Processor::LDY_imdt(Memory *mem) {
    Y = mem->readMemVal(PC + 1);
    if(Y == 0) setZeroBit();
    else resetZeroBit();
    
    if((Y & 0b10000000) == 0b10000000) setNegativeBit();
    else resetNegativeBit();

    updateClock(mem->readMemVal(PC));
    UpdatePC(mem->readMemVal(PC));
}

void Processor::LDY_abs(Memory *mem) {
    uint16_t nextTwoWordsAddr = mem->readNextTwoWords(PC + 1);
    Y = mem->readMemVal(nextTwoWordsAddr);

    if(Y == 0) setZeroBit();
    else resetZeroBit();

    if((Y & 0b10000000) == 0b10000000) setNegativeBit();
    else resetNegativeBit();

    updateClock(mem->readMemVal(PC));
    UpdatePC(mem->readMemVal(PC));
}

void Processor::LDY_zpg(Memory *mem) {
    uint8_t zeroPageAddr = mem->readMemVal(PC + 1);

    // Load the value from the zero-page address into the X register
    Y = mem->readMemVal(zeroPageAddr);
    if(Y == 0 ) setZeroBit();
    else resetZeroBit();
    
    if((Y & 0b10000000) == 0b10000000) setNegativeBit();
    else resetNegativeBit();

    updateClock(mem->readMemVal(PC));
    UpdatePC(mem->readMemVal(PC));
}

void Processor::LDY_zpgx(Memory *mem) {
    uint8_t zpgAddrY = mem->readMemVal(PC+1);
    zpgAddrY += X;

    Y = mem->readMemVal(zpgAddrY);
    if(Y == 0) setZeroBit();
    else resetZeroBit();
    
    if((Y & 0b10000000) == 0b10000000) setNegativeBit();
    else resetNegativeBit();

    updateClock(mem->readMemVal(PC));
    UpdatePC(mem->readMemVal(PC));
}

void Processor::ORA_imdt(Memory *mem) {
    uint8_t tempMem = 0;
    tempMem = mem->readMemVal(PC + 1);

    A |= tempMem;
    if(A == 0) setZeroBit();
    else setZeroBit();

    if((A & 0b10000000) == 0b10000000) setNegativeBit();
    else resetNegativeBit();
    
    updateClock(mem->readMemVal(PC));
    UpdatePC(mem->readMemVal(PC));
}

void Processor::ORA_abs(Memory *mem) {
    uint8_t tempMem = 0;

    uint16_t nextTwoWordsAddr = mem->readNextTwoWords(PC + 1);
    tempMem = mem->readMemVal(nextTwoWordsAddr);

    A |= tempMem;
    if(A == 0) setZeroBit();
    else resetZeroBit();
        
    
    if((A & 0b10000000) == 0b10000000) setNegativeBit();
    else resetNegativeBit();
    

    updateClock(mem->readMemVal(PC));
    UpdatePC(mem->readMemVal(PC));
}

void Processor::ORA_zpg(Memory *mem) {
    uint8_t tempMem = 0;

    uint8_t zeroPageAddr = mem->readMemVal(PC + 1);
    tempMem = mem->readMemVal(zeroPageAddr);

    A |= tempMem;
    if(A == 0) setZeroBit();
    else resetZeroBit();

    if((A & 0b10000000) == 0b10000000) setNegativeBit();
    else resetNegativeBit();

    updateClock(mem->readMemVal(PC));
    UpdatePC(mem->readMemVal(PC));
}

void Processor::ORA_zpgx(Memory *mem) {
    uint8_t tempMem = 0;
    uint8_t zpgAddrX = mem->readMemVal(PC+1);
    zpgAddrX += X;

    tempMem = mem->readMemVal(zpgAddrX);

    A |= tempMem;
    if(A == 0) setZeroBit();
    else resetZeroBit();
    
    if((A & 0b10000000) == 0b10000000) setNegativeBit();
    else resetNegativeBit();

    updateClock(mem->readMemVal(PC));
    UpdatePC(mem->readMemVal(PC));
}

void Processor::ORA_idrx(Memory *mem) {
    uint8_t tempMem = 0 ;

    uint8_t zeroPageAddr = mem->readMemVal(PC + 1);
    uint16_t effectiveAddr = zeroPageAddr + X; // Wrap around if needed
    tempMem = mem->readMemVal(effectiveAddr);

    A |= tempMem;
    if(A == 0) setZeroBit();
    else resetZeroBit();

    if((A & 0b10000000) == 0b10000000) setNegativeBit();
    else resetNegativeBit();

    updateClock(mem->readMemVal(PC));
    UpdatePC(mem->readMemVal(PC));
}

void Processor::EOR_imdt(Memory *mem) {
    uint8_t tempMem = 0;
    tempMem = mem->readMemVal(PC + 1);

    A ^= tempMem;
    if(A == 0) setZeroBit();
    else resetZeroBit();

    if((A & 0b10000000) == 0b10000000) setNegativeBit();
    else resetNegativeBit();

    updateClock(mem->readMemVal(PC));
    UpdatePC(mem->readMemVal(PC));
}

void Processor::EOR_abs(Memory *mem) {
    uint8_t tempMem = 0;

    uint16_t nextTwoWordsAddr = mem->readNextTwoWords(PC + 1);
    tempMem = mem->readMemVal(nextTwoWordsAddr);

    A ^= tempMem;
    if(A == 0) setZeroBit();
    else resetZeroBit();
    
    if((A & 0b10000000) == 0b10000000) setNegativeBit();
    else resetNegativeBit();

    updateClock(mem->readMemVal(PC));
    UpdatePC(mem->readMemVal(PC));
}

void Processor::EOR_zpg(Memory *mem) {
    uint8_t tempMem = 0;

    uint8_t zeroPageAddr = mem->readMemVal(PC + 1);
    tempMem = mem->readMemVal(zeroPageAddr);

    A ^= tempMem;
    if(A == 0) setZeroBit();
    else resetZeroBit();

    if((A & 0b10000000) == 0b10000000) setNegativeBit();
    else resetNegativeBit();

    updateClock(mem->readMemVal(PC));
    UpdatePC(mem->readMemVal(PC));
}

void Processor::EOR_zpgx(Memory *mem) {
    uint8_t tempMem = 0;
    uint8_t zpgAddrX = mem->readMemVal(PC+1);
    zpgAddrX += X;

    tempMem = mem->readMemVal(zpgAddrX);

    A ^= tempMem;
    if(A == 0) setZeroBit();
    else resetZeroBit();
    
    if((A & 0b10000000) == 0b10000000) setNegativeBit();
    else resetNegativeBit();

    updateClock(mem->readMemVal(PC));
    UpdatePC(mem->readMemVal(PC));
}

void Processor::EOR_idrx(Memory *mem) {
    uint8_t tempMem = 0 ;

    uint8_t zeroPageAddr = mem->readMemVal(PC + 1);
    uint16_t effectiveAddr = zeroPageAddr + X;
    tempMem = mem->readMemVal(effectiveAddr);

    A ^= tempMem;
    if(A == 0) setZeroBit();
    else resetZeroBit();

    if((A & 0b10000000) == 0b10000000) setNegativeBit();
    else resetNegativeBit();

    updateClock(mem->readMemVal(PC));
    UpdatePC(mem->readMemVal(PC));

}

void Processor::AND_imdt(Memory *mem) {
    uint8_t tempMem = 0;
    tempMem = mem->readMemVal(PC + 1);

    A &= tempMem;
    if(A == 0){
        setZeroBit();
    }
    if((A & 0b10000000) == 0b10000000){
        setNegativeBit();
    }
    updateClock(mem->readMemVal(PC));
    UpdatePC(mem->readMemVal(PC));
}

void Processor::AND_abs(Memory *mem) {
    uint8_t tempMem = 0;

    uint16_t nextTwoWordsAddr = mem->readNextTwoWords(PC + 1);
    tempMem = mem->readMemVal(nextTwoWordsAddr);

    A &= tempMem;
    if(A == 0){
        setZeroBit();
    }
    if((A & 0b10000000) == 0b10000000){
        setNegativeBit();
    }

    updateClock(mem->readMemVal(PC));
    UpdatePC(mem->readMemVal(PC));
}

void Processor::AND_zpg(Memory *mem) {
    uint8_t tempMem = 0;

    uint8_t zeroPageAddr = mem->readMemVal(PC + 1);
    tempMem = mem->readMemVal(zeroPageAddr);

    A &= tempMem;
    if(A == 0){
        setZeroBit();
    }
    if((A & 0b10000000) == 0b10000000){
        setNegativeBit();
    }

    updateClock(mem->readMemVal(PC));
    UpdatePC(mem->readMemVal(PC));
}

void Processor::AND_zpgx(Memory *mem) {
    uint8_t tempMem = 0;
    uint8_t zpgAddrX = mem->readMemVal(PC+1);
    zpgAddrX += X;

    tempMem = mem->readMemVal(zpgAddrX);

    A &= tempMem;
    if(A == 0){
        setZeroBit();
    }
    if((A & 0b10000000) == 0b10000000){
        setNegativeBit();
    }

    updateClock(mem->readMemVal(PC));
    UpdatePC(mem->readMemVal(PC));
}

void Processor::AND_idrx(Memory *mem) {
    uint8_t tempMem = 0 ;

    uint8_t zeroPageAddr = mem->readMemVal(PC + 1);
    uint16_t effectiveAddr = zeroPageAddr + X;
    tempMem = mem->readMemVal(effectiveAddr);

    A &= tempMem;
    if(A == 0){
        setZeroBit();
    }
    if((A & 0b10000000) == 0b10000000){
        setNegativeBit();
    }

    updateClock(mem->readMemVal(PC));
    UpdatePC(mem->readMemVal(PC));
}

void Processor::DEC_zpg(Memory *mem) {
    uint8_t tempMem = 0;

    uint8_t zeroPageAddr = mem->readMemVal(PC + 1);
    tempMem = mem->readMemVal(zeroPageAddr);
    tempMem = tempMem - 1;
    if(A == 0){
        setZeroBit();
    }
    if((A & 0b10000000) == 0b10000000){
        setNegativeBit();
    }

    updateClock(mem->readMemVal(PC));
    UpdatePC(mem->readMemVal(PC));
}

void Processor::DEC_abs(Memory *mem) {
    uint8_t tempMem = 0;

    uint16_t nextTwoWordsAddr = mem->readNextTwoWords(PC + 1);
    tempMem = mem->readMemVal(nextTwoWordsAddr);
    tempMem = tempMem - 1;
    if(A == 0){
        setZeroBit();
    }
    if((A & 0b10000000) == 0b10000000){
        setNegativeBit();
    }

    updateClock(mem->readMemVal(PC));
    UpdatePC(mem->readMemVal(PC));
}

void Processor::DEC_absx(Memory *mem) {
    uint8_t tempMem = 0;

    uint16_t nextTwoWordsAddr = mem->readNextTwoWords(PC + 1);
    uint16_t effectiveAddr = nextTwoWordsAddr + X;
    tempMem = mem->readMemVal(effectiveAddr);
    tempMem = tempMem - 1;
    if(A == 0){
        setZeroBit();
    }
    if((A & 0b10000000) == 0b10000000){
        setNegativeBit();
    }

    updateClock(mem->readMemVal(PC));
    UpdatePC(mem->readMemVal(PC));
}

void Processor::DEC_zpgx(Memory *mem) {
    uint8_t tempMem = 0;
    uint8_t zpgAddrX = mem->readMemVal(PC+1);
    zpgAddrX += X;
    tempMem = mem->readMemVal(zpgAddrX);
    tempMem = tempMem - 1;
    if(A == 0){
        setZeroBit();
    }
    if((A & 0b10000000) == 0b10000000){
        setNegativeBit();
    }

    updateClock(mem->readMemVal(PC));
    UpdatePC(mem->readMemVal(PC));
}

void Processor::CPX_imdt(Memory *mem) {
    uint8_t tempMem = 0;
    tempMem = mem->readMemVal(PC + 1);
    uint8_t result = X - tempMem;

    if(result == 0){
        setZeroBit();
    }
    if((result & 0b10000000) == 0b10000000){
        setNegativeBit();
    }

    updateClock(mem->readMemVal(PC));
    UpdatePC(mem->readMemVal(PC));
}

void Processor::CPX_abs(Memory *mem) {
    uint8_t tempMem = 0;
    uint16_t nextTwoWordsAddr = mem->readNextTwoWords(PC + 1);
    tempMem = mem->readMemVal(nextTwoWordsAddr);
    uint8_t result = X - tempMem;

    if(result == 0){
        setZeroBit();
    }
    if((result & 0b10000000) == 0b10000000){
        setNegativeBit();
    }

    updateClock(mem->readMemVal(PC));
    UpdatePC(mem->readMemVal(PC));
}

void Processor::CPX_zpg(Memory *mem) {
    uint8_t tempMem = 0;

    uint8_t zeroPageAddr = mem->readMemVal(PC + 1);
    tempMem = mem->readMemVal(zeroPageAddr);
    uint8_t result = X - tempMem;
    if(result == 0){
        setZeroBit();
    }
    if((result & 0b10000000) == 0b10000000){
        setNegativeBit();
    }

    updateClock(mem->readMemVal(PC));
    UpdatePC(mem->readMemVal(PC));
}

void Processor::CPY_imdt(Memory *mem) {
    uint8_t tempMem = 0;
    tempMem = mem->readMemVal(PC + 1);
    uint8_t result = Y - tempMem;

    if(result == 0){
        setZeroBit();
    }
    if((result & 0b10000000) == 0b10000000){
        setNegativeBit();
    }

    updateClock(mem->readMemVal(PC));
    UpdatePC(mem->readMemVal(PC));
}

void Processor::CPY_abs(Memory *mem) {
    uint8_t tempMem = 0;
    uint16_t nextTwoWordsAddr = mem->readNextTwoWords(PC + 1);
    tempMem = mem->readMemVal(nextTwoWordsAddr);
    uint8_t result = Y - tempMem;

    if(result == 0){
        setZeroBit();
    }
    if((result & 0b10000000) == 0b10000000){
        setNegativeBit();
    }

    updateClock(mem->readMemVal(PC));
    UpdatePC(mem->readMemVal(PC));
}

void Processor::CPY_zpg(Memory *mem) {
    uint8_t tempMem = 0;

    uint8_t zeroPageAddr = mem->readMemVal(PC + 1);
    tempMem = mem->readMemVal(zeroPageAddr);
    uint8_t result = Y - tempMem;
    if(result == 0){
        setZeroBit();
    }
    if((result & 0b10000000) == 0b10000000){
        setNegativeBit();
    }

    updateClock(mem->readMemVal(PC));
    UpdatePC(mem->readMemVal(PC));
}
