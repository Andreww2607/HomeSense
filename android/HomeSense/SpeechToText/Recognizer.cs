using System;
using System.Collections.Generic;
using System.Linq;
using Android.Content;
using HomeSense.Commands;

namespace HomeSense.SpeechToText
{
    public class Recognizer
    {
        private readonly Context _context;

        public Recognizer(Context context)
        {
            _context = context; 
        }

        public void Setup()
        {
            if (MicrophoneTester.Test(_context))
            {
                Console.WriteLine("Detected microphone!");
            }

        }

        public void HandleRecognizedText(IList<string> recognizedWords)
        {
            var command = recognizedWords.Aggregate((i, j) => i + ' ' + j);
                Console.WriteLine(command);
                SendSpeechCommand(command);
        }

        private static void SendSpeechCommand(string command)
        {
            var commandRequest = new CommandRequest();
            string parameters = null; 

            //temperature commands
            if (command.Contains("heat"))
            {
                if (command.Contains("on"))
                {
                    parameters = "heat-on";
                }
                else if (command.Contains("off"))
                {
                    parameters = "heat-off";
                }
            }
            //music commands
            else if (command.Contains("music"))
            {
                if (command.Contains("on"))
                {
                    parameters = "music-on";
                }
                else if (command.Contains("off"))
                {
                    parameters = "music-off";
                }
            }
            //light commands
            else if (command.Contains("light"))
            {
                if (command.Contains("on"))
                {
                    parameters = "light-on";
                }
                else if (command.Contains("off"))
                {
                    parameters = "light-off";
                }
            }
            if (parameters != null)
                commandRequest.Send(parameters);
        }

        private string ProcessSpeechCommand(string inputCommand)
        {
            var outputCommand = inputCommand;

            //ToDo: process cmd here
            return outputCommand; 
        }
    }
}
