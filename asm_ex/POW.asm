LDA #01         ; init accumulator
STA $0015       ; value of accumulator(=1) is stored at 0015
                ; result will computed at 0015
LDX #02         ; loaded value of base
STX $0007       ; value of base(=2) is stored at 0007
LDY #03         ; loaded value of exponent
STY $0011       ; value of exponent(=3) is stored at 0011
                ; at this point all the values stored in A, X, Y are safely stored in memory
                ; and registers can be overwritten
BEQ end         ; branch to end if exponent is 0
; while(sty>0)
;    mul A * stx
v: LDA #00      ; init for multiplication
LDX $0007       ; value of acumulator
STX $0005       ; stored value of counter for mul at 0005
q: ADC $0015
DEC $0005
BNE q           ; branch for repeated addition
STA $0015
DEC $0011
BNE v           ; branch to keep multiplying till exponent becomes zero

end: LDA $0015 ; final result is moved into A register