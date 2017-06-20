    li  $s2, 20
    li  $s1, 30
    li  $s0, 0	# the product
whileLoop:
  	ble  $s2, $0, endWhile
  	add  $s0, $s0, $s1
  	addi $s2, $s2, -1
  	j    whileLoop
endWhile:
    li	$v0, 10			 # calls exit command (code 10)
    SYSCALL				     # end of program
