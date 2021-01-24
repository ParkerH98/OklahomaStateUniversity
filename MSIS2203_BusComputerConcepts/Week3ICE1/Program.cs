using System;

namespace Week3ICE1
{
    class MainClass
    {
        public static void Main(string[] args)
        {
            // Parker Hague. 11821214. TR 10:30

            // prints name question
            Console.WriteLine("What is your name?");

            // reads user input
            string userName = Console.ReadLine();

            // prints drink question
            Console.WriteLine("What is your beverage of choice?");

            // reads user input
            string userBeverage = Console.ReadLine();

            // prints budget question
            Console.WriteLine("What is your budget?");

            // these lines read the user input as a string and converts it to an int
            string userBudget = Console.ReadLine();
            int budget = int.Parse(userBudget);

            // prints BOC price question
            Console.WriteLine("What is price of your Beverage of choice?");

            // these lines read the user input as a string and converts it to an int
            string drinkPrice = Console.ReadLine();
            int price = int.Parse(drinkPrice);

            // variable that calculates quantity
            int quantity = budget / price;

            // if statement pulls this line of code if my parameters are met
            if (quantity == 1)
            {
                // what will be printed if parameters are met
                Console.WriteLine("{0} can buy {1} {2}.", userName, quantity, userBeverage);
            }

            // if statement pulls this line of code if my parameters are met
            else if (quantity >= 1)
            {
                // what will be printed if parameters are met
                Console.WriteLine("{0} can buy {1} {2}s.", userName, quantity, userBeverage);
            }

            // if statement pulls this line of code if my parameters are met
            else if (quantity == 0)
            {
                // what will be printed if parameters are met
                Console.WriteLine("{0} can not afford to buy a single {1}.", userName, userBeverage);
            }

        }
    }
}

