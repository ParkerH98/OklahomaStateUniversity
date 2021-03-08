
// Parker Hague
// Problem 3

public class Problem2_3{

    public void function(int a, int b, int[] c){

        int n = b + 1; // addi t4 = a3 + 1

        int i; // t5
        int temp; // t6
        while (n <= a){ // if n <= a continue // bge t4, a2

            temp = array[i]; // load t5 into t6
            array[i - 1] = temp; // store t5 into t6
            // subtracting 1 because the location of i is being subtracted by 4
        }

        return;
    }
}


