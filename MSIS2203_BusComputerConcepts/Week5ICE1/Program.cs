using System;

namespace Week5ICE1
{
    class MainClass
    {

        public static void Main(string[] args)
        {
            string[] cities = new string[5] { "Paris", "London", "Barcelona", "Rome", "Amsterdam" };

            float[] celsius = new float[5] { 22, 18, 19, 21, 17 };

            float[] fahrenheit = new float[5];

            for (int i = 0; i < 5; i++)
            {
                fahrenheit[i] = Conversion(celsius[i]);

                Console.WriteLine("The temperature in " + cities[i] + " is " + fahrenheit[i]) ;
            }

            Console.ReadLine();
        }

        //method begins here
        static float Conversion(float celsius)
        {
            float fahrenheit =(celsius * 9) / 5 + 32;
            return fahrenheit;
        }
    }
}
