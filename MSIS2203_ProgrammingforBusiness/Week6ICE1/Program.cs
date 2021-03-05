using System;

namespace Week6ICE1
{
    class MainClass
    {
        public static void Main(string[] args)
        {
            // Correct pass
            string correctPassword = "pizza";
            // user pass
            string userPassword = "";
            // declaring wrong password true
            bool passwordIncorrect = true;
            // start of while loop. going to iterate until the pass is correct
            while(passwordIncorrect)
            {

                Console.WriteLine("Enter password");
                userPassword = Console.ReadLine();

                // if and else statements print answer dependent upon pass entered
                if (userPassword == correctPassword)
                {
                    passwordIncorrect = false;
                  
                   
                }
                else {
                    Console.WriteLine("Incorrect. Try again.");

                }


            }
            Console.WriteLine("Password correct!");
        }
    }
}