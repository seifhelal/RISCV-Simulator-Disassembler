main:
    #li $a3, 1024     
    li $t0, 0
    li $t1, 4

while_input:
    bge $t0, $t1, end_input
    li $v0, 5
    SYSCALL

    sll $t2, $t0, 2
    add $t2, $t2, $sp #$a3
    sw $v0, 0($t2)

    addi $t0, $t0, 1
    j while_input

end_input:
    li $t0, 0
    li $t1, 3

while_output:
    blt $t1, $t0, done

    sll $t2, $t1, 2
    add $t2, $t2, $sp #$a3
    lw $a0, 0($t2)

    li $v0, 1
    SYSCALL

    addi $t1, $t1, -1
    j while_output

done:
    li	$v0, 10
    SYSCALL


# print array of four integers in reverse


