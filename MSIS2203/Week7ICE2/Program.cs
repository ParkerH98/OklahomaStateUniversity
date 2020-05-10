using System;

namespace Week7ICE2
{
    class MainClass
    {
        public static void Main(string[] args)
        {

            while (true)
                {
                    Console.WriteLine();

                    DateTime currentDate = DateTime.Now;

                    Console.WriteLine("Please enter your birthday.");

                    DateTime userBirthday = DateTime.Parse(Console.ReadLine());

                    TimeSpan age = DateTime.Now.Subtract(userBirthday);

                    if (age.TotalDays < 7665)
                    {
                        Console.WriteLine("You're not old enough. Get the hell out of here.");
                    }
                    else
                    {
                        Console.WriteLine("Welcome.");
                    }

                }
        }
    }
}
