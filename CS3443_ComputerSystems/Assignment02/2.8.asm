
# Parker Hague
# Problem 8

Func1:


add		$t0, $a0, $zero		# $t0 = $a0 + $zero...stores a into register
add		$t1, $a1, $zero		# $t1 = $a1 + $zero...stores b into register
add		$t2, $a2, $zero		# $t2 = $a2 + $zero...stores c into register

add		$a0, $t0, $t1		# $a0 = $t0 + $t1... a = a + b
add		$a1, $t1, $t2		# $a1 = $t1 + $t2... b = b + c

jal Func2                   # makes first call

add		$a0, $v0, $zero		# $a0 = $v0 + $zero... store return value into argument
add		$a1, $t0, $t2		# $a1 = $t0 + $t2... b = a + c

jal Func2                   # makes second call
