
#Parker Hague
#problem 9

# $s0 = temp1
# $s1 = temp2
# $t0 = i


addi	$s0, $s0, 9			# $s0 = $s0 + 9 temp1
addi	$s1, $s1, 0			# $s1 = $s1 + 0 temp2
add	$t0, $zero, $zero		# $t0 = $zero + $zero i

addi	$t1, $t1, 10		# $t1 = $t1 + 10



slt $t2, $t1, $s0       # if 10 < temp1

beq $t2, 0, Else        # executes Else if temp1 < 10

If:

    beq $t0, $t1, Break

    add		$s1, $s1, $t0		# $s1 = $s1 + $t0       # temp2 = temp2 + i

    addi	$t0, $t0, 1			# $t0 = $t0 + 1     i++

    j If
    

Else:

addi $t3, $zero, -10        # sets t3 to -10
add	$t0, $zero, $zero		# $t0 = $zero + $zero i

    L2:

        beq $t0, $t3, Break     # if $t0 == $t3

        add		$s1, $s1, $t0           # $s1 = $s1 + $t0       # temp2 = temp2 + i

        addi $t0, $t0, -1       # decrements in for loop

        j L2        # loops


Break: