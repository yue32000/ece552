	.file	1 "mbq1.c"

 # GNU C 2.7.2.3 [AL 1.1, MM 40, tma 0.1] SimpleScalar running sstrix compiled by GNU C

 # Cc1 defaults:
 # -mgas -mgpOPT

 # Cc1 arguments (-G value = 8, Cpu = default, ISA = 1):
 # -quiet -dumpbase -O1 -o

gcc2_compiled.:
__gnu_compiled_c:
	.rdata
	.align	2
$LC0:
	.ascii	"% d , %d , %d,%d,%d,%d,%d\000"
	.text
	.align	2
	.globl	main

	.extern	stdin, 4
	.extern	stdout, 4

	.text

	.loc	1 11
	.ent	main
main:
	.frame	$sp,40,$31		# vars= 0, regs= 1/0, args= 32, extra= 0
	.mask	0x80000000,-8
	.fmask	0x00000000,0
	subu	$sp,$sp,40
	sw	$31,32($sp)
	jal	__main
	li	$5,0x00000001		# 1
	li	$6,0x00000001		# 1
	li	$4,0x00000001		# 1
	li	$10,0x00000001		# 1
	li	$9,0x00000001		# 1
	move	$3,$0
	li	$8,0x000f423f		# 999999
$L17:
	addu	$7,$5,$6
	addu	$6,$5,$7
	addu	$3,$3,1
	slt	$2,$8,$3
	beq	$2,$0,$L17
	move	$3,$0
	li	$11,0x0007a11f		# 499999
$L22:
	addu	$8,$10,$9
	addu	$4,$4,1
	addu	$9,$10,$8
	addu	$5,$5,1
	addu	$3,$3,1
	slt	$2,$11,$3
	beq	$2,$0,$L22
	move	$3,$0
	li	$11,0x001e847f		# 1999999
$L27:
 #APP
	lw $2 , 0($sp)
	addu $5,$2,$2
 #NO_APP
	addu	$4,$4,1
 #APP
	lw $2 , 0($sp)
	nop
	addu $5,$2,$2
 #NO_APP
	addu	$3,$3,1
	slt	$2,$11,$3
	beq	$2,$0,$L27
	sw	$4,16($sp)
	la	$4,$LC0
	sw	$10,20($sp)
	sw	$9,24($sp)
	sw	$8,28($sp)
	jal	printf
	move	$2,$0
	lw	$31,32($sp)
	addu	$sp,$sp,40
	j	$31
	.end	main
