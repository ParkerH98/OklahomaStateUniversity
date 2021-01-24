using System;
using System.IO;

namespace Week9ICE1
{
    class MainClass
    {
        public static void Main(string[] args)
        {
            string data = File.ReadAllText("/Users/Parker/Documents/College/MSIS2203/Week9ICE1/GDPdata.csv");
            Console.WriteLine(data);

            int a = 20 / 3;
            Console.WriteLine(a);

            for (int r = 0; r < 5; r++)
            {
                for (int c = 0; c < 4; c++)
                {
                    Console.WriteLine((r + c) + " ");
                }
                Console.WriteLine();
            }
        }
    }
}
