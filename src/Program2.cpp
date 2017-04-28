#include "Program2.hpp"
extern unsigned int memory[1200];




unsigned int program2[1200] = {

0x00000898,	// $sp = 2200
0x00000898,	// $fp = 2200
0x00000320,	// data segment pointer used by the program
0x00000000,
0x00000000,
0x00000078,	// $pc = 120
0x00000000,
0x00000000,
0x00000000,
0x00000000,
0x80a70000,   // 	lb	a3,0(a1)
0x10e0001e,   // 	beqz	a3,4008b0 <ceasar_encrypt+0x80>
0x24a50001,   // 	addiu	a1,a1,1
0x30e200ff,   // 	andi	v0,a3,0xff
0x2443ff9f,   // 	addiu	v1,v0,-97
0x306300ff,   // 	andi	v1,v1,0xff
0x2c63001a,   // 	sltiu	v1,v1,26
0x10600009,   // 	beqz	v1,400874 <ceasar_encrypt+0x44>
0x2443ffbf,   // 	addiu	v1,v0,-65
0x00441021,   // 	addu	v0,v0,a0
0x304200ff,   // 	andi	v0,v0,0xff
0x7c023c20,   // 	seb	a3,v0
0x28e3007b,   // 	slti	v1,a3,123
0x1460000d,   // 	bnez	v1,40089c <ceasar_encrypt+0x6c>
0x2442ffe6,   // 	addiu	v0,v0,-26
0x1000000b,   // 	b	40089c <ceasar_encrypt+0x6c>
0x7c023c20,   // 	seb	a3,v0
0x306300ff,   // 	andi	v1,v1,0xff
0x2c63001a,   // 	sltiu	v1,v1,26
0x10600007,   // 	beqz	v1,40089c <ceasar_encrypt+0x6c>
0x00441021,   // 	addu	v0,v0,a0
0x304300ff,   // 	andi	v1,v0,0xff
0x7c033c20,   // 	seb	a3,v1
0x28e2005b,   // 	slti	v0,a3,91
0x14400002,   // 	bnez	v0,40089c <ceasar_encrypt+0x6c>
0x2463ffe6,   // 	addiu	v1,v1,-26
0x7c033c20,   // 	seb	a3,v1
0xa0c70000,   // 	sb	a3,0(a2)
0x80a70000,   // 	lb	a3,0(a1)
0x24c60001,   // 	addiu	a2,a2,1
0x14e0ffe4,   // 	bnez	a3,40083c <ceasar_encrypt+0xc>
0x24a50001,   // 	addiu	a1,a1,1
0x03e00008,   // 	jr	ra
0x00000000,   // 	nop
0x00000000,   // 	nop
0x00000000,   // 	nop
0x00000000,   // 	nop
0x00000000,   // 	nop
0x00000000,   // 	nop
0x00000000,   // 	nop
0x80a70000,   // 	lb	a3,0(a1)
0x10e0001e,   // 	beqz	a3,400938 <ceasar_decrypt+0x80>
0x24a50001,   // 	addiu	a1,a1,1
0x30e200ff,   // 	andi	v0,a3,0xff
0x2443ff9f,   // 	addiu	v1,v0,-97
0x306300ff,   // 	andi	v1,v1,0xff
0x2c63001a,   // 	sltiu	v1,v1,26
0x10600009,   // 	beqz	v1,4008fc <ceasar_decrypt+0x44>
0x2443ffbf,   // 	addiu	v1,v0,-65
0x00441023,   // 	subu	v0,v0,a0
0x304200ff,   // 	andi	v0,v0,0xff
0x7c023c20,   // 	seb	a3,v0
0x28e30061,   // 	slti	v1,a3,97
0x1060000d,   // 	beqz	v1,400924 <ceasar_decrypt+0x6c>
0x2442001a,   // 	addiu	v0,v0,26
0x1000000b,   // 	b	400924 <ceasar_decrypt+0x6c>
0x7c023c20,   // 	seb	a3,v0
0x306300ff,   // 	andi	v1,v1,0xff
0x2c63001a,   // 	sltiu	v1,v1,26
0x10600007,   // 	beqz	v1,400924 <ceasar_decrypt+0x6c>
0x00441023,   // 	subu	v0,v0,a0
0x304300ff,   // 	andi	v1,v0,0xff
0x7c033c20,   // 	seb	a3,v1
0x28e20041,   // 	slti	v0,a3,65
0x10400002,   // 	beqz	v0,400924 <ceasar_decrypt+0x6c>
0x2463001a,   // 	addiu	v1,v1,26
0x7c033c20,   // 	seb	a3,v1
0xa0c70000,   // 	sb	a3,0(a2)
0x80a70000,   // 	lb	a3,0(a1)
0x24c60001,   // 	addiu	a2,a2,1
0x14e0ffe4,   // 	bnez	a3,4008c4 <ceasar_decrypt+0xc>
0x24a50001,   // 	addiu	a1,a1,1
0x03e00008,   // 	jr	ra
0x00000000,   // 	nop
0x00000000,   // 	nop
0x00000000,   // 	nop
0x00000000,   // 	nop
0x00000000,   // 	nop
0x00000000,   // 	nop
0x00000000,   // 	nop
0x80860000,   // 	lb	a2,0(a0)
0x10c0000f,   // 	beqz	a2,400984 <compare_string+0x44>
0x00a04025,   // 	move	t0,a1
0x24840001,   // 	addiu	a0,a0,1
0x00003825,   // 	move	a3,zero
0x24020001,   // 	li	v0,1
0x81030000,   // 	lb	v1,0(t0)
0x00661826,   // 	xor	v1,v1,a2
0x0003100b,   // 	movn	v0,zero,v1
0x24e70001,   // 	addiu	a3,a3,1
0x00e01825,   // 	move	v1,a3
0x80860000,   // 	lb	a2,0(a0)
0x25080001,   // 	addiu	t0,t0,1
0x14c0fff8,   // 	bnez	a2,400958 <compare_string+0x18>
0x24840001,   // 	addiu	a0,a0,1
0x10000004,   // 	b	400990 <compare_string+0x50>
0x00a32821,   // 	addu	a1,a1,v1
0x00001825,   // 	move	v1,zero
0x24020001,   // 	li	v0,1
0x00a32821,   // 	addu	a1,a1,v1
0x80a30000,   // 	lb	v1,0(a1)
0x03e00008,   // 	jr	ra
0x0003100b,   // 	movn	v0,zero,v1
0x00000000,   // 	nop
0x00000000,   // 	nop
0x00000000,   // 	nop
0x00000000,   // 	nop
0x00000000,   // 	nop
0x00000000,   // 	nop
0x00000000,   // 	nop
0x27bdfc50,   // 	addiu	sp,sp,-944
0xafbf03ac,   // 	sw	ra,940(sp)
0xafb203a8,   // 	sw	s2,936(sp)
0xafb103a4,   // 	sw	s1,932(sp)
0xafb003a0,   // 	sw	s0,928(sp)
0x8e020000,   // 	lw	v0,0(s0)
0xafa2039c,   // 	sw	v0,924(sp)
0x27b20144,   // 	addiu	s2,sp,324
0x02403025,   // 	move	a2,s2
0x3c020000,   // 	lui	v0,0x00
0x8c050008,	  //	lw $a1, 8($zero)	0x8c450008,   // 	lw	a1,8(v0)
0x24040005,   // 	li	a0,5
0x0c00000a,   // 	jal	10 <ceasar_encrypt>
0x00000000,   // 	nop
0x27b10270,   // 	addiu	s1,sp,624
0x02203025,   // 	move	a2,s1
0x02402825,   // 	move	a1,s2
0x24040005,   // 	li	a0,5
0x0c000032,   // 	jal	50 <ceasar_decrypt>
0x00000000,   // 	nop
0x02202825,   // 	move	a1,s1
0x8c040008,	  //	lw $a0, 8($zero) 0x27a40018,   // 	addiu	a0,sp,24
0x0c00005a,   // 	jal	90 <compare_string>
0x00000000,   // 	nop
0x8fa4039c,   // 	lw	a0,924(sp)
0x8e030000,   // 	lw	v1,0(s0)
0x10830004,   // 	beq	a0,v1,400a34 <main+0x98>
0x8fbf03ac,   // 	lw	ra,940(sp)
0x00000000,   // 	nop
0x00000000,   // 	nop
0x00000000,   // 	nop
0x00000000,   // 	nop
0x00000000,   // 	nop
0x00000000,   // 	nop
0x00000000,   // 	nop
0x00000000,   // 	nop
0x00000000,   // 	nop
0x8c080384,   // 	lw $t0, 900($zero)
0x8c090690,   // 	lw $t1, 1680($zero)
0x8c0a07bc,   // 	lw $t2, 1980($zero)
0xac08001c,   // 	sw $t0, 28($zero)
0xac090020,   // 	sw $t1, 32($zero)
0xac0a0024,   // 	sw $t2, 36($zero)
0xac020018,   // 	sw $v0, 24($zero)
0x8c08041c,   // 	lw $t0, 1052($zero)
0x8c090420,   // 	lw $t1, 1056($zero)
0x8c0a0424,   // 	lw $t2, 1060($zero)
0x8c080418,   // 	lw $t0, 1048($zero)
0x8fb203a8,   // 	lw	s2,936(sp)
0x8fb103a4,   // 	lw	s1,932(sp)
0x8fb003a0,   // 	lw	s0,928(sp)
0x00000008,   // 	jr	to PC = $zero to end program
0x27bd03b0,   // 	addiu	sp,sp,944
0x00000000,   // 	nop
0x00000000,   // 	nop
0x00000000,   // 	nop
0x00000000,   // 	nop
0x00000000,   // 	nop
0x00000000,   // 	nop
0x00000000,   // 	nop
0x00000000,   // 	nop
0x00000000,   // 	nop
0x00000000,   // 	nop
0x00000000,   // 	nop
0x00000000,   // 	nop
0x00000000,   // 	nop
0x00000000,   // 	nop
0x00000000,   // 	nop
0x00000000,   // 	nop
0x00000000,   // 	nop
0x00000000,   // 	nop
0x00000000,   // 	nop
0x00000000,   // 	nop
0x00000000,   // 	nop
0x00000000,   // 	nop
0x00000000,   // 	nop
0x00000000,   // 	nop
0x00000000,   // 	nop
0x00000000,   // 	nop
0x00000000,   // 	nop
0x44757269,   // 	Duri
0x6e672061,   // 	ng a
0x20666577,   // 	 few
0x20646179,   // 	 day
0x73206861,   // 	s ha
0x6c74206e,   // 	lt n
0x65617220,   // 	ear
0x5665736f,   // 	Veso
0x6e74696f,   // 	ntio
0x20666f72,   // 	 for
0x20746865,   // 	 the
0x2070726f,   // 	 pro
0x76697369,   // 	visi
0x6f6e206f,   // 	on o
0x6620636f,   // 	f co
0x726e2061,   // 	rn a
0x6e64206f,   // 	nd o
0x74686572,   // 	ther
0x20737570,   // 	 sup
0x706c6965,   // 	plie
0x73206120,   // 	s a
0x70616e69,   // 	pani
0x63206172,   // 	c ar
0x6f736520,   // 	ose
0x66726f6d,   // 	from
0x20696e71,   // 	 inq
0x75697269,   // 	uiri
0x6573206d,   // 	es m
0x61646520,   // 	ade
0x6279206f,   // 	by o
0x75722074,   // 	ur t
0x726f6f70,   // 	roop
0x7320616e,   // 	s an
0x64207265,   // 	d re
0x6d61726b,   // 	mark
0x73207574,   // 	s ut
0x74657265,   // 	tere
0x64206279,   // 	d by
0x20476175,   // 	 Gau
0x6c732061,   // 	ls a
0x6e642074,   // 	nd t
0x72616465,   // 	rade
0x72732077,   // 	rs w
0x686f2061,   // 	ho a
0x66666972,   // 	ffir
0x6d656420,   // 	med
0x74686174,   // 	that
0x20746865,   // 	 the
0x20476572,   // 	 Ger
0x6d616e73,   // 	mans
0x20776572,   // 	 wer
0x65206d65,   // 	e me
0x6e206f66,   // 	n of
0x2061206d,   // 	 a m
0x69676874,   // 	ight
0x79206672,   // 	y fr
0x616d6520,   // 	ame
0x616e6420,   // 	and
0x616e2069,   // 	an i
0x6e637265,   // 	ncre
0x6469626c,   // 	dibl
0x65207661,   // 	e va
0x6c6f7572,   // 	lour
0x20616e64,   // 	and
0x20736b69,   // 	ski
0x6c6c2061,   // 	ll
0x74206172,   // 	t ar
0x6d73204a,   // 	ms J
0x756c6975,   // 	uliu
0x73204361,   // 	s Ca
0x65736172,   // 	esar
0x00000000   // 	nop
};


void transfer_Program2(void)
{
    for(unsigned int i = 0; i < 1200; i++)
        memory[i] = program2[i];
}
