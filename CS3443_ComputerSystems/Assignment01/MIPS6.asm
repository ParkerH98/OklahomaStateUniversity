

# Problem 6
# C to MIPS
# Parker Hague

add		$t0, $zero, $zero		# $t0 = $zero + $zero

sll     $t1, $s1, 2             # i * 4 ... ith index of array

sll     $t2, $s2, 2             # j * 4 ... jth index of array

add		$t1, $t1, $s0		# $t1 = $t1 + $s0

add		$t2, $t2, $s0		# $t0 = $t1 + $t2

lw		$t3, 0($t1)		    # $t3 = A[i]

lw		$t4, 0($t2)		    # $t4 = A[j]


bne		$t3, $t4, True	# if $t3 != $t4 then True

j		False				# jump to False
                            # if bne is false, True block doesn't get executed



True:

        add		$t0, $t3, $t3		# $t0 = $t3 + $t4


False:                              # false statement will execute regardless of bne result

        lw      $t5, 0($s0)
        add		$t0, $t0, 0($s0)		# $t0 = $t0 + 0($s0)
        
        






