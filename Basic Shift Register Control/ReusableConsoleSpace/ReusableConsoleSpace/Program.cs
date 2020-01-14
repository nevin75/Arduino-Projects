
using System;

// We will learn about namespaces in a different lesson.
namespace CSharpBootCamp
{
    class HomeworkAssignment
    {
        /*
            Homework #1 
            Read name, surename, age, weight (in kg) and height (in cm) from console.
            1) Print all the info based on the example message below:
            Tom Jefferson is 19 years old, his weight is 50 kg and his height is 156.5 cm. 

            2) Calculate and print body-mass index (BMI)
            3) Do 1 and 2 for another person.
        */

        static void Main(string[] args)
        {
            GetAndReportData_AssignmentOne();
        }

        private static void GetAndReportData_AssignmentOne()
        {
            char again = 'y';

            while (again == 'y')
            {
                Request("first name");
                string firstName = Console.ReadLine();

                Request("last name");
                string surname = Console.ReadLine();

                Request("age in years");
                int age = GetInt();

                Request("weight in kilograms");
                double weight = GetDouble();

                Request("height in centimeters");
                double height = GetDouble();

                ReportBasicInfo(firstName, surname, age, weight, height);

                ReportBMI(firstName, weight, height);

                again = RunAgain();
            }
        }

        private static void Request(string prompt)
        {
            Console.Write("Please enter user's " + prompt + ": ");
        }

        private static double GetDouble()
        {
            return Convert.ToDouble(Console.ReadLine());
        }

        private static int GetInt()
        {
            return Convert.ToInt32(Console.ReadLine()); 
        }

        private static void ReportBasicInfo(string firstName, string surname, int age, double weight, double height)
        {
            Console.WriteLine("\n" + firstName + " " + surname +
                " is " + age + " years old, " +
                "their weight is " + weight + " kg " +
                "and their height is " + height + " cm.");
        }

        private static void ReportBMI(string firstName, double weight, double height)
        {
            Console.WriteLine("\n" + firstName + "'s BMI is " + (CalculateBMI(weight, height)) + ".");
        }

        private static double CalculateBMI (double weight, double height)
        {
            double heightInMeters = height * .01;
            return weight / (heightInMeters * heightInMeters);
        }

        private static char RunAgain()
        {
            Console.Write("\nWould you like to repeat this program? (y or n)");
            return Convert.ToChar(Console.ReadLine());
        }

    }
} 