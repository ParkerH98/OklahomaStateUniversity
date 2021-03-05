
#problem 7
#Parker Hague


add		$s1, $zero, $zero		# $s1 = $zero + $zero...i variable

addi	$t0, $zero, 10			# $t0 = $zero + 10... 10

L1:

    slt $t2, $s1, $t1

    beq		$t2, $zero, Exit	# if $t2 == $zero then Exit

    sll $t3, $s1, 2             # i * 4

    add $t3, $t3, $s0           # element at A[i]

    sw		$s1, 0($t3)		    # stores array index in array location

    addi	$s1, $s1, 1			# $s1 = $s1 + 1
    
    j L1                        # reiterates through for loop




Exit:

add		$s1, $zero, $zero		# $s1 = $zero + $zero...sets i back to zero
addi	$t3, $zero, 5			# $t3 = $zero +5
addi	$t5, $zero, 9			# $t5 = $zero + 9


L2:

    beq $s1, $t3, Done          # checks if i = 5

    sll $t3, $s1, 2             # i * 4 for ith index

    add $t3, $t3, $s0           # adds i index to A array creating element

    lw $t0, 0($t3)              # loads i index into temp

    sub $t4, $t5, $s1           # $t4 = 9 - i

    sll $t4, $t4, 2             # multiply by 4 for array address

    add $t4, $t4, $s0           # adds for array value

    lw $t6, 0($t4)              # A[9 - i]

    sw $t6, 0($t3)              # A[i] = A[9 - i]

    sw $t0, 0($t4)              # A[9 - i] = temp

    addi	$s1, $s1, 1			# $s1 = $s1 + 1...i += 1

    j L2
    
Done: