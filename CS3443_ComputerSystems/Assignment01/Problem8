
#Problem 8
# Parker Hague

# $s0 = A[0]
# $s1 = i
# $s2= j
# $s3 = M
# $s4 = N


add	$s1, $zero, $zero			# $s1 = $zero + $zero i = 0
add	$s2, $zero, $zero			# $s2 = $zero + $zero

L1:

    beq		$s1, $s3, Exit	# if $s1 == $s3 then Exit

    L2:

        beq $s2, $s4, End       # $s2 == $s4 then break out of loop

        add		$t0, $s1, $s2		# $t0 = $s1 + $s2

        sll $t0, $t0, 2     # i * j * 4

        add		$t0, $t0, $s0		# $t0 = $t0 + $s0

        mul $t1 $t1, $s1, $s2       # multiply i * j and store into $t1

        sw $t1, 0($t0)          #stores i * j into A[i + j]

        addi	$s2, $s2, 1			# $s2 = $s2 + 1

        j L2

End:

addi	$s1, $s1, 1			# $s1 = $s1 + 1

j L1        # loops L1

Exit: