main:
	li	$s1, 0xBBAA
	li	$s2, 0xDDCC
	sll $s2, $s2, 16 # s2 = 0xDDCC0000
    or  $s3, $s2, $s1 # s3 = 0xDDCCBBAA
    andi $s4, $s2, 0xff # s4 = 0
    li	$v0, 1
	move	$a0, $s4
	SYSCALL # prints a 0
	srl $s3, $s3, 8 # s3 = 0xDDCCBB
    andi $s4, $s2, 0xff # s4 = 0
    li	$v0, 1
	move	$a0, $s4
	SYSCALL # prints a 0
	srl $s3, $s3, 8 # s3 = 0xDDCC
    andi $s4, $s2, 0xff # s4 = 0
    li	$v0, 1
	move	$a0, $s4
	SYSCALL # prints a 0
	srl $s3, $s3, 8 # s3 = 0xDD
    andi $s4, $s2, 0xff # s4 = 0
    li	$v0, 1
	move	$a0, $s4
	SYSCALL # prints a 0
    
	li	$v0, 10			 # calls exit command (code 10)
    SYSCALL				     # end of program


