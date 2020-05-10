using System;

namespace Week3HW3
{
    class MainClass
    {
        public static void Main(string[] args)
        {
            Console.WriteLine("What is your name?");

            string yourName = Console.ReadLine();

            // start of grade 1

            Console.WriteLine("Course 1");

            string course1 = Console.ReadLine();

            Console.WriteLine("Grade in Course 1");

            string grade1 = Console.ReadLine();

            int qp1 = 0;

            if (grade1 == "A")
            {
                 qp1 = 4;
            }
                else if (grade1 == "B")
            {
                 qp1 = 3;
            }
                else if (grade1 == "C")
            {
                 qp1 = 2;
            }
                else if (grade1 == "D")
            {
                 qp1 = 1;
            }

            // start of grade 2

            Console.WriteLine("Course 2");

            string course2 = Console.ReadLine();

            Console.WriteLine("Grade in Course 2");

            string grade2 = Console.ReadLine();

            int qp2 = 0;

                if (grade2 == "A")
            {
                qp2 = 4;
            }
            else if (grade1 == "B")
            {
                qp2 = 3;
            }
            else if (grade2 == "C")
            {
                qp2 = 2;
            }
            else if (grade1 == "D")
            {
                qp2 = 1;
            }

            // start of grade 3

            Console.WriteLine("Course 3");

            string course3 = Console.ReadLine();

            Console.WriteLine("Grade in Course 3");

            string grade3 = Console.ReadLine();

            int qp3 = 0;

                if (grade3 == "A")
            {
                 qp3 = 4;
            }
            else if (grade3 == "B")
            {
                 qp3 = 3;
            }
            else if (grade3 == "C")
            {
                 qp3 = 2;
            }
            else if (grade3 == "D")
            {
                 qp3 = 1;
            }

            int gpa = (qp1 + qp2 + qp3) / 3;


            if (gpa > 3)
            {
                Console.WriteLine("Congratulations! You qualified!");
            }

            else 
            {
                Console.WriteLine("You did not qualify.");
            }


        } // end of Main(string[] args)
    }
}
