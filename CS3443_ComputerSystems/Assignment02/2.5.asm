
#Parker Hague
#Problem5

Func1:

lw $t0, 0($a0)          # load base array into y
addi $t2, $zero, 0      # t2 = j 
srl $t1, $t0, 1         # sifts right by 1 to divide by two

For:

slt $t3, $a1, $t2       # if k < j then t3 = 1...will exit if value is 0
beq $t3, $zero, Exit    # Exit if t3 = 0
sll $t4, $t2, 2         # j * 4
add $t4, $t4, $a0       # jth index into base array
lw $t4, 0($t4)          # jth position into array
slt $t3, $t1, $t4       # if t1 < t4 then t3 = 1
beq $t3, $zero, Skip    # Skip if t3 = 0
sll $t1, $t4, 2         # t4 * 4 and store i t1

Skip:
  
addi $t2, $t2, 2        # increments j b y 2

Exit:

add $v0, $t1, $zero     #returns t1
jr $ra