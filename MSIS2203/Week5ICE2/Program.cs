using System;

namespace Week5ICE2
{
    class MainClass
    {
        public static void Main(string[] args)
        {
            string[] skiResort = new string[] {"Snowbird", "Whistler", "Heavenly", "Aspen", "Courchevel"};
            int[] heightFeet = new int[] { 2200, 1850, 2700, 1500, 1300 };
            int[] heightMeter = new int[5];
            string[] difficulty = new string[5];
            for (int i = 0; i < 5; i++)
            {
                if (heightFeet[i] >= (int)2000)
                
                {
                    difficulty[i] = "Hard";
                }
                else if (heightFeet[i] >= (int)1500 && heightFeet[i] <= (int)1999)
                {
                    difficulty[i] = "Intermediate";
                }
                else
                {
                    difficulty[i] = "Easy";
                }
                heightMeter[i] = FeetConversion(heightFeet[i]);
                Console.WriteLine("{0} ski resort has a height of {1} feet. Difficulty: {2}", skiResort[i], heightMeter[i], difficulty[i]);
            }

        }

        static int FeetConversion (int heightFeet)
        {
            int heightMeter = (int)(heightFeet * 3.28);
            return heightMeter;
        }
    }
}
