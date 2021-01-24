using System;

namespace Week12HW12
{
    class MainClass
    {
        public static void Main(string[] args)
        {
            // creates instance of People & Fee class
            Student user = new Student();
            Fee userFee = new Fee();

            Console.WriteLine("What is your name?");
            user.studentName = Console.ReadLine();

            Console.WriteLine("What is your CWID?");
            user.CWID = int.Parse(Console.ReadLine());

            Console.WriteLine("What is your major?");
            user.major = Console.ReadLine();

            Console.WriteLine("What is your GPA?");
            user.GPA = double.Parse(Console.ReadLine());

            Console.WriteLine("How many credits are you taking?");
            userFee.credits = int.Parse(Console.ReadLine());

            userFee.CalculateFee(userFee.credits);
            Console.WriteLine("Your tuition is {0:C} per semester.", userFee.tuition);
        }


        public class People
        {
            // instance variables
            public string studentName;
            public int CWID;
        }


        public class Student : People
        {
            // instance variables
            public string major;
            public double GPA;

        }


        public class Fee : Student
        {
            // instance variables
            public int credits;
            public double tuition;

            public static double tuitionRate = 300.6;

            // takes credits as a parameter and returns the tuition
            public double CalculateFee(int credits){
                tuition = credits * tuitionRate;
                return tuition;
            }
        }
    }
}
