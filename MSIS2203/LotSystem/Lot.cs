using System;
namespace LotSystem
{
    public class Lot
    {
        public static  int count30Mins = 30; // displays the quantity of each type of space
        public static int count60Mins = 30;
        public static int count24Hours = 20;
        public static int countUnlimited = 20;

        public static int UpdateSpaceQuantity(int UserSpaceType){ // calculations to update the quantity of available spaces
            switch (UserSpaceType)
            {
                case 1:
                    count30Mins -= 1;
                    return count30Mins;
                case 2:
                    count60Mins -= 1;
                    return count60Mins;
                case 3:
                    count24Hours -= 1;
                    return count24Hours;
                case 4:
                    countUnlimited -= 1;
                    break;
            }

            return count24Hours;
        }
    }
}