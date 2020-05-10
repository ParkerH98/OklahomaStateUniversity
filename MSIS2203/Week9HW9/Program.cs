using System;
using System.IO;

namespace Week9HW9
{
    class MainClass
    {
        public static void Main(string[] args)
        {
            // original file
            string filepath = "/Users/Parker/Documents/College/MSIS2203/Week9HW9/GDPdata-2.csv";
            // new file
            string writefile = "/Users/Parker/Documents/College/MSIS2203/Week9HW9/Week9HW.csv";
            // sets up new file for writing
            var writer = new StreamWriter(File.OpenWrite(writefile));
            // reads text and assigns to variable
            var file = File.ReadAllText(filepath);
            // writes data to new file
            writer.WriteLine(file);
            // closes writer
            writer.Close();
            // prints all data to console
            Console.WriteLine(file);
            }
        }
}
