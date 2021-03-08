using System;
namespace LotSystem
{
    public class Fare : Lot
    {
        public DateTime now = DateTime.Now; // used to calculate expired time
        public DateTime expired; // used to calculate expired time
        const double hourlyRate = .75; // hourly rate set as a constant
        public double rentalPrice;
        public double hours;

        public static void InfoScreen(){ // main info screen
            Console.Clear();
            Console.WriteLine("Welcome to Lot #29.");
            Console.WriteLine("Please indicate what type of parking space you would like.\n");
            Console.WriteLine("#1\t30 minute parking\tLot count: {0}", count30Mins);
            Console.WriteLine("#2\t60 minute parking\tLot count: {0}", count60Mins);
            Console.WriteLine("#3\t24 hour parking\t\tLot count: {0}", count24Hours);
            Console.WriteLine("#4\tPaid parking\t\tLot count: {0}\n", countUnlimited);
        }

        public double FreeFare(){ // calculates the fare for spots 1, 2, & 3
            rentalPrice = 0;
            return rentalPrice;
        }

        public double PaidFare(double hours){ // calculates fare for spot 4
            rentalPrice = hourlyRate * hours;
            return rentalPrice;
        }

        public DateTime GetExpiredTime(int userSpaceType){ // calculates the expired time base on userSpaceType
            switch (userSpaceType)
            {
                case 1:
                    expired = now.AddMinutes(30);
                    return expired;
                case 2:
                    expired = now.AddMinutes(60);
                    return expired;
                case 3:
                    expired = now.AddHours(24);
                    return expired;
                case 4:
                    expired = now.AddHours(hours);
                    break;
            }
            return expired;
        }

        public static void PaymentScreen(){ // display for the payment screen
            Console.WriteLine("How would you like to pay?");
            Console.WriteLine("#1\t\tCash");
            Console.WriteLine("#2\t\tCard");
        }
    }
}
