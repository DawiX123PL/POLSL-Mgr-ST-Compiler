
output.elf:     file format elf32-littlearm


Disassembly of section .symbol_table:

00000000 <.symbol_table>:
   0:	000013a5 	andeq	r1, r0, r5, lsr #7
   4:	0000136d 	andeq	r1, r0, sp, ror #6
   8:	00000010 	andeq	r0, r0, r0, lsl r0

Disassembly of section .text:

00000050 <__aeabi_frsub>:
      50:	f080 4000 	eor.w	r0, r0, #2147483648	; 0x80000000
      54:	e002      	b.n	5c <__addsf3>
      56:	bf00      	nop

00000058 <__aeabi_fsub>:
      58:	f081 4100 	eor.w	r1, r1, #2147483648	; 0x80000000

0000005c <__addsf3>:
      5c:	0042      	lsls	r2, r0, #1
      5e:	bf1f      	itttt	ne
      60:	ea5f 0341 	movsne.w	r3, r1, lsl #1
      64:	ea92 0f03 	teqne	r2, r3
      68:	ea7f 6c22 	mvnsne.w	ip, r2, asr #24
      6c:	ea7f 6c23 	mvnsne.w	ip, r3, asr #24
      70:	d06a      	beq.n	148 <__addsf3+0xec>
      72:	ea4f 6212 	mov.w	r2, r2, lsr #24
      76:	ebd2 6313 	rsbs	r3, r2, r3, lsr #24
      7a:	bfc1      	itttt	gt
      7c:	18d2      	addgt	r2, r2, r3
      7e:	4041      	eorgt	r1, r0
      80:	4048      	eorgt	r0, r1
      82:	4041      	eorgt	r1, r0
      84:	bfb8      	it	lt
      86:	425b      	neglt	r3, r3
      88:	2b19      	cmp	r3, #25
      8a:	bf88      	it	hi
      8c:	4770      	bxhi	lr
      8e:	f010 4f00 	tst.w	r0, #2147483648	; 0x80000000
      92:	f440 0000 	orr.w	r0, r0, #8388608	; 0x800000
      96:	f020 407f 	bic.w	r0, r0, #4278190080	; 0xff000000
      9a:	bf18      	it	ne
      9c:	4240      	negne	r0, r0
      9e:	f011 4f00 	tst.w	r1, #2147483648	; 0x80000000
      a2:	f441 0100 	orr.w	r1, r1, #8388608	; 0x800000
      a6:	f021 417f 	bic.w	r1, r1, #4278190080	; 0xff000000
      aa:	bf18      	it	ne
      ac:	4249      	negne	r1, r1
      ae:	ea92 0f03 	teq	r2, r3
      b2:	d03f      	beq.n	134 <__addsf3+0xd8>
      b4:	f1a2 0201 	sub.w	r2, r2, #1
      b8:	fa41 fc03 	asr.w	ip, r1, r3
      bc:	eb10 000c 	adds.w	r0, r0, ip
      c0:	f1c3 0320 	rsb	r3, r3, #32
      c4:	fa01 f103 	lsl.w	r1, r1, r3
      c8:	f000 4300 	and.w	r3, r0, #2147483648	; 0x80000000
      cc:	d502      	bpl.n	d4 <__addsf3+0x78>
      ce:	4249      	negs	r1, r1
      d0:	eb60 0040 	sbc.w	r0, r0, r0, lsl #1
      d4:	f5b0 0f00 	cmp.w	r0, #8388608	; 0x800000
      d8:	d313      	bcc.n	102 <__addsf3+0xa6>
      da:	f1b0 7f80 	cmp.w	r0, #16777216	; 0x1000000
      de:	d306      	bcc.n	ee <__addsf3+0x92>
      e0:	0840      	lsrs	r0, r0, #1
      e2:	ea4f 0131 	mov.w	r1, r1, rrx
      e6:	f102 0201 	add.w	r2, r2, #1
      ea:	2afe      	cmp	r2, #254	; 0xfe
      ec:	d251      	bcs.n	192 <__addsf3+0x136>
      ee:	f1b1 4f00 	cmp.w	r1, #2147483648	; 0x80000000
      f2:	eb40 50c2 	adc.w	r0, r0, r2, lsl #23
      f6:	bf08      	it	eq
      f8:	f020 0001 	biceq.w	r0, r0, #1
      fc:	ea40 0003 	orr.w	r0, r0, r3
     100:	4770      	bx	lr
     102:	0049      	lsls	r1, r1, #1
     104:	eb40 0000 	adc.w	r0, r0, r0
     108:	3a01      	subs	r2, #1
     10a:	bf28      	it	cs
     10c:	f5b0 0f00 	cmpcs.w	r0, #8388608	; 0x800000
     110:	d2ed      	bcs.n	ee <__addsf3+0x92>
     112:	fab0 fc80 	clz	ip, r0
     116:	f1ac 0c08 	sub.w	ip, ip, #8
     11a:	ebb2 020c 	subs.w	r2, r2, ip
     11e:	fa00 f00c 	lsl.w	r0, r0, ip
     122:	bfaa      	itet	ge
     124:	eb00 50c2 	addge.w	r0, r0, r2, lsl #23
     128:	4252      	neglt	r2, r2
     12a:	4318      	orrge	r0, r3
     12c:	bfbc      	itt	lt
     12e:	40d0      	lsrlt	r0, r2
     130:	4318      	orrlt	r0, r3
     132:	4770      	bx	lr
     134:	f092 0f00 	teq	r2, #0
     138:	f481 0100 	eor.w	r1, r1, #8388608	; 0x800000
     13c:	bf06      	itte	eq
     13e:	f480 0000 	eoreq.w	r0, r0, #8388608	; 0x800000
     142:	3201      	addeq	r2, #1
     144:	3b01      	subne	r3, #1
     146:	e7b5      	b.n	b4 <__addsf3+0x58>
     148:	ea4f 0341 	mov.w	r3, r1, lsl #1
     14c:	ea7f 6c22 	mvns.w	ip, r2, asr #24
     150:	bf18      	it	ne
     152:	ea7f 6c23 	mvnsne.w	ip, r3, asr #24
     156:	d021      	beq.n	19c <__addsf3+0x140>
     158:	ea92 0f03 	teq	r2, r3
     15c:	d004      	beq.n	168 <__addsf3+0x10c>
     15e:	f092 0f00 	teq	r2, #0
     162:	bf08      	it	eq
     164:	4608      	moveq	r0, r1
     166:	4770      	bx	lr
     168:	ea90 0f01 	teq	r0, r1
     16c:	bf1c      	itt	ne
     16e:	2000      	movne	r0, #0
     170:	4770      	bxne	lr
     172:	f012 4f7f 	tst.w	r2, #4278190080	; 0xff000000
     176:	d104      	bne.n	182 <__addsf3+0x126>
     178:	0040      	lsls	r0, r0, #1
     17a:	bf28      	it	cs
     17c:	f040 4000 	orrcs.w	r0, r0, #2147483648	; 0x80000000
     180:	4770      	bx	lr
     182:	f112 7200 	adds.w	r2, r2, #33554432	; 0x2000000
     186:	bf3c      	itt	cc
     188:	f500 0000 	addcc.w	r0, r0, #8388608	; 0x800000
     18c:	4770      	bxcc	lr
     18e:	f000 4300 	and.w	r3, r0, #2147483648	; 0x80000000
     192:	f043 40fe 	orr.w	r0, r3, #2130706432	; 0x7f000000
     196:	f440 0000 	orr.w	r0, r0, #8388608	; 0x800000
     19a:	4770      	bx	lr
     19c:	ea7f 6222 	mvns.w	r2, r2, asr #24
     1a0:	bf16      	itet	ne
     1a2:	4608      	movne	r0, r1
     1a4:	ea7f 6323 	mvnseq.w	r3, r3, asr #24
     1a8:	4601      	movne	r1, r0
     1aa:	0242      	lsls	r2, r0, #9
     1ac:	bf06      	itte	eq
     1ae:	ea5f 2341 	movseq.w	r3, r1, lsl #9
     1b2:	ea90 0f01 	teqeq	r0, r1
     1b6:	f440 0080 	orrne.w	r0, r0, #4194304	; 0x400000
     1ba:	4770      	bx	lr

000001bc <__aeabi_ui2f>:
     1bc:	f04f 0300 	mov.w	r3, #0
     1c0:	e004      	b.n	1cc <__aeabi_i2f+0x8>
     1c2:	bf00      	nop

000001c4 <__aeabi_i2f>:
     1c4:	f010 4300 	ands.w	r3, r0, #2147483648	; 0x80000000
     1c8:	bf48      	it	mi
     1ca:	4240      	negmi	r0, r0
     1cc:	ea5f 0c00 	movs.w	ip, r0
     1d0:	bf08      	it	eq
     1d2:	4770      	bxeq	lr
     1d4:	f043 4396 	orr.w	r3, r3, #1258291200	; 0x4b000000
     1d8:	4601      	mov	r1, r0
     1da:	f04f 0000 	mov.w	r0, #0
     1de:	e01c      	b.n	21a <__aeabi_l2f+0x2a>

000001e0 <__aeabi_ul2f>:
     1e0:	ea50 0201 	orrs.w	r2, r0, r1
     1e4:	bf08      	it	eq
     1e6:	4770      	bxeq	lr
     1e8:	f04f 0300 	mov.w	r3, #0
     1ec:	e00a      	b.n	204 <__aeabi_l2f+0x14>
     1ee:	bf00      	nop

000001f0 <__aeabi_l2f>:
     1f0:	ea50 0201 	orrs.w	r2, r0, r1
     1f4:	bf08      	it	eq
     1f6:	4770      	bxeq	lr
     1f8:	f011 4300 	ands.w	r3, r1, #2147483648	; 0x80000000
     1fc:	d502      	bpl.n	204 <__aeabi_l2f+0x14>
     1fe:	4240      	negs	r0, r0
     200:	eb61 0141 	sbc.w	r1, r1, r1, lsl #1
     204:	ea5f 0c01 	movs.w	ip, r1
     208:	bf02      	ittt	eq
     20a:	4684      	moveq	ip, r0
     20c:	4601      	moveq	r1, r0
     20e:	2000      	moveq	r0, #0
     210:	f043 43b6 	orr.w	r3, r3, #1526726656	; 0x5b000000
     214:	bf08      	it	eq
     216:	f1a3 5380 	subeq.w	r3, r3, #268435456	; 0x10000000
     21a:	f5a3 0300 	sub.w	r3, r3, #8388608	; 0x800000
     21e:	fabc f28c 	clz	r2, ip
     222:	3a08      	subs	r2, #8
     224:	eba3 53c2 	sub.w	r3, r3, r2, lsl #23
     228:	db10      	blt.n	24c <__aeabi_l2f+0x5c>
     22a:	fa01 fc02 	lsl.w	ip, r1, r2
     22e:	4463      	add	r3, ip
     230:	fa00 fc02 	lsl.w	ip, r0, r2
     234:	f1c2 0220 	rsb	r2, r2, #32
     238:	f1bc 4f00 	cmp.w	ip, #2147483648	; 0x80000000
     23c:	fa20 f202 	lsr.w	r2, r0, r2
     240:	eb43 0002 	adc.w	r0, r3, r2
     244:	bf08      	it	eq
     246:	f020 0001 	biceq.w	r0, r0, #1
     24a:	4770      	bx	lr
     24c:	f102 0220 	add.w	r2, r2, #32
     250:	fa01 fc02 	lsl.w	ip, r1, r2
     254:	f1c2 0220 	rsb	r2, r2, #32
     258:	ea50 004c 	orrs.w	r0, r0, ip, lsl #1
     25c:	fa21 f202 	lsr.w	r2, r1, r2
     260:	eb43 0002 	adc.w	r0, r3, r2
     264:	bf08      	it	eq
     266:	ea20 70dc 	biceq.w	r0, r0, ip, lsr #31
     26a:	4770      	bx	lr

0000026c <__gesf2>:
     26c:	f04f 3cff 	mov.w	ip, #4294967295
     270:	e006      	b.n	280 <__cmpsf2+0x4>
     272:	bf00      	nop

00000274 <__lesf2>:
     274:	f04f 0c01 	mov.w	ip, #1
     278:	e002      	b.n	280 <__cmpsf2+0x4>
     27a:	bf00      	nop

0000027c <__cmpsf2>:
     27c:	f04f 0c01 	mov.w	ip, #1
     280:	f84d cd04 	str.w	ip, [sp, #-4]!
     284:	ea4f 0240 	mov.w	r2, r0, lsl #1
     288:	ea4f 0341 	mov.w	r3, r1, lsl #1
     28c:	ea7f 6c22 	mvns.w	ip, r2, asr #24
     290:	bf18      	it	ne
     292:	ea7f 6c23 	mvnsne.w	ip, r3, asr #24
     296:	d011      	beq.n	2bc <__cmpsf2+0x40>
     298:	b001      	add	sp, #4
     29a:	ea52 0c53 	orrs.w	ip, r2, r3, lsr #1
     29e:	bf18      	it	ne
     2a0:	ea90 0f01 	teqne	r0, r1
     2a4:	bf58      	it	pl
     2a6:	ebb2 0003 	subspl.w	r0, r2, r3
     2aa:	bf88      	it	hi
     2ac:	17c8      	asrhi	r0, r1, #31
     2ae:	bf38      	it	cc
     2b0:	ea6f 70e1 	mvncc.w	r0, r1, asr #31
     2b4:	bf18      	it	ne
     2b6:	f040 0001 	orrne.w	r0, r0, #1
     2ba:	4770      	bx	lr
     2bc:	ea7f 6c22 	mvns.w	ip, r2, asr #24
     2c0:	d102      	bne.n	2c8 <__cmpsf2+0x4c>
     2c2:	ea5f 2c40 	movs.w	ip, r0, lsl #9
     2c6:	d105      	bne.n	2d4 <__cmpsf2+0x58>
     2c8:	ea7f 6c23 	mvns.w	ip, r3, asr #24
     2cc:	d1e4      	bne.n	298 <__cmpsf2+0x1c>
     2ce:	ea5f 2c41 	movs.w	ip, r1, lsl #9
     2d2:	d0e1      	beq.n	298 <__cmpsf2+0x1c>
     2d4:	f85d 0b04 	ldr.w	r0, [sp], #4
     2d8:	4770      	bx	lr
     2da:	bf00      	nop

000002dc <__aeabi_cfrcmple>:
     2dc:	4684      	mov	ip, r0
     2de:	4608      	mov	r0, r1
     2e0:	4661      	mov	r1, ip
     2e2:	e7ff      	b.n	2e4 <__aeabi_cfcmpeq>

000002e4 <__aeabi_cfcmpeq>:
     2e4:	b50f      	push	{r0, r1, r2, r3, lr}
     2e6:	f7ff ffc9 	bl	27c <__cmpsf2>
     2ea:	2800      	cmp	r0, #0
     2ec:	bf48      	it	mi
     2ee:	f110 0f00 	cmnmi.w	r0, #0
     2f2:	bd0f      	pop	{r0, r1, r2, r3, pc}

000002f4 <__aeabi_fcmpeq>:
     2f4:	f84d ed08 	str.w	lr, [sp, #-8]!
     2f8:	f7ff fff4 	bl	2e4 <__aeabi_cfcmpeq>
     2fc:	bf0c      	ite	eq
     2fe:	2001      	moveq	r0, #1
     300:	2000      	movne	r0, #0
     302:	f85d fb08 	ldr.w	pc, [sp], #8
     306:	bf00      	nop

00000308 <__aeabi_fcmplt>:
     308:	f84d ed08 	str.w	lr, [sp, #-8]!
     30c:	f7ff ffea 	bl	2e4 <__aeabi_cfcmpeq>
     310:	bf34      	ite	cc
     312:	2001      	movcc	r0, #1
     314:	2000      	movcs	r0, #0
     316:	f85d fb08 	ldr.w	pc, [sp], #8
     31a:	bf00      	nop

0000031c <__aeabi_fcmple>:
     31c:	f84d ed08 	str.w	lr, [sp, #-8]!
     320:	f7ff ffe0 	bl	2e4 <__aeabi_cfcmpeq>
     324:	bf94      	ite	ls
     326:	2001      	movls	r0, #1
     328:	2000      	movhi	r0, #0
     32a:	f85d fb08 	ldr.w	pc, [sp], #8
     32e:	bf00      	nop

00000330 <__aeabi_fcmpge>:
     330:	f84d ed08 	str.w	lr, [sp, #-8]!
     334:	f7ff ffd2 	bl	2dc <__aeabi_cfrcmple>
     338:	bf94      	ite	ls
     33a:	2001      	movls	r0, #1
     33c:	2000      	movhi	r0, #0
     33e:	f85d fb08 	ldr.w	pc, [sp], #8
     342:	bf00      	nop

00000344 <__aeabi_fcmpgt>:
     344:	f84d ed08 	str.w	lr, [sp, #-8]!
     348:	f7ff ffc8 	bl	2dc <__aeabi_cfrcmple>
     34c:	bf34      	ite	cc
     34e:	2001      	movcc	r0, #1
     350:	2000      	movcs	r0, #0
     352:	f85d fb08 	ldr.w	pc, [sp], #8
     356:	bf00      	nop

00000358 <selfrel_offset31>:
     358:	6803      	ldr	r3, [r0, #0]
     35a:	005a      	lsls	r2, r3, #1
     35c:	bf4c      	ite	mi
     35e:	f043 4300 	orrmi.w	r3, r3, #2147483648	; 0x80000000
     362:	f023 4300 	bicpl.w	r3, r3, #2147483648	; 0x80000000
     366:	4418      	add	r0, r3
     368:	4770      	bx	lr
     36a:	bf00      	nop

0000036c <search_EIT_table>:
     36c:	e92d 43f8 	stmdb	sp!, {r3, r4, r5, r6, r7, r8, r9, lr}
     370:	b329      	cbz	r1, 3be <search_EIT_table+0x52>
     372:	1e4f      	subs	r7, r1, #1
     374:	4604      	mov	r4, r0
     376:	4615      	mov	r5, r2
     378:	463e      	mov	r6, r7
     37a:	f04f 0800 	mov.w	r8, #0
     37e:	eb08 0106 	add.w	r1, r8, r6
     382:	eb01 71d1 	add.w	r1, r1, r1, lsr #31
     386:	1049      	asrs	r1, r1, #1
     388:	eb04 09c1 	add.w	r9, r4, r1, lsl #3
     38c:	4648      	mov	r0, r9
     38e:	f7ff ffe3 	bl	358 <selfrel_offset31>
     392:	4603      	mov	r3, r0
     394:	00c8      	lsls	r0, r1, #3
     396:	3008      	adds	r0, #8
     398:	428f      	cmp	r7, r1
     39a:	4420      	add	r0, r4
     39c:	d009      	beq.n	3b2 <search_EIT_table+0x46>
     39e:	42ab      	cmp	r3, r5
     3a0:	d809      	bhi.n	3b6 <search_EIT_table+0x4a>
     3a2:	f7ff ffd9 	bl	358 <selfrel_offset31>
     3a6:	3801      	subs	r0, #1
     3a8:	42a8      	cmp	r0, r5
     3aa:	d20a      	bcs.n	3c2 <search_EIT_table+0x56>
     3ac:	f101 0801 	add.w	r8, r1, #1
     3b0:	e7e5      	b.n	37e <search_EIT_table+0x12>
     3b2:	42ab      	cmp	r3, r5
     3b4:	d905      	bls.n	3c2 <search_EIT_table+0x56>
     3b6:	4588      	cmp	r8, r1
     3b8:	d001      	beq.n	3be <search_EIT_table+0x52>
     3ba:	1e4e      	subs	r6, r1, #1
     3bc:	e7df      	b.n	37e <search_EIT_table+0x12>
     3be:	f04f 0900 	mov.w	r9, #0
     3c2:	4648      	mov	r0, r9
     3c4:	e8bd 83f8 	ldmia.w	sp!, {r3, r4, r5, r6, r7, r8, r9, pc}

000003c8 <__gnu_unwind_get_pr_addr>:
     3c8:	2801      	cmp	r0, #1
     3ca:	d007      	beq.n	3dc <__gnu_unwind_get_pr_addr+0x14>
     3cc:	2802      	cmp	r0, #2
     3ce:	d007      	beq.n	3e0 <__gnu_unwind_get_pr_addr+0x18>
     3d0:	4b04      	ldr	r3, [pc, #16]	; (3e4 <__gnu_unwind_get_pr_addr+0x1c>)
     3d2:	2800      	cmp	r0, #0
     3d4:	bf0c      	ite	eq
     3d6:	4618      	moveq	r0, r3
     3d8:	2000      	movne	r0, #0
     3da:	4770      	bx	lr
     3dc:	4802      	ldr	r0, [pc, #8]	; (3e8 <__gnu_unwind_get_pr_addr+0x20>)
     3de:	4770      	bx	lr
     3e0:	4802      	ldr	r0, [pc, #8]	; (3ec <__gnu_unwind_get_pr_addr+0x24>)
     3e2:	4770      	bx	lr
     3e4:	00000aa1 	andeq	r0, r0, r1, lsr #21
     3e8:	00000aa5 	andeq	r0, r0, r5, lsr #21
     3ec:	00000aa9 	andeq	r0, r0, r9, lsr #21

000003f0 <get_eit_entry>:
     3f0:	b530      	push	{r4, r5, lr}
     3f2:	4b23      	ldr	r3, [pc, #140]	; (480 <get_eit_entry+0x90>)
     3f4:	b083      	sub	sp, #12
     3f6:	4604      	mov	r4, r0
     3f8:	1e8d      	subs	r5, r1, #2
     3fa:	b33b      	cbz	r3, 44c <get_eit_entry+0x5c>
     3fc:	a901      	add	r1, sp, #4
     3fe:	4628      	mov	r0, r5
     400:	f000 f800 	bl	404 <get_eit_entry+0x14>
     404:	b1e8      	cbz	r0, 442 <get_eit_entry+0x52>
     406:	9901      	ldr	r1, [sp, #4]
     408:	462a      	mov	r2, r5
     40a:	f7ff ffaf 	bl	36c <search_EIT_table>
     40e:	4601      	mov	r1, r0
     410:	b1b8      	cbz	r0, 442 <get_eit_entry+0x52>
     412:	f7ff ffa1 	bl	358 <selfrel_offset31>
     416:	684b      	ldr	r3, [r1, #4]
     418:	64a0      	str	r0, [r4, #72]	; 0x48
     41a:	2b01      	cmp	r3, #1
     41c:	d02c      	beq.n	478 <get_eit_entry+0x88>
     41e:	2b00      	cmp	r3, #0
     420:	f101 0004 	add.w	r0, r1, #4
     424:	db24      	blt.n	470 <get_eit_entry+0x80>
     426:	f7ff ff97 	bl	358 <selfrel_offset31>
     42a:	2300      	movs	r3, #0
     42c:	e9c4 0313 	strd	r0, r3, [r4, #76]	; 0x4c
     430:	6803      	ldr	r3, [r0, #0]
     432:	2b00      	cmp	r3, #0
     434:	db11      	blt.n	45a <get_eit_entry+0x6a>
     436:	f7ff ff8f 	bl	358 <selfrel_offset31>
     43a:	6120      	str	r0, [r4, #16]
     43c:	2000      	movs	r0, #0
     43e:	b003      	add	sp, #12
     440:	bd30      	pop	{r4, r5, pc}
     442:	2300      	movs	r3, #0
     444:	2009      	movs	r0, #9
     446:	6123      	str	r3, [r4, #16]
     448:	b003      	add	sp, #12
     44a:	bd30      	pop	{r4, r5, pc}
     44c:	4b0d      	ldr	r3, [pc, #52]	; (484 <get_eit_entry+0x94>)
     44e:	490e      	ldr	r1, [pc, #56]	; (488 <get_eit_entry+0x98>)
     450:	1ac9      	subs	r1, r1, r3
     452:	10c9      	asrs	r1, r1, #3
     454:	4618      	mov	r0, r3
     456:	9101      	str	r1, [sp, #4]
     458:	e7d6      	b.n	408 <get_eit_entry+0x18>
     45a:	f3c3 6003 	ubfx	r0, r3, #24, #4
     45e:	f7ff ffb3 	bl	3c8 <__gnu_unwind_get_pr_addr>
     462:	2800      	cmp	r0, #0
     464:	6120      	str	r0, [r4, #16]
     466:	bf14      	ite	ne
     468:	2000      	movne	r0, #0
     46a:	2009      	moveq	r0, #9
     46c:	b003      	add	sp, #12
     46e:	bd30      	pop	{r4, r5, pc}
     470:	2301      	movs	r3, #1
     472:	e9c4 0313 	strd	r0, r3, [r4, #76]	; 0x4c
     476:	e7db      	b.n	430 <get_eit_entry+0x40>
     478:	2300      	movs	r3, #0
     47a:	6123      	str	r3, [r4, #16]
     47c:	2005      	movs	r0, #5
     47e:	e7de      	b.n	43e <get_eit_entry+0x4e>
     480:	00000000 	andeq	r0, r0, r0
     484:	000015d8 	ldrdeq	r1, [r0], -r8
     488:	00001718 	andeq	r1, r0, r8, lsl r7

0000048c <restore_non_core_regs>:
     48c:	6803      	ldr	r3, [r0, #0]
     48e:	07da      	lsls	r2, r3, #31
     490:	b510      	push	{r4, lr}
     492:	4604      	mov	r4, r0
     494:	d406      	bmi.n	4a4 <restore_non_core_regs+0x18>
     496:	079b      	lsls	r3, r3, #30
     498:	f100 0048 	add.w	r0, r0, #72	; 0x48
     49c:	d509      	bpl.n	4b2 <restore_non_core_regs+0x26>
     49e:	f000 fc5b 	bl	d58 <__gnu_Unwind_Restore_VFP_D>
     4a2:	6823      	ldr	r3, [r4, #0]
     4a4:	0759      	lsls	r1, r3, #29
     4a6:	d509      	bpl.n	4bc <restore_non_core_regs+0x30>
     4a8:	071a      	lsls	r2, r3, #28
     4aa:	d50e      	bpl.n	4ca <restore_non_core_regs+0x3e>
     4ac:	06db      	lsls	r3, r3, #27
     4ae:	d513      	bpl.n	4d8 <restore_non_core_regs+0x4c>
     4b0:	bd10      	pop	{r4, pc}
     4b2:	f000 fc49 	bl	d48 <__gnu_Unwind_Restore_VFP>
     4b6:	6823      	ldr	r3, [r4, #0]
     4b8:	0759      	lsls	r1, r3, #29
     4ba:	d4f5      	bmi.n	4a8 <restore_non_core_regs+0x1c>
     4bc:	f104 00d0 	add.w	r0, r4, #208	; 0xd0
     4c0:	f000 fc52 	bl	d68 <__gnu_Unwind_Restore_VFP_D_16_to_31>
     4c4:	6823      	ldr	r3, [r4, #0]
     4c6:	071a      	lsls	r2, r3, #28
     4c8:	d4f0      	bmi.n	4ac <restore_non_core_regs+0x20>
     4ca:	f504 70a8 	add.w	r0, r4, #336	; 0x150
     4ce:	f000 fc53 	bl	d78 <__gnu_Unwind_Restore_WMMXD>
     4d2:	6823      	ldr	r3, [r4, #0]
     4d4:	06db      	lsls	r3, r3, #27
     4d6:	d4eb      	bmi.n	4b0 <restore_non_core_regs+0x24>
     4d8:	f504 70e8 	add.w	r0, r4, #464	; 0x1d0
     4dc:	e8bd 4010 	ldmia.w	sp!, {r4, lr}
     4e0:	f000 bc8e 	b.w	e00 <__gnu_Unwind_Restore_WMMXC>

000004e4 <__gnu_unwind_24bit.constprop.0>:
     4e4:	2009      	movs	r0, #9
     4e6:	4770      	bx	lr

000004e8 <_Unwind_decode_typeinfo_ptr.constprop.0>:
     4e8:	4603      	mov	r3, r0
     4ea:	6800      	ldr	r0, [r0, #0]
     4ec:	b100      	cbz	r0, 4f0 <_Unwind_decode_typeinfo_ptr.constprop.0+0x8>
     4ee:	4418      	add	r0, r3
     4f0:	4770      	bx	lr
     4f2:	bf00      	nop

000004f4 <_Unwind_DebugHook>:
     4f4:	4770      	bx	lr
     4f6:	bf00      	nop

000004f8 <unwind_phase2>:
     4f8:	b570      	push	{r4, r5, r6, lr}
     4fa:	4604      	mov	r4, r0
     4fc:	460e      	mov	r6, r1
     4fe:	6c31      	ldr	r1, [r6, #64]	; 0x40
     500:	4620      	mov	r0, r4
     502:	f7ff ff75 	bl	3f0 <get_eit_entry>
     506:	4605      	mov	r5, r0
     508:	b988      	cbnz	r0, 52e <unwind_phase2+0x36>
     50a:	6c32      	ldr	r2, [r6, #64]	; 0x40
     50c:	6162      	str	r2, [r4, #20]
     50e:	6923      	ldr	r3, [r4, #16]
     510:	4632      	mov	r2, r6
     512:	4621      	mov	r1, r4
     514:	2001      	movs	r0, #1
     516:	4798      	blx	r3
     518:	2808      	cmp	r0, #8
     51a:	d0f0      	beq.n	4fe <unwind_phase2+0x6>
     51c:	2807      	cmp	r0, #7
     51e:	d106      	bne.n	52e <unwind_phase2+0x36>
     520:	4628      	mov	r0, r5
     522:	6c31      	ldr	r1, [r6, #64]	; 0x40
     524:	f7ff ffe6 	bl	4f4 <_Unwind_DebugHook>
     528:	1d30      	adds	r0, r6, #4
     52a:	f000 fc01 	bl	d30 <__restore_core_regs>
     52e:	f000 ffe5 	bl	14fc <abort>
     532:	bf00      	nop

00000534 <unwind_phase2_forced>:
     534:	e92d 47f0 	stmdb	sp!, {r4, r5, r6, r7, r8, r9, sl, lr}
     538:	1d0d      	adds	r5, r1, #4
     53a:	f8d0 800c 	ldr.w	r8, [r0, #12]
     53e:	f8d0 9018 	ldr.w	r9, [r0, #24]
     542:	4607      	mov	r7, r0
     544:	4614      	mov	r4, r2
     546:	cd0f      	ldmia	r5!, {r0, r1, r2, r3}
     548:	f5ad 7d72 	sub.w	sp, sp, #968	; 0x3c8
     54c:	f10d 0c0c 	add.w	ip, sp, #12
     550:	e8ac 000f 	stmia.w	ip!, {r0, r1, r2, r3}
     554:	cd0f      	ldmia	r5!, {r0, r1, r2, r3}
     556:	e8ac 000f 	stmia.w	ip!, {r0, r1, r2, r3}
     55a:	cd0f      	ldmia	r5!, {r0, r1, r2, r3}
     55c:	e8ac 000f 	stmia.w	ip!, {r0, r1, r2, r3}
     560:	e895 000f 	ldmia.w	r5, {r0, r1, r2, r3}
     564:	ae02      	add	r6, sp, #8
     566:	f04f 0e00 	mov.w	lr, #0
     56a:	e88c 000f 	stmia.w	ip, {r0, r1, r2, r3}
     56e:	f8c6 e000 	str.w	lr, [r6]
     572:	e020      	b.n	5b6 <unwind_phase2_forced+0x82>
     574:	6c33      	ldr	r3, [r6, #64]	; 0x40
     576:	617b      	str	r3, [r7, #20]
     578:	f44f 72f0 	mov.w	r2, #480	; 0x1e0
     57c:	4631      	mov	r1, r6
     57e:	a87a      	add	r0, sp, #488	; 0x1e8
     580:	f000 fcac 	bl	edc <memcpy>
     584:	693b      	ldr	r3, [r7, #16]
     586:	aa7a      	add	r2, sp, #488	; 0x1e8
     588:	4639      	mov	r1, r7
     58a:	4650      	mov	r0, sl
     58c:	4798      	blx	r3
     58e:	9b88      	ldr	r3, [sp, #544]	; 0x220
     590:	6473      	str	r3, [r6, #68]	; 0x44
     592:	4621      	mov	r1, r4
     594:	e9cd 6900 	strd	r6, r9, [sp]
     598:	4605      	mov	r5, r0
     59a:	463b      	mov	r3, r7
     59c:	463a      	mov	r2, r7
     59e:	2001      	movs	r0, #1
     5a0:	47c0      	blx	r8
     5a2:	4604      	mov	r4, r0
     5a4:	b9e0      	cbnz	r0, 5e0 <unwind_phase2_forced+0xac>
     5a6:	f44f 72f0 	mov.w	r2, #480	; 0x1e0
     5aa:	a97a      	add	r1, sp, #488	; 0x1e8
     5ac:	4630      	mov	r0, r6
     5ae:	f000 fc95 	bl	edc <memcpy>
     5b2:	2d08      	cmp	r5, #8
     5b4:	d11a      	bne.n	5ec <unwind_phase2_forced+0xb8>
     5b6:	6c31      	ldr	r1, [r6, #64]	; 0x40
     5b8:	4638      	mov	r0, r7
     5ba:	f7ff ff19 	bl	3f0 <get_eit_entry>
     5be:	3409      	adds	r4, #9
     5c0:	fa5f fa84 	uxtb.w	sl, r4
     5c4:	4605      	mov	r5, r0
     5c6:	2800      	cmp	r0, #0
     5c8:	d0d4      	beq.n	574 <unwind_phase2_forced+0x40>
     5ca:	6bb3      	ldr	r3, [r6, #56]	; 0x38
     5cc:	6473      	str	r3, [r6, #68]	; 0x44
     5ce:	463a      	mov	r2, r7
     5d0:	e9cd 6900 	strd	r6, r9, [sp]
     5d4:	463b      	mov	r3, r7
     5d6:	f04a 0110 	orr.w	r1, sl, #16
     5da:	2001      	movs	r0, #1
     5dc:	47c0      	blx	r8
     5de:	b100      	cbz	r0, 5e2 <unwind_phase2_forced+0xae>
     5e0:	2509      	movs	r5, #9
     5e2:	4628      	mov	r0, r5
     5e4:	f50d 7d72 	add.w	sp, sp, #968	; 0x3c8
     5e8:	e8bd 87f0 	ldmia.w	sp!, {r4, r5, r6, r7, r8, r9, sl, pc}
     5ec:	2d07      	cmp	r5, #7
     5ee:	d1f7      	bne.n	5e0 <unwind_phase2_forced+0xac>
     5f0:	4620      	mov	r0, r4
     5f2:	6c31      	ldr	r1, [r6, #64]	; 0x40
     5f4:	f7ff ff7e 	bl	4f4 <_Unwind_DebugHook>
     5f8:	a803      	add	r0, sp, #12
     5fa:	f000 fb99 	bl	d30 <__restore_core_regs>
     5fe:	bf00      	nop

00000600 <_Unwind_GetCFA>:
     600:	6c40      	ldr	r0, [r0, #68]	; 0x44
     602:	4770      	bx	lr

00000604 <__gnu_Unwind_RaiseException>:
     604:	b5f0      	push	{r4, r5, r6, r7, lr}
     606:	6bcb      	ldr	r3, [r1, #60]	; 0x3c
     608:	640b      	str	r3, [r1, #64]	; 0x40
     60a:	f101 0c04 	add.w	ip, r1, #4
     60e:	460e      	mov	r6, r1
     610:	4605      	mov	r5, r0
     612:	e8bc 000f 	ldmia.w	ip!, {r0, r1, r2, r3}
     616:	b0f9      	sub	sp, #484	; 0x1e4
     618:	ac01      	add	r4, sp, #4
     61a:	c40f      	stmia	r4!, {r0, r1, r2, r3}
     61c:	e8bc 000f 	ldmia.w	ip!, {r0, r1, r2, r3}
     620:	c40f      	stmia	r4!, {r0, r1, r2, r3}
     622:	e8bc 000f 	ldmia.w	ip!, {r0, r1, r2, r3}
     626:	c40f      	stmia	r4!, {r0, r1, r2, r3}
     628:	e89c 000f 	ldmia.w	ip, {r0, r1, r2, r3}
     62c:	f04f 37ff 	mov.w	r7, #4294967295
     630:	e884 000f 	stmia.w	r4, {r0, r1, r2, r3}
     634:	9700      	str	r7, [sp, #0]
     636:	e006      	b.n	646 <__gnu_Unwind_RaiseException+0x42>
     638:	692b      	ldr	r3, [r5, #16]
     63a:	466a      	mov	r2, sp
     63c:	4629      	mov	r1, r5
     63e:	4798      	blx	r3
     640:	2808      	cmp	r0, #8
     642:	4604      	mov	r4, r0
     644:	d108      	bne.n	658 <__gnu_Unwind_RaiseException+0x54>
     646:	9910      	ldr	r1, [sp, #64]	; 0x40
     648:	4628      	mov	r0, r5
     64a:	f7ff fed1 	bl	3f0 <get_eit_entry>
     64e:	2800      	cmp	r0, #0
     650:	d0f2      	beq.n	638 <__gnu_Unwind_RaiseException+0x34>
     652:	2009      	movs	r0, #9
     654:	b079      	add	sp, #484	; 0x1e4
     656:	bdf0      	pop	{r4, r5, r6, r7, pc}
     658:	4668      	mov	r0, sp
     65a:	f7ff ff17 	bl	48c <restore_non_core_regs>
     65e:	2c06      	cmp	r4, #6
     660:	d1f7      	bne.n	652 <__gnu_Unwind_RaiseException+0x4e>
     662:	4631      	mov	r1, r6
     664:	4628      	mov	r0, r5
     666:	f7ff ff47 	bl	4f8 <unwind_phase2>
     66a:	bf00      	nop

0000066c <__gnu_Unwind_ForcedUnwind>:
     66c:	60c1      	str	r1, [r0, #12]
     66e:	6bd9      	ldr	r1, [r3, #60]	; 0x3c
     670:	6182      	str	r2, [r0, #24]
     672:	6419      	str	r1, [r3, #64]	; 0x40
     674:	2200      	movs	r2, #0
     676:	4619      	mov	r1, r3
     678:	e75c      	b.n	534 <unwind_phase2_forced>
     67a:	bf00      	nop

0000067c <__gnu_Unwind_Resume>:
     67c:	b570      	push	{r4, r5, r6, lr}
     67e:	68c6      	ldr	r6, [r0, #12]
     680:	6943      	ldr	r3, [r0, #20]
     682:	640b      	str	r3, [r1, #64]	; 0x40
     684:	b9ae      	cbnz	r6, 6b2 <__gnu_Unwind_Resume+0x36>
     686:	6903      	ldr	r3, [r0, #16]
     688:	460a      	mov	r2, r1
     68a:	4604      	mov	r4, r0
     68c:	460d      	mov	r5, r1
     68e:	4601      	mov	r1, r0
     690:	2002      	movs	r0, #2
     692:	4798      	blx	r3
     694:	2807      	cmp	r0, #7
     696:	d005      	beq.n	6a4 <__gnu_Unwind_Resume+0x28>
     698:	2808      	cmp	r0, #8
     69a:	d10f      	bne.n	6bc <__gnu_Unwind_Resume+0x40>
     69c:	4629      	mov	r1, r5
     69e:	4620      	mov	r0, r4
     6a0:	f7ff ff2a 	bl	4f8 <unwind_phase2>
     6a4:	4630      	mov	r0, r6
     6a6:	6c29      	ldr	r1, [r5, #64]	; 0x40
     6a8:	f7ff ff24 	bl	4f4 <_Unwind_DebugHook>
     6ac:	1d28      	adds	r0, r5, #4
     6ae:	f000 fb3f 	bl	d30 <__restore_core_regs>
     6b2:	2201      	movs	r2, #1
     6b4:	f7ff ff3e 	bl	534 <unwind_phase2_forced>
     6b8:	f000 ff20 	bl	14fc <abort>
     6bc:	f000 ff1e 	bl	14fc <abort>

000006c0 <__gnu_Unwind_Resume_or_Rethrow>:
     6c0:	68c2      	ldr	r2, [r0, #12]
     6c2:	b11a      	cbz	r2, 6cc <__gnu_Unwind_Resume_or_Rethrow+0xc>
     6c4:	6bca      	ldr	r2, [r1, #60]	; 0x3c
     6c6:	640a      	str	r2, [r1, #64]	; 0x40
     6c8:	2200      	movs	r2, #0
     6ca:	e733      	b.n	534 <unwind_phase2_forced>
     6cc:	e79a      	b.n	604 <__gnu_Unwind_RaiseException>
     6ce:	bf00      	nop

000006d0 <_Unwind_Complete>:
     6d0:	4770      	bx	lr
     6d2:	bf00      	nop

000006d4 <_Unwind_DeleteException>:
     6d4:	6883      	ldr	r3, [r0, #8]
     6d6:	4601      	mov	r1, r0
     6d8:	b10b      	cbz	r3, 6de <_Unwind_DeleteException+0xa>
     6da:	2001      	movs	r0, #1
     6dc:	4718      	bx	r3
     6de:	4770      	bx	lr

000006e0 <_Unwind_VRS_Get>:
     6e0:	2901      	cmp	r1, #1
     6e2:	d012      	beq.n	70a <_Unwind_VRS_Get+0x2a>
     6e4:	d809      	bhi.n	6fa <_Unwind_VRS_Get+0x1a>
     6e6:	b973      	cbnz	r3, 706 <_Unwind_VRS_Get+0x26>
     6e8:	2a0f      	cmp	r2, #15
     6ea:	d80c      	bhi.n	706 <_Unwind_VRS_Get+0x26>
     6ec:	eb00 0282 	add.w	r2, r0, r2, lsl #2
     6f0:	4618      	mov	r0, r3
     6f2:	6853      	ldr	r3, [r2, #4]
     6f4:	9a00      	ldr	r2, [sp, #0]
     6f6:	6013      	str	r3, [r2, #0]
     6f8:	4770      	bx	lr
     6fa:	3903      	subs	r1, #3
     6fc:	2901      	cmp	r1, #1
     6fe:	bf94      	ite	ls
     700:	2001      	movls	r0, #1
     702:	2002      	movhi	r0, #2
     704:	4770      	bx	lr
     706:	2002      	movs	r0, #2
     708:	4770      	bx	lr
     70a:	4608      	mov	r0, r1
     70c:	4770      	bx	lr
     70e:	bf00      	nop

00000710 <_Unwind_GetGR>:
     710:	b500      	push	{lr}
     712:	b085      	sub	sp, #20
     714:	460a      	mov	r2, r1
     716:	2300      	movs	r3, #0
     718:	a903      	add	r1, sp, #12
     71a:	9100      	str	r1, [sp, #0]
     71c:	4619      	mov	r1, r3
     71e:	f7ff ffdf 	bl	6e0 <_Unwind_VRS_Get>
     722:	9803      	ldr	r0, [sp, #12]
     724:	b005      	add	sp, #20
     726:	f85d fb04 	ldr.w	pc, [sp], #4
     72a:	bf00      	nop

0000072c <_Unwind_VRS_Set>:
     72c:	2901      	cmp	r1, #1
     72e:	d012      	beq.n	756 <_Unwind_VRS_Set+0x2a>
     730:	d809      	bhi.n	746 <_Unwind_VRS_Set+0x1a>
     732:	b973      	cbnz	r3, 752 <_Unwind_VRS_Set+0x26>
     734:	2a0f      	cmp	r2, #15
     736:	d80c      	bhi.n	752 <_Unwind_VRS_Set+0x26>
     738:	eb00 0082 	add.w	r0, r0, r2, lsl #2
     73c:	9a00      	ldr	r2, [sp, #0]
     73e:	6812      	ldr	r2, [r2, #0]
     740:	6042      	str	r2, [r0, #4]
     742:	4618      	mov	r0, r3
     744:	4770      	bx	lr
     746:	3903      	subs	r1, #3
     748:	2901      	cmp	r1, #1
     74a:	bf94      	ite	ls
     74c:	2001      	movls	r0, #1
     74e:	2002      	movhi	r0, #2
     750:	4770      	bx	lr
     752:	2002      	movs	r0, #2
     754:	4770      	bx	lr
     756:	4608      	mov	r0, r1
     758:	4770      	bx	lr
     75a:	bf00      	nop

0000075c <_Unwind_SetGR>:
     75c:	b510      	push	{r4, lr}
     75e:	b084      	sub	sp, #16
     760:	2300      	movs	r3, #0
     762:	ac03      	add	r4, sp, #12
     764:	9203      	str	r2, [sp, #12]
     766:	9400      	str	r4, [sp, #0]
     768:	460a      	mov	r2, r1
     76a:	4619      	mov	r1, r3
     76c:	f7ff ffde 	bl	72c <_Unwind_VRS_Set>
     770:	b004      	add	sp, #16
     772:	bd10      	pop	{r4, pc}

00000774 <__gnu_Unwind_Backtrace>:
     774:	b570      	push	{r4, r5, r6, lr}
     776:	6bd3      	ldr	r3, [r2, #60]	; 0x3c
     778:	6413      	str	r3, [r2, #64]	; 0x40
     77a:	f102 0c04 	add.w	ip, r2, #4
     77e:	4605      	mov	r5, r0
     780:	460c      	mov	r4, r1
     782:	e8bc 000f 	ldmia.w	ip!, {r0, r1, r2, r3}
     786:	f5ad 7d0e 	sub.w	sp, sp, #568	; 0x238
     78a:	f10d 0e5c 	add.w	lr, sp, #92	; 0x5c
     78e:	e8ae 000f 	stmia.w	lr!, {r0, r1, r2, r3}
     792:	e8bc 000f 	ldmia.w	ip!, {r0, r1, r2, r3}
     796:	e8ae 000f 	stmia.w	lr!, {r0, r1, r2, r3}
     79a:	e8bc 000f 	ldmia.w	ip!, {r0, r1, r2, r3}
     79e:	e8ae 000f 	stmia.w	lr!, {r0, r1, r2, r3}
     7a2:	e89c 000f 	ldmia.w	ip, {r0, r1, r2, r3}
     7a6:	f04f 36ff 	mov.w	r6, #4294967295
     7aa:	e88e 000f 	stmia.w	lr, {r0, r1, r2, r3}
     7ae:	9616      	str	r6, [sp, #88]	; 0x58
     7b0:	e010      	b.n	7d4 <__gnu_Unwind_Backtrace+0x60>
     7b2:	f7ff ffd3 	bl	75c <_Unwind_SetGR>
     7b6:	4621      	mov	r1, r4
     7b8:	a816      	add	r0, sp, #88	; 0x58
     7ba:	47a8      	blx	r5
     7bc:	4603      	mov	r3, r0
     7be:	aa16      	add	r2, sp, #88	; 0x58
     7c0:	4669      	mov	r1, sp
     7c2:	2008      	movs	r0, #8
     7c4:	b983      	cbnz	r3, 7e8 <__gnu_Unwind_Backtrace+0x74>
     7c6:	9b04      	ldr	r3, [sp, #16]
     7c8:	4798      	blx	r3
     7ca:	2805      	cmp	r0, #5
     7cc:	4606      	mov	r6, r0
     7ce:	d00c      	beq.n	7ea <__gnu_Unwind_Backtrace+0x76>
     7d0:	2809      	cmp	r0, #9
     7d2:	d009      	beq.n	7e8 <__gnu_Unwind_Backtrace+0x74>
     7d4:	9926      	ldr	r1, [sp, #152]	; 0x98
     7d6:	4668      	mov	r0, sp
     7d8:	f7ff fe0a 	bl	3f0 <get_eit_entry>
     7dc:	4603      	mov	r3, r0
     7de:	466a      	mov	r2, sp
     7e0:	210c      	movs	r1, #12
     7e2:	a816      	add	r0, sp, #88	; 0x58
     7e4:	2b00      	cmp	r3, #0
     7e6:	d0e4      	beq.n	7b2 <__gnu_Unwind_Backtrace+0x3e>
     7e8:	2609      	movs	r6, #9
     7ea:	a816      	add	r0, sp, #88	; 0x58
     7ec:	f7ff fe4e 	bl	48c <restore_non_core_regs>
     7f0:	4630      	mov	r0, r6
     7f2:	f50d 7d0e 	add.w	sp, sp, #568	; 0x238
     7f6:	bd70      	pop	{r4, r5, r6, pc}

000007f8 <__gnu_unwind_pr_common>:
     7f8:	e92d 4ff0 	stmdb	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, lr}
     7fc:	6ccc      	ldr	r4, [r1, #76]	; 0x4c
     7fe:	b089      	sub	sp, #36	; 0x24
     800:	461e      	mov	r6, r3
     802:	f854 3b04 	ldr.w	r3, [r4], #4
     806:	9406      	str	r4, [sp, #24]
     808:	460d      	mov	r5, r1
     80a:	4617      	mov	r7, r2
     80c:	f000 0803 	and.w	r8, r0, #3
     810:	2e00      	cmp	r6, #0
     812:	d079      	beq.n	908 <__gnu_unwind_pr_common+0x110>
     814:	0c1a      	lsrs	r2, r3, #16
     816:	041b      	lsls	r3, r3, #16
     818:	9305      	str	r3, [sp, #20]
     81a:	f88d 201d 	strb.w	r2, [sp, #29]
     81e:	2302      	movs	r3, #2
     820:	b2d2      	uxtb	r2, r2
     822:	eb04 0482 	add.w	r4, r4, r2, lsl #2
     826:	f88d 301c 	strb.w	r3, [sp, #28]
     82a:	6d2b      	ldr	r3, [r5, #80]	; 0x50
     82c:	f1b8 0f02 	cmp.w	r8, #2
     830:	bf08      	it	eq
     832:	6bac      	ldreq	r4, [r5, #56]	; 0x38
     834:	f013 0301 	ands.w	r3, r3, #1
     838:	d00c      	beq.n	854 <__gnu_unwind_pr_common+0x5c>
     83a:	a905      	add	r1, sp, #20
     83c:	4638      	mov	r0, r7
     83e:	f000 fc13 	bl	1068 <__gnu_unwind_execute>
     842:	b918      	cbnz	r0, 84c <__gnu_unwind_pr_common+0x54>
     844:	2008      	movs	r0, #8
     846:	b009      	add	sp, #36	; 0x24
     848:	e8bd 8ff0 	ldmia.w	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, pc}
     84c:	2009      	movs	r0, #9
     84e:	b009      	add	sp, #36	; 0x24
     850:	e8bd 8ff0 	ldmia.w	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, pc}
     854:	f8d4 a000 	ldr.w	sl, [r4]
     858:	f1ba 0f00 	cmp.w	sl, #0
     85c:	d0ed      	beq.n	83a <__gnu_unwind_pr_common+0x42>
     85e:	9301      	str	r3, [sp, #4]
     860:	f000 0308 	and.w	r3, r0, #8
     864:	9302      	str	r3, [sp, #8]
     866:	2e02      	cmp	r6, #2
     868:	d04a      	beq.n	900 <__gnu_unwind_pr_common+0x108>
     86a:	f8b4 a000 	ldrh.w	sl, [r4]
     86e:	f8b4 9002 	ldrh.w	r9, [r4, #2]
     872:	3404      	adds	r4, #4
     874:	6cab      	ldr	r3, [r5, #72]	; 0x48
     876:	f029 0b01 	bic.w	fp, r9, #1
     87a:	210f      	movs	r1, #15
     87c:	4638      	mov	r0, r7
     87e:	449b      	add	fp, r3
     880:	f7ff ff46 	bl	710 <_Unwind_GetGR>
     884:	4583      	cmp	fp, r0
     886:	d839      	bhi.n	8fc <__gnu_unwind_pr_common+0x104>
     888:	f02a 0301 	bic.w	r3, sl, #1
     88c:	449b      	add	fp, r3
     88e:	4583      	cmp	fp, r0
     890:	bf94      	ite	ls
     892:	2000      	movls	r0, #0
     894:	2001      	movhi	r0, #1
     896:	ea4f 0349 	mov.w	r3, r9, lsl #1
     89a:	f003 0302 	and.w	r3, r3, #2
     89e:	f00a 0a01 	and.w	sl, sl, #1
     8a2:	ea43 030a 	orr.w	r3, r3, sl
     8a6:	2b01      	cmp	r3, #1
     8a8:	d049      	beq.n	93e <__gnu_unwind_pr_common+0x146>
     8aa:	2b02      	cmp	r3, #2
     8ac:	d032      	beq.n	914 <__gnu_unwind_pr_common+0x11c>
     8ae:	2b00      	cmp	r3, #0
     8b0:	d1cc      	bne.n	84c <__gnu_unwind_pr_common+0x54>
     8b2:	f1b8 0f00 	cmp.w	r8, #0
     8b6:	d002      	beq.n	8be <__gnu_unwind_pr_common+0xc6>
     8b8:	2800      	cmp	r0, #0
     8ba:	f040 80cd 	bne.w	a58 <__gnu_unwind_pr_common+0x260>
     8be:	3404      	adds	r4, #4
     8c0:	f8d4 a000 	ldr.w	sl, [r4]
     8c4:	f1ba 0f00 	cmp.w	sl, #0
     8c8:	d1cd      	bne.n	866 <__gnu_unwind_pr_common+0x6e>
     8ca:	a905      	add	r1, sp, #20
     8cc:	4638      	mov	r0, r7
     8ce:	f000 fbcb 	bl	1068 <__gnu_unwind_execute>
     8d2:	2800      	cmp	r0, #0
     8d4:	d1ba      	bne.n	84c <__gnu_unwind_pr_common+0x54>
     8d6:	9b01      	ldr	r3, [sp, #4]
     8d8:	2b00      	cmp	r3, #0
     8da:	d0b3      	beq.n	844 <__gnu_unwind_pr_common+0x4c>
     8dc:	210f      	movs	r1, #15
     8de:	4638      	mov	r0, r7
     8e0:	f7ff ff16 	bl	710 <_Unwind_GetGR>
     8e4:	210e      	movs	r1, #14
     8e6:	4602      	mov	r2, r0
     8e8:	4638      	mov	r0, r7
     8ea:	f7ff ff37 	bl	75c <_Unwind_SetGR>
     8ee:	4638      	mov	r0, r7
     8f0:	4a6a      	ldr	r2, [pc, #424]	; (a9c <__gnu_unwind_pr_common+0x2a4>)
     8f2:	210f      	movs	r1, #15
     8f4:	f7ff ff32 	bl	75c <_Unwind_SetGR>
     8f8:	2007      	movs	r0, #7
     8fa:	e7a8      	b.n	84e <__gnu_unwind_pr_common+0x56>
     8fc:	2000      	movs	r0, #0
     8fe:	e7ca      	b.n	896 <__gnu_unwind_pr_common+0x9e>
     900:	f8d4 9004 	ldr.w	r9, [r4, #4]
     904:	3408      	adds	r4, #8
     906:	e7b5      	b.n	874 <__gnu_unwind_pr_common+0x7c>
     908:	021b      	lsls	r3, r3, #8
     90a:	9305      	str	r3, [sp, #20]
     90c:	2303      	movs	r3, #3
     90e:	f8ad 301c 	strh.w	r3, [sp, #28]
     912:	e78a      	b.n	82a <__gnu_unwind_pr_common+0x32>
     914:	6823      	ldr	r3, [r4, #0]
     916:	f023 4b00 	bic.w	fp, r3, #2147483648	; 0x80000000
     91a:	f1b8 0f00 	cmp.w	r8, #0
     91e:	d145      	bne.n	9ac <__gnu_unwind_pr_common+0x1b4>
     920:	b128      	cbz	r0, 92e <__gnu_unwind_pr_common+0x136>
     922:	9a02      	ldr	r2, [sp, #8]
     924:	2a00      	cmp	r2, #0
     926:	d05c      	beq.n	9e2 <__gnu_unwind_pr_common+0x1ea>
     928:	f1bb 0f00 	cmp.w	fp, #0
     92c:	d074      	beq.n	a18 <__gnu_unwind_pr_common+0x220>
     92e:	2b00      	cmp	r3, #0
     930:	da00      	bge.n	934 <__gnu_unwind_pr_common+0x13c>
     932:	3404      	adds	r4, #4
     934:	f10b 0b01 	add.w	fp, fp, #1
     938:	eb04 048b 	add.w	r4, r4, fp, lsl #2
     93c:	e7c0      	b.n	8c0 <__gnu_unwind_pr_common+0xc8>
     93e:	f1b8 0f00 	cmp.w	r8, #0
     942:	d119      	bne.n	978 <__gnu_unwind_pr_common+0x180>
     944:	b1b0      	cbz	r0, 974 <__gnu_unwind_pr_common+0x17c>
     946:	6863      	ldr	r3, [r4, #4]
     948:	6822      	ldr	r2, [r4, #0]
     94a:	1c99      	adds	r1, r3, #2
     94c:	ea4f 72d2 	mov.w	r2, r2, lsr #31
     950:	f43f af7c 	beq.w	84c <__gnu_unwind_pr_common+0x54>
     954:	f105 0158 	add.w	r1, r5, #88	; 0x58
     958:	3301      	adds	r3, #1
     95a:	9104      	str	r1, [sp, #16]
     95c:	f000 8090 	beq.w	a80 <__gnu_unwind_pr_common+0x288>
     960:	1d20      	adds	r0, r4, #4
     962:	f7ff fdc1 	bl	4e8 <_Unwind_decode_typeinfo_ptr.constprop.0>
     966:	ab04      	add	r3, sp, #16
     968:	4601      	mov	r1, r0
     96a:	4628      	mov	r0, r5
     96c:	f000 f800 	bl	970 <__gnu_unwind_pr_common+0x178>
     970:	2800      	cmp	r0, #0
     972:	d15b      	bne.n	a2c <__gnu_unwind_pr_common+0x234>
     974:	3408      	adds	r4, #8
     976:	e7a3      	b.n	8c0 <__gnu_unwind_pr_common+0xc8>
     978:	210d      	movs	r1, #13
     97a:	4638      	mov	r0, r7
     97c:	f8d5 9020 	ldr.w	r9, [r5, #32]
     980:	f7ff fec6 	bl	710 <_Unwind_GetGR>
     984:	4581      	cmp	r9, r0
     986:	d1f5      	bne.n	974 <__gnu_unwind_pr_common+0x17c>
     988:	6aab      	ldr	r3, [r5, #40]	; 0x28
     98a:	429c      	cmp	r4, r3
     98c:	d1f2      	bne.n	974 <__gnu_unwind_pr_common+0x17c>
     98e:	4620      	mov	r0, r4
     990:	f7ff fce2 	bl	358 <selfrel_offset31>
     994:	210f      	movs	r1, #15
     996:	4602      	mov	r2, r0
     998:	4638      	mov	r0, r7
     99a:	f7ff fedf 	bl	75c <_Unwind_SetGR>
     99e:	4638      	mov	r0, r7
     9a0:	462a      	mov	r2, r5
     9a2:	2100      	movs	r1, #0
     9a4:	f7ff feda 	bl	75c <_Unwind_SetGR>
     9a8:	2007      	movs	r0, #7
     9aa:	e750      	b.n	84e <__gnu_unwind_pr_common+0x56>
     9ac:	210d      	movs	r1, #13
     9ae:	4638      	mov	r0, r7
     9b0:	f8d5 9020 	ldr.w	r9, [r5, #32]
     9b4:	f7ff feac 	bl	710 <_Unwind_GetGR>
     9b8:	4581      	cmp	r9, r0
     9ba:	d001      	beq.n	9c0 <__gnu_unwind_pr_common+0x1c8>
     9bc:	6823      	ldr	r3, [r4, #0]
     9be:	e7b6      	b.n	92e <__gnu_unwind_pr_common+0x136>
     9c0:	6aab      	ldr	r3, [r5, #40]	; 0x28
     9c2:	429c      	cmp	r4, r3
     9c4:	d1fa      	bne.n	9bc <__gnu_unwind_pr_common+0x1c4>
     9c6:	2304      	movs	r3, #4
     9c8:	2200      	movs	r2, #0
     9ca:	e9c5 230b 	strd	r2, r3, [r5, #44]	; 0x2c
     9ce:	18e3      	adds	r3, r4, r3
     9d0:	f8c5 b028 	str.w	fp, [r5, #40]	; 0x28
     9d4:	636b      	str	r3, [r5, #52]	; 0x34
     9d6:	6823      	ldr	r3, [r4, #0]
     9d8:	2b00      	cmp	r3, #0
     9da:	db59      	blt.n	a90 <__gnu_unwind_pr_common+0x298>
     9dc:	2301      	movs	r3, #1
     9de:	9301      	str	r3, [sp, #4]
     9e0:	e7a8      	b.n	934 <__gnu_unwind_pr_common+0x13c>
     9e2:	f105 0358 	add.w	r3, r5, #88	; 0x58
     9e6:	f8cd 800c 	str.w	r8, [sp, #12]
     9ea:	f104 0a04 	add.w	sl, r4, #4
     9ee:	46b0      	mov	r8, r6
     9f0:	4691      	mov	r9, r2
     9f2:	461e      	mov	r6, r3
     9f4:	e00e      	b.n	a14 <__gnu_unwind_pr_common+0x21c>
     9f6:	4650      	mov	r0, sl
     9f8:	9604      	str	r6, [sp, #16]
     9fa:	f7ff fd75 	bl	4e8 <_Unwind_decode_typeinfo_ptr.constprop.0>
     9fe:	2200      	movs	r2, #0
     a00:	4601      	mov	r1, r0
     a02:	ab04      	add	r3, sp, #16
     a04:	4628      	mov	r0, r5
     a06:	f109 0901 	add.w	r9, r9, #1
     a0a:	f10a 0a04 	add.w	sl, sl, #4
     a0e:	f000 f800 	bl	a12 <__gnu_unwind_pr_common+0x21a>
     a12:	b9e0      	cbnz	r0, a4e <__gnu_unwind_pr_common+0x256>
     a14:	45d9      	cmp	r9, fp
     a16:	d1ee      	bne.n	9f6 <__gnu_unwind_pr_common+0x1fe>
     a18:	210d      	movs	r1, #13
     a1a:	4638      	mov	r0, r7
     a1c:	f7ff fe78 	bl	710 <_Unwind_GetGR>
     a20:	9b04      	ldr	r3, [sp, #16]
     a22:	62ac      	str	r4, [r5, #40]	; 0x28
     a24:	e9c5 0308 	strd	r0, r3, [r5, #32]
     a28:	2006      	movs	r0, #6
     a2a:	e710      	b.n	84e <__gnu_unwind_pr_common+0x56>
     a2c:	4681      	mov	r9, r0
     a2e:	210d      	movs	r1, #13
     a30:	4638      	mov	r0, r7
     a32:	f7ff fe6d 	bl	710 <_Unwind_GetGR>
     a36:	f1b9 0f02 	cmp.w	r9, #2
     a3a:	6228      	str	r0, [r5, #32]
     a3c:	d125      	bne.n	a8a <__gnu_unwind_pr_common+0x292>
     a3e:	462b      	mov	r3, r5
     a40:	9a04      	ldr	r2, [sp, #16]
     a42:	f843 2f2c 	str.w	r2, [r3, #44]!
     a46:	626b      	str	r3, [r5, #36]	; 0x24
     a48:	62ac      	str	r4, [r5, #40]	; 0x28
     a4a:	2006      	movs	r0, #6
     a4c:	e6ff      	b.n	84e <__gnu_unwind_pr_common+0x56>
     a4e:	4646      	mov	r6, r8
     a50:	6823      	ldr	r3, [r4, #0]
     a52:	f8dd 800c 	ldr.w	r8, [sp, #12]
     a56:	e76a      	b.n	92e <__gnu_unwind_pr_common+0x136>
     a58:	4620      	mov	r0, r4
     a5a:	f7ff fc7d 	bl	358 <selfrel_offset31>
     a5e:	3404      	adds	r4, #4
     a60:	4602      	mov	r2, r0
     a62:	63ac      	str	r4, [r5, #56]	; 0x38
     a64:	4628      	mov	r0, r5
     a66:	4614      	mov	r4, r2
     a68:	f000 f800 	bl	a6c <__gnu_unwind_pr_common+0x274>
     a6c:	2800      	cmp	r0, #0
     a6e:	f43f aeed 	beq.w	84c <__gnu_unwind_pr_common+0x54>
     a72:	4638      	mov	r0, r7
     a74:	4622      	mov	r2, r4
     a76:	210f      	movs	r1, #15
     a78:	f7ff fe70 	bl	75c <_Unwind_SetGR>
     a7c:	2007      	movs	r0, #7
     a7e:	e6e6      	b.n	84e <__gnu_unwind_pr_common+0x56>
     a80:	210d      	movs	r1, #13
     a82:	4638      	mov	r0, r7
     a84:	f7ff fe44 	bl	710 <_Unwind_GetGR>
     a88:	6228      	str	r0, [r5, #32]
     a8a:	9b04      	ldr	r3, [sp, #16]
     a8c:	626b      	str	r3, [r5, #36]	; 0x24
     a8e:	e7db      	b.n	a48 <__gnu_unwind_pr_common+0x250>
     a90:	f10b 0001 	add.w	r0, fp, #1
     a94:	eb04 0080 	add.w	r0, r4, r0, lsl #2
     a98:	e77a      	b.n	990 <__gnu_unwind_pr_common+0x198>
     a9a:	bf00      	nop
     a9c:	00000000 	andeq	r0, r0, r0

00000aa0 <__aeabi_unwind_cpp_pr0>:
     aa0:	2300      	movs	r3, #0
     aa2:	e6a9      	b.n	7f8 <__gnu_unwind_pr_common>

00000aa4 <__aeabi_unwind_cpp_pr1>:
     aa4:	2301      	movs	r3, #1
     aa6:	e6a7      	b.n	7f8 <__gnu_unwind_pr_common>

00000aa8 <__aeabi_unwind_cpp_pr2>:
     aa8:	2302      	movs	r3, #2
     aaa:	e6a5      	b.n	7f8 <__gnu_unwind_pr_common>

00000aac <_Unwind_VRS_Pop>:
     aac:	e92d 43f0 	stmdb	sp!, {r4, r5, r6, r7, r8, r9, lr}
     ab0:	4606      	mov	r6, r0
     ab2:	b0c3      	sub	sp, #268	; 0x10c
     ab4:	4615      	mov	r5, r2
     ab6:	461c      	mov	r4, r3
     ab8:	2904      	cmp	r1, #4
     aba:	f200 80bf 	bhi.w	c3c <_Unwind_VRS_Pop+0x190>
     abe:	e8df f001 	tbb	[pc, r1]
     ac2:	2dbd579e 	ldccs	7, cr5, [sp, #632]!	; 0x278
     ac6:	2c000003 	stccs	0, cr0, [r0], {3}
     aca:	f040 80b7 	bne.w	c3c <_Unwind_VRS_Pop+0x190>
     ace:	2a10      	cmp	r2, #16
     ad0:	f200 80b4 	bhi.w	c3c <_Unwind_VRS_Pop+0x190>
     ad4:	6803      	ldr	r3, [r0, #0]
     ad6:	06d8      	lsls	r0, r3, #27
     ad8:	f100 80f9 	bmi.w	cce <_Unwind_VRS_Pop+0x222>
     adc:	af20      	add	r7, sp, #128	; 0x80
     ade:	4638      	mov	r0, r7
     ae0:	f000 f998 	bl	e14 <__gnu_Unwind_Save_WMMXC>
     ae4:	6bb4      	ldr	r4, [r6, #56]	; 0x38
     ae6:	4639      	mov	r1, r7
     ae8:	2300      	movs	r3, #0
     aea:	f04f 0c01 	mov.w	ip, #1
     aee:	fa0c f203 	lsl.w	r2, ip, r3
     af2:	422a      	tst	r2, r5
     af4:	4620      	mov	r0, r4
     af6:	f103 0301 	add.w	r3, r3, #1
     afa:	d003      	beq.n	b04 <_Unwind_VRS_Pop+0x58>
     afc:	f850 2b04 	ldr.w	r2, [r0], #4
     b00:	600a      	str	r2, [r1, #0]
     b02:	4604      	mov	r4, r0
     b04:	2b04      	cmp	r3, #4
     b06:	f101 0104 	add.w	r1, r1, #4
     b0a:	d1f0      	bne.n	aee <_Unwind_VRS_Pop+0x42>
     b0c:	4638      	mov	r0, r7
     b0e:	63b4      	str	r4, [r6, #56]	; 0x38
     b10:	f000 f976 	bl	e00 <__gnu_Unwind_Restore_WMMXC>
     b14:	2000      	movs	r0, #0
     b16:	b043      	add	sp, #268	; 0x10c
     b18:	e8bd 83f0 	ldmia.w	sp!, {r4, r5, r6, r7, r8, r9, pc}
     b1c:	2c03      	cmp	r4, #3
     b1e:	f040 808d 	bne.w	c3c <_Unwind_VRS_Pop+0x190>
     b22:	b294      	uxth	r4, r2
     b24:	eb04 4312 	add.w	r3, r4, r2, lsr #16
     b28:	2b10      	cmp	r3, #16
     b2a:	ea4f 4512 	mov.w	r5, r2, lsr #16
     b2e:	f200 8085 	bhi.w	c3c <_Unwind_VRS_Pop+0x190>
     b32:	6803      	ldr	r3, [r0, #0]
     b34:	071f      	lsls	r7, r3, #28
     b36:	f100 80d2 	bmi.w	cde <_Unwind_VRS_Pop+0x232>
     b3a:	af20      	add	r7, sp, #128	; 0x80
     b3c:	4638      	mov	r0, r7
     b3e:	f000 f93d 	bl	dbc <__gnu_Unwind_Save_WMMXD>
     b42:	6bb2      	ldr	r2, [r6, #56]	; 0x38
     b44:	eb07 01c5 	add.w	r1, r7, r5, lsl #3
     b48:	b154      	cbz	r4, b60 <_Unwind_VRS_Pop+0xb4>
     b4a:	460b      	mov	r3, r1
     b4c:	1ad0      	subs	r0, r2, r3
     b4e:	eb01 01c4 	add.w	r1, r1, r4, lsl #3
     b52:	00e4      	lsls	r4, r4, #3
     b54:	581d      	ldr	r5, [r3, r0]
     b56:	f843 5b04 	str.w	r5, [r3], #4
     b5a:	428b      	cmp	r3, r1
     b5c:	d1fa      	bne.n	b54 <_Unwind_VRS_Pop+0xa8>
     b5e:	4422      	add	r2, r4
     b60:	4638      	mov	r0, r7
     b62:	63b2      	str	r2, [r6, #56]	; 0x38
     b64:	f000 f908 	bl	d78 <__gnu_Unwind_Restore_WMMXD>
     b68:	2000      	movs	r0, #0
     b6a:	b043      	add	sp, #268	; 0x10c
     b6c:	e8bd 83f0 	ldmia.w	sp!, {r4, r5, r6, r7, r8, r9, pc}
     b70:	2c01      	cmp	r4, #1
     b72:	ea4f 4812 	mov.w	r8, r2, lsr #16
     b76:	b295      	uxth	r5, r2
     b78:	d05c      	beq.n	c34 <_Unwind_VRS_Pop+0x188>
     b7a:	2c05      	cmp	r4, #5
     b7c:	d15e      	bne.n	c3c <_Unwind_VRS_Pop+0x190>
     b7e:	eb08 0905 	add.w	r9, r8, r5
     b82:	f1b9 0f20 	cmp.w	r9, #32
     b86:	d859      	bhi.n	c3c <_Unwind_VRS_Pop+0x190>
     b88:	f1b8 0f0f 	cmp.w	r8, #15
     b8c:	d979      	bls.n	c82 <_Unwind_VRS_Pop+0x1d6>
     b8e:	46a9      	mov	r9, r5
     b90:	2d00      	cmp	r5, #0
     b92:	f040 808a 	bne.w	caa <_Unwind_VRS_Pop+0x1fe>
     b96:	6bb3      	ldr	r3, [r6, #56]	; 0x38
     b98:	b36d      	cbz	r5, bf6 <_Unwind_VRS_Pop+0x14a>
     b9a:	af20      	add	r7, sp, #128	; 0x80
     b9c:	f04f 0900 	mov.w	r9, #0
     ba0:	eb07 07c8 	add.w	r7, r7, r8, lsl #3
     ba4:	3f04      	subs	r7, #4
     ba6:	eb03 05c5 	add.w	r5, r3, r5, lsl #3
     baa:	f853 1b04 	ldr.w	r1, [r3], #4
     bae:	f847 1f04 	str.w	r1, [r7, #4]!
     bb2:	42ab      	cmp	r3, r5
     bb4:	d1f9      	bne.n	baa <_Unwind_VRS_Pop+0xfe>
     bb6:	f1b9 0f00 	cmp.w	r9, #0
     bba:	d00f      	beq.n	bdc <_Unwind_VRS_Pop+0x130>
     bbc:	466f      	mov	r7, sp
     bbe:	4641      	mov	r1, r8
     bc0:	2910      	cmp	r1, #16
     bc2:	bf38      	it	cc
     bc4:	2110      	movcc	r1, #16
     bc6:	eb07 01c1 	add.w	r1, r7, r1, lsl #3
     bca:	3984      	subs	r1, #132	; 0x84
     bcc:	eb03 05c9 	add.w	r5, r3, r9, lsl #3
     bd0:	f853 0b04 	ldr.w	r0, [r3], #4
     bd4:	f841 0f04 	str.w	r0, [r1, #4]!
     bd8:	42ab      	cmp	r3, r5
     bda:	d1f9      	bne.n	bd0 <_Unwind_VRS_Pop+0x124>
     bdc:	2c01      	cmp	r4, #1
     bde:	f000 8086 	beq.w	cee <_Unwind_VRS_Pop+0x242>
     be2:	f1b8 0f0f 	cmp.w	r8, #15
     be6:	63b5      	str	r5, [r6, #56]	; 0x38
     be8:	d947      	bls.n	c7a <_Unwind_VRS_Pop+0x1ce>
     bea:	f1b9 0f00 	cmp.w	r9, #0
     bee:	d002      	beq.n	bf6 <_Unwind_VRS_Pop+0x14a>
     bf0:	4668      	mov	r0, sp
     bf2:	f000 f8b9 	bl	d68 <__gnu_Unwind_Restore_VFP_D_16_to_31>
     bf6:	2000      	movs	r0, #0
     bf8:	b043      	add	sp, #268	; 0x10c
     bfa:	e8bd 83f0 	ldmia.w	sp!, {r4, r5, r6, r7, r8, r9, pc}
     bfe:	b9ec      	cbnz	r4, c3c <_Unwind_VRS_Pop+0x190>
     c00:	6b80      	ldr	r0, [r0, #56]	; 0x38
     c02:	4623      	mov	r3, r4
     c04:	fa1f fc82 	uxth.w	ip, r2
     c08:	2401      	movs	r4, #1
     c0a:	1d37      	adds	r7, r6, #4
     c0c:	fa04 f203 	lsl.w	r2, r4, r3
     c10:	ea12 0f0c 	tst.w	r2, ip
     c14:	4601      	mov	r1, r0
     c16:	d004      	beq.n	c22 <_Unwind_VRS_Pop+0x176>
     c18:	f851 2b04 	ldr.w	r2, [r1], #4
     c1c:	f847 2023 	str.w	r2, [r7, r3, lsl #2]
     c20:	4608      	mov	r0, r1
     c22:	3301      	adds	r3, #1
     c24:	2b10      	cmp	r3, #16
     c26:	d1f1      	bne.n	c0c <_Unwind_VRS_Pop+0x160>
     c28:	f415 5500 	ands.w	r5, r5, #8192	; 0x2000
     c2c:	d1e3      	bne.n	bf6 <_Unwind_VRS_Pop+0x14a>
     c2e:	63b0      	str	r0, [r6, #56]	; 0x38
     c30:	4628      	mov	r0, r5
     c32:	e004      	b.n	c3e <_Unwind_VRS_Pop+0x192>
     c34:	eb08 0305 	add.w	r3, r8, r5
     c38:	2b10      	cmp	r3, #16
     c3a:	d903      	bls.n	c44 <_Unwind_VRS_Pop+0x198>
     c3c:	2002      	movs	r0, #2
     c3e:	b043      	add	sp, #268	; 0x10c
     c40:	e8bd 83f0 	ldmia.w	sp!, {r4, r5, r6, r7, r8, r9, pc}
     c44:	f1b8 0f0f 	cmp.w	r8, #15
     c48:	d8f8      	bhi.n	c3c <_Unwind_VRS_Pop+0x190>
     c4a:	6833      	ldr	r3, [r6, #0]
     c4c:	07da      	lsls	r2, r3, #31
     c4e:	d506      	bpl.n	c5e <_Unwind_VRS_Pop+0x1b2>
     c50:	4630      	mov	r0, r6
     c52:	f023 0303 	bic.w	r3, r3, #3
     c56:	f840 3b48 	str.w	r3, [r0], #72
     c5a:	f000 f879 	bl	d50 <__gnu_Unwind_Save_VFP>
     c5e:	af20      	add	r7, sp, #128	; 0x80
     c60:	4638      	mov	r0, r7
     c62:	f000 f875 	bl	d50 <__gnu_Unwind_Save_VFP>
     c66:	6bb3      	ldr	r3, [r6, #56]	; 0x38
     c68:	2d00      	cmp	r5, #0
     c6a:	d197      	bne.n	b9c <_Unwind_VRS_Pop+0xf0>
     c6c:	461d      	mov	r5, r3
     c6e:	3504      	adds	r5, #4
     c70:	63b5      	str	r5, [r6, #56]	; 0x38
     c72:	4638      	mov	r0, r7
     c74:	f000 f868 	bl	d48 <__gnu_Unwind_Restore_VFP>
     c78:	e7bd      	b.n	bf6 <_Unwind_VRS_Pop+0x14a>
     c7a:	a820      	add	r0, sp, #128	; 0x80
     c7c:	f000 f86c 	bl	d58 <__gnu_Unwind_Restore_VFP_D>
     c80:	e7b3      	b.n	bea <_Unwind_VRS_Pop+0x13e>
     c82:	f1b9 0f10 	cmp.w	r9, #16
     c86:	d940      	bls.n	d0a <_Unwind_VRS_Pop+0x25e>
     c88:	f1a9 0910 	sub.w	r9, r9, #16
     c8c:	6833      	ldr	r3, [r6, #0]
     c8e:	07d9      	lsls	r1, r3, #31
     c90:	d508      	bpl.n	ca4 <_Unwind_VRS_Pop+0x1f8>
     c92:	f023 0301 	bic.w	r3, r3, #1
     c96:	4630      	mov	r0, r6
     c98:	f043 0302 	orr.w	r3, r3, #2
     c9c:	f840 3b48 	str.w	r3, [r0], #72
     ca0:	f000 f85e 	bl	d60 <__gnu_Unwind_Save_VFP_D>
     ca4:	f1b9 0f00 	cmp.w	r9, #0
     ca8:	d032      	beq.n	d10 <_Unwind_VRS_Pop+0x264>
     caa:	6833      	ldr	r3, [r6, #0]
     cac:	075a      	lsls	r2, r3, #29
     cae:	d420      	bmi.n	cf2 <_Unwind_VRS_Pop+0x246>
     cb0:	f1b8 0f0f 	cmp.w	r8, #15
     cb4:	d925      	bls.n	d02 <_Unwind_VRS_Pop+0x256>
     cb6:	466f      	mov	r7, sp
     cb8:	4638      	mov	r0, r7
     cba:	f1c8 0510 	rsb	r5, r8, #16
     cbe:	f000 f857 	bl	d70 <__gnu_Unwind_Save_VFP_D_16_to_31>
     cc2:	2d00      	cmp	r5, #0
     cc4:	6bb3      	ldr	r3, [r6, #56]	; 0x38
     cc6:	f77f af7a 	ble.w	bbe <_Unwind_VRS_Pop+0x112>
     cca:	af20      	add	r7, sp, #128	; 0x80
     ccc:	e768      	b.n	ba0 <_Unwind_VRS_Pop+0xf4>
     cce:	f023 0310 	bic.w	r3, r3, #16
     cd2:	6033      	str	r3, [r6, #0]
     cd4:	f506 70e8 	add.w	r0, r6, #464	; 0x1d0
     cd8:	f000 f89c 	bl	e14 <__gnu_Unwind_Save_WMMXC>
     cdc:	e6fe      	b.n	adc <_Unwind_VRS_Pop+0x30>
     cde:	f023 0308 	bic.w	r3, r3, #8
     ce2:	6003      	str	r3, [r0, #0]
     ce4:	f500 70a8 	add.w	r0, r0, #336	; 0x150
     ce8:	f000 f868 	bl	dbc <__gnu_Unwind_Save_WMMXD>
     cec:	e725      	b.n	b3a <_Unwind_VRS_Pop+0x8e>
     cee:	af20      	add	r7, sp, #128	; 0x80
     cf0:	e7bd      	b.n	c6e <_Unwind_VRS_Pop+0x1c2>
     cf2:	4630      	mov	r0, r6
     cf4:	f023 0304 	bic.w	r3, r3, #4
     cf8:	f840 3bd0 	str.w	r3, [r0], #208
     cfc:	f000 f838 	bl	d70 <__gnu_Unwind_Save_VFP_D_16_to_31>
     d00:	e7d6      	b.n	cb0 <_Unwind_VRS_Pop+0x204>
     d02:	a820      	add	r0, sp, #128	; 0x80
     d04:	f000 f82c 	bl	d60 <__gnu_Unwind_Save_VFP_D>
     d08:	e7d5      	b.n	cb6 <_Unwind_VRS_Pop+0x20a>
     d0a:	f04f 0900 	mov.w	r9, #0
     d0e:	e7bd      	b.n	c8c <_Unwind_VRS_Pop+0x1e0>
     d10:	f1b8 0f0f 	cmp.w	r8, #15
     d14:	f63f af3f 	bhi.w	b96 <_Unwind_VRS_Pop+0xea>
     d18:	af20      	add	r7, sp, #128	; 0x80
     d1a:	4638      	mov	r0, r7
     d1c:	f000 f820 	bl	d60 <__gnu_Unwind_Save_VFP_D>
     d20:	6bb3      	ldr	r3, [r6, #56]	; 0x38
     d22:	2d00      	cmp	r5, #0
     d24:	f47f af3a 	bne.w	b9c <_Unwind_VRS_Pop+0xf0>
     d28:	4638      	mov	r0, r7
     d2a:	f000 f815 	bl	d58 <__gnu_Unwind_Restore_VFP_D>
     d2e:	e762      	b.n	bf6 <_Unwind_VRS_Pop+0x14a>

00000d30 <__restore_core_regs>:
     d30:	f100 0134 	add.w	r1, r0, #52	; 0x34
     d34:	e891 0038 	ldmia.w	r1, {r3, r4, r5}
     d38:	469c      	mov	ip, r3
     d3a:	46a6      	mov	lr, r4
     d3c:	f84c 5d04 	str.w	r5, [ip, #-4]!
     d40:	e890 0fff 	ldmia.w	r0, {r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, sl, fp}
     d44:	46e5      	mov	sp, ip
     d46:	bd00      	pop	{pc}

00000d48 <__gnu_Unwind_Restore_VFP>:
     d48:	ec90 0b21 	fldmiax	r0, {d0-d15}	;@ Deprecated
     d4c:	4770      	bx	lr
     d4e:	bf00      	nop

00000d50 <__gnu_Unwind_Save_VFP>:
     d50:	ec80 0b21 	fstmiax	r0, {d0-d15}	;@ Deprecated
     d54:	4770      	bx	lr
     d56:	bf00      	nop

00000d58 <__gnu_Unwind_Restore_VFP_D>:
     d58:	ec90 0b20 	vldmia	r0, {d0-d15}
     d5c:	4770      	bx	lr
     d5e:	bf00      	nop

00000d60 <__gnu_Unwind_Save_VFP_D>:
     d60:	ec80 0b20 	vstmia	r0, {d0-d15}
     d64:	4770      	bx	lr
     d66:	bf00      	nop

00000d68 <__gnu_Unwind_Restore_VFP_D_16_to_31>:
     d68:	ecd0 0b20 	vldmia	r0, {d16-d31}
     d6c:	4770      	bx	lr
     d6e:	bf00      	nop

00000d70 <__gnu_Unwind_Save_VFP_D_16_to_31>:
     d70:	ecc0 0b20 	vstmia	r0, {d16-d31}
     d74:	4770      	bx	lr
     d76:	bf00      	nop

00000d78 <__gnu_Unwind_Restore_WMMXD>:
     d78:	ecf0 0102 	ldfe	f0, [r0], #8
     d7c:	ecf0 1102 	ldfe	f1, [r0], #8
     d80:	ecf0 2102 	ldfe	f2, [r0], #8
     d84:	ecf0 3102 	ldfe	f3, [r0], #8
     d88:	ecf0 4102 	ldfe	f4, [r0], #8
     d8c:	ecf0 5102 	ldfe	f5, [r0], #8
     d90:	ecf0 6102 	ldfe	f6, [r0], #8
     d94:	ecf0 7102 	ldfe	f7, [r0], #8
     d98:	ecf0 8102 	ldfp	f0, [r0], #8
     d9c:	ecf0 9102 	ldfp	f1, [r0], #8
     da0:	ecf0 a102 	ldfp	f2, [r0], #8
     da4:	ecf0 b102 	ldfp	f3, [r0], #8
     da8:	ecf0 c102 	ldfp	f4, [r0], #8
     dac:	ecf0 d102 	ldfp	f5, [r0], #8
     db0:	ecf0 e102 	ldfp	f6, [r0], #8
     db4:	ecf0 f102 	ldfp	f7, [r0], #8
     db8:	4770      	bx	lr
     dba:	bf00      	nop

00000dbc <__gnu_Unwind_Save_WMMXD>:
     dbc:	ece0 0102 	stfe	f0, [r0], #8
     dc0:	ece0 1102 	stfe	f1, [r0], #8
     dc4:	ece0 2102 	stfe	f2, [r0], #8
     dc8:	ece0 3102 	stfe	f3, [r0], #8
     dcc:	ece0 4102 	stfe	f4, [r0], #8
     dd0:	ece0 5102 	stfe	f5, [r0], #8
     dd4:	ece0 6102 	stfe	f6, [r0], #8
     dd8:	ece0 7102 	stfe	f7, [r0], #8
     ddc:	ece0 8102 	stfp	f0, [r0], #8
     de0:	ece0 9102 	stfp	f1, [r0], #8
     de4:	ece0 a102 	stfp	f2, [r0], #8
     de8:	ece0 b102 	stfp	f3, [r0], #8
     dec:	ece0 c102 	stfp	f4, [r0], #8
     df0:	ece0 d102 	stfp	f5, [r0], #8
     df4:	ece0 e102 	stfp	f6, [r0], #8
     df8:	ece0 f102 	stfp	f7, [r0], #8
     dfc:	4770      	bx	lr
     dfe:	bf00      	nop

00000e00 <__gnu_Unwind_Restore_WMMXC>:
     e00:	fcb0 8101 	ldc2	1, cr8, [r0], #4
     e04:	fcb0 9101 	ldc2	1, cr9, [r0], #4
     e08:	fcb0 a101 	ldc2	1, cr10, [r0], #4
     e0c:	fcb0 b101 	ldc2	1, cr11, [r0], #4
     e10:	4770      	bx	lr
     e12:	bf00      	nop

00000e14 <__gnu_Unwind_Save_WMMXC>:
     e14:	fca0 8101 	stc2	1, cr8, [r0], #4
     e18:	fca0 9101 	stc2	1, cr9, [r0], #4
     e1c:	fca0 a101 	stc2	1, cr10, [r0], #4
     e20:	fca0 b101 	stc2	1, cr11, [r0], #4
     e24:	4770      	bx	lr
     e26:	bf00      	nop

00000e28 <_Unwind_RaiseException>:
     e28:	46ec      	mov	ip, sp
     e2a:	b500      	push	{lr}
     e2c:	e92d 5000 	stmdb	sp!, {ip, lr}
     e30:	e92d 1fff 	stmdb	sp!, {r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, sl, fp, ip}
     e34:	f04f 0300 	mov.w	r3, #0
     e38:	e92d 000c 	stmdb	sp!, {r2, r3}
     e3c:	a901      	add	r1, sp, #4
     e3e:	f7ff fbe1 	bl	604 <__gnu_Unwind_RaiseException>
     e42:	f8dd e040 	ldr.w	lr, [sp, #64]	; 0x40
     e46:	b012      	add	sp, #72	; 0x48
     e48:	4770      	bx	lr
     e4a:	bf00      	nop

00000e4c <_Unwind_Resume>:
     e4c:	46ec      	mov	ip, sp
     e4e:	b500      	push	{lr}
     e50:	e92d 5000 	stmdb	sp!, {ip, lr}
     e54:	e92d 1fff 	stmdb	sp!, {r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, sl, fp, ip}
     e58:	f04f 0300 	mov.w	r3, #0
     e5c:	e92d 000c 	stmdb	sp!, {r2, r3}
     e60:	a901      	add	r1, sp, #4
     e62:	f7ff fc0b 	bl	67c <__gnu_Unwind_Resume>
     e66:	f8dd e040 	ldr.w	lr, [sp, #64]	; 0x40
     e6a:	b012      	add	sp, #72	; 0x48
     e6c:	4770      	bx	lr
     e6e:	bf00      	nop

00000e70 <_Unwind_Resume_or_Rethrow>:
     e70:	46ec      	mov	ip, sp
     e72:	b500      	push	{lr}
     e74:	e92d 5000 	stmdb	sp!, {ip, lr}
     e78:	e92d 1fff 	stmdb	sp!, {r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, sl, fp, ip}
     e7c:	f04f 0300 	mov.w	r3, #0
     e80:	e92d 000c 	stmdb	sp!, {r2, r3}
     e84:	a901      	add	r1, sp, #4
     e86:	f7ff fc1b 	bl	6c0 <__gnu_Unwind_Resume_or_Rethrow>
     e8a:	f8dd e040 	ldr.w	lr, [sp, #64]	; 0x40
     e8e:	b012      	add	sp, #72	; 0x48
     e90:	4770      	bx	lr
     e92:	bf00      	nop

00000e94 <_Unwind_ForcedUnwind>:
     e94:	46ec      	mov	ip, sp
     e96:	b500      	push	{lr}
     e98:	e92d 5000 	stmdb	sp!, {ip, lr}
     e9c:	e92d 1fff 	stmdb	sp!, {r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, sl, fp, ip}
     ea0:	f04f 0300 	mov.w	r3, #0
     ea4:	e92d 000c 	stmdb	sp!, {r2, r3}
     ea8:	ab01      	add	r3, sp, #4
     eaa:	f7ff fbdf 	bl	66c <__gnu_Unwind_ForcedUnwind>
     eae:	f8dd e040 	ldr.w	lr, [sp, #64]	; 0x40
     eb2:	b012      	add	sp, #72	; 0x48
     eb4:	4770      	bx	lr
     eb6:	bf00      	nop

00000eb8 <_Unwind_Backtrace>:
     eb8:	46ec      	mov	ip, sp
     eba:	b500      	push	{lr}
     ebc:	e92d 5000 	stmdb	sp!, {ip, lr}
     ec0:	e92d 1fff 	stmdb	sp!, {r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, sl, fp, ip}
     ec4:	f04f 0300 	mov.w	r3, #0
     ec8:	e92d 000c 	stmdb	sp!, {r2, r3}
     ecc:	aa01      	add	r2, sp, #4
     ece:	f7ff fc51 	bl	774 <__gnu_Unwind_Backtrace>
     ed2:	f8dd e040 	ldr.w	lr, [sp, #64]	; 0x40
     ed6:	b012      	add	sp, #72	; 0x48
     ed8:	4770      	bx	lr
     eda:	bf00      	nop

00000edc <memcpy>:
     edc:	4684      	mov	ip, r0
     ede:	ea41 0300 	orr.w	r3, r1, r0
     ee2:	f013 0303 	ands.w	r3, r3, #3
     ee6:	d16d      	bne.n	fc4 <memcpy+0xe8>
     ee8:	3a40      	subs	r2, #64	; 0x40
     eea:	d341      	bcc.n	f70 <memcpy+0x94>
     eec:	f851 3b04 	ldr.w	r3, [r1], #4
     ef0:	f840 3b04 	str.w	r3, [r0], #4
     ef4:	f851 3b04 	ldr.w	r3, [r1], #4
     ef8:	f840 3b04 	str.w	r3, [r0], #4
     efc:	f851 3b04 	ldr.w	r3, [r1], #4
     f00:	f840 3b04 	str.w	r3, [r0], #4
     f04:	f851 3b04 	ldr.w	r3, [r1], #4
     f08:	f840 3b04 	str.w	r3, [r0], #4
     f0c:	f851 3b04 	ldr.w	r3, [r1], #4
     f10:	f840 3b04 	str.w	r3, [r0], #4
     f14:	f851 3b04 	ldr.w	r3, [r1], #4
     f18:	f840 3b04 	str.w	r3, [r0], #4
     f1c:	f851 3b04 	ldr.w	r3, [r1], #4
     f20:	f840 3b04 	str.w	r3, [r0], #4
     f24:	f851 3b04 	ldr.w	r3, [r1], #4
     f28:	f840 3b04 	str.w	r3, [r0], #4
     f2c:	f851 3b04 	ldr.w	r3, [r1], #4
     f30:	f840 3b04 	str.w	r3, [r0], #4
     f34:	f851 3b04 	ldr.w	r3, [r1], #4
     f38:	f840 3b04 	str.w	r3, [r0], #4
     f3c:	f851 3b04 	ldr.w	r3, [r1], #4
     f40:	f840 3b04 	str.w	r3, [r0], #4
     f44:	f851 3b04 	ldr.w	r3, [r1], #4
     f48:	f840 3b04 	str.w	r3, [r0], #4
     f4c:	f851 3b04 	ldr.w	r3, [r1], #4
     f50:	f840 3b04 	str.w	r3, [r0], #4
     f54:	f851 3b04 	ldr.w	r3, [r1], #4
     f58:	f840 3b04 	str.w	r3, [r0], #4
     f5c:	f851 3b04 	ldr.w	r3, [r1], #4
     f60:	f840 3b04 	str.w	r3, [r0], #4
     f64:	f851 3b04 	ldr.w	r3, [r1], #4
     f68:	f840 3b04 	str.w	r3, [r0], #4
     f6c:	3a40      	subs	r2, #64	; 0x40
     f6e:	d2bd      	bcs.n	eec <memcpy+0x10>
     f70:	3230      	adds	r2, #48	; 0x30
     f72:	d311      	bcc.n	f98 <memcpy+0xbc>
     f74:	f851 3b04 	ldr.w	r3, [r1], #4
     f78:	f840 3b04 	str.w	r3, [r0], #4
     f7c:	f851 3b04 	ldr.w	r3, [r1], #4
     f80:	f840 3b04 	str.w	r3, [r0], #4
     f84:	f851 3b04 	ldr.w	r3, [r1], #4
     f88:	f840 3b04 	str.w	r3, [r0], #4
     f8c:	f851 3b04 	ldr.w	r3, [r1], #4
     f90:	f840 3b04 	str.w	r3, [r0], #4
     f94:	3a10      	subs	r2, #16
     f96:	d2ed      	bcs.n	f74 <memcpy+0x98>
     f98:	320c      	adds	r2, #12
     f9a:	d305      	bcc.n	fa8 <memcpy+0xcc>
     f9c:	f851 3b04 	ldr.w	r3, [r1], #4
     fa0:	f840 3b04 	str.w	r3, [r0], #4
     fa4:	3a04      	subs	r2, #4
     fa6:	d2f9      	bcs.n	f9c <memcpy+0xc0>
     fa8:	3204      	adds	r2, #4
     faa:	d008      	beq.n	fbe <memcpy+0xe2>
     fac:	07d2      	lsls	r2, r2, #31
     fae:	bf1c      	itt	ne
     fb0:	f811 3b01 	ldrbne.w	r3, [r1], #1
     fb4:	f800 3b01 	strbne.w	r3, [r0], #1
     fb8:	d301      	bcc.n	fbe <memcpy+0xe2>
     fba:	880b      	ldrh	r3, [r1, #0]
     fbc:	8003      	strh	r3, [r0, #0]
     fbe:	4660      	mov	r0, ip
     fc0:	4770      	bx	lr
     fc2:	bf00      	nop
     fc4:	2a08      	cmp	r2, #8
     fc6:	d313      	bcc.n	ff0 <memcpy+0x114>
     fc8:	078b      	lsls	r3, r1, #30
     fca:	d08d      	beq.n	ee8 <memcpy+0xc>
     fcc:	f010 0303 	ands.w	r3, r0, #3
     fd0:	d08a      	beq.n	ee8 <memcpy+0xc>
     fd2:	f1c3 0304 	rsb	r3, r3, #4
     fd6:	1ad2      	subs	r2, r2, r3
     fd8:	07db      	lsls	r3, r3, #31
     fda:	bf1c      	itt	ne
     fdc:	f811 3b01 	ldrbne.w	r3, [r1], #1
     fe0:	f800 3b01 	strbne.w	r3, [r0], #1
     fe4:	d380      	bcc.n	ee8 <memcpy+0xc>
     fe6:	f831 3b02 	ldrh.w	r3, [r1], #2
     fea:	f820 3b02 	strh.w	r3, [r0], #2
     fee:	e77b      	b.n	ee8 <memcpy+0xc>
     ff0:	3a04      	subs	r2, #4
     ff2:	d3d9      	bcc.n	fa8 <memcpy+0xcc>
     ff4:	3a01      	subs	r2, #1
     ff6:	f811 3b01 	ldrb.w	r3, [r1], #1
     ffa:	f800 3b01 	strb.w	r3, [r0], #1
     ffe:	d2f9      	bcs.n	ff4 <memcpy+0x118>
    1000:	780b      	ldrb	r3, [r1, #0]
    1002:	7003      	strb	r3, [r0, #0]
    1004:	784b      	ldrb	r3, [r1, #1]
    1006:	7043      	strb	r3, [r0, #1]
    1008:	788b      	ldrb	r3, [r1, #2]
    100a:	7083      	strb	r3, [r0, #2]
    100c:	4660      	mov	r0, ip
    100e:	4770      	bx	lr

00001010 <next_unwind_byte>:
    1010:	7a02      	ldrb	r2, [r0, #8]
    1012:	4603      	mov	r3, r0
    1014:	b97a      	cbnz	r2, 1036 <next_unwind_byte+0x26>
    1016:	7a42      	ldrb	r2, [r0, #9]
    1018:	b1a2      	cbz	r2, 1044 <next_unwind_byte+0x34>
    101a:	6841      	ldr	r1, [r0, #4]
    101c:	3a01      	subs	r2, #1
    101e:	b410      	push	{r4}
    1020:	7242      	strb	r2, [r0, #9]
    1022:	6808      	ldr	r0, [r1, #0]
    1024:	2203      	movs	r2, #3
    1026:	1d0c      	adds	r4, r1, #4
    1028:	721a      	strb	r2, [r3, #8]
    102a:	0202      	lsls	r2, r0, #8
    102c:	605c      	str	r4, [r3, #4]
    102e:	0e00      	lsrs	r0, r0, #24
    1030:	bc10      	pop	{r4}
    1032:	601a      	str	r2, [r3, #0]
    1034:	4770      	bx	lr
    1036:	6800      	ldr	r0, [r0, #0]
    1038:	3a01      	subs	r2, #1
    103a:	721a      	strb	r2, [r3, #8]
    103c:	0202      	lsls	r2, r0, #8
    103e:	601a      	str	r2, [r3, #0]
    1040:	0e00      	lsrs	r0, r0, #24
    1042:	4770      	bx	lr
    1044:	20b0      	movs	r0, #176	; 0xb0
    1046:	4770      	bx	lr

00001048 <_Unwind_GetGR.constprop.0>:
    1048:	b500      	push	{lr}
    104a:	b085      	sub	sp, #20
    104c:	2300      	movs	r3, #0
    104e:	aa03      	add	r2, sp, #12
    1050:	9200      	str	r2, [sp, #0]
    1052:	4619      	mov	r1, r3
    1054:	220c      	movs	r2, #12
    1056:	f7ff fb43 	bl	6e0 <_Unwind_VRS_Get>
    105a:	9803      	ldr	r0, [sp, #12]
    105c:	b005      	add	sp, #20
    105e:	f85d fb04 	ldr.w	pc, [sp], #4
    1062:	bf00      	nop

00001064 <unwind_UCB_from_context>:
    1064:	e7f0      	b.n	1048 <_Unwind_GetGR.constprop.0>
    1066:	bf00      	nop

00001068 <__gnu_unwind_execute>:
    1068:	e92d 43f0 	stmdb	sp!, {r4, r5, r6, r7, r8, r9, lr}
    106c:	4605      	mov	r5, r0
    106e:	b085      	sub	sp, #20
    1070:	460e      	mov	r6, r1
    1072:	f04f 0800 	mov.w	r8, #0
    1076:	4630      	mov	r0, r6
    1078:	f7ff ffca 	bl	1010 <next_unwind_byte>
    107c:	28b0      	cmp	r0, #176	; 0xb0
    107e:	4604      	mov	r4, r0
    1080:	f000 80ba 	beq.w	11f8 <__gnu_unwind_execute+0x190>
    1084:	0607      	lsls	r7, r0, #24
    1086:	d520      	bpl.n	10ca <__gnu_unwind_execute+0x62>
    1088:	f000 03f0 	and.w	r3, r0, #240	; 0xf0
    108c:	2b80      	cmp	r3, #128	; 0x80
    108e:	d04d      	beq.n	112c <__gnu_unwind_execute+0xc4>
    1090:	2b90      	cmp	r3, #144	; 0x90
    1092:	d036      	beq.n	1102 <__gnu_unwind_execute+0x9a>
    1094:	2ba0      	cmp	r3, #160	; 0xa0
    1096:	d060      	beq.n	115a <__gnu_unwind_execute+0xf2>
    1098:	2bb0      	cmp	r3, #176	; 0xb0
    109a:	d074      	beq.n	1186 <__gnu_unwind_execute+0x11e>
    109c:	2bc0      	cmp	r3, #192	; 0xc0
    109e:	f000 808b 	beq.w	11b8 <__gnu_unwind_execute+0x150>
    10a2:	f000 03f8 	and.w	r3, r0, #248	; 0xf8
    10a6:	2bd0      	cmp	r3, #208	; 0xd0
    10a8:	d10b      	bne.n	10c2 <__gnu_unwind_execute+0x5a>
    10aa:	f000 0207 	and.w	r2, r0, #7
    10ae:	3201      	adds	r2, #1
    10b0:	2305      	movs	r3, #5
    10b2:	f442 2200 	orr.w	r2, r2, #524288	; 0x80000
    10b6:	2101      	movs	r1, #1
    10b8:	4628      	mov	r0, r5
    10ba:	f7ff fcf7 	bl	aac <_Unwind_VRS_Pop>
    10be:	2800      	cmp	r0, #0
    10c0:	d0d9      	beq.n	1076 <__gnu_unwind_execute+0xe>
    10c2:	2009      	movs	r0, #9
    10c4:	b005      	add	sp, #20
    10c6:	e8bd 83f0 	ldmia.w	sp!, {r4, r5, r6, r7, r8, r9, pc}
    10ca:	0083      	lsls	r3, r0, #2
    10cc:	b2db      	uxtb	r3, r3
    10ce:	1d1f      	adds	r7, r3, #4
    10d0:	f10d 090c 	add.w	r9, sp, #12
    10d4:	2300      	movs	r3, #0
    10d6:	4619      	mov	r1, r3
    10d8:	f8cd 9000 	str.w	r9, [sp]
    10dc:	220d      	movs	r2, #13
    10de:	4628      	mov	r0, r5
    10e0:	f7ff fafe 	bl	6e0 <_Unwind_VRS_Get>
    10e4:	9b03      	ldr	r3, [sp, #12]
    10e6:	f8cd 9000 	str.w	r9, [sp]
    10ea:	0660      	lsls	r0, r4, #25
    10ec:	bf4c      	ite	mi
    10ee:	1bdf      	submi	r7, r3, r7
    10f0:	18ff      	addpl	r7, r7, r3
    10f2:	2300      	movs	r3, #0
    10f4:	220d      	movs	r2, #13
    10f6:	4619      	mov	r1, r3
    10f8:	4628      	mov	r0, r5
    10fa:	9703      	str	r7, [sp, #12]
    10fc:	f7ff fb16 	bl	72c <_Unwind_VRS_Set>
    1100:	e7b9      	b.n	1076 <__gnu_unwind_execute+0xe>
    1102:	f000 030d 	and.w	r3, r0, #13
    1106:	2b0d      	cmp	r3, #13
    1108:	d0db      	beq.n	10c2 <__gnu_unwind_execute+0x5a>
    110a:	af03      	add	r7, sp, #12
    110c:	2300      	movs	r3, #0
    110e:	f000 020f 	and.w	r2, r0, #15
    1112:	4619      	mov	r1, r3
    1114:	9700      	str	r7, [sp, #0]
    1116:	4628      	mov	r0, r5
    1118:	f7ff fae2 	bl	6e0 <_Unwind_VRS_Get>
    111c:	2300      	movs	r3, #0
    111e:	9700      	str	r7, [sp, #0]
    1120:	220d      	movs	r2, #13
    1122:	4619      	mov	r1, r3
    1124:	4628      	mov	r0, r5
    1126:	f7ff fb01 	bl	72c <_Unwind_VRS_Set>
    112a:	e7a4      	b.n	1076 <__gnu_unwind_execute+0xe>
    112c:	4630      	mov	r0, r6
    112e:	f7ff ff6f 	bl	1010 <next_unwind_byte>
    1132:	0224      	lsls	r4, r4, #8
    1134:	4320      	orrs	r0, r4
    1136:	f5b0 4f00 	cmp.w	r0, #32768	; 0x8000
    113a:	d0c2      	beq.n	10c2 <__gnu_unwind_execute+0x5a>
    113c:	0104      	lsls	r4, r0, #4
    113e:	2300      	movs	r3, #0
    1140:	b2a2      	uxth	r2, r4
    1142:	4619      	mov	r1, r3
    1144:	4628      	mov	r0, r5
    1146:	f7ff fcb1 	bl	aac <_Unwind_VRS_Pop>
    114a:	2800      	cmp	r0, #0
    114c:	d1b9      	bne.n	10c2 <__gnu_unwind_execute+0x5a>
    114e:	f414 4f00 	tst.w	r4, #32768	; 0x8000
    1152:	bf18      	it	ne
    1154:	f04f 0801 	movne.w	r8, #1
    1158:	e78d      	b.n	1076 <__gnu_unwind_execute+0xe>
    115a:	43c2      	mvns	r2, r0
    115c:	f002 0307 	and.w	r3, r2, #7
    1160:	f44f 627f 	mov.w	r2, #4080	; 0xff0
    1164:	411a      	asrs	r2, r3
    1166:	0701      	lsls	r1, r0, #28
    1168:	f402 627f 	and.w	r2, r2, #4080	; 0xff0
    116c:	f04f 0300 	mov.w	r3, #0
    1170:	bf48      	it	mi
    1172:	f442 4280 	orrmi.w	r2, r2, #16384	; 0x4000
    1176:	4619      	mov	r1, r3
    1178:	4628      	mov	r0, r5
    117a:	f7ff fc97 	bl	aac <_Unwind_VRS_Pop>
    117e:	2800      	cmp	r0, #0
    1180:	f43f af79 	beq.w	1076 <__gnu_unwind_execute+0xe>
    1184:	e79d      	b.n	10c2 <__gnu_unwind_execute+0x5a>
    1186:	28b1      	cmp	r0, #177	; 0xb1
    1188:	d03b      	beq.n	1202 <__gnu_unwind_execute+0x19a>
    118a:	28b2      	cmp	r0, #178	; 0xb2
    118c:	f000 8093 	beq.w	12b6 <__gnu_unwind_execute+0x24e>
    1190:	28b3      	cmp	r0, #179	; 0xb3
    1192:	d041      	beq.n	1218 <__gnu_unwind_execute+0x1b0>
    1194:	f000 03fc 	and.w	r3, r0, #252	; 0xfc
    1198:	2bb4      	cmp	r3, #180	; 0xb4
    119a:	d092      	beq.n	10c2 <__gnu_unwind_execute+0x5a>
    119c:	f000 0207 	and.w	r2, r0, #7
    11a0:	3201      	adds	r2, #1
    11a2:	2301      	movs	r3, #1
    11a4:	f442 2200 	orr.w	r2, r2, #524288	; 0x80000
    11a8:	4619      	mov	r1, r3
    11aa:	4628      	mov	r0, r5
    11ac:	f7ff fc7e 	bl	aac <_Unwind_VRS_Pop>
    11b0:	2800      	cmp	r0, #0
    11b2:	f43f af60 	beq.w	1076 <__gnu_unwind_execute+0xe>
    11b6:	e784      	b.n	10c2 <__gnu_unwind_execute+0x5a>
    11b8:	28c6      	cmp	r0, #198	; 0xc6
    11ba:	d04a      	beq.n	1252 <__gnu_unwind_execute+0x1ea>
    11bc:	28c7      	cmp	r0, #199	; 0xc7
    11be:	d054      	beq.n	126a <__gnu_unwind_execute+0x202>
    11c0:	f000 03f8 	and.w	r3, r0, #248	; 0xf8
    11c4:	2bc0      	cmp	r3, #192	; 0xc0
    11c6:	d063      	beq.n	1290 <__gnu_unwind_execute+0x228>
    11c8:	28c8      	cmp	r0, #200	; 0xc8
    11ca:	d068      	beq.n	129e <__gnu_unwind_execute+0x236>
    11cc:	28c9      	cmp	r0, #201	; 0xc9
    11ce:	f47f af78 	bne.w	10c2 <__gnu_unwind_execute+0x5a>
    11d2:	4630      	mov	r0, r6
    11d4:	f7ff ff1c 	bl	1010 <next_unwind_byte>
    11d8:	0302      	lsls	r2, r0, #12
    11da:	f000 000f 	and.w	r0, r0, #15
    11de:	f402 2270 	and.w	r2, r2, #983040	; 0xf0000
    11e2:	3001      	adds	r0, #1
    11e4:	4302      	orrs	r2, r0
    11e6:	2101      	movs	r1, #1
    11e8:	2305      	movs	r3, #5
    11ea:	4628      	mov	r0, r5
    11ec:	f7ff fc5e 	bl	aac <_Unwind_VRS_Pop>
    11f0:	2800      	cmp	r0, #0
    11f2:	f43f af40 	beq.w	1076 <__gnu_unwind_execute+0xe>
    11f6:	e764      	b.n	10c2 <__gnu_unwind_execute+0x5a>
    11f8:	f1b8 0f00 	cmp.w	r8, #0
    11fc:	d018      	beq.n	1230 <__gnu_unwind_execute+0x1c8>
    11fe:	2000      	movs	r0, #0
    1200:	e760      	b.n	10c4 <__gnu_unwind_execute+0x5c>
    1202:	4630      	mov	r0, r6
    1204:	f7ff ff04 	bl	1010 <next_unwind_byte>
    1208:	4602      	mov	r2, r0
    120a:	2800      	cmp	r0, #0
    120c:	f43f af59 	beq.w	10c2 <__gnu_unwind_execute+0x5a>
    1210:	f010 03f0 	ands.w	r3, r0, #240	; 0xf0
    1214:	d0c8      	beq.n	11a8 <__gnu_unwind_execute+0x140>
    1216:	e754      	b.n	10c2 <__gnu_unwind_execute+0x5a>
    1218:	4630      	mov	r0, r6
    121a:	f7ff fef9 	bl	1010 <next_unwind_byte>
    121e:	0302      	lsls	r2, r0, #12
    1220:	f000 030f 	and.w	r3, r0, #15
    1224:	3301      	adds	r3, #1
    1226:	f402 2270 	and.w	r2, r2, #983040	; 0xf0000
    122a:	431a      	orrs	r2, r3
    122c:	2301      	movs	r3, #1
    122e:	e7bb      	b.n	11a8 <__gnu_unwind_execute+0x140>
    1230:	ac03      	add	r4, sp, #12
    1232:	4643      	mov	r3, r8
    1234:	220e      	movs	r2, #14
    1236:	4641      	mov	r1, r8
    1238:	9400      	str	r4, [sp, #0]
    123a:	4628      	mov	r0, r5
    123c:	f7ff fa50 	bl	6e0 <_Unwind_VRS_Get>
    1240:	9400      	str	r4, [sp, #0]
    1242:	4643      	mov	r3, r8
    1244:	220f      	movs	r2, #15
    1246:	4641      	mov	r1, r8
    1248:	4628      	mov	r0, r5
    124a:	f7ff fa6f 	bl	72c <_Unwind_VRS_Set>
    124e:	4640      	mov	r0, r8
    1250:	e738      	b.n	10c4 <__gnu_unwind_execute+0x5c>
    1252:	4630      	mov	r0, r6
    1254:	f7ff fedc 	bl	1010 <next_unwind_byte>
    1258:	0302      	lsls	r2, r0, #12
    125a:	f000 030f 	and.w	r3, r0, #15
    125e:	3301      	adds	r3, #1
    1260:	f402 2270 	and.w	r2, r2, #983040	; 0xf0000
    1264:	431a      	orrs	r2, r3
    1266:	2303      	movs	r3, #3
    1268:	e79e      	b.n	11a8 <__gnu_unwind_execute+0x140>
    126a:	4630      	mov	r0, r6
    126c:	f7ff fed0 	bl	1010 <next_unwind_byte>
    1270:	4602      	mov	r2, r0
    1272:	2800      	cmp	r0, #0
    1274:	f43f af25 	beq.w	10c2 <__gnu_unwind_execute+0x5a>
    1278:	f010 03f0 	ands.w	r3, r0, #240	; 0xf0
    127c:	f47f af21 	bne.w	10c2 <__gnu_unwind_execute+0x5a>
    1280:	2104      	movs	r1, #4
    1282:	4628      	mov	r0, r5
    1284:	f7ff fc12 	bl	aac <_Unwind_VRS_Pop>
    1288:	2800      	cmp	r0, #0
    128a:	f43f aef4 	beq.w	1076 <__gnu_unwind_execute+0xe>
    128e:	e718      	b.n	10c2 <__gnu_unwind_execute+0x5a>
    1290:	f000 020f 	and.w	r2, r0, #15
    1294:	3201      	adds	r2, #1
    1296:	2303      	movs	r3, #3
    1298:	f442 2220 	orr.w	r2, r2, #655360	; 0xa0000
    129c:	e784      	b.n	11a8 <__gnu_unwind_execute+0x140>
    129e:	4630      	mov	r0, r6
    12a0:	f7ff feb6 	bl	1010 <next_unwind_byte>
    12a4:	f000 02f0 	and.w	r2, r0, #240	; 0xf0
    12a8:	f000 030f 	and.w	r3, r0, #15
    12ac:	3210      	adds	r2, #16
    12ae:	3301      	adds	r3, #1
    12b0:	ea43 3202 	orr.w	r2, r3, r2, lsl #12
    12b4:	e797      	b.n	11e6 <__gnu_unwind_execute+0x17e>
    12b6:	2300      	movs	r3, #0
    12b8:	f10d 090c 	add.w	r9, sp, #12
    12bc:	220d      	movs	r2, #13
    12be:	4619      	mov	r1, r3
    12c0:	f8cd 9000 	str.w	r9, [sp]
    12c4:	4628      	mov	r0, r5
    12c6:	f7ff fa0b 	bl	6e0 <_Unwind_VRS_Get>
    12ca:	4630      	mov	r0, r6
    12cc:	f7ff fea0 	bl	1010 <next_unwind_byte>
    12d0:	0602      	lsls	r2, r0, #24
    12d2:	f04f 0402 	mov.w	r4, #2
    12d6:	d50c      	bpl.n	12f2 <__gnu_unwind_execute+0x28a>
    12d8:	9b03      	ldr	r3, [sp, #12]
    12da:	f000 007f 	and.w	r0, r0, #127	; 0x7f
    12de:	40a0      	lsls	r0, r4
    12e0:	4418      	add	r0, r3
    12e2:	9003      	str	r0, [sp, #12]
    12e4:	4630      	mov	r0, r6
    12e6:	f7ff fe93 	bl	1010 <next_unwind_byte>
    12ea:	0603      	lsls	r3, r0, #24
    12ec:	f104 0407 	add.w	r4, r4, #7
    12f0:	d4f2      	bmi.n	12d8 <__gnu_unwind_execute+0x270>
    12f2:	9b03      	ldr	r3, [sp, #12]
    12f4:	f8cd 9000 	str.w	r9, [sp]
    12f8:	f000 027f 	and.w	r2, r0, #127	; 0x7f
    12fc:	40a2      	lsls	r2, r4
    12fe:	f503 7301 	add.w	r3, r3, #516	; 0x204
    1302:	441a      	add	r2, r3
    1304:	2300      	movs	r3, #0
    1306:	9203      	str	r2, [sp, #12]
    1308:	4619      	mov	r1, r3
    130a:	220d      	movs	r2, #13
    130c:	4628      	mov	r0, r5
    130e:	f7ff fa0d 	bl	72c <_Unwind_VRS_Set>
    1312:	e6b0      	b.n	1076 <__gnu_unwind_execute+0xe>

00001314 <__gnu_unwind_frame>:
    1314:	b510      	push	{r4, lr}
    1316:	6cc2      	ldr	r2, [r0, #76]	; 0x4c
    1318:	6853      	ldr	r3, [r2, #4]
    131a:	b084      	sub	sp, #16
    131c:	f04f 0c03 	mov.w	ip, #3
    1320:	3208      	adds	r2, #8
    1322:	021c      	lsls	r4, r3, #8
    1324:	4608      	mov	r0, r1
    1326:	0e1b      	lsrs	r3, r3, #24
    1328:	a901      	add	r1, sp, #4
    132a:	9401      	str	r4, [sp, #4]
    132c:	9202      	str	r2, [sp, #8]
    132e:	f88d c00c 	strb.w	ip, [sp, #12]
    1332:	f88d 300d 	strb.w	r3, [sp, #13]
    1336:	f7ff fe97 	bl	1068 <__gnu_unwind_execute>
    133a:	b004      	add	sp, #16
    133c:	bd10      	pop	{r4, pc}
    133e:	bf00      	nop

00001340 <_Unwind_GetRegionStart>:
    1340:	b508      	push	{r3, lr}
    1342:	f7ff fe8f 	bl	1064 <unwind_UCB_from_context>
    1346:	6c80      	ldr	r0, [r0, #72]	; 0x48
    1348:	bd08      	pop	{r3, pc}
    134a:	bf00      	nop

0000134c <_Unwind_GetLanguageSpecificData>:
    134c:	b508      	push	{r3, lr}
    134e:	f7ff fe89 	bl	1064 <unwind_UCB_from_context>
    1352:	6cc0      	ldr	r0, [r0, #76]	; 0x4c
    1354:	79c3      	ldrb	r3, [r0, #7]
    1356:	3302      	adds	r3, #2
    1358:	eb00 0083 	add.w	r0, r0, r3, lsl #2
    135c:	bd08      	pop	{r3, pc}
    135e:	bf00      	nop

Disassembly of section .text.WORD_TO_REAL:

00001360 <WORD_TO_REAL>:
    1360:	b580      	push	{r7, lr}
    1362:	466f      	mov	r7, sp
    1364:	4608      	mov	r0, r1
    1366:	f7fe ff29 	bl	1bc <__aeabi_ui2f>
    136a:	bd80      	pop	{r7, pc}

Disassembly of section .text.main.init:

0000136c <main.init>:
    136c:	2001      	movs	r0, #1
    136e:	f649 1c99 	movw	ip, #39321	; 0x9999
    1372:	f649 129a 	movw	r2, #39322	; 0x999a
    1376:	f24b 2300 	movw	r3, #45568	; 0xb200
    137a:	7008      	strb	r0, [r1, #0]
    137c:	f6c3 7cf1 	movt	ip, #16369	; 0x3ff1
    1380:	f6c9 1299 	movt	r2, #39321	; 0x9999
    1384:	f2c4 03a0 	movt	r3, #16544	; 0x40a0
    1388:	2000      	movs	r0, #0
    138a:	f8c1 2001 	str.w	r2, [r1, #1]
    138e:	f8c1 c005 	str.w	ip, [r1, #5]
    1392:	f8c1 0009 	str.w	r0, [r1, #9]
    1396:	f8c1 300d 	str.w	r3, [r1, #13]
    139a:	f8a1 000d 	strh.w	r0, [r1, #13]
    139e:	73c8      	strb	r0, [r1, #15]
    13a0:	4770      	bx	lr

Disassembly of section .text.main:

000013a4 <main>:
    13a4:	b510      	push	{r4, lr}
    13a6:	4604      	mov	r4, r0
    13a8:	20ff      	movs	r0, #255	; 0xff
    13aa:	f8b4 1042 	ldrh.w	r1, [r4, #66]	; 0x42
    13ae:	f884 0141 	strb.w	r0, [r4, #321]	; 0x141
    13b2:	4620      	mov	r0, r4
    13b4:	f7ff ffd4 	bl	1360 <WORD_TO_REAL>
    13b8:	2100      	movs	r1, #0
    13ba:	f7fe ffaf 	bl	31c <__aeabi_fcmple>
    13be:	f894 1140 	ldrb.w	r1, [r4, #320]	; 0x140
    13c2:	fab0 f080 	clz	r0, r0
    13c6:	0940      	lsrs	r0, r0, #5
    13c8:	f001 01fe 	and.w	r1, r1, #254	; 0xfe
    13cc:	4408      	add	r0, r1
    13ce:	f8b4 1042 	ldrh.w	r1, [r4, #66]	; 0x42
    13d2:	f884 0140 	strb.w	r0, [r4, #320]	; 0x140
    13d6:	4620      	mov	r0, r4
    13d8:	f7ff ffc2 	bl	1360 <WORD_TO_REAL>
    13dc:	2100      	movs	r1, #0
    13de:	f2c4 21c8 	movt	r1, #17096	; 0x42c8
    13e2:	f7fe ff9b 	bl	31c <__aeabi_fcmple>
    13e6:	f894 1140 	ldrb.w	r1, [r4, #320]	; 0x140
    13ea:	fab0 f080 	clz	r0, r0
    13ee:	0940      	lsrs	r0, r0, #5
    13f0:	f001 01fd 	and.w	r1, r1, #253	; 0xfd
    13f4:	ea41 0040 	orr.w	r0, r1, r0, lsl #1
    13f8:	f8b4 1042 	ldrh.w	r1, [r4, #66]	; 0x42
    13fc:	f884 0140 	strb.w	r0, [r4, #320]	; 0x140
    1400:	4620      	mov	r0, r4
    1402:	f7ff ffad 	bl	1360 <WORD_TO_REAL>
    1406:	2100      	movs	r1, #0
    1408:	f2c4 3148 	movt	r1, #17224	; 0x4348
    140c:	f7fe ff86 	bl	31c <__aeabi_fcmple>
    1410:	f894 1140 	ldrb.w	r1, [r4, #320]	; 0x140
    1414:	fab0 f080 	clz	r0, r0
    1418:	0940      	lsrs	r0, r0, #5
    141a:	f001 01fb 	and.w	r1, r1, #251	; 0xfb
    141e:	ea41 0080 	orr.w	r0, r1, r0, lsl #2
    1422:	f8b4 1042 	ldrh.w	r1, [r4, #66]	; 0x42
    1426:	f884 0140 	strb.w	r0, [r4, #320]	; 0x140
    142a:	4620      	mov	r0, r4
    142c:	f7ff ff98 	bl	1360 <WORD_TO_REAL>
    1430:	2100      	movs	r1, #0
    1432:	f2c4 3196 	movt	r1, #17302	; 0x4396
    1436:	f7fe ff71 	bl	31c <__aeabi_fcmple>
    143a:	f894 1140 	ldrb.w	r1, [r4, #320]	; 0x140
    143e:	fab0 f080 	clz	r0, r0
    1442:	0940      	lsrs	r0, r0, #5
    1444:	f001 01f7 	and.w	r1, r1, #247	; 0xf7
    1448:	ea41 00c0 	orr.w	r0, r1, r0, lsl #3
    144c:	f8b4 1042 	ldrh.w	r1, [r4, #66]	; 0x42
    1450:	f884 0140 	strb.w	r0, [r4, #320]	; 0x140
    1454:	4620      	mov	r0, r4
    1456:	f7ff ff83 	bl	1360 <WORD_TO_REAL>
    145a:	2100      	movs	r1, #0
    145c:	f2c4 31c8 	movt	r1, #17352	; 0x43c8
    1460:	f7fe ff5c 	bl	31c <__aeabi_fcmple>
    1464:	f894 1140 	ldrb.w	r1, [r4, #320]	; 0x140
    1468:	fab0 f080 	clz	r0, r0
    146c:	0940      	lsrs	r0, r0, #5
    146e:	f001 01ef 	and.w	r1, r1, #239	; 0xef
    1472:	ea41 1000 	orr.w	r0, r1, r0, lsl #4
    1476:	f8b4 1042 	ldrh.w	r1, [r4, #66]	; 0x42
    147a:	f884 0140 	strb.w	r0, [r4, #320]	; 0x140
    147e:	4620      	mov	r0, r4
    1480:	f7ff ff6e 	bl	1360 <WORD_TO_REAL>
    1484:	2100      	movs	r1, #0
    1486:	f2c4 31fa 	movt	r1, #17402	; 0x43fa
    148a:	f7fe ff47 	bl	31c <__aeabi_fcmple>
    148e:	f894 1140 	ldrb.w	r1, [r4, #320]	; 0x140
    1492:	fab0 f080 	clz	r0, r0
    1496:	0940      	lsrs	r0, r0, #5
    1498:	f001 01df 	and.w	r1, r1, #223	; 0xdf
    149c:	ea41 1040 	orr.w	r0, r1, r0, lsl #5
    14a0:	f8b4 1042 	ldrh.w	r1, [r4, #66]	; 0x42
    14a4:	f884 0140 	strb.w	r0, [r4, #320]	; 0x140
    14a8:	4620      	mov	r0, r4
    14aa:	f7ff ff59 	bl	1360 <WORD_TO_REAL>
    14ae:	2100      	movs	r1, #0
    14b0:	f2c4 4116 	movt	r1, #17430	; 0x4416
    14b4:	f7fe ff32 	bl	31c <__aeabi_fcmple>
    14b8:	f894 1140 	ldrb.w	r1, [r4, #320]	; 0x140
    14bc:	fab0 f080 	clz	r0, r0
    14c0:	0940      	lsrs	r0, r0, #5
    14c2:	f001 01bf 	and.w	r1, r1, #191	; 0xbf
    14c6:	ea41 1080 	orr.w	r0, r1, r0, lsl #6
    14ca:	f8b4 1042 	ldrh.w	r1, [r4, #66]	; 0x42
    14ce:	f884 0140 	strb.w	r0, [r4, #320]	; 0x140
    14d2:	4620      	mov	r0, r4
    14d4:	f7ff ff44 	bl	1360 <WORD_TO_REAL>
    14d8:	2100      	movs	r1, #0
    14da:	f2c4 412f 	movt	r1, #17455	; 0x442f
    14de:	f7fe ff1d 	bl	31c <__aeabi_fcmple>
    14e2:	f894 1140 	ldrb.w	r1, [r4, #320]	; 0x140
    14e6:	fab0 f080 	clz	r0, r0
    14ea:	0940      	lsrs	r0, r0, #5
    14ec:	f001 017f 	and.w	r1, r1, #127	; 0x7f
    14f0:	ea41 10c0 	orr.w	r0, r1, r0, lsl #7
    14f4:	f884 0140 	strb.w	r0, [r4, #320]	; 0x140
    14f8:	bd10      	pop	{r4, pc}

Disassembly of section .text.abort:

000014fc <abort>:
    14fc:	b508      	push	{r3, lr}
    14fe:	2006      	movs	r0, #6
    1500:	f000 f804 	bl	150c <raise>
    1504:	2001      	movs	r0, #1
    1506:	f000 f857 	bl	15b8 <_exit>
    150a:	bf00      	nop

Disassembly of section .text.raise:

0000150c <raise>:
    150c:	b538      	push	{r3, r4, r5, lr}
    150e:	4b15      	ldr	r3, [pc, #84]	; (1564 <raise+0x58>)
    1510:	281f      	cmp	r0, #31
    1512:	681d      	ldr	r5, [r3, #0]
    1514:	d820      	bhi.n	1558 <raise+0x4c>
    1516:	f8d5 22dc 	ldr.w	r2, [r5, #732]	; 0x2dc
    151a:	4604      	mov	r4, r0
    151c:	b162      	cbz	r2, 1538 <raise+0x2c>
    151e:	f852 3020 	ldr.w	r3, [r2, r0, lsl #2]
    1522:	b14b      	cbz	r3, 1538 <raise+0x2c>
    1524:	2b01      	cmp	r3, #1
    1526:	d015      	beq.n	1554 <raise+0x48>
    1528:	1c59      	adds	r1, r3, #1
    152a:	d00f      	beq.n	154c <raise+0x40>
    152c:	2500      	movs	r5, #0
    152e:	f842 5020 	str.w	r5, [r2, r0, lsl #2]
    1532:	4798      	blx	r3
    1534:	4628      	mov	r0, r5
    1536:	bd38      	pop	{r3, r4, r5, pc}
    1538:	4628      	mov	r0, r5
    153a:	f000 f82b 	bl	1594 <_getpid_r>
    153e:	4622      	mov	r2, r4
    1540:	4601      	mov	r1, r0
    1542:	4628      	mov	r0, r5
    1544:	e8bd 4038 	ldmia.w	sp!, {r3, r4, r5, lr}
    1548:	f000 b80e 	b.w	1568 <_kill_r>
    154c:	2316      	movs	r3, #22
    154e:	602b      	str	r3, [r5, #0]
    1550:	2001      	movs	r0, #1
    1552:	bd38      	pop	{r3, r4, r5, pc}
    1554:	2000      	movs	r0, #0
    1556:	bd38      	pop	{r3, r4, r5, pc}
    1558:	2316      	movs	r3, #22
    155a:	602b      	str	r3, [r5, #0]
    155c:	f04f 30ff 	mov.w	r0, #4294967295
    1560:	bd38      	pop	{r3, r4, r5, pc}
    1562:	bf00      	nop
    1564:	00001718 	andeq	r1, r0, r8, lsl r7

Disassembly of section .text._kill_r:

00001568 <_kill_r>:
    1568:	b570      	push	{r4, r5, r6, lr}
    156a:	460c      	mov	r4, r1
    156c:	4d08      	ldr	r5, [pc, #32]	; (1590 <_kill_r+0x28>)
    156e:	4603      	mov	r3, r0
    1570:	2600      	movs	r6, #0
    1572:	4620      	mov	r0, r4
    1574:	4611      	mov	r1, r2
    1576:	461c      	mov	r4, r3
    1578:	602e      	str	r6, [r5, #0]
    157a:	f000 f80d 	bl	1598 <_kill>
    157e:	1c43      	adds	r3, r0, #1
    1580:	d000      	beq.n	1584 <_kill_r+0x1c>
    1582:	bd70      	pop	{r4, r5, r6, pc}
    1584:	682b      	ldr	r3, [r5, #0]
    1586:	2b00      	cmp	r3, #0
    1588:	d0fb      	beq.n	1582 <_kill_r+0x1a>
    158a:	6023      	str	r3, [r4, #0]
    158c:	bd70      	pop	{r4, r5, r6, pc}
    158e:	bf00      	nop
    1590:	000015bc 			; <UNDEFINED> instruction: 0x000015bc

Disassembly of section .text._getpid_r:

00001594 <_getpid_r>:
    1594:	f000 b808 	b.w	15a8 <_getpid>

Disassembly of section .text._kill:

00001598 <_kill>:
    1598:	4b02      	ldr	r3, [pc, #8]	; (15a4 <_kill+0xc>)
    159a:	2258      	movs	r2, #88	; 0x58
    159c:	601a      	str	r2, [r3, #0]
    159e:	f04f 30ff 	mov.w	r0, #4294967295
    15a2:	4770      	bx	lr
    15a4:	000015bc 			; <UNDEFINED> instruction: 0x000015bc

Disassembly of section .text._getpid:

000015a8 <_getpid>:
    15a8:	4b02      	ldr	r3, [pc, #8]	; (15b4 <_getpid+0xc>)
    15aa:	2258      	movs	r2, #88	; 0x58
    15ac:	601a      	str	r2, [r3, #0]
    15ae:	f04f 30ff 	mov.w	r0, #4294967295
    15b2:	4770      	bx	lr
    15b4:	000015bc 			; <UNDEFINED> instruction: 0x000015bc

Disassembly of section .text._exit:

000015b8 <_exit>:
    15b8:	e7fe      	b.n	15b8 <_exit>
    15ba:	bf00      	nop

Disassembly of section .bss.errno:

000015bc <errno>:
    15bc:	00000000 	andeq	r0, r0, r0

Disassembly of section .ARM.attributes:

00000000 <.ARM.attributes>:
   0:	00004441 	andeq	r4, r0, r1, asr #8
   4:	61656100 	cmnvs	r5, r0, lsl #2
   8:	01006962 	tsteq	r0, r2, ror #18
   c:	0000003a 	andeq	r0, r0, sl, lsr r0
  10:	302e3243 	eorcc	r3, lr, r3, asr #4
  14:	63050039 	movwvs	r0, #20537	; 0x5039
  18:	6574726f 	ldrbvs	r7, [r4, #-623]!	; 0xfffffd91
  1c:	346d2d78 	strbtcc	r2, [sp], #-3448	; 0xfffff288
  20:	070d0600 	streq	r0, [sp, -r0, lsl #12]
  24:	0900084d 	stmdbeq	r0, {r0, r2, r3, r6, fp}
  28:	0f000e02 	svceq	0x00000e02
  2c:	11011001 	tstne	r1, r1
  30:	14041202 	strne	r1, [r4], #-514	; 0xfffffdfe
  34:	17001501 	strne	r1, [r0, -r1, lsl #10]
  38:	19011803 	stmdbne	r1, {r0, r1, fp, ip}
  3c:	1e021a01 	vmlane.f32	s2, s4, s2
  40:	26002203 	strcs	r2, [r0], -r3, lsl #4
  44:	Address 0x00000044 is out of bounds.


Disassembly of section .comment:

00000000 <.comment>:
   0:	6e616c63 	cdpvs	12, 6, cr6, cr1, cr3, {3}
   4:	65762067 	ldrbvs	r2, [r6, #-103]!	; 0xffffff99
   8:	6f697372 	svcvs	0x00697372
   c:	3831206e 	ldmdacc	r1!, {r1, r2, r3, r5, r6, sp}
  10:	382e312e 	stmdacc	lr!, {r1, r2, r3, r5, r8, ip, sp}
  14:	694c0000 	stmdbvs	ip, {}^	; <UNPREDICTABLE>
  18:	72656b6e 	rsbvc	r6, r5, #112640	; 0x1b800
  1c:	4c4c203a 	mcrrmi	0, 3, r2, ip, cr10
  20:	38312044 	ldmdacc	r1!, {r2, r6, sp}
  24:	382e312e 	stmdacc	lr!, {r1, r2, r3, r5, r8, ip, sp}
	...

Disassembly of section .debug_frame:

00000000 <.debug_frame>:
   0:	0000000c 	andeq	r0, r0, ip
   4:	ffffffff 			; <UNDEFINED> instruction: 0xffffffff
   8:	7c020001 	stcvc	0, cr0, [r2], {1}
   c:	000d0c0e 	andeq	r0, sp, lr, lsl #24
  10:	00000010 	andeq	r0, r0, r0, lsl r0
  14:	00000000 	andeq	r0, r0, r0
  18:	00000050 	andeq	r0, r0, r0, asr r0
  1c:	0000016c 	andeq	r0, r0, ip, ror #2
  20:	0bb6020a 	bleq	fed80850 <_edata+0xfed7ed08>
  24:	00000010 	andeq	r0, r0, r0, lsl r0
  28:	00000000 	andeq	r0, r0, r0
  2c:	000001bc 			; <UNDEFINED> instruction: 0x000001bc
  30:	00000024 	andeq	r0, r0, r4, lsr #32
  34:	000b520a 	andeq	r5, fp, sl, lsl #4
  38:	00000010 	andeq	r0, r0, r0, lsl r0
  3c:	00000000 	andeq	r0, r0, r0
  40:	000001e0 	andeq	r0, r0, r0, ror #3
  44:	0000008c 	andeq	r0, r0, ip, lsl #1
  48:	0b46020a 	bleq	1180878 <_edata+0x117ed30>
  4c:	0000000c 	andeq	r0, r0, ip
  50:	ffffffff 			; <UNDEFINED> instruction: 0xffffffff
  54:	7c020001 	stcvc	0, cr0, [r2], {1}
  58:	000d0c0e 	andeq	r0, sp, lr, lsl #24
  5c:	0000001c 	andeq	r0, r0, ip, lsl r0
  60:	0000004c 	andeq	r0, r0, ip, asr #32
  64:	00000000 	andeq	r0, r0, r0
  68:	00000282 	andeq	r0, r0, r2, lsl #5
  6c:	0c0e470a 	stceq	7, cr4, [lr], {10}
  70:	02850384 	addeq	r0, r5, #132, 6	; 0x10000002
  74:	3a03018e 	bcc	c06b4 <_edata+0xbeb6c>
  78:	00000b01 	andeq	r0, r0, r1, lsl #22
  7c:	00000018 	andeq	r0, r0, r8, lsl r0
  80:	0000004c 	andeq	r0, r0, ip, asr #32
  84:	00000000 	andeq	r0, r0, r0
  88:	0000001e 	andeq	r0, r0, lr, lsl r0
  8c:	0c0e460a 	stceq	6, cr4, [lr], {10}
  90:	02850384 	addeq	r0, r5, #132, 6	; 0x10000002
  94:	0b49018e 	bleq	12406d4 <_edata+0x123eb8c>
  98:	00000018 	andeq	r0, r0, r8, lsl r0
  9c:	0000004c 	andeq	r0, r0, ip, asr #32
  a0:	00000000 	andeq	r0, r0, r0
  a4:	00000022 	andeq	r0, r0, r2, lsr #32
  a8:	0c0e460a 	stceq	6, cr4, [lr], {10}
  ac:	02850384 	addeq	r0, r5, #132, 6	; 0x10000002
  b0:	0b4b018e 	bleq	12c06f0 <_edata+0x12beba8>
  b4:	00000018 	andeq	r0, r0, r8, lsl r0
  b8:	0000004c 	andeq	r0, r0, ip, asr #32
  bc:	00000000 	andeq	r0, r0, r0
  c0:	00000042 	andeq	r0, r0, r2, asr #32
  c4:	0c0e5a0a 			; <UNDEFINED> instruction: 0x0c0e5a0a
  c8:	02850384 	addeq	r0, r5, #132, 6	; 0x10000002
  cc:	0b47018e 	bleq	11c070c <_edata+0x11bebc4>
  d0:	00000024 	andeq	r0, r0, r4, lsr #32
  d4:	0000004c 	andeq	r0, r0, ip, asr #32
  d8:	00000000 	andeq	r0, r0, r0
  dc:	0000006a 	andeq	r0, r0, sl, rrx
  e0:	0e450a0a 	vmlaeq.f32	s1, s10, s20
  e4:	8503840c 	strhi	r8, [r3, #-1036]	; 0xfffffbf4
  e8:	43018e02 	movwmi	r8, #7682	; 0x1e02
  ec:	0c0e450b 	cfstr32eq	mvfx4, [lr], {11}
  f0:	02850384 	addeq	r0, r5, #132, 6	; 0x10000002
  f4:	0b68018e 	bleq	1a00734 <_edata+0x19febec>
  f8:	0000000c 	andeq	r0, r0, ip
  fc:	ffffffff 			; <UNDEFINED> instruction: 0xffffffff
 100:	7c020001 	stcvc	0, cr0, [r2], {1}
 104:	000d0c0e 	andeq	r0, sp, lr, lsl #24
 108:	0000001c 	andeq	r0, r0, ip, lsl r0
 10c:	000000f8 	strdeq	r0, [r0], -r8
 110:	0000026c 	andeq	r0, r0, ip, ror #4
 114:	0000006e 	andeq	r0, r0, lr, rrx
 118:	040e4c0a 	streq	r4, [lr], #-3082	; 0xfffff3f6
 11c:	0e410a4a 	vmlseq.f32	s1, s2, s20
 120:	4e0b5100 	adfmie	f5, f3, f0
 124:	0b41000e 	bleq	1040164 <_edata+0x103e61c>
 128:	0000001c 	andeq	r0, r0, ip, lsl r0
 12c:	000000f8 	strdeq	r0, [r0], -r8
 130:	000002dc 	ldrdeq	r0, [r0], -ip
 134:	00000018 	andeq	r0, r0, r8, lsl r0
 138:	140e450a 	strne	r4, [lr], #-1290	; 0xfffffaf6
 13c:	04810580 	streq	r0, [r1], #1408	; 0x580
 140:	02830382 	addeq	r0, r3, #134217730	; 0x8000002
 144:	0b47018e 	bleq	11c0784 <_edata+0x11bec3c>
 148:	00000014 	andeq	r0, r0, r4, lsl r0
 14c:	000000f8 	strdeq	r0, [r0], -r8
 150:	000002f4 	strdeq	r0, [r0], -r4
 154:	00000012 	andeq	r0, r0, r2, lsl r0
 158:	080e420a 	stmdaeq	lr, {r1, r3, r9, lr}
 15c:	0b47028e 	bleq	11c0b9c <_edata+0x11bf054>
 160:	00000014 	andeq	r0, r0, r4, lsl r0
 164:	000000f8 	strdeq	r0, [r0], -r8
 168:	00000308 	andeq	r0, r0, r8, lsl #6
 16c:	00000012 	andeq	r0, r0, r2, lsl r0
 170:	080e420a 	stmdaeq	lr, {r1, r3, r9, lr}
 174:	0b47028e 	bleq	11c0bb4 <_edata+0x11bf06c>
 178:	00000014 	andeq	r0, r0, r4, lsl r0
 17c:	000000f8 	strdeq	r0, [r0], -r8
 180:	0000031c 	andeq	r0, r0, ip, lsl r3
 184:	00000012 	andeq	r0, r0, r2, lsl r0
 188:	080e420a 	stmdaeq	lr, {r1, r3, r9, lr}
 18c:	0b47028e 	bleq	11c0bcc <_edata+0x11bf084>
 190:	00000014 	andeq	r0, r0, r4, lsl r0
 194:	000000f8 	strdeq	r0, [r0], -r8
 198:	00000330 	andeq	r0, r0, r0, lsr r3
 19c:	00000012 	andeq	r0, r0, r2, lsl r0
 1a0:	080e420a 	stmdaeq	lr, {r1, r3, r9, lr}
 1a4:	0b47028e 	bleq	11c0be4 <_edata+0x11bf09c>
 1a8:	00000014 	andeq	r0, r0, r4, lsl r0
 1ac:	000000f8 	strdeq	r0, [r0], -r8
 1b0:	00000344 	andeq	r0, r0, r4, asr #6
 1b4:	00000012 	andeq	r0, r0, r2, lsl r0
 1b8:	080e420a 	stmdaeq	lr, {r1, r3, r9, lr}
 1bc:	0b47028e 	bleq	11c0bfc <_edata+0x11bf0b4>
 1c0:	0000000c 	andeq	r0, r0, ip
 1c4:	ffffffff 			; <UNDEFINED> instruction: 0xffffffff
 1c8:	7c020001 	stcvc	0, cr0, [r2], {1}
 1cc:	000d0c0e 	andeq	r0, sp, lr, lsl #24
 1d0:	00000010 	andeq	r0, r0, r0, lsl r0
 1d4:	000001c0 	andeq	r0, r0, r0, asr #3
 1d8:	00000000 	andeq	r0, r0, r0
 1dc:	0000004c 	andeq	r0, r0, ip, asr #32
 1e0:	000b660a 	andeq	r6, fp, sl, lsl #12
 1e4:	0000000c 	andeq	r0, r0, ip
 1e8:	ffffffff 			; <UNDEFINED> instruction: 0xffffffff
 1ec:	7c020001 	stcvc	0, cr0, [r2], {1}
 1f0:	000d0c0e 	andeq	r0, sp, lr, lsl #24
 1f4:	0000001c 	andeq	r0, r0, ip, lsl r0
 1f8:	000001e4 	andeq	r0, r0, r4, ror #3
 1fc:	00000000 	andeq	r0, r0, r0
 200:	00000026 	andeq	r0, r0, r6, lsr #32
 204:	84080e41 	strhi	r0, [r8], #-3649	; 0xfffff1bf
 208:	48018e02 	stmdami	r1, {r1, r9, sl, fp, pc}
 20c:	0ec4ce0a 	cdpeq	14, 12, cr12, cr4, cr10, {0}
 210:	000b4200 	andeq	r4, fp, r0, lsl #4
 214:	0000000c 	andeq	r0, r0, ip
 218:	ffffffff 			; <UNDEFINED> instruction: 0xffffffff
 21c:	7c020001 	stcvc	0, cr0, [r2], {1}
 220:	000d0c0e 	andeq	r0, sp, lr, lsl #24
 224:	00000018 	andeq	r0, r0, r8, lsl r0
 228:	00000214 	andeq	r0, r0, r4, lsl r2
 22c:	00000000 	andeq	r0, r0, r0
 230:	00000040 	andeq	r0, r0, r0, asr #32
 234:	84100e41 	ldrhi	r0, [r0], #-3649	; 0xfffff1bf
 238:	87038604 	strhi	r8, [r3, -r4, lsl #12]
 23c:	00018e02 	andeq	r8, r1, r2, lsl #28
 240:	0000000c 	andeq	r0, r0, ip
 244:	ffffffff 			; <UNDEFINED> instruction: 0xffffffff
 248:	7c020001 	stcvc	0, cr0, [r2], {1}
 24c:	000d0c0e 	andeq	r0, sp, lr, lsl #24
 250:	0000001c 	andeq	r0, r0, ip, lsl r0
 254:	00000240 	andeq	r0, r0, r0, asr #4
 258:	00000000 	andeq	r0, r0, r0
 25c:	00000254 	andeq	r0, r0, r4, asr r2
 260:	100e410a 	andne	r4, lr, sl, lsl #2
 264:	03850484 	orreq	r0, r5, #132, 8	; 0x84000000
 268:	018e0286 	orreq	r0, lr, r6, lsl #5
 26c:	0b012903 	bleq	4a680 <_edata+0x48b38>
 270:	0000000c 	andeq	r0, r0, ip
 274:	ffffffff 			; <UNDEFINED> instruction: 0xffffffff
 278:	7c020001 	stcvc	0, cr0, [r2], {1}
 27c:	000d0c0e 	andeq	r0, sp, lr, lsl #24
 280:	00000010 	andeq	r0, r0, r0, lsl r0
 284:	00000270 	andeq	r0, r0, r0, ror r2
 288:	00000000 	andeq	r0, r0, r0
 28c:	00000040 	andeq	r0, r0, r0, asr #32
 290:	000b600a 	andeq	r6, fp, sl
 294:	0000000c 	andeq	r0, r0, ip
 298:	ffffffff 			; <UNDEFINED> instruction: 0xffffffff
 29c:	7c020001 	stcvc	0, cr0, [r2], {1}
 2a0:	000d0c0e 	andeq	r0, sp, lr, lsl #24
 2a4:	00000010 	andeq	r0, r0, r0, lsl r0
 2a8:	00000294 	muleq	r0, r4, r2
 2ac:	00000000 	andeq	r0, r0, r0
 2b0:	0000003e 	andeq	r0, r0, lr, lsr r0
 2b4:	000b5f0a 	andeq	r5, fp, sl, lsl #30
 2b8:	0000000c 	andeq	r0, r0, ip
 2bc:	ffffffff 			; <UNDEFINED> instruction: 0xffffffff
 2c0:	7c020001 	stcvc	0, cr0, [r2], {1}
 2c4:	000d0c0e 	andeq	r0, sp, lr, lsl #24
 2c8:	0000001c 	andeq	r0, r0, ip, lsl r0
 2cc:	000002b8 			; <UNDEFINED> instruction: 0x000002b8
 2d0:	00000000 	andeq	r0, r0, r0
 2d4:	0000008a 	andeq	r0, r0, sl, lsl #1
 2d8:	040e4c0a 	streq	r4, [lr], #-3082	; 0xfffff3f6
 2dc:	0e410a4a 	vmlseq.f32	s1, s2, s20
 2e0:	520b5b00 	andpl	r5, fp, #0, 22
 2e4:	0b41000e 	bleq	1040324 <_edata+0x103e7dc>
 2e8:	00000018 	andeq	r0, r0, r8, lsl r0
 2ec:	000002b8 			; <UNDEFINED> instruction: 0x000002b8
 2f0:	00000000 	andeq	r0, r0, r0
 2f4:	00000020 	andeq	r0, r0, r0, lsr #32
 2f8:	080e490a 	stmdaeq	lr, {r1, r3, r8, fp, lr}
 2fc:	018e0280 	orreq	r0, lr, r0, lsl #5
 300:	00000b47 	andeq	r0, r0, r7, asr #22
 304:	00000014 	andeq	r0, r0, r4, lsl r0
 308:	000002b8 			; <UNDEFINED> instruction: 0x000002b8
 30c:	00000000 	andeq	r0, r0, r0
 310:	00000012 	andeq	r0, r0, r2, lsl r0
 314:	080e420a 	stmdaeq	lr, {r1, r3, r9, lr}
 318:	0b47028e 	bleq	11c0d58 <_edata+0x11bf210>
 31c:	00000014 	andeq	r0, r0, r4, lsl r0
 320:	000002b8 			; <UNDEFINED> instruction: 0x000002b8
 324:	00000000 	andeq	r0, r0, r0
 328:	00000012 	andeq	r0, r0, r2, lsl r0
 32c:	080e420a 	stmdaeq	lr, {r1, r3, r9, lr}
 330:	0b47028e 	bleq	11c0d70 <_edata+0x11bf228>
 334:	00000014 	andeq	r0, r0, r4, lsl r0
 338:	000002b8 			; <UNDEFINED> instruction: 0x000002b8
 33c:	00000000 	andeq	r0, r0, r0
 340:	00000012 	andeq	r0, r0, r2, lsl r0
 344:	080e420a 	stmdaeq	lr, {r1, r3, r9, lr}
 348:	0b47028e 	bleq	11c0d88 <_edata+0x11bf240>
 34c:	00000014 	andeq	r0, r0, r4, lsl r0
 350:	000002b8 			; <UNDEFINED> instruction: 0x000002b8
 354:	00000000 	andeq	r0, r0, r0
 358:	00000012 	andeq	r0, r0, r2, lsl r0
 35c:	080e420a 	stmdaeq	lr, {r1, r3, r9, lr}
 360:	0b47028e 	bleq	11c0da0 <_edata+0x11bf258>
 364:	00000014 	andeq	r0, r0, r4, lsl r0
 368:	000002b8 			; <UNDEFINED> instruction: 0x000002b8
 36c:	00000000 	andeq	r0, r0, r0
 370:	00000012 	andeq	r0, r0, r2, lsl r0
 374:	080e420a 	stmdaeq	lr, {r1, r3, r9, lr}
 378:	0b47028e 	bleq	11c0db8 <_edata+0x11bf270>
 37c:	0000000c 	andeq	r0, r0, ip
 380:	ffffffff 			; <UNDEFINED> instruction: 0xffffffff
 384:	7c020001 	stcvc	0, cr0, [r2], {1}
 388:	000d0c0e 	andeq	r0, sp, lr, lsl #24
 38c:	00000010 	andeq	r0, r0, r0, lsl r0
 390:	0000037c 	andeq	r0, r0, ip, ror r3
 394:	00000000 	andeq	r0, r0, r0
 398:	0000004e 	andeq	r0, r0, lr, asr #32
 39c:	000b670a 	andeq	r6, fp, sl, lsl #14
 3a0:	0000000c 	andeq	r0, r0, ip
 3a4:	ffffffff 			; <UNDEFINED> instruction: 0xffffffff
 3a8:	7c020001 	stcvc	0, cr0, [r2], {1}
 3ac:	000d0c0e 	andeq	r0, sp, lr, lsl #24
 3b0:	00000024 	andeq	r0, r0, r4, lsr #32
 3b4:	000003a0 	andeq	r0, r0, r0, lsr #7
 3b8:	00000000 	andeq	r0, r0, r0
 3bc:	00000032 	andeq	r0, r0, r2, lsr r0
 3c0:	83100e41 	tsthi	r0, #1040	; 0x410
 3c4:	85038404 	strhi	r8, [r3, #-1028]	; 0xfffffbfc
 3c8:	4d018e02 	stcmi	14, cr8, [r1, #-8]
 3cc:	c4c5ce0a 	strbgt	ip, [r5], #3594	; 0xe0a
 3d0:	42000ec3 	andmi	r0, r0, #3120	; 0xc30
 3d4:	0000000b 	andeq	r0, r0, fp
 3d8:	0000000c 	andeq	r0, r0, ip
 3dc:	ffffffff 			; <UNDEFINED> instruction: 0xffffffff
 3e0:	7c020001 	stcvc	0, cr0, [r2], {1}
 3e4:	000d0c0e 	andeq	r0, sp, lr, lsl #24
 3e8:	00000018 	andeq	r0, r0, r8, lsl r0
 3ec:	000003d8 	ldrdeq	r0, [r0], -r8
 3f0:	00000000 	andeq	r0, r0, r0
 3f4:	0000003c 	andeq	r0, r0, ip, lsr r0
 3f8:	84100e41 	ldrhi	r0, [r0], #-3649	; 0xfffff1bf
 3fc:	87038604 	strhi	r8, [r3, -r4, lsl #12]
 400:	00018e02 	andeq	r8, r1, r2, lsl #28
 404:	0000000c 	andeq	r0, r0, ip
 408:	ffffffff 			; <UNDEFINED> instruction: 0xffffffff
 40c:	7c020001 	stcvc	0, cr0, [r2], {1}
 410:	000d0c0e 	andeq	r0, sp, lr, lsl #24
 414:	00000010 	andeq	r0, r0, r0, lsl r0
 418:	00000404 	andeq	r0, r0, r4, lsl #8
 41c:	00000000 	andeq	r0, r0, r0
 420:	0000009e 	muleq	r0, lr, r0
 424:	0b4f020a 	bleq	13c0c54 <_edata+0x13bf10c>
 428:	0000000c 	andeq	r0, r0, ip
 42c:	ffffffff 			; <UNDEFINED> instruction: 0xffffffff
 430:	7c020001 	stcvc	0, cr0, [r2], {1}
 434:	000d0c0e 	andeq	r0, sp, lr, lsl #24
 438:	0000001c 	andeq	r0, r0, ip, lsl r0
 43c:	00000428 	andeq	r0, r0, r8, lsr #8
 440:	00000000 	andeq	r0, r0, r0
 444:	00000254 	andeq	r0, r0, r4, asr r2
 448:	100e410a 	andne	r4, lr, sl, lsl #2
 44c:	03850484 	orreq	r0, r5, #132, 8	; 0x84000000
 450:	018e0286 	orreq	r0, lr, r6, lsl #5
 454:	0b012903 	bleq	4a868 <_edata+0x48d20>
 458:	0000001c 	andeq	r0, r0, ip, lsl r0
 45c:	00000428 	andeq	r0, r0, r8, lsr #8
 460:	00000000 	andeq	r0, r0, r0
 464:	000001d0 	ldrdeq	r0, [r0], -r0	; <UNPREDICTABLE>
 468:	100e410a 	andne	r4, lr, sl, lsl #2
 46c:	03850484 	orreq	r0, r5, #132, 8	; 0x84000000
 470:	018e0286 	orreq	r0, lr, r6, lsl #5
 474:	000be702 	andeq	lr, fp, r2, lsl #14
 478:	0000000c 	andeq	r0, r0, ip
 47c:	ffffffff 			; <UNDEFINED> instruction: 0xffffffff
 480:	7c020001 	stcvc	0, cr0, [r2], {1}
 484:	000d0c0e 	andeq	r0, sp, lr, lsl #24
 488:	0000000c 	andeq	r0, r0, ip
 48c:	00000478 	andeq	r0, r0, r8, ror r4
 490:	00000358 	andeq	r0, r0, r8, asr r3
 494:	00000012 	andeq	r0, r0, r2, lsl r0
 498:	00000020 	andeq	r0, r0, r0, lsr #32
 49c:	00000478 	andeq	r0, r0, r8, ror r4
 4a0:	0000036c 	andeq	r0, r0, ip, ror #6
 4a4:	0000005c 	andeq	r0, r0, ip, asr r0
 4a8:	83200e42 			; <UNDEFINED> instruction: 0x83200e42
 4ac:	85078408 	strhi	r8, [r7, #-1032]	; 0xfffffbf8
 4b0:	87058606 	strhi	r8, [r5, -r6, lsl #12]
 4b4:	89038804 	stmdbhi	r3, {r2, fp, pc}
 4b8:	00018e02 	andeq	r8, r1, r2, lsl #28
 4bc:	0000000c 	andeq	r0, r0, ip
 4c0:	00000478 	andeq	r0, r0, r8, ror r4
 4c4:	000003c8 	andeq	r0, r0, r8, asr #7
 4c8:	00000028 	andeq	r0, r0, r8, lsr #32
 4cc:	0000002c 	andeq	r0, r0, ip, lsr #32
 4d0:	00000478 	andeq	r0, r0, r8, ror r4
 4d4:	000003f0 	strdeq	r0, [r0], -r0	; <UNPREDICTABLE>
 4d8:	0000009c 	muleq	r0, ip, r0
 4dc:	840c0e41 	strhi	r0, [ip], #-3649	; 0xfffff1bf
 4e0:	8e028503 	cfsh32hi	mvfx8, mvfx2, #3
 4e4:	180e4201 	stmdane	lr, {r0, r9, lr}
 4e8:	0c0e0a65 			; <UNDEFINED> instruction: 0x0c0e0a65
 4ec:	0a440b41 	beq	11031f8 <_edata+0x11016b0>
 4f0:	0b410c0e 	bleq	1043530 <_edata+0x10419e8>
 4f4:	0c0e0a51 			; <UNDEFINED> instruction: 0x0c0e0a51
 4f8:	00000b41 	andeq	r0, r0, r1, asr #22
 4fc:	00000018 	andeq	r0, r0, r8, lsl r0
 500:	00000478 	andeq	r0, r0, r8, ror r4
 504:	0000048c 	andeq	r0, r0, ip, lsl #9
 508:	00000058 	andeq	r0, r0, r8, asr r0
 50c:	84080e43 	strhi	r0, [r8], #-3651	; 0xfffff1bd
 510:	67018e02 	strvs	r8, [r1, -r2, lsl #28]
 514:	000ec4ce 	andeq	ip, lr, lr, asr #9
 518:	0000000c 	andeq	r0, r0, ip
 51c:	00000478 	andeq	r0, r0, r8, ror r4
 520:	000004e4 	andeq	r0, r0, r4, ror #9
 524:	00000004 	andeq	r0, r0, r4
 528:	0000000c 	andeq	r0, r0, ip
 52c:	00000478 	andeq	r0, r0, r8, ror r4
 530:	000004e8 	andeq	r0, r0, r8, ror #9
 534:	0000000a 	andeq	r0, r0, sl
 538:	0000000c 	andeq	r0, r0, ip
 53c:	00000478 	andeq	r0, r0, r8, ror r4
 540:	000004f4 	strdeq	r0, [r0], -r4
 544:	00000002 	andeq	r0, r0, r2
 548:	00000018 	andeq	r0, r0, r8, lsl r0
 54c:	00000478 	andeq	r0, r0, r8, ror r4
 550:	000004f8 	strdeq	r0, [r0], -r8
 554:	0000003a 	andeq	r0, r0, sl, lsr r0
 558:	84100e41 	ldrhi	r0, [r0], #-3649	; 0xfffff1bf
 55c:	86038504 	strhi	r8, [r3], -r4, lsl #10
 560:	00018e02 	andeq	r8, r1, r2, lsl #28
 564:	0000002c 	andeq	r0, r0, ip, lsr #32
 568:	00000478 	andeq	r0, r0, r8, ror r4
 56c:	00000534 	andeq	r0, r0, r4, lsr r5
 570:	000000ca 	andeq	r0, r0, sl, asr #1
 574:	84200e42 	strthi	r0, [r0], #-3650	; 0xfffff1be
 578:	86078508 	strhi	r8, [r7], -r8, lsl #10
 57c:	88058706 	stmdahi	r5, {r1, r2, r8, r9, sl, pc}
 580:	8a038904 	bhi	e2998 <_edata+0xe0e50>
 584:	4a018e02 	bmi	63d94 <_edata+0x6224c>
 588:	0207e80e 	andeq	lr, r7, #917504	; 0xe0000
 58c:	200e0a4e 	andcs	r0, lr, lr, asr #20
 590:	00000b42 	andeq	r0, r0, r2, asr #22
 594:	0000000c 	andeq	r0, r0, ip
 598:	00000478 	andeq	r0, r0, r8, ror r4
 59c:	00000600 	andeq	r0, r0, r0, lsl #12
 5a0:	00000004 	andeq	r0, r0, r4
 5a4:	00000024 	andeq	r0, r0, r4, lsr #32
 5a8:	00000478 	andeq	r0, r0, r8, ror r4
 5ac:	00000604 	andeq	r0, r0, r4, lsl #12
 5b0:	00000066 	andeq	r0, r0, r6, rrx
 5b4:	84140e41 	ldrhi	r0, [r4], #-3649	; 0xfffff1bf
 5b8:	86048505 	strhi	r8, [r4], -r5, lsl #10
 5bc:	8e028703 	cdphi	7, 0, cr8, cr2, cr3, {0}
 5c0:	f80e4901 			; <UNDEFINED> instruction: 0xf80e4901
 5c4:	0e0a5f03 	cdpeq	15, 0, cr5, cr10, cr3, {0}
 5c8:	000b4114 	andeq	r4, fp, r4, lsl r1
 5cc:	0000000c 	andeq	r0, r0, ip
 5d0:	00000478 	andeq	r0, r0, r8, ror r4
 5d4:	0000066c 	andeq	r0, r0, ip, ror #12
 5d8:	0000000e 	andeq	r0, r0, lr
 5dc:	00000018 	andeq	r0, r0, r8, lsl r0
 5e0:	00000478 	andeq	r0, r0, r8, ror r4
 5e4:	0000067c 	andeq	r0, r0, ip, ror r6
 5e8:	00000044 	andeq	r0, r0, r4, asr #32
 5ec:	84100e41 	ldrhi	r0, [r0], #-3649	; 0xfffff1bf
 5f0:	86038504 	strhi	r8, [r3], -r4, lsl #10
 5f4:	00018e02 	andeq	r8, r1, r2, lsl #28
 5f8:	0000000c 	andeq	r0, r0, ip
 5fc:	00000478 	andeq	r0, r0, r8, ror r4
 600:	000006c0 	andeq	r0, r0, r0, asr #13
 604:	0000000e 	andeq	r0, r0, lr
 608:	0000000c 	andeq	r0, r0, ip
 60c:	00000478 	andeq	r0, r0, r8, ror r4
 610:	000006d0 	ldrdeq	r0, [r0], -r0	; <UNPREDICTABLE>
 614:	00000002 	andeq	r0, r0, r2
 618:	0000000c 	andeq	r0, r0, ip
 61c:	00000478 	andeq	r0, r0, r8, ror r4
 620:	000006d4 	ldrdeq	r0, [r0], -r4
 624:	0000000c 	andeq	r0, r0, ip
 628:	0000000c 	andeq	r0, r0, ip
 62c:	00000478 	andeq	r0, r0, r8, ror r4
 630:	000006e0 	andeq	r0, r0, r0, ror #13
 634:	0000002e 	andeq	r0, r0, lr, lsr #32
 638:	00000018 	andeq	r0, r0, r8, lsl r0
 63c:	00000478 	andeq	r0, r0, r8, ror r4
 640:	00000710 	andeq	r0, r0, r0, lsl r7
 644:	0000001a 	andeq	r0, r0, sl, lsl r0
 648:	8e040e41 	cdphi	14, 0, cr0, cr4, cr1, {2}
 64c:	180e4101 	stmdane	lr, {r0, r8, lr}
 650:	00040e49 	andeq	r0, r4, r9, asr #28
 654:	0000000c 	andeq	r0, r0, ip
 658:	00000478 	andeq	r0, r0, r8, ror r4
 65c:	0000072c 	andeq	r0, r0, ip, lsr #14
 660:	0000002e 	andeq	r0, r0, lr, lsr #32
 664:	0000001c 	andeq	r0, r0, ip, lsl r0
 668:	00000478 	andeq	r0, r0, r8, ror r4
 66c:	0000075c 	andeq	r0, r0, ip, asr r7
 670:	00000018 	andeq	r0, r0, r8, lsl r0
 674:	84080e41 	strhi	r0, [r8], #-3649	; 0xfffff1bf
 678:	41018e02 	tstmi	r1, r2, lsl #28
 67c:	0e49180e 	cdpeq	8, 4, cr1, cr9, cr14, {0}
 680:	00000008 	andeq	r0, r0, r8
 684:	00000020 	andeq	r0, r0, r0, lsr #32
 688:	00000478 	andeq	r0, r0, r8, ror r4
 68c:	00000774 	andeq	r0, r0, r4, ror r7
 690:	00000084 	andeq	r0, r0, r4, lsl #1
 694:	84100e41 	ldrhi	r0, [r0], #-3649	; 0xfffff1bf
 698:	86038504 	strhi	r8, [r3], -r4, lsl #10
 69c:	4a018e02 	bmi	63eac <_edata+0x62364>
 6a0:	7604c80e 	strvc	ip, [r4], -lr, lsl #16
 6a4:	0000100e 	andeq	r1, r0, lr
 6a8:	00000030 	andeq	r0, r0, r0, lsr r0
 6ac:	00000478 	andeq	r0, r0, r8, ror r4
 6b0:	000007f8 	strdeq	r0, [r0], -r8
 6b4:	000002a8 	andeq	r0, r0, r8, lsr #5
 6b8:	84240e42 	strthi	r0, [r4], #-3650	; 0xfffff1be
 6bc:	86088509 	strhi	r8, [r8], -r9, lsl #10
 6c0:	88068707 	stmdahi	r6, {r0, r1, r2, r8, r9, sl, pc}
 6c4:	8a048905 	bhi	122ae0 <_edata+0x120f98>
 6c8:	8e028b03 	vmlahi.f64	d8, d2, d3
 6cc:	480e4201 	stmdami	lr, {r0, r9, lr}
 6d0:	240e0a64 	strcs	r0, [lr], #-2660	; 0xfffff59c
 6d4:	0a420b42 	beq	10833e4 <_edata+0x108189c>
 6d8:	0b42240e 	bleq	1089718 <_edata+0x1087bd0>
 6dc:	0000000c 	andeq	r0, r0, ip
 6e0:	00000478 	andeq	r0, r0, r8, ror r4
 6e4:	00000aa0 	andeq	r0, r0, r0, lsr #21
 6e8:	00000004 	andeq	r0, r0, r4
 6ec:	0000000c 	andeq	r0, r0, ip
 6f0:	00000478 	andeq	r0, r0, r8, ror r4
 6f4:	00000aa4 	andeq	r0, r0, r4, lsr #21
 6f8:	00000004 	andeq	r0, r0, r4
 6fc:	0000000c 	andeq	r0, r0, ip
 700:	00000478 	andeq	r0, r0, r8, ror r4
 704:	00000aa8 	andeq	r0, r0, r8, lsr #21
 708:	00000004 	andeq	r0, r0, r4
 70c:	0000003c 	andeq	r0, r0, ip, lsr r0
 710:	00000478 	andeq	r0, r0, r8, ror r4
 714:	00000aac 	andeq	r0, r0, ip, lsr #21
 718:	00000284 	andeq	r0, r0, r4, lsl #5
 71c:	841c0e42 	ldrhi	r0, [ip], #-3650	; 0xfffff1be
 720:	86068507 	strhi	r8, [r6], -r7, lsl #10
 724:	88048705 	stmdahi	r4, {r0, r2, r8, r9, sl, pc}
 728:	8e028903 	vmlahi.f16	s16, s4, s6	; <UNPREDICTABLE>
 72c:	a80e4201 	stmdage	lr, {r0, r9, lr}
 730:	0e0a7202 	cdpeq	2, 0, cr7, cr10, cr2, {0}
 734:	680b421c 	stmdavs	fp, {r2, r3, r4, r9, lr}
 738:	421c0e0a 	andsmi	r0, ip, #10, 28	; 0xa0
 73c:	0a45020b 	beq	1140f70 <_edata+0x113f428>
 740:	0b421c0e 	bleq	1087780 <_edata+0x1085c38>
 744:	1c0e0a61 			; <UNDEFINED> instruction: 0x1c0e0a61
 748:	00000b42 	andeq	r0, r0, r2, asr #22
 74c:	0000000c 	andeq	r0, r0, ip
 750:	ffffffff 			; <UNDEFINED> instruction: 0xffffffff
 754:	7c020001 	stcvc	0, cr0, [r2], {1}
 758:	000d0c0e 	andeq	r0, sp, lr, lsl #24
 75c:	00000014 	andeq	r0, r0, r4, lsl r0
 760:	0000074c 	andeq	r0, r0, ip, asr #14
 764:	000014fc 	strdeq	r1, [r0], -ip
 768:	0000000e 	andeq	r0, r0, lr
 76c:	83080e41 	movwhi	r0, #36417	; 0x8e41
 770:	00018e02 	andeq	r8, r1, r2, lsl #28
 774:	0000000c 	andeq	r0, r0, ip
 778:	ffffffff 			; <UNDEFINED> instruction: 0xffffffff
 77c:	7c020001 	stcvc	0, cr0, [r2], {1}
 780:	000d0c0e 	andeq	r0, sp, lr, lsl #24
 784:	00000018 	andeq	r0, r0, r8, lsl r0
 788:	00000774 	andeq	r0, r0, r4, ror r7
 78c:	00000000 	andeq	r0, r0, r0
 790:	00000030 	andeq	r0, r0, r0, lsr r0
 794:	83100e41 	tsthi	r0, #1040	; 0x410
 798:	85038404 	strhi	r8, [r3, #-1028]	; 0xfffffbfc
 79c:	00018e02 	andeq	r8, r1, r2, lsl #28
 7a0:	0000001c 	andeq	r0, r0, ip, lsl r0
 7a4:	00000774 	andeq	r0, r0, r4, ror r7
 7a8:	00000000 	andeq	r0, r0, r0
 7ac:	0000004c 	andeq	r0, r0, ip, asr #32
 7b0:	83180e42 	tsthi	r8, #1056	; 0x420
 7b4:	85058406 	strhi	r8, [r5, #-1030]	; 0xfffffbfa
 7b8:	87038604 	strhi	r8, [r3, -r4, lsl #12]
 7bc:	00018e02 	andeq	r8, r1, r2, lsl #28
 7c0:	00000024 	andeq	r0, r0, r4, lsr #32
 7c4:	00000774 	andeq	r0, r0, r4, ror r7
 7c8:	00000000 	andeq	r0, r0, r0
 7cc:	00000056 	andeq	r0, r0, r6, asr r0
 7d0:	83100e42 	tsthi	r0, #1056	; 0x420
 7d4:	85038404 	strhi	r8, [r3, #-1028]	; 0xfffffbfc
 7d8:	5c018e02 	stcpl	14, cr8, [r1], {2}
 7dc:	c4c5ce0a 	strbgt	ip, [r5], #3594	; 0xe0a
 7e0:	42000ec3 	andmi	r0, r0, #3120	; 0xc30
 7e4:	0000000b 	andeq	r0, r0, fp
 7e8:	00000020 	andeq	r0, r0, r0, lsr #32
 7ec:	00000774 	andeq	r0, r0, r4, ror r7
 7f0:	00000000 	andeq	r0, r0, r0
 7f4:	00000064 	andeq	r0, r0, r4, rrx
 7f8:	83100e45 	tsthi	r0, #1104	; 0x450
 7fc:	85038404 	strhi	r8, [r3, #-1028]	; 0xfffffbfc
 800:	6a018e02 	bvs	64010 <_edata+0x624c8>
 804:	c4c3000e 	strbgt	r0, [r3], #14
 808:	0000cec5 	andeq	ip, r0, r5, asr #29
 80c:	00000024 	andeq	r0, r0, r4, lsr #32
 810:	00000774 	andeq	r0, r0, r4, ror r7
 814:	0000150c 	andeq	r1, r0, ip, lsl #10
 818:	0000005c 	andeq	r0, r0, ip, asr r0
 81c:	83100e41 	tsthi	r0, #1040	; 0x410
 820:	85038404 	strhi	r8, [r3, #-1028]	; 0xfffffbfc
 824:	5d018e02 	stcpl	14, cr8, [r1, #-8]
 828:	c4c5ce0a 	strbgt	ip, [r5], #3594	; 0xe0a
 82c:	42000ec3 	andmi	r0, r0, #3120	; 0xc30
 830:	0000000b 	andeq	r0, r0, fp
 834:	00000018 	andeq	r0, r0, r8, lsl r0
 838:	00000774 	andeq	r0, r0, r4, ror r7
 83c:	00000000 	andeq	r0, r0, r0
 840:	00000054 	andeq	r0, r0, r4, asr r0
 844:	84100e43 	ldrhi	r0, [r0], #-3651	; 0xfffff1bd
 848:	86038504 	strhi	r8, [r3], -r4, lsl #10
 84c:	00018e02 	andeq	r8, r1, r2, lsl #28
 850:	00000018 	andeq	r0, r0, r8, lsl r0
 854:	00000774 	andeq	r0, r0, r4, ror r7
 858:	00000000 	andeq	r0, r0, r0
 85c:	00000038 	andeq	r0, r0, r8, lsr r0
 860:	83100e41 	tsthi	r0, #1040	; 0x410
 864:	85038404 	strhi	r8, [r3, #-1028]	; 0xfffffbfc
 868:	00018e02 	andeq	r8, r1, r2, lsl #28
 86c:	00000018 	andeq	r0, r0, r8, lsl r0
 870:	00000774 	andeq	r0, r0, r4, ror r7
 874:	00000000 	andeq	r0, r0, r0
 878:	00000068 	andeq	r0, r0, r8, rrx
 87c:	83100e41 	tsthi	r0, #1040	; 0x410
 880:	85038404 	strhi	r8, [r3, #-1028]	; 0xfffffbfc
 884:	00018e02 	andeq	r8, r1, r2, lsl #28
 888:	0000000c 	andeq	r0, r0, ip
 88c:	ffffffff 			; <UNDEFINED> instruction: 0xffffffff
 890:	7c020001 	stcvc	0, cr0, [r2], {1}
 894:	000d0c0e 	andeq	r0, sp, lr, lsl #24
 898:	00000038 	andeq	r0, r0, r8, lsr r0
 89c:	00000888 	andeq	r0, r0, r8, lsl #17
 8a0:	00000000 	andeq	r0, r0, r0
 8a4:	00000560 	andeq	r0, r0, r0, ror #10
 8a8:	84240e42 	strthi	r0, [r4], #-3650	; 0xfffff1be
 8ac:	86088509 	strhi	r8, [r8], -r9, lsl #10
 8b0:	88068707 	stmdahi	r6, {r0, r1, r2, r8, r9, sl, pc}
 8b4:	8a048905 	bhi	122cd0 <_edata+0x121188>
 8b8:	8e028b03 	vmlahi.f64	d8, d2, d3
 8bc:	300e4401 	andcc	r4, lr, r1, lsl #8
 8c0:	240e0a65 	strcs	r0, [lr], #-2661	; 0xfffff59b
 8c4:	9d020b42 	vstrls	d0, [r2, #-264]	; 0xfffffef8
 8c8:	42240e0a 	eormi	r0, r4, #10, 28	; 0xa0
 8cc:	0aaa020b 	beq	fea81100 <_edata+0xfea7f5b8>
 8d0:	0b42240e 	bleq	1089910 <_edata+0x1087dc8>
 8d4:	0000000c 	andeq	r0, r0, ip
 8d8:	ffffffff 			; <UNDEFINED> instruction: 0xffffffff
 8dc:	7c020001 	stcvc	0, cr0, [r2], {1}
 8e0:	000d0c0e 	andeq	r0, sp, lr, lsl #24
 8e4:	0000000c 	andeq	r0, r0, ip
 8e8:	000008d4 	ldrdeq	r0, [r0], -r4
 8ec:	00000000 	andeq	r0, r0, r0
 8f0:	0000000c 	andeq	r0, r0, ip
 8f4:	0000000c 	andeq	r0, r0, ip
 8f8:	000008d4 	ldrdeq	r0, [r0], -r4
 8fc:	00000000 	andeq	r0, r0, r0
 900:	0000000c 	andeq	r0, r0, ip
 904:	0000000c 	andeq	r0, r0, ip
 908:	ffffffff 			; <UNDEFINED> instruction: 0xffffffff
 90c:	7c020001 	stcvc	0, cr0, [r2], {1}
 910:	000d0c0e 	andeq	r0, sp, lr, lsl #24
 914:	0000000c 	andeq	r0, r0, ip
 918:	00000904 	andeq	r0, r0, r4, lsl #18
 91c:	00000000 	andeq	r0, r0, r0
 920:	00000002 	andeq	r0, r0, r2
 924:	0000000c 	andeq	r0, r0, ip
 928:	00000904 	andeq	r0, r0, r4, lsl #18
 92c:	00000000 	andeq	r0, r0, r0
 930:	00000002 	andeq	r0, r0, r2
 934:	0000000c 	andeq	r0, r0, ip
 938:	00000904 	andeq	r0, r0, r4, lsl #18
 93c:	00000000 	andeq	r0, r0, r0
 940:	00000002 	andeq	r0, r0, r2
 944:	0000000c 	andeq	r0, r0, ip
 948:	00000904 	andeq	r0, r0, r4, lsl #18
 94c:	00000000 	andeq	r0, r0, r0
 950:	00000002 	andeq	r0, r0, r2
 954:	0000000c 	andeq	r0, r0, ip
 958:	00000904 	andeq	r0, r0, r4, lsl #18
 95c:	00000000 	andeq	r0, r0, r0
 960:	00000002 	andeq	r0, r0, r2
 964:	0000000c 	andeq	r0, r0, ip
 968:	00000904 	andeq	r0, r0, r4, lsl #18
 96c:	00000000 	andeq	r0, r0, r0
 970:	00000002 	andeq	r0, r0, r2
 974:	0000000c 	andeq	r0, r0, ip
 978:	00000904 	andeq	r0, r0, r4, lsl #18
 97c:	00000000 	andeq	r0, r0, r0
 980:	00000004 	andeq	r0, r0, r4
 984:	0000000c 	andeq	r0, r0, ip
 988:	00000904 	andeq	r0, r0, r4, lsl #18
 98c:	00000000 	andeq	r0, r0, r0
 990:	00000004 	andeq	r0, r0, r4
 994:	0000000c 	andeq	r0, r0, ip
 998:	00000904 	andeq	r0, r0, r4, lsl #18
 99c:	00000000 	andeq	r0, r0, r0
 9a0:	00000002 	andeq	r0, r0, r2
 9a4:	0000000c 	andeq	r0, r0, ip
 9a8:	00000904 	andeq	r0, r0, r4, lsl #18
 9ac:	00000000 	andeq	r0, r0, r0
 9b0:	00000002 	andeq	r0, r0, r2
 9b4:	0000000c 	andeq	r0, r0, ip
 9b8:	ffffffff 			; <UNDEFINED> instruction: 0xffffffff
 9bc:	7c020001 	stcvc	0, cr0, [r2], {1}
 9c0:	000d0c0e 	andeq	r0, sp, lr, lsl #24
 9c4:	00000018 	andeq	r0, r0, r8, lsl r0
 9c8:	000009b4 			; <UNDEFINED> instruction: 0x000009b4
 9cc:	00000000 	andeq	r0, r0, r0
 9d0:	00000024 	andeq	r0, r0, r4, lsr #32
 9d4:	83100e41 	tsthi	r0, #1040	; 0x410
 9d8:	85038404 	strhi	r8, [r3, #-1028]	; 0xfffffbfc
 9dc:	00018e02 	andeq	r8, r1, r2, lsl #28
 9e0:	0000000c 	andeq	r0, r0, ip
 9e4:	ffffffff 			; <UNDEFINED> instruction: 0xffffffff
 9e8:	7c020001 	stcvc	0, cr0, [r2], {1}
 9ec:	000d0c0e 	andeq	r0, sp, lr, lsl #24
 9f0:	0000000c 	andeq	r0, r0, ip
 9f4:	000009e0 	andeq	r0, r0, r0, ror #19
 9f8:	00000000 	andeq	r0, r0, r0
 9fc:	0000001c 	andeq	r0, r0, ip, lsl r0
 a00:	0000000c 	andeq	r0, r0, ip
 a04:	ffffffff 			; <UNDEFINED> instruction: 0xffffffff
 a08:	7c020001 	stcvc	0, cr0, [r2], {1}
 a0c:	000d0c0e 	andeq	r0, sp, lr, lsl #24
 a10:	00000024 	andeq	r0, r0, r4, lsr #32
 a14:	00000a00 	andeq	r0, r0, r0, lsl #20
 a18:	00000000 	andeq	r0, r0, r0
 a1c:	00000048 	andeq	r0, r0, r8, asr #32
 a20:	84180e42 	ldrhi	r0, [r8], #-3650	; 0xfffff1be
 a24:	86058506 	strhi	r8, [r5], -r6, lsl #10
 a28:	88038704 	stmdahi	r3, {r2, r8, r9, sl, pc}
 a2c:	60018e02 	andvs	r8, r1, r2, lsl #28
 a30:	c6c7c8ce 	strbgt	ip, [r7], lr, asr #17
 a34:	000ec4c5 	andeq	ip, lr, r5, asr #9
 a38:	00000028 	andeq	r0, r0, r8, lsr #32
 a3c:	00000a00 	andeq	r0, r0, r0, lsl #20
 a40:	00000000 	andeq	r0, r0, r0
 a44:	00000090 	muleq	r0, r0, r0
 a48:	84100e46 	ldrhi	r0, [r0], #-3654	; 0xfffff1ba
 a4c:	86038504 	strhi	r8, [r3], -r4, lsl #10
 a50:	7c018e02 	stcvc	14, cr8, [r1], {2}
 a54:	c5c6ce0a 	strbgt	ip, [r6, #3594]	; 0xe0a
 a58:	42000ec4 	andmi	r0, r0, #196, 28	; 0xc40
 a5c:	000e410b 	andeq	r4, lr, fp, lsl #2
 a60:	cec6c5c4 	cdpgt	5, 12, cr12, cr6, cr4, {6}
 a64:	0000000c 	andeq	r0, r0, ip
 a68:	ffffffff 			; <UNDEFINED> instruction: 0xffffffff
 a6c:	7c020001 	stcvc	0, cr0, [r2], {1}
 a70:	000d0c0e 	andeq	r0, sp, lr, lsl #24
 a74:	0000001c 	andeq	r0, r0, ip, lsl r0
 a78:	00000a64 	andeq	r0, r0, r4, ror #20
 a7c:	00000000 	andeq	r0, r0, r0
 a80:	000000a0 	andeq	r0, r0, r0, lsr #1
 a84:	83180e41 	tsthi	r8, #1040	; 0x410
 a88:	85058406 	strhi	r8, [r5, #-1030]	; 0xfffffbfa
 a8c:	87038604 	strhi	r8, [r3, -r4, lsl #12]
 a90:	00018e02 	andeq	r8, r1, r2, lsl #28
 a94:	00000058 	andeq	r0, r0, r8, asr r0
 a98:	00000a64 	andeq	r0, r0, r4, ror #20
 a9c:	00000000 	andeq	r0, r0, r0
 aa0:	0000020c 	andeq	r0, r0, ip, lsl #4
 aa4:	83180e43 	tsthi	r8, #1072	; 0x430
 aa8:	85058406 	strhi	r8, [r5, #-1030]	; 0xfffffbfa
 aac:	87038604 	strhi	r8, [r3, -r4, lsl #12]
 ab0:	02018e02 	andeq	r8, r1, #2, 28
 ab4:	c7ce0a4a 	strbgt	r0, [lr, sl, asr #20]
 ab8:	c3c4c5c6 	bicgt	ip, r4, #830472192	; 0x31800000
 abc:	0b42000e 	bleq	1080afc <_edata+0x107efb4>
 ac0:	c3000e55 	movwgt	r0, #3669	; 0xe55
 ac4:	c7c6c5c4 	strbgt	ip, [r6, r4, asr #11]
 ac8:	180e41ce 	stmdane	lr, {r1, r2, r3, r6, r7, r8, lr}
 acc:	05840683 	streq	r0, [r4, #1667]	; 0x683
 ad0:	03860485 	orreq	r0, r6, #-2063597568	; 0x85000000
 ad4:	018e0287 	orreq	r0, lr, r7, lsl #5
 ad8:	c7ce0a69 	strbgt	r0, [lr, r9, ror #20]
 adc:	c3c4c5c6 	bicgt	ip, r4, #830472192	; 0x31800000
 ae0:	0b42000e 	bleq	1080b20 <_edata+0x107efd8>
 ae4:	c7ce0a51 			; <UNDEFINED> instruction: 0xc7ce0a51
 ae8:	c3c4c5c6 	bicgt	ip, r4, #830472192	; 0x31800000
 aec:	0b42000e 	bleq	1080b2c <_edata+0x107efe4>
 af0:	0000000c 	andeq	r0, r0, ip
 af4:	ffffffff 			; <UNDEFINED> instruction: 0xffffffff
 af8:	7c020001 	stcvc	0, cr0, [r2], {1}
 afc:	000d0c0e 	andeq	r0, sp, lr, lsl #24
 b00:	00000018 	andeq	r0, r0, r8, lsl r0
 b04:	00000af0 	strdeq	r0, [r0], -r0	; <UNPREDICTABLE>
 b08:	00001568 	andeq	r1, r0, r8, ror #10
 b0c:	0000002c 	andeq	r0, r0, ip, lsr #32
 b10:	84100e41 	ldrhi	r0, [r0], #-3649	; 0xfffff1bf
 b14:	86038504 	strhi	r8, [r3], -r4, lsl #10
 b18:	00018e02 	andeq	r8, r1, r2, lsl #28
 b1c:	0000000c 	andeq	r0, r0, ip
 b20:	00000af0 	strdeq	r0, [r0], -r0	; <UNPREDICTABLE>
 b24:	00001594 	muleq	r0, r4, r5
 b28:	00000004 	andeq	r0, r0, r4
 b2c:	0000000c 	andeq	r0, r0, ip
 b30:	ffffffff 			; <UNDEFINED> instruction: 0xffffffff
 b34:	7c020001 	stcvc	0, cr0, [r2], {1}
 b38:	000d0c0e 	andeq	r0, sp, lr, lsl #24
 b3c:	0000000c 	andeq	r0, r0, ip
 b40:	00000b2c 	andeq	r0, r0, ip, lsr #22
 b44:	00001598 	muleq	r0, r8, r5
 b48:	00000010 	andeq	r0, r0, r0, lsl r0
 b4c:	0000000c 	andeq	r0, r0, ip
 b50:	ffffffff 			; <UNDEFINED> instruction: 0xffffffff
 b54:	7c020001 	stcvc	0, cr0, [r2], {1}
 b58:	000d0c0e 	andeq	r0, sp, lr, lsl #24
 b5c:	0000000c 	andeq	r0, r0, ip
 b60:	00000b4c 	andeq	r0, r0, ip, asr #22
 b64:	000015a8 	andeq	r1, r0, r8, lsr #11
 b68:	00000010 	andeq	r0, r0, r0, lsl r0
 b6c:	0000000c 	andeq	r0, r0, ip
 b70:	ffffffff 			; <UNDEFINED> instruction: 0xffffffff
 b74:	7c020001 	stcvc	0, cr0, [r2], {1}
 b78:	000d0c0e 	andeq	r0, sp, lr, lsl #24
 b7c:	0000000c 	andeq	r0, r0, ip
 b80:	00000b6c 	andeq	r0, r0, ip, ror #22
 b84:	000015b8 			; <UNDEFINED> instruction: 0x000015b8
 b88:	00000002 	andeq	r0, r0, r2
 b8c:	0000000c 	andeq	r0, r0, ip
 b90:	ffffffff 			; <UNDEFINED> instruction: 0xffffffff
 b94:	7c020001 	stcvc	0, cr0, [r2], {1}
 b98:	000d0c0e 	andeq	r0, sp, lr, lsl #24
 b9c:	00000018 	andeq	r0, r0, r8, lsl r0
 ba0:	00000b8c 	andeq	r0, r0, ip, lsl #23
 ba4:	00001010 	andeq	r1, r0, r0, lsl r0
 ba8:	00000038 	andeq	r0, r0, r8, lsr r0
 bac:	84040e48 	strhi	r0, [r4], #-3656	; 0xfffff1b8
 bb0:	0ec44901 	vdiveq.f16	s9, s8, s2	; <UNPREDICTABLE>
 bb4:	00000000 	andeq	r0, r0, r0
 bb8:	00000018 	andeq	r0, r0, r8, lsl r0
 bbc:	00000b8c 	andeq	r0, r0, ip, lsl #23
 bc0:	00001048 	andeq	r1, r0, r8, asr #32
 bc4:	0000001a 	andeq	r0, r0, sl, lsl r0
 bc8:	8e040e41 	cdphi	14, 0, cr0, cr4, cr1, {2}
 bcc:	180e4101 	stmdane	lr, {r0, r8, lr}
 bd0:	00040e49 	andeq	r0, r4, r9, asr #28
 bd4:	0000000c 	andeq	r0, r0, ip
 bd8:	00000b8c 	andeq	r0, r0, ip, lsl #23
 bdc:	00001064 	andeq	r1, r0, r4, rrx
 be0:	00000002 	andeq	r0, r0, r2
 be4:	00000028 	andeq	r0, r0, r8, lsr #32
 be8:	00000b8c 	andeq	r0, r0, ip, lsl #23
 bec:	00001068 	andeq	r1, r0, r8, rrx
 bf0:	000002ac 	andeq	r0, r0, ip, lsr #5
 bf4:	841c0e42 	ldrhi	r0, [ip], #-3650	; 0xfffff1be
 bf8:	86068507 	strhi	r8, [r6], -r7, lsl #10
 bfc:	88048705 	stmdahi	r4, {r0, r2, r8, r9, sl, pc}
 c00:	8e028903 	vmlahi.f16	s16, s4, s6	; <UNPREDICTABLE>
 c04:	300e4201 	andcc	r4, lr, r1, lsl #4
 c08:	1c0e0a6b 			; <UNDEFINED> instruction: 0x1c0e0a6b
 c0c:	00000b42 	andeq	r0, r0, r2, asr #22
 c10:	0000001c 	andeq	r0, r0, ip, lsl r0
 c14:	00000b8c 	andeq	r0, r0, ip, lsl #23
 c18:	00001314 	andeq	r1, r0, r4, lsl r3
 c1c:	0000002a 	andeq	r0, r0, sl, lsr #32
 c20:	84080e41 	strhi	r0, [r8], #-3649	; 0xfffff1bf
 c24:	43018e02 	movwmi	r8, #7682	; 0x1e02
 c28:	0e50180e 	cdpeq	8, 5, cr1, cr0, cr14, {0}
 c2c:	00000008 	andeq	r0, r0, r8
 c30:	00000014 	andeq	r0, r0, r4, lsl r0
 c34:	00000b8c 	andeq	r0, r0, ip, lsl #23
 c38:	00001340 	andeq	r1, r0, r0, asr #6
 c3c:	0000000a 	andeq	r0, r0, sl
 c40:	83080e41 	movwhi	r0, #36417	; 0x8e41
 c44:	00018e02 	andeq	r8, r1, r2, lsl #28
 c48:	00000014 	andeq	r0, r0, r4, lsl r0
 c4c:	00000b8c 	andeq	r0, r0, ip, lsl #23
 c50:	0000134c 	andeq	r1, r0, ip, asr #6
 c54:	00000012 	andeq	r0, r0, r2, lsl r0
 c58:	83080e41 	movwhi	r0, #36417	; 0x8e41
 c5c:	00018e02 	andeq	r8, r1, r2, lsl #28
 c60:	00000014 	andeq	r0, r0, r4, lsl r0
 c64:	00000b8c 	andeq	r0, r0, ip, lsl #23
 c68:	00000000 	andeq	r0, r0, r0
 c6c:	00000006 	andeq	r0, r0, r6
 c70:	83080e41 	movwhi	r0, #36417	; 0x8e41
 c74:	00018e02 	andeq	r8, r1, r2, lsl #28
 c78:	00000014 	andeq	r0, r0, r4, lsl r0
 c7c:	00000b8c 	andeq	r0, r0, ip, lsl #23
 c80:	00000000 	andeq	r0, r0, r0
 c84:	00000006 	andeq	r0, r0, r6
 c88:	83080e41 	movwhi	r0, #36417	; 0x8e41
 c8c:	00018e02 	andeq	r8, r1, r2, lsl #28

Disassembly of section .stab:

00000000 <.stab>:
   0:	00000001 	andeq	r0, r0, r1
   4:	00020000 	andeq	r0, r2, r0
   8:	0000003c 	andeq	r0, r0, ip, lsr r0
   c:	00000008 	andeq	r0, r0, r8
  10:	0000001e 	andeq	r0, r0, lr, lsl r0
  14:	00000000 	andeq	r0, r0, r0
  18:	00000036 	andeq	r0, r0, r6, lsr r0
  1c:	00000001 	andeq	r0, r0, r1
  20:	00000000 	andeq	r0, r0, r0
  24:	00000001 	andeq	r0, r0, r1
  28:	00020000 	andeq	r0, r2, r0
  2c:	00000042 	andeq	r0, r0, r2, asr #32
  30:	0000000a 	andeq	r0, r0, sl
  34:	0000001e 	andeq	r0, r0, lr, lsl r0
  38:	00000000 	andeq	r0, r0, r0
  3c:	0000003a 	andeq	r0, r0, sl, lsr r0
  40:	00000001 	andeq	r0, r0, r1
  44:	00000000 	andeq	r0, r0, r0

Disassembly of section .ARM.extab:

000015c0 <.ARM.extab>:
    15c0:	8101b108 	tsthi	r1, r8, lsl #2
    15c4:	8400b0b0 	strhi	fp, [r0], #-176	; 0xffffff50
    15c8:	00000000 	andeq	r0, r0, r0
    15cc:	8101b108 	tsthi	r1, r8, lsl #2
    15d0:	8400b0b0 	strhi	fp, [r0], #-176	; 0xffffff50
    15d4:	00000000 	andeq	r0, r0, r0

Disassembly of section .ARM:

000015d8 <__exidx_start>:
    15d8:	7fffea78 	svcvc	0x00ffea78
    15dc:	00000001 	andeq	r0, r0, r1
    15e0:	7fffed78 	svcvc	0x00ffed78
    15e4:	00000001 	andeq	r0, r0, r1
    15e8:	7fffed84 	svcvc	0x00ffed84
    15ec:	00000001 	andeq	r0, r0, r1
    15f0:	7fffedd8 	svcvc	0x00ffedd8
    15f4:	00000001 	andeq	r0, r0, r1
    15f8:	7fffedf8 	svcvc	0x00ffedf8
    15fc:	8002a9b0 			; <UNDEFINED> instruction: 0x8002a9b0
    1600:	7fffee8c 	svcvc	0x00ffee8c
    1604:	80a8b0b0 	strhthi	fp, [r8], r0
    1608:	7fffeedc 	svcvc	0x00ffeedc
    160c:	00000001 	andeq	r0, r0, r1
    1610:	7fffeed8 	svcvc	0x00ffeed8
    1614:	00000001 	andeq	r0, r0, r1
    1618:	7fffeedc 	svcvc	0x00ffeedc
    161c:	00000001 	andeq	r0, r0, r1
    1620:	7fffeed8 	svcvc	0x00ffeed8
    1624:	80aab0b0 	strhthi	fp, [sl], r0
    1628:	7fffef0c 	svcvc	0x00ffef0c
    162c:	80b271ae 	adcshi	r7, r2, lr, lsr #3
    1630:	7fffefd0 	svcvc	0x00ffefd0
    1634:	00000001 	andeq	r0, r0, r1
    1638:	7fffefcc 	svcvc	0x00ffefcc
    163c:	80383fab 	eorshi	r3, r8, fp, lsr #31
    1640:	7ffff02c 	svcvc	0x00fff02c
    1644:	00000001 	andeq	r0, r0, r1
    1648:	7ffff034 	svcvc	0x00fff034
    164c:	80aab0b0 	strhthi	fp, [sl], r0
    1650:	7ffff070 	svcvc	0x00fff070
    1654:	00000001 	andeq	r0, r0, r1
    1658:	7ffff078 	svcvc	0x00fff078
    165c:	00000001 	andeq	r0, r0, r1
    1660:	7ffff074 	svcvc	0x00fff074
    1664:	00000001 	andeq	r0, r0, r1
    1668:	7ffff078 	svcvc	0x00fff078
    166c:	00000001 	andeq	r0, r0, r1
    1670:	7ffff0a0 	svcvc	0x00fff0a0
    1674:	00000001 	andeq	r0, r0, r1
    1678:	7ffff0b4 	svcvc	0x00fff0b4
    167c:	00000001 	andeq	r0, r0, r1
    1680:	7ffff0dc 	svcvc	0x00fff0dc
    1684:	00000001 	andeq	r0, r0, r1
    1688:	7ffff0ec 	svcvc	0x00fff0ec
    168c:	80b20daa 	adcshi	r0, r2, sl, lsr #27
    1690:	7ffff168 	svcvc	0x00fff168
    1694:	8008afb0 			; <UNDEFINED> instruction: 0x8008afb0
    1698:	7ffff408 	svcvc	0x00fff408
    169c:	00000001 	andeq	r0, r0, r1
    16a0:	7ffff404 	svcvc	0x00fff404
    16a4:	00000001 	andeq	r0, r0, r1
    16a8:	7ffff400 	svcvc	0x00fff400
    16ac:	00000001 	andeq	r0, r0, r1
    16b0:	7ffff3fc 	svcvc	0x00fff3fc
    16b4:	80023fad 	andhi	r3, r2, sp, lsr #31
    16b8:	7ffff678 	svcvc	0x00fff678
    16bc:	00000001 	andeq	r0, r0, r1
    16c0:	7ffff950 	svcvc	0x00fff950
    16c4:	00000001 	andeq	r0, r0, r1
    16c8:	7ffff980 	svcvc	0x00fff980
    16cc:	80048400 	andhi	r8, r4, r0, lsl #8
    16d0:	7ffff994 	svcvc	0x00fff994
    16d4:	00000001 	andeq	r0, r0, r1
    16d8:	7ffff990 	svcvc	0x00fff990
    16dc:	8004adb0 			; <UNDEFINED> instruction: 0x8004adb0
    16e0:	7ffffc34 	svcvc	0x00fffc34
    16e4:	8003a8b0 			; <UNDEFINED> instruction: 0x8003a8b0
    16e8:	7ffffc58 	svcvc	0x00fffc58
    16ec:	7ffffed4 	svcvc	0x00fffed4
    16f0:	7ffffc5c 	svcvc	0x00fffc5c
    16f4:	7ffffed8 	svcvc	0x00fffed8
    16f8:	7ffffc68 	svcvc	0x00fffc68
    16fc:	00000001 	andeq	r0, r0, r1
    1700:	7ffffca4 	svcvc	0x00fffca4
    1704:	80a8b0b0 	strhthi	fp, [r8], r0
    1708:	7ffffdf4 	svcvc	0x00fffdf4
    170c:	00000001 	andeq	r0, r0, r1
    1710:	7ffffeac 	svcvc	0x00fffeac
    1714:	00000001 	andeq	r0, r0, r1

Disassembly of section .data:

00001718 <_impure_ptr>:
    1718:	00001720 	andeq	r1, r0, r0, lsr #14
    171c:	00000000 	andeq	r0, r0, r0

00001720 <impure_data>:
    1720:	00000000 	andeq	r0, r0, r0
    1724:	00001a0c 	andeq	r1, r0, ip, lsl #20
    1728:	00001a74 	andeq	r1, r0, r4, ror sl
    172c:	00001adc 	ldrdeq	r1, [r0], -ip
	...
    17c8:	00000001 	andeq	r0, r0, r1
    17cc:	00000000 	andeq	r0, r0, r0
    17d0:	abcd330e 	blge	ff34e410 <_edata+0xff34c8c8>
    17d4:	e66d1234 			; <UNDEFINED> instruction: 0xe66d1234
    17d8:	0005deec 	andeq	sp, r5, ip, ror #29
    17dc:	0000000b 	andeq	r0, r0, fp
	...
