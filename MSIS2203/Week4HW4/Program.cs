using System;

namespace Week4HW4
{
    class MainClass
    {
        public static void Main(string[] args)
        {
            string[] courseName = { "ENTO 0001", "ENTO 0002", "ENTO 0003", "ENTO 0004", "ENTO 0005" };

            string[] grades = { "A", "B", "C", "D", "F" };

            float[] qp = new float[5];

            float totalqp = 0;

            Console.WriteLine("Enter your letter grades for all of your classes.");

            // Console is reading user input
            for (int i = 0; i < 5; i++)
            {
                grades[i] = Console.ReadLine();

            }
            // Console displays a report card
            for (int i = 0; i < 5; i++)
            {
                Console.WriteLine("Course: " + courseName[i] + " Grade: " + grades[i]);

            }
            // Console stores quality points to calculate GPA
            for (int i = 0; i < 5; i++)
            {
                if (grades[i] == "A") qp[i] = 4;
                if (grades[i] == "B") qp[i] = 3;
                if (grades[i] == "C") qp[i] = 2;
                if (grades[i] == "D") qp[i] = 1;
                if (grades[i] == "F") qp[i] = 0;
                totalqp = totalqp + qp[i];
            }

            float gpa = totalqp / 5;

            Console.WriteLine("Your GPA is " + gpa);

            if (gpa > 3)
            {
                Console.WriteLine("Congratulations! You qualified!");
            }

            else
            {
                Console.WriteLine("You did not qualify.");

            }
        }
    }
}
