using System;

namespace Week12ICE1
{
    class MainClass
    {
        public static void Main(string[] args)
        {
            while (true)
            {
                Console.Clear();
                const int maxHours = 8;

                Console.WriteLine("Please enter rental time in hours.");

                double hoursRented = double.Parse(Console.ReadLine());

                while (hoursRented <= maxHours && hoursRented > 0)
                {
                    // declares a current time
                    DateTime time = DateTime.Now;

                    // calculates the customer fare
                    Fare fare = new Fare();
                    double customerFare = fare.CalculateFare(hoursRented);
                    // get time when rental is oevr
                    DateTime expiredTime = time.AddHours(hoursRented);

                    Console.WriteLine("Your total is {0:C}. Your time expires at {1}.", customerFare, expiredTime);

                    // clears console for next user and breaks out of loop
                    Console.ReadLine();
                    break;
                }
            }
        }

        public class Fare
        {
            public const double hourlyRate = 2.5;

            public double CalculateFare(double hoursRented)
            {
                double fare = hourlyRate * hoursRented;
                return fare;
            }
        }
    }
}

