

#Parker Hague
#Problem10

# A[] = $s0
# x = $t0
# i = $t1
# j = $t2
# h = $t3

L1:

    beq $t1, $t3, Break        # if i == j

    sll $t4, $t1, 2         # i * 4

    add	$t4, $t4, $s0       # adds i index to A[]


    lw $t5, 0($t4)          # loads index into register

    add		$t0, $t0, $t5		# $t0 = $t0 + $t5      x = x + A[i]

    add		$t1, $t1, $t2		# $t1 = $t1 + $t2

    j L1;       # loops back to top

Break: