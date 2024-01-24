//
// Created by shobhit on 27/10/23.
//
#include <iostream>
#include <fstream>

#include "codeLoad.hpp"

// read opcodes from the file, and start loading data
// into memory at addrLoc starting from the 'loc' index
void CodeLoad::CodeLoadFromFile(std::string opcodeFilePath, uint16_t loc, Memory *mem) {
    std::string str;
    str.clear();
    std::fstream readChar(opcodeFilePath);
    int idx = 0;
    char tempChar;
    while(readChar.get(tempChar)) {
        idx++;
        str.append(1, tempChar);
        if(idx % 2 == 0) {
            std::cout << str << std::endl;
            int Val = std::stoi(str, 0, 16);
            mem->setMem(loc, Val);
            loc++;
            str.clear();
            readChar.get(tempChar);
        }
    }
    readChar.close();
}

// read opcodes from the string buffer, and start loading data
// into memory at addrLoc starting from the 'loc' index
void CodeLoad::CodeLoadFromStrBuffer(std::string opcodeBuffer, uint16_t loc, Memory *mem) {
    std::string temp;
    temp.clear();
    for(unsigned int idx = 0; idx < opcodeBuffer.length(); idx++) {
        // if empty element
        if( (idx+1) % 3 == 0 )
            continue;
        else {
            temp.append(1, opcodeBuffer[idx]);
            // if end element
            if(idx%3 != 0) {
                int Val = std::stoi(temp, 0, 16);
                mem->setMem(loc, Val);
                loc++;
                temp.clear();
            }
        }
    }
}