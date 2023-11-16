#include <iostream>
#include "memory.hpp"
#include "processor.hpp"
#include "instructionCycle.hpp"
#include "dataView.hpp"

int main() {
    InstructionCycle IC;
    dataView dv;
    Processor P;
    P.VMInit();
    //std::cout << std::hex << P.retStackTopLoc() << std::endl;

    IC.IFetch();

    return 0;
}
