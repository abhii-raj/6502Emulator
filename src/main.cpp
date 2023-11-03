#include <iostream>
#include "instructionCycle.hpp"
#include "dataView.hpp"

int main() {
    InstructionCycle IC;
    dataView dv;

    dv.FDump_hex(IC.retProcessorObj());
    return 0;
}
