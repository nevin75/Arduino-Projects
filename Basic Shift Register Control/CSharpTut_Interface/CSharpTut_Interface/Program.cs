using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CSharpTut_Interface
{
    class Program
    {
        static void Main(string[] args)
        {
            IElectronicDevice TV = TVRemote.GetDevice();

            PowerButton powBut = new PowerButton(TV);

            powBut.Execute();
            powBut.Undo();

            Volume volBut = new Volume(TV);
           


            

            

            Console.ReadLine();

        }
    }
}
