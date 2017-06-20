main:
	li	$0, 1 #x0, 1
	li	$s1, 1 #x1, 1
	li	$s2, 1 #x2, 1
	add	$s3, $0, $s1 #x3, x0, x1 -> x3 = 2
	add	$s4, $s1, $s2 #x4, x1, x2 -> x4 = 2
	add	$s5, $s3, $s4 #x5, x3, x4 -> x5 = 4
	li	$v0, 1 #a7, 1
	move	$a0, $s5 #a0, x5
	SYSCALL
	li	$v0, 10 #a7, 10			 # calls exit command (code 10)
    SYSCALL				     # end of program


