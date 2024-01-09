#include <iostream>
#include "memory.hpp"
#include "processor.hpp"
#include "instructionCycle.hpp"
#include "dataView.hpp"
#include "ui_render.hpp"

int main(int argc, char **argv) {
    //InstructionCycle IC(1);
    //mainUI(&argc, &argv);
    Memory mem;
    CodeLoad cl;
    cl.CodeLoadFromStrBuffer("A9 13 8D 08 04 C9 24", 0x0400, &mem);
    dataView dv;
    mem.readMem(0x400);
    mem.readMem(0x401);
    mem.readMem(0x402);
    mem.readMem(0x403);
    mem.readMem(0x405);
    mem.readMem(0x406);

    //P.VMInit(IC.retMemoryObj());
    //std::cout << std::hex << P.retStackTopLoc() << std::endl;
    //IC.IFetch();
    return 0;
}
