using System;

namespace Week4ICE2
{
    class MainClass
    {
        public static void Main(string[] args)
        {
            string[] courseName = new string[5] { "ENTO 0001", "ENTO 0002", "ENTO 0003", "ENTO 0004", "ENTO 0005" };

            string[] grades = new string[5] { "A", "B", "C", "D", "F" };

            float[] qp = new float[5];

            Console.WriteLine("Enter your letter grades for all of your classes.");

            for (int i = 0; i < 5; i++)
            {
                grades[i] = Console.ReadLine();

            }

            for (int i = 0; i < 5; i++)
            {
                Console.WriteLine("Course: " + courseName[i] + " Grade: " + grades[i]);
            }
        }
    }
}
