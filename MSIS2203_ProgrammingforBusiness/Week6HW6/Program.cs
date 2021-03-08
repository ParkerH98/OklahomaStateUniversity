using System;

namespace Week6HW6
{
    class MainClass
    {
        public static void Main(string[] args)
        {

            Console.WriteLine("How much money would you like to spend today?");
            double budget = double.Parse(Console.ReadLine());
            double moneySpent = 0;
            double price = 0;
            double total = 0;
            while (moneySpent <= budget)
            {
                Console.WriteLine("Do you want to buy a pizza, apple, or macaroni");

                // Gets users food selection and price for that food
                string foodChoice = Console.ReadLine();
                GetFoodSelection(foodChoice);

                // Gets quantity and calculates remaining budget
                Console.WriteLine("How many {0}s do you want?", foodChoice);


                double quantity = double.Parse(Console.ReadLine());
                double amnt = AmountSpent(quantity);

                if (budget <= 0)
                {
                    break;
                }

                // Displays remaining budget
                Console.WriteLine("You have {0} left", budget);

                Console.WriteLine("Do you want to continue?");
                Console.WriteLine("yes or no");
                string done = Console.ReadLine();

                // exits loop if user is done shopping
                if (done == "no")
                {
                    break;
                }
                Console.Clear();
            }
            Console.WriteLine("Your total is {0}", total);

            string GetFoodSelection(string foodChoice)
            {

                if (foodChoice == "pizza")
                {
                    price = 5.99;
                }
                else if (foodChoice == "apple")
                {
                    price = 1.19;
                }
                else if (foodChoice == "macaroni")
                {
                    price = 2.49;
                }

                return foodChoice;
            }

           double AmountSpent(double quantity)
            {
                double foodPrice = quantity * price;
                budget -= foodPrice;
                total += foodPrice;
                if (budget <= 0)
                {
                    Console.WriteLine("You're out of money.");
                }
                return foodPrice;
            }
        }
    }
}