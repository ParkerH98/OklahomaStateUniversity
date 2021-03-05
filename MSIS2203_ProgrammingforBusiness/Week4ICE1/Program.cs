using System;

namespace Week4ICE1
{
    class MainClass
    {
        public static void Main(string[] args)
        {
            float sum = 0;
            int qp = 0;

            for (int i = 0; i < 5; i++)
            {
                Console.WriteLine("What grade did you get in this course?");
                string grade = Console.ReadLine();
                
                if (grade == "A") qp = 4;
                if (grade == "B") qp = 3;
                if (grade == "C") qp = 2;
                if (grade == "D") qp = 1;
                if (grade == "F") qp = 0;
                
                sum = sum + qp;
            }
            float gpa = sum / 5;

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
