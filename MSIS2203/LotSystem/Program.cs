using System;

namespace LotSystem
{
    class MainClass
    {
        public static void Main(string[] args)
        {
            while (true) // loops the program
            {
                Fare customerFare = new Fare(); // creates object of Fare class
                DateTime expired; //used to assign expired time

                Fare.InfoScreen(); // prints info screen

                int userSpaceType = int.Parse(Console.ReadLine()); // gets user input for their desired type of space

                Lot.UpdateSpaceQuantity(userSpaceType); // updates the amount of remaining spaces

                Fare.InfoScreen(); // prints the updated info screen

                if (userSpaceType == 1 || userSpaceType == 2 || userSpaceType == 3) // checks which space is selected // spaces 1, 2, & 3 are the same because they are free
                {
                    expired = customerFare.GetExpiredTime(userSpaceType); // gets expired time based on the selected space
                    customerFare.FreeFare(); // calculates fare
                    Console.WriteLine("Your fee is {0:C}. Your space expires at {1}", customerFare.rentalPrice, expired); // prints message
                }
                else if (userSpaceType == 4) // 4 has its own check because the fare is calculated differently
                {
                    Console.WriteLine("How many hours would you like to rent the spot for?");
                    customerFare.hours = double.Parse(Console.ReadLine()); // gets user input to calcualte fare
                    expired = customerFare.GetExpiredTime(userSpaceType);
                    customerFare.PaidFare(customerFare.hours); // calculates fare
                    Console.WriteLine("Your fee is {0:C}. Your space expires at {1}\n", customerFare.rentalPrice, expired);
                    Fare.PaymentScreen(); // prints the payment method screen
                    Console.ReadLine();
                    Console.WriteLine("Thank you.");

                }
                else // checks if user didn't input a valid space number
                {
                    Console.WriteLine("Please enter a valid selection.");
                }
                Console.ReadLine();
            }
        }
    }
}