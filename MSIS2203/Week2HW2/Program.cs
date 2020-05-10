using System;

namespace Week2HW2
{
    class MainClass
    {
        public static void Main(string[] args)
        {
            //Parker Hague. 11821314. TR 10:30.


            // Declaring X coord. values
            var x1 = -27;
            int x2 = 5;

            // Printing the X coords.
            Console.WriteLine("X wing 2-D plane X Coordinates : ({0}, {1}) ", x1, x2);

            // Declaring Y coord. values
            int y1 = -10;
            int y2 = 19;

            // Printing the Y coords.
            Console.WriteLine("X wing 2-D plane Y Coordinates : ({0}, {1}) ", y1, y2);

            // Printing the Y coords.
            int xCo = (x1 + x2) / 2;
            int yCo = (y1 + y2) / 2;

            // Printing final target coords.
            Console.WriteLine("The proton torpedoes must be shot at ({0}, {1}) to destroy the Death Star.", xCo, yCo);


        }
    }
}
