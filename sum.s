main:
    li $v0, 5        # enter the value
    SYSCALL
    
    move $a2, $v0 #a7
    jal sum
    

    li $v0, 1
    SYSCALL

    li $v0, 10
    SYSCALL

sum:
    li $a0, 0
loop:
    ble $a2, $zero, stop
    add $a0, $a2, $a0
    addi $a2, $a2, -1
    j loop

stop:
    addi $a1, $a1, 4
    jr $ra

# should print the summation the values: enter 4 prints 10
