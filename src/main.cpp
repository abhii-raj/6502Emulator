#include <iostream>
#include "instructionCycle.hpp"
#include "dataView.hpp"

int main() {
    InstructionCycle IC;
    dataView dv;

    dv.FDump(IC.retProcessorObj());
    return 0;
}
