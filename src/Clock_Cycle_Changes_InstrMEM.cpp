    // 
    // if(EXMEM.MemRead && (MEMWB.DstReg != 0)  && ((EXMEM.DstReg == Shadow_IDEX.Rs) || (EXMEM.DstReg == Shadow_IDEX.Rt))\
    //  && ((Shadow_IDEX.opcode == blez_opcode) || (Shadow_IDEX.opcode == bltz_opcode)\
    //   || (Shadow_IDEX.opcode == bgtz_opcode) || (Shadow_IDEX.opcode == beq_opcode) || (Shadow_IDEX.opcode == bne_opcode))\
    //   && (taken == 0))
    // {
    //
    //       // cout << "Entered Forwarding Stall 3: Load and Branch Issue: " << endl;
    //       // cout << pc + 1<< endl;
    //       delay_cycles = delay_cycles + 1;
    //       taken = 1;
    // }
    //
    // if(EXMEM.RegWrite && (MEMWB.DstReg != 0)  && ((EXMEM.DstReg == Shadow_IDEX.Rs) || (EXMEM.DstReg == Shadow_IDEX.Rt))\
    //   && ((Shadow_IDEX.opcode == blez_opcode) || (Shadow_IDEX.opcode == bltz_opcode)\
    //   || (Shadow_IDEX.opcode == bgtz_opcode) || (Shadow_IDEX.opcode == beq_opcode) || (Shadow_IDEX.opcode == bne_opcode))\
    //   && (taken == 0))
    // {
    //       // if((pc +1 != 28) && (pc + 1 != 18) && (pc + 1 != 38)){
    //       // cout << "Entered Forwarding Stall 3: Instr and Branch Issue:  " << endl;
    //       // cout << pc + 1 << endl;}
    //       delay_cycles++;
    //       taken = 1;
    // }
    // if(EXMEM.MemRead && (MEMWB.DstReg != 0)  && ((EXMEM.DstReg == Shadow_IDEX.Rt) || (EXMEM.DstReg == Shadow_IDEX.Rs))\
    //   && ((Shadow_IDEX.opcode != blez_opcode) || (Shadow_IDEX.opcode != bltz_opcode)\
    //   || (Shadow_IDEX.opcode != bgtz_opcode) || (Shadow_IDEX.opcode != beq_opcode) || (Shadow_IDEX.opcode != bne_opcode))\
    //   && (taken == 0))
    // {
    //       // if(pc + 1 != 127)
    //       // {
    //       //   cout << "Entered Forwarding Stall 4: Load ahead of instr using result. Issue: " << endl;
    //       //   cout << pc + 1<< endl;
    //       // }
    //       delay_cycles++;
    //       taken = 1;
    // }
    //
    // if((MEMWB.RegWrite) && (MEMWB.DstReg != 0) && ((MEMWB.DstReg == Shadow_IDEX.Rs) || (MEMWB.DstReg == Shadow_IDEX.Rt))\
    //   && !((EXMEM.RegWrite) && (EXMEM.DstReg == Shadow_IDEX.Rs) && (EXMEM.DstReg != 0))\
    //   && (taken == 0))
    // {
    //       // cout << "Entered Forwarding Stall 1: " << endl;
    //       // cout << pc + 1 << endl;
    //       delay_cycles++;
    //        taken = 1;
    // }
    // if((EXMEM.MemWrite) && (Shadow_EXMEM.RegWrite || Shadow_EXMEM.MemRead) && ((IDEX.Rt == Shadow_IDEX.Rs) || (IDEX.Rt == Shadow_IDEX.Rt))\
    //   && (taken == 0))
    // {
    //       // cout << "Entered Forwarding Stall ?: " << endl;
    //       // cout << pc + 1 << endl;
    //       delay_cycles++;
    //        taken = 1;
    // }
