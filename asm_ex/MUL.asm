LDA #00 ; init
LDX #03 ; counter
STX $0005
q: ADC #05
DEC $0005
BNE q