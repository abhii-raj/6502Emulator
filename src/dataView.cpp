//
// Created by shobhit on 3/11/23.
//

#include "dataView.hpp"
#include "processor.hpp"

#include <iostream>

void dataView::FDump_hex(Processor P) {
    uint8_t t = 0b00000001;
    for(int idx = 0; idx < 8; idx++) {
        std::cout << (P.FR & t)  << " ";
        P.FR<<1;
    }
    std::cout << std::endl;
}
