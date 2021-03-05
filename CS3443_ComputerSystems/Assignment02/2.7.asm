
# Parker Hague
# Problem 7

Func1:

beq $a2, $zero, If      # go to If if argument 2 = 0

j Else

If:

add $v0, $a0, $a1       # adds x + y
jr $ra

Else:

sll $a1, $a0, 1         # multiply a0 by 2
sub $a0, $a0, $a1       # sub a1 from a0
sub $a2, $a2, 1         # sub 1 from z
jr $ra
