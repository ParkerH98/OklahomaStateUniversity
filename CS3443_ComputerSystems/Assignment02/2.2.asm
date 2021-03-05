
#Parker Hague
#Problem2

add		$a0, $a0, $zero		# $a0 = $a0 + $zero... initalize argument parameter

Func1:

If:

bne		$a0, $zero, True	# if $a0 != $zero then True

# else do...

Else:


add		$v0, $a0, $v0		    # $v0 = $a0 + $v0
addi	$a0, $a0, -1			# $a0 = $a0 + -1

jal Func1                       # returns

jr $ra


True:

add		$v0, $a0, $v0		# $v0 = $a0 + $v0... return n
addi	$a0, $a0, 1		    # $a0 = $a0 + -1... n = n + 1
jal Func1

jr $ra
