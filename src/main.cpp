#include <iostream>
#include "memory.hpp"
#include "processor.hpp"
#include "instructionCycle.hpp"
#include "dataView.hpp"

int main(int argc, char **argv) {
    InstructionCycle IC(1, &argc, &argv);
    //P.VMInit(IC.retMemoryObj());
    //std::cout << std::hex << P.retStackTopLoc() << std::endl;
    //IC.IFetch();
    return 0;
}
