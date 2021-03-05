using System;
using System.Threading;

namespace Week11ICE1
{
    class MainClass
    {
        // game created by Sourabh Somani
        // comments by Parker Hague



        // creates an array that stores game positions 
        static char[] arr = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };
        static int player = 1;
        // user choice/move
        static int choice;

        // flag varibale is a way of controlling the while loop so that the game can begin and end when it is supposed to
        static int flag = 0;

        static void Main(string[] args)
        {
            do
            {
                // game starts here 
                Console.Clear();
                Console.WriteLine("Player1:X and Player2:O");
                Console.WriteLine("\n");

                // uses a counter to decide whose turn it is
                if (player % 2 == 0)
                {
                    Console.WriteLine("Player 2 Chance");
                }
                else
                {
                    Console.WriteLine("Player 1 Chance");
                }
                Console.WriteLine("\n");

                // calls the gameboard
                Board();
                // takes user move

                choice = int.Parse(Console.ReadLine());

                // checks to see if entered value is valid
                if (arr[choice] != 'X' && arr[choice] != 'O')
                {
                    // assigns X or O to players
                    if (player % 2 == 0)
                    {
                        arr[choice] = 'O';
                        // this counter is how each player is switching turns
                        player++;
                    }
                    else
                    {
                        arr[choice] = 'X';
                        player++;
                    }
                }
                // checks if player trys to move where a move has already been made
                else
                {
                    Console.WriteLine("Sorry the row {0} is already marked with {1}", choice, arr[choice]);
                    Console.WriteLine("\n");
                    Console.WriteLine("Please wait 2 second board is loading again.....");
                    Thread.Sleep(2000);
                }

                // checking if a winning move has been made
                flag = CheckWin();

                // loops game until flag is anything but zero
            } while (flag != 1 && flag != -1);

            {

                Console.Clear();

                // creating board game for next game
                Board();

                // if flag value is 1 then someone won
                if (flag == 1)
                {
                    Console.WriteLine("Player {0} has won", (player % 2) + 1);
                }
                // the game resulted in a draw
                else
                {
                    Console.WriteLine("Draw");
                }
                Console.ReadLine();
            }
        }
        // method that creates board game
        private static void Board()
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
            // defines a method for various win scenarios 
            // a 1 will be returned for any of the win scenarios thus ending the game
            // by changing the flag & therefore ending the while loop
            private static int CheckWin()
            {
                #region Horzontal Winning Condtion
                //Winning Condition For First Row   
                if (arr[1] == arr[2] && arr[2] == arr[3])
                {
                    return 1;
                }
                //Winning Condition For Second Row   
                else if (arr[4] == arr[5] && arr[5] == arr[6])
                {
                    return 1;
                }
                //Winning Condition For Third Row   
                else if (arr[6] == arr[7] && arr[7] == arr[8])
                {
                    return 1;
                }
                #endregion

                #region vertical Winning Condtion
                //Winning Condition For First Column       
                else if (arr[1] == arr[4] && arr[4] == arr[7])
                {
                    return 1;
                }
                //Winning Condition For Second Column  
                else if (arr[2] == arr[5] && arr[5] == arr[8])
                {
                    return 1;
                }
                //Winning Condition For Third Column  
                else if (arr[3] == arr[6] && arr[6] == arr[9])
                {
                    return 1;
                }
                #endregion

                #region Diagonal Winning Condition
                else if (arr[1] == arr[5] && arr[5] == arr[9])
                {
                    return 1;
                }
                else if (arr[3] == arr[5] && arr[5] == arr[7])
                {
                    return 1;
                }
                #endregion

                #region Checking For Draw
                // If all the cells or values filled with X or O then any player has won the match  
                else if (arr[1] != '1' && arr[2] != '2' && arr[3] != '3' && arr[4] != '4' && arr[5] != '5' && arr[6] != '6' && arr[7] != '7' && arr[8] != '8' && arr[9] != '9')
                {
                    return -1;
                }
                #endregion

                else
                {
                    return 0;
                }
            }
        }
}
