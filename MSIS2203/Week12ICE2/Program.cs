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

                Fare fare = new Fare();
                const int maxHours = 8;

                Console.WriteLine("Please enter rental time in hours.");

                double hoursRented = double.Parse(Console.ReadLine());

                Console.WriteLine("Do you have a parking pass? Y or N?");
                string yN = Console.ReadLine();

                while (hoursRented <= maxHours && hoursRented > 0)
                {
                    // declares a current time
                    DateTime time = DateTime.Now;

                    // calculates the customer fare based on parking pass
                    double customerFare;
                    if (yN == "Y"){
                        customerFare =  fare.CalculateFareY(hoursRented);
                    }
                    else{
                        customerFare =  fare.CalculateFareN(hoursRented);
                    }
                    // prints customer parking pass statement
                    Console.WriteLine(fare.PassCustomer(yN));

                    // get time when rental is oevr
                    DateTime expiredTime = time.AddHours(hoursRented);

                    Console.WriteLine("Your total is {0:C}. Your time expires at {1}.", customerFare, expiredTime);

                    // clears console for next user and breaks out of loop
                    Console.ReadLine();
                    break;
                }
            }
        }

        public class Fare : ParkingPass
        {
            protected const double hourlyRate = 2.5;

            public double CalculateFareN(double hoursRented){
                    double fare = hourlyRate * hoursRented;
                    return fare;
            }

            public double CalculateFareY(double hoursRented){
                return 0;
            }
        }

        public class ParkingPass
        {
            public string PassCustomer(string yN){
                if (yN == "Y")
                {
                    return "You don't need to pay.";
                }
                else
                {
                    return "You need to pay.";
                }
            }
        }
    }
}