using System;
using Castle.Windsor;
using MargieBot;
using System.ComponentModel;
using System.Configuration;
using ClubSpeedSlackBot;
using System.Text;

namespace CountdownToMexico
{
    class Program
    {
        static void Main(string[] args)
        {
           // var container = new WindsorContainer();
           // container.Register(Component.For<IResponder>().ImplementedBy<HelloResponder>());

            var bot = new Bot();
           // var responders = container.ResolveAll<IResponder>();
           // foreach (var responder in responders)
          //  {
         //       bot.Responders.Add(responder);
            //    bot.Say(ReportTimeLeft());
           // }
            var connect = bot.Connect(ConfigurationManager.AppSettings["SlackBotApiToken"]);
            bot.Say (ReportTimeLeft());
            while (Console.ReadLine() != "close")
            {
               
            }




            // Maybe....https://github.com/jammerware/margiebot/wiki
            var myBot = new Bot();
            myBot.RespondsTo("Hi Margie").With("Hey, friend!");
            myBot.RespondsTo("wheelsup").With(ReportTimeLeft("yqr");
            myBot.Connect("<your bot's slack API token>");
        }

        private static String ReportTimeLeft(string location)
        {
         
                DateTime currentTime = DateTime.Now;
            
                DateTime yqrTripStartTime = new DateTime(2020, 2, 29, 9, 40, 00);

                DateTime yvrTripStartTime = new DateTime(2020, 2, 29, 6, 0, 00);
                DateTime ywgTripStartTime = new DateTime(2020, 2, 29, 6, 45, 00);
                DateTime cltTripStartTime = new DateTime(2020, 2, 29, 11, 20, 00);

            if (location == "yqr")
                TimeSpan TimeToWait = yqrTripStartTime.Date - currentTime;
            if (location == "clt")
                string TimeLeft = "The time before wheels up is " + TimeToWait.Days + " days, " + TimeToWait.Hours + " hours, " + TimeToWait.Minutes + " minutes and approximately " + TimeToWait.Seconds + " seconds.");
                return TimeLeft;
        }
    }
   
   


}
namespace ClubSpeedSlackBot
{
    public class HelloResponder : IResponder
    {
        public bool CanRespond(ResponseContext context)
        {
            return context.Message.MentionsBot
                  && !context.BotHasResponded
                  && context.Message.Text.ToLower().Contains("wheelsup");
        }

        public BotMessage GetResponse(ResponseContext context)
        {
            //var builder = new StringBuilder();
           // builder.Append("Hello ").Append(context.Message.User.FormattedUserID);

            return new BotMessage { Text = ReportTimeLeft(context) };
        }
        
    }
    }
}