using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;

namespace Week9ICE2
{
    class MainClass
    {
        public static void Main(string[] args)
        {
            // printing address book by importing CSV and rewriting
            int i = 0;

            string filepath = "/Users/Parker/Documents/College/MSIS2203/Week9ICE2/AddressBook.csv";

            using (var reader = new StreamReader(filepath))
            {
                List<string> Name = new List<string>();
                List<string> PhoneNumber = new List<string>();

                while (!reader.EndOfStream)
                {
                    var line = reader.ReadLine();
                    var contents = line.Split(',');
                    Name.Add(contents[0]);
                    PhoneNumber.Add(contents[1]);
                }

                string writefile = "/Users/Parker/Documents/College/MSIS2203/Week9ICE2/AddressBookNew.csv";

                var writer = new StreamWriter(File.OpenWrite(writefile));

                while (i < 5)
                {
                    writer.WriteLine(Name.ElementAt(i) + "'s phone number is " +
                                     PhoneNumber.ElementAt(i));

                    i++;
                }

                writer.Close();
            }

            string addressBook = File.ReadAllText("/Users/Parker/Documents/College/MSIS2203/Week9ICE2/AddressBookNew.csv");
            Console.WriteLine(addressBook);


            // Creates new CSV file and adds grades to it.

            using (var Gradesreader = new StreamReader("/Users/Parker/Documents/College/MSIS2203/Week9ICE2/Grades.csv"))
            {
                List<string> Class = new List<string>();
                List<string> Grades = new List<string>();

                while (!Gradesreader.EndOfStream)
                {
                    var gradesLine = Gradesreader.ReadLine();
                    var gradesContents = gradesLine.Split(',');
                    Class.Add(gradesContents[0]);
                    Grades.Add(gradesContents[1]);
                }

                string gradefile = "/Users/Parker/Documents/College/MSIS2203/Week9ICE2/GradesNew.csv";

                var gradesWriter = new StreamWriter(gradefile);

                Class.Add("BADM1113");
                Grades.Add("A");

                gradesWriter.Close();

            }
            string newGrades = File.ReadAllText("/Users/Parker/Documents/College/MSIS2203/Week9ICE2/GradesNew.csv");

            Console.WriteLine(newGrades);
        }

    }
}
