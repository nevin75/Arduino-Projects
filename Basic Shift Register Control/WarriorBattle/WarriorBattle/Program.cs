using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace WarriorBattle
{
    class Program
    {
        static void Main(string[] args)
        {
            Flashcard newCard = new Warrior("Maximus", 1000, 120, 40);
            Warrior bob = new Warrior("Bob", 1000, 120, 40);
            Battle.StartFight(maximus, bob);

            Console.ReadLine();
        }
    }
}
