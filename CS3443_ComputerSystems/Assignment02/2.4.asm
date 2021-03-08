
#Parker Hague
#Problem 4

Func1:


addi $t6, $zero, 100        # t6 = 100
add $t7, $zero, $zero       #t7 = j

For:

bgt $t7, $a1, Exit          # j <= k
sll $t4, $t7, 2             # j * 4 for array
add $t4, $a0, $t4
lw $a3, 0($t4)              #makes argument equal to

jal func2

#array in position
bgt $v0, $zero, Not        # executes if func2(X[j]) <= 0

addi $t6, $t6, -1           # decrements y

Not:


addi $t6, $t6, 1            #iterator
j For

Exit:

add $v0, $t6, $zero         #prepares this for return
jr $ra