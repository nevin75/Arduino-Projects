using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Assignment3
{
    class Program
    {
        public static void Main()
        {
            //get input from the user

            System.Console.Out.Write("Enter the length of the room:”);
            string num1  = System.Console.ReadLine();
            double num1AsDoub = System.Convert.ToDouble(num1);

            System.Console.Out.Write("Enter the width of the room: ");
                    

            string num2 = System.Console.ReadLine();
            double num2AsDoub = System.Convert.ToDouble(num2);

            //Calculate the area
            Double area = num1AsDoub * num2AsDoub;

            //display result

            System.Console.Out.Writeline(“The area of the room is”+area);
            //calculate the costs

            Decimal cost = area * 10.00;

            //display the result

            System.Console.Out.Writeline(“The cost of carpeting the room is $s” +cost);
        }
            }
        }
    }
}
