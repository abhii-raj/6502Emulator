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