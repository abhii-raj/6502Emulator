//
// Created by shobhit on 3/11/23.
//

#include "dataView.hpp"
#include "processor.hpp"

#include <iostream>

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
