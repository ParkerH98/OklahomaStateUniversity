using System;

namespace Week3ICE2
{
    class MainClass
    {
        public static void Main(string[] args)
        {
            // prints name question
            Console.WriteLine("What is your name?");

            // reads user input
            string yourName = Console.ReadLine();

            // prints amount question
            Console.WriteLine("Amount due?");

            // sets variable
            int amountDue = Int32.Parse(Console.ReadLine());

            // prints question
            Console.WriteLine("How many $20 dollar bills did you give?");

            // sets variable
            int noOfBills = Int32.Parse(Console.ReadLine());

            // calcualtes change
            int change = (noOfBills * 20) - amountDue;

            // first if statement
            if (change > 0)
            {
                // prints change
                Console.WriteLine("Your change would be $" + change);
            }

            // program reads this statement if the first one didnt complete
            else if (change == 0)
            {
                // prints no change
                Console.WriteLine("You don't have any change.");
            }

            // // program reads this statement if the first two didnt complete
            else if (change < 0)
            {
                // prints more cash
                Console.WriteLine("I need more cash.");
            }

        }
    }
}
