
# Parker Hague
# Problem6

Func1:

jal Func2

add $t0, $v0, $zero

bgez $t0, If            # go to If if t0 >= 0
j Else

If:
add $v0, $a0, $zero     #returns x 
j exit

Else:
add $v0, $a1, $zero     #returns y

Exit:

jr $ra                  # returns before method call

Func2:

sll $t0, $a0, 1         # multiplies x by 2
srl $t1, $a1, 2         # divides y by 4
sub $v0, $t0, $t1       #returns jr $ra