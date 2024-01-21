//
// Created by shobhit on 26/10/23.
//

#ifndef INC_6502EMULATOR_PROCESSOR_HPP
#define INC_6502EMULATOR_PROCESSOR_HPP


#include <cstdint>

#include "memory.hpp"

class Processor {
    // table to store how many cpu clock cycle is taken by a particular instruction
    // first index is the high nibble value
    // second index is the low nibble value
    int InstrTicksTable[16][16] = {
            {7,6,0,0,0,3,2,0,3,2,1,0,0,3,3,0},
            {2,5,0,0,0,4,6,0,2,4,0,0,0,4,7,0},
            {6,6,0,0,3,3,5,0,4,2,2,0,4,4,6,0},
            {2,5,0,0,0,4,6,0,2,4,0,0,0,4,7,0},
            {6,6,0,0,0,3,5,0,3,2,2,0,3,4,3,0},
            {2,6,0,0,0,4,6,0,2,4,0,0,0,4,7,0},
            {6,6,0,0,0,3,5,0,4,2,2,0,5,4,6,0},
            {2,5,0,0,0,4,6,0,2,4,0,0,0,4,7,0},
            {0,6,0,0,3,3,3,0,2,0,2,0,4,4,4,0},
            {2,6,0,0,4,4,4,0,2,5,2,0,0,5,0,0},
            {2,6,2,0,3,3,3,0,2,2,2,0,4,4,4,0},
            {2,5,0,0,4,4,4,0,2,4,2,0,4,4,4,0},
            {2,6,0,0,3,3,5,0,2,2,2,0,4,4,6,0},
            {2,5,0,0,0,4,6,0,2,4,0,0,0,4,7,0},
            {2,6,0,0,3,3,5,0,2,2,2,0,4,4,6,0},
            {2,5,0,0,0,4,6,0,2,4,0,0,0,4,6,0}
    };

    // table to store how many subsequent words(or bytes) is used by a particular instruction
    // first index is the high nibble value
    // second index is the low nibble value
    int InstrByteTable[16][16] = {
            {1,2,0,0,0,2,2,0,1,2,1,0,0,3,3,0},
            {2,2,0,0,0,2,2,0,1,3,0,0,0,3,3,0},
            {3,2,0,0,2,2,2,0,1,2,1,0,3,3,3,0},
            {2,2,0,0,0,2,2,0,1,3,0,0,0,3,3,0},
            {1,2,0,0,0,2,2,0,1,2,1,0,3,3,3,0},
            {2,2,0,0,0,2,2,0,1,3,0,0,0,3,3,0},
            {1,2,0,0,0,2,2,0,1,2,1,0,3,3,3,0},
            {2,2,0,0,0,2,2,0,1,3,0,0,0,3,3,0},
            {0,2,0,0,2,2,2,0,1,0,1,0,3,3,3,0},
            {2,2,0,0,2,2,2,0,1,3,1,0,0,3,0,0},
            {2,2,2,0,2,2,2,0,1,2,1,0,3,3,3,0},
            {2,2,0,0,2,2,2,0,1,3,1,0,3,3,3,0},
            {2,2,0,0,2,2,2,0,1,2,1,0,3,3,3,0},
            {2,2,0,0,0,2,2,0,1,3,0,0,0,3,3,0},
            {2,2,0,0,2,2,2,0,1,2,1,0,3,3,3,0},
            {2,2,0,0,0,2,2,0,1,3,0,0,0,3,3,0}
    };

    //Memory mem;
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

    // cpu clock
    long cpuClock = 0;

    // Initialises the values of relevant registers before instruction fetch
    void VMInit(Memory *mem);

    // increments the clock tick depending on opcode
    void updateClock(uint8_t opcode);

    // increments extra clock tick depending on transition during page transition
    void updateClockOnTransition(uint8_t opcode, uint8_t offset);

    // increments PC depending on opcode
    void UpdatePC(uint8_t opcode);

    // gives the location of top of the stack
    int retStackTopLoc();

    uint8_t lowNibble(uint8_t opcode);
    uint8_t highNibble(uint8_t opcode);

    void setNegativeBit();
    void setOverflowBit();
    void setBreakBit();
    void setDecimalBit();
    void setInterruptDisableBit();
    void setZeroBit();
    void setCarryBit();

    void resetNegativeBit();
    void resetOverflowBit();
    void resetBreakBit();
    void resetDecimalBit();
    void resetInterruptDisableBit();
    void resetZeroBit();
    void resetCarryBit();

    /*** LDA Instructions ***/
    // Processor Instructions
    void LDA_imdt(Memory *mem);  // LDA #oper
    void LDA_zpg(Memory *mem);   // LDA oper
    void LDA_zpgx(Memory *mem);  // LDA oper, X
    void LDA_abs(Memory *mem);   // LDA oper
    void LDA_absx(Memory *mem);  // LDA oper, X
    void LDA_absy(Memory *mem);  // LDA oper, Y
    void LDA_ind_x(Memory *mem); // LDA (oper ,X)
    void LDA_ind_y(Memory *mem); // LDA (oper), Y .... verify addressing mode

    /*** STA Instructions ***/
    void STA_zpg(Memory *mem);
    void STA_zpgx(Memory *mem);
    void STA_abs(Memory *mem);
    void STA_absx(Memory *mem);
    void STA_absy(Memory *mem);
    void STA_ind_x(Memory *mem);
    void STA_ind_y(Memory *mem);

    /*** CMP Instructions ***/
    void CMP_imdt(Memory *mem);
    //testing of following functions not done
    void CMP_zpg(Memory *mem);
    void CMP_zpgx(Memory *mem);
    void CMP_abs(Memory *mem);

    // testing of all the following instructions not done

    /*** TYA Instructions ***/
    void TYA_impl(Memory *mem);

    /*** TXS Instructions ***/
    void TXS_impl(Memory *mem);

    /*** TXA Instructions ***/
    void TXA_impl(Memory *mem);

    /*** JMP Instructions ***/
    void JMP_abs(Memory *mem);
    void JMP_idr(Memory *mem);

    /*** TAX Instructions ***/
    void TAX_impl(Memory *mem);

    /*** TAY Instructions ***/
    void TAY_impl(Memory *mem);

     /*** TSX Instructions ***/
    void TSX_impl(Memory *mem);

      /*** INX Instructions ***/
    void INX_impl(Memory *mem);

     /*** INY Instructions ***/
    void INY_impl(Memory *mem);

    /***DEX Instructions ***/
    void DEX_impl(Memory *mem);

    /***DEY Instructions ***/
    void DEY_impl(Memory *mem);

    /***CLC Instructions ***/
    void CLC_impl(Memory *mem);

    /***CLD Instructions ***/
    void CLD_impl(Memory *mem);

    /***CLI Instructions ***/
    void CLI_impl(Memory *mem);

    /***CLV Instructions ***/
    void CLV_impl(Memory *mem);

    /***STY Instructions ***/
    void STY_zpg(Memory *mem);
    void STY_zpgx(Memory *mem);
    void STY_abs(Memory *mem);

    /***STX Instructions ***/
    void STX_zpg(Memory *mem);
    void STX_zpgx(Memory *mem);
    void STX_abs(Memory *mem);

    /***SEI Instructions ***/
    void SEI_impl(Memory *mem);

    /***SED Instructions ***/
    void SED_impl(Memory *mem);

     /***SEC Instructions ***/
    void SEC_impl(Memory *mem);

     /***INC Instructions ***/
    void INC_zpg(Memory *mem);
    void INC_zpgx(Memory *mem);
    void INC_abs(Memory *mem);
    void INC_absx(Memory *mem);

    /*** NOP Instruction ***/
    void NOP_impl(Memory *mem);

    /*** JSR Instruction ***/
    //Jump to New Location Saving Return Address
    void JSR_abs(Memory *mem);

    /*** PHA Instruction ***/
    void PHA_impl(Memory *mem);

    /*** PHP Instruction ***/
    void PHP_impl(Memory *mem);

    /*** PLA Instruction ***/
    void PLA_impl(Memory *mem);

    /*** PLP Instruction ***/
    void PLP_impl(Memory *mem);

    /*** LDX Instruction ***/
    void LDX_imdt(Memory *mem);
    void LDX_abs(Memory *mem);
    void LDX_zpg(Memory *mem);
    void LDX_zpgy(Memory *mem);

    /***  LDY Instruction ***/
    void LDY_imdt(Memory *mem);
    void LDY_abs(Memory *mem);
    void LDY_zpg(Memory *mem);
    void LDY_zpgx(Memory *mem);

    /*** ORA Instructions ***/
    void ORA_imdt(Memory *mem);
    void ORA_zpg(Memory *mem);
    void ORA_zpgx(Memory *mem);
    void ORA_abs(Memory *mem);
    void ORA_idrx(Memory *mem);

    /*** EOR Instructions ***/
    void EOR_imdt(Memory *mem);
    void EOR_zpg(Memory *mem);
    void EOR_zpgx(Memory *mem);
    void EOR_abs(Memory *mem);
    void EOR_idrx(Memory *mem);

    /*** AND Instructions ***/
    void AND_imdt(Memory *mem);
    void AND_zpg(Memory *mem);
    void AND_zpgx(Memory *mem);
    void AND_abs(Memory *mem);
    void AND_idrx(Memory *mem);

    /*** DEC Instructions ***/
    void DEC_zpg(Memory *mem);
    void DEC_zpgx(Memory *mem);
    void DEC_abs(Memory *mem);
    void DEC_absx(Memory *mem);

    /*** CPX Instructions ***/
    void CPX_imdt(Memory *mem);
    void CPX_zpg(Memory *mem);
    void CPX_abs(Memory *mem);

    /*** CPY Instructions ***/
    void CPY_imdt(Memory *mem);
    void CPY_zpg(Memory *mem);
    void CPY_abs(Memory *mem);

    /*** ROL Instructions ***/
    // Rotates the bits in the Accumulator or in a byte in memory to the left, by one bit.
    // moves bit 7 to the carry, moves the carry into bit 0, and every other bit moves one position to its left.
    void ROL_A(Memory *mem);
    void ROL_zpg(Memory *mem);
    void ROL_zpgx(Memory *mem);
    void ROL_abs(Memory *mem);
    void ROL_absx(Memory *mem);

    /*** ROR Instructions ***/
    void ROR_A(Memory *mem);
    void ROR_zpg(Memory *mem);
    void ROR_zpgx(Memory *mem);
    void ROR_abs(Memory *mem);
    void ROR_absx(Memory *mem);

    /***  ASL Instructions ***/
    void ASL_A(Memory *mem);
    void ASL_zpg(Memory *mem);
    void ASL_zpgx(Memory *mem);
    void ASL_abs(Memory *mem);
    void ASL_absx(Memory *mem);

    /*** ADC Instructions ***/
    void ADC_imdt(Memory *mem);
    void ADC_zpg(Memory *mem);
    void ADC_zpgx(Memory *mem);
    void ADC_abs(Memory *mem);
    void ADC_idrx(Memory *mem);

    /*** BCC Instructions ***/
    void BCC_rel(Memory *mem);
    /*** BCS Instructions ***/
    void BCS_rel(Memory *mem);
    /*** BEQ Instructions ***/
    void BEQ_rel(Memory *mem);
    /*** BNE Instructions ***/
    void BNE_rel(Memory *mem);
    /*** BMI Instructions ***/
    void BMI_rel(Memory *mem);
    /*** BPL Instructions ***/
    void BPL_rel(Memory *mem);
    /*** BVC Instructions ***/
    void BVC_rel(Memory *mem);
    /*** BVS Instructions ***/
    void BVS_rel(Memory *mem);
};


#endif //INC_6502EMULATOR_PROCESSOR_HPP
