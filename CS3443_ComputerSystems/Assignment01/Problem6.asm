

// problem 5
// MIPS to C
// Parker Hague

int a = 0; // add 0 + 0

int b = 0; // add 0 + 0

int c = 20; // add 0 + 20

int d; // $t1


// combined slt & beq functions
// jump with condition creates while loop
while (b < c && b != d){        // have to use != because if beq func is true then the system will exit

    d = 1;

    if (b == d){

        break; // exit if true
    }

    else{

        d = 0; // false of slt function

        a = a + b; // false of beq function
    }

    b++; // b = b + 1
}
