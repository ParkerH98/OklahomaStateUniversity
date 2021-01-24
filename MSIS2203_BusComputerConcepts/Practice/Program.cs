using System;

namespace Practice
{
    class MainClass
    {
        public static void Main(string[] args)
        {
            string[] stateName = new string[4];
            int[] statePop = new int[4];
            int maxPop = 0;
            int index = 0;

            for (int i = 0; i < 4; i++){
                Console.WriteLine("What is the state name?");
                stateName[i] = Console.ReadLine();
                Console.WriteLine("What is the population?");
                statePop[i] = int.Parse(Console.ReadLine());

                if (statePop[i] > maxPop)
                {
                    maxPop = statePop[i];
                    index = i;
                }

                Console.WriteLine("The state with the highest population is {0} with a population of {1}", stateName[index], statePop[index]);
                Console.ReadLine();
                Console.Clear();
            }
        }
    }
}
