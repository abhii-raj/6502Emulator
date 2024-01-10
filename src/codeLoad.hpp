//
// Created by shobhit on 27/10/23.
//

#ifndef INC_6502EMULATOR_CODELOAD_HPP
#define INC_6502EMULATOR_CODELOAD_HPP

#include <string>

#include "memory.hpp"

class CodeLoad {
public:
    // read opcodes from the file, and start loading data
    // into memory at addrLoc starting from the 'loc' index
    void CodeLoadFromFile(std::string opcodeFilePath, uint16_t loc, Memory *mem);

    // read opcodes from the string buffer, and start loading data
    // into memory at addrLoc starting from the 'loc' index
    void CodeLoadFromStrBuffer(std::string opcodeBuffer, uint16_t loc, Memory *mem);
};


#endif //INC_6502EMULATOR_CODELOAD_HPP
