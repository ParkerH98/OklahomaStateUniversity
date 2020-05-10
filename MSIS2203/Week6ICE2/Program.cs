using System;

namespace Week6ICE2
{
    class MainClass
    {
        public static void Main(string[] args)
        {
            // Currency
            Console.WriteLine(String.Format("{0:C}", 115.82));

            // Number with commas
            Console.WriteLine(String.Format("{0:N}", 992334654));

            // Percentage
            Console.WriteLine(String.Format("{0:P}", .986));

            // Custom format // Phone number
            Console.WriteLine(String.Format("{0:(###) ###-####}", 4058220384));

            // Upper and lower case
            string name = "Parker";
            Console.WriteLine(name.ToUpper());
            Console.WriteLine(name.ToLower());

            // Replaces "a" with "u"
            Console.WriteLine(name.Replace("a", "u"));


        }
    }
}
