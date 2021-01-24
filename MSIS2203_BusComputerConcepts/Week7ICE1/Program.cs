using System;

namespace Week7ICE1
{
    class MainClass
    {
        public static void Main(string[] args)
        {
            Console.WriteLine("Please enter the manufacturer date.");

            // Gets user input date
            DateTime manufactureDate = DateTime.Parse(Console.ReadLine());

            // Creates a ketchup age by subtracting now from the user date
            TimeSpan ketchupAge = DateTime.Now.Subtract(manufactureDate);

            // Compares the days in the ketchup age to 700
            if (ketchupAge.TotalDays > 700)
            {
                Console.WriteLine("Sorry this ketchup is too old.");
            }

            else 
            {
                Console.WriteLine("This ketchup is good. Enjoy!");
            }

        }
    }
}
