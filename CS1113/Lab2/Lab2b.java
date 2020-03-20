// CS 1113 Lab 2
// Parker Hague
// 60863
// September 13, 2018
public class Lab2b {
    public static void main(String [] args){
        System.out.println("Lab 2b for Parker Hague, Lab CRN 60863");
        for(int i=1; i <=100; ++i)
        {
            if ( i % 5 == 0) 
            {
                  System.out.print("Fizz"); 
            }
            if ( i % 3 == 0) 
            {
                  System.out.print("Buzz"); 
            }
            else
            {
                  System.out.print(i); 
            }  
            System.out.print(" ");
        } // end of for loop
        System.out.println();
    }
}