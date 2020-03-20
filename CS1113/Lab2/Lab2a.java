// CS 1113 Lab 2
// Parker Hague
// 60863
// September 13, 2018
public class Lab2a {
    public static void main(String [] args){
        System.out.println("Lab 2a for Parker Hague, Lab CRN 60863");
        for(int i=1; i <=100; ++i)
        {
            if ( i % 5 == 0  ) 
            {
                if ( i % 3 == 0 && i % 5 == 0  ) 
                {
                      System.out.println("FizzBuzz ");
                } else 
                {
                      System.out.println("Fizz ");
                } 
            } else 
            {
                if ( i % 3 == 0 ) 
                {
                      System.out.println("Buzz ");
                } else 
                {
                      System.out.println(i+" ");
                } 
            }  
        } // end of for loop
        System.out.println();
    }
}