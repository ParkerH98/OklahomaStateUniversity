
#Parker Hague
# Problem1  

For1:

        beq		$t5, $s5, Exit1	# if $t5 == $s5 then Exit6... Exit if i == x

        # else do...

        addi	$t5, $t5, 1			# $t5 = $t5 + 1... i++



        For2:


                beq		$t6, $s6, Exit2	        # if $t6 == $s6 then Exit2... Exit if j == y

                # else do...

                # setting up array

                sll             $t3, $t6, 2             # j * 4 for array index location
                add		$t3, $t3, $t7		# $t3 = $t3 + $t7... gets index locaton of array... Array[j]
                sll             $t4, $t3, 1             # Array[j] = Array[j * 2]


                addi	        $t6, $t6, 1		# $t6 = $t6 + 1... j++

                add		$t5, $t5, $t6		# $t5 = $t5 + $t6... t5 = i + j
                srl             $t5, $t5, 2             # (i + j) / 4

                sw		$t5, 0($t7)		# store value of (i + j) / 4 into array

                j For1
                
Exit2:

Exit1:
