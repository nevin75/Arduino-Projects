using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.PeerToPeer.Collaboration;
using System.Text;
using System.Threading.Tasks;
using PokerEvaluatorLibrary.Tests;
using PokerEvaluatorLibrary.Classes;


namespace Oct4BobTaborReferencesInAssembly
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("How many players are we evaluating?");
            int numOfPlayers;
            numOfPlayers = Convert.ToInt32(Console.ReadLine());

            Console.WriteLine("How many cards are in each hand? (max is 6)");
            int sizeOfHand;
            sizeOfHand = Convert.ToInt32(Console.ReadLine());

            string[,] arrayOfAllCards = new string[numOfPlayers - 1 , sizeOfHand - 1];
            Hand[] hands = new Hand[numOfPlayers - 1];
            string card1, card2, card3, card4, card5;

            string[] hand1, hand2, hand3;


            for (int i = 0; i <= numOfPlayers - 1; i++)
            {
                Console.WriteLine("What is the name of player{0}?", i + 1);
                hands[i].playerName = Console.ReadLine();

                Console.WriteLine("What is their first card (Number and Letter) for {0}", hands[i].playerName);
                card1 = Console.ReadLine();

                Console.WriteLine("What is their second card (Number and Letter) for {0}", hands[i].playerName);
                card2 = Console.ReadLine();

                Console.WriteLine("What is their third card (Number and Letter) for {0}", hands[i].playerName);
                card3 = Console.ReadLine();

                Console.WriteLine("What is their fourth card (Number and Letter) for {0}", hands[i].playerName);
                card4 = Console.ReadLine();

                Console.WriteLine("What is their fift card (Number and Letter)");
                card5 = Console.ReadLine();
                hands[i].nums
                if (i == 0)
                {
                    hand1 = StaticHandEvaluationTools.ConvertStringsToArray(card1, card2, card3, card4, card5);
                }
                if (i == 1)
                {
                    hand2 = StaticHandEvaluationTools.ConvertStringsToArray(card1, card2, card3, card4, card5);
                }
                if (i == 2)
                {
                    hand3 = StaticHandEvaluationTools.ConvertStringsToArray(card1, card2, card3, card4, card5);
                }

                CompareHands.FindWinner(hand1, hands[0].playerName, hand2, hand3, hands[2].playerName ;

        }

    }
}
