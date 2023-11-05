#include <iostream>
#include "memory.hpp"
#include "processor.hpp"
//#include "instructionCycle.hpp"
//#include "dataView.hpp"

int main() {
    //InstructionCycle IC;
    //dataView dv;

    //dv.FDump(IC.retProcessorObj());
    //dv.PCDump_hex(IC.retProcessorObj());

    Memory memo;

    memo.readMem(0x0400);
    memo.readMem(0x0401);
    memo.readMem(0x0402);
    memo.readMem(0x0403);
    memo.readMem(0x0404);
    memo.readMem(0x0405);
    memo.readMem(0x0406);
    memo.readMem(0x0407);
    memo.readMem(0x0408);
    memo.readMem(0x0409);
    memo.readMem(0x040A);
    memo.readMem(0x040B);
    memo.readMem(0x040C);
    memo.readMem(0x040D);
    memo.readMem(0x040E);

    Processor P;
    P.VMInit();
    std::cout << std::hex << P.retStackTopLoc() << std::endl;

    return 0;
}
