//
// Created by shobhit on 3/11/23.
//

#ifndef INC_6502EMULATOR_DATAVIEW_HPP
#define INC_6502EMULATOR_DATAVIEW_HPP

#include "processor.hpp"
class dataView {
public:
    // register dump
    /***void PCDump_hex(Processor P);
    void ADump_hex(Processor P);
    void XDump_hex(Processor P);
    void YDump_hex(Processor P);***/
    void FDump_hex(Processor P);

    // mem dump
    //void StackDump_hex();
};


#endif //INC_6502EMULATOR_DATAVIEW_HPP
