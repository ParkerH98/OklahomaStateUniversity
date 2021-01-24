using System;

namespace Week10ICE1
{
    class MainClass
    {
        public static void Main(string[] args)
        {
            Student parkerHague = new Student();

            Console.WriteLine("What is your major?");
            parkerHague.Major = Console.ReadLine();

            Console.WriteLine("What is your GPA?");
            parkerHague.GPA = double.Parse(Console.ReadLine());

            Console.WriteLine("What is your class standing?");
            parkerHague.Class_standing = Console.ReadLine();

            string evaluation = Evaluation(parkerHague);

            Console.WriteLine(evaluation);
        }




        class Student
        {
            public string Major;
            public double GPA;
            public string Class_standing;
        }

        static string Evaluation(Student parkerHague)
        {
            string goodEvaluation = "You are an exemplary student.";
            string badEvaluation = "You need to do better.";

            if (parkerHague.GPA > 3.0)
            {
                return goodEvaluation;
            }
            else
            {
                return badEvaluation;
            }
        }
    }
}