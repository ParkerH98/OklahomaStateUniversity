using System;

namespace Week11ICE1
{
    class MainClass
    {
        // assigns positions on the game board
        static char[] arr = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };
   
        // creates the game board
        public static void GameBoard()
        {
            Console.WriteLine("     |     |      ");
            Console.WriteLine("  {0}  |  {1}  |  {2}", arr[1], arr[2], arr[3]);
            Console.WriteLine("_____|_____|_____ ");
            Console.WriteLine("     |     |      ");
            Console.WriteLine("  {0}  |  {1}  |  {2}", arr[4], arr[5], arr[6]);
            Console.WriteLine("_____|_____|_____ ");
            Console.WriteLine("     |     |      ");
            Console.WriteLine("  {0}  |  {1}  |  {2}", arr[7], arr[8], arr[9]);
            Console.WriteLine("     |     |      ");
        }

        public static void Main(string[] args)
        {
            GameBoard();
        }
    }
}
