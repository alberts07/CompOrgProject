# CompOrgProject
CompOrgProject

## TODO Create the Shadow_IFEX function to create global lookup
## TODO Need to put in all the #DEFINEs
## TODO Define rtype as 0 itype as 1 jtype as 2
## TODO Test Vector implementations

functions all lower case
variables all lower case
Tabs should be convertered to 4 spaces


Functions and definitions

Instr_Decode.cpp
    Output program counter,

find_func.cpp
    R type
    Mask out function (bits 0-5) from the machine code instruction

find_shamt.cpp
    R type
    Mask out shift amount (bits 6 - 10) from the machine code instruction

find_rd.cpp
    R type
    Mask out rd (bits 11 - 15) from the machine code instruction


find_rt.cpp
    R/I Type
    Mask out rt (bits 16 - 20) from the machine code instruction
    Returns int

find_rs.cpp
    R/I Type
    Mask out rs (bits 21 - 25) from the machine code instruction
    Returns int

find_opcode.cpp
    All Types
    Mask out opcode (bits 31- 26) from the machine code instruction
    Returns int

find_immed16.cpp
    I Type
    Mask out Immediate (bits 0 - 15) from the machine code instruction
    Returns short

find_immed26.cpp
    J Type
    Mask out Immediate 26 (bits 0 - 26) from the machine code instruction
    Returns int

find_format.cpp
    Determines the format of the machine code by looking at the opcode value
    Returns vector of ints
