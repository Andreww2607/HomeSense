using System;
using System.Collections.Generic;
using Android.Content;

namespace HomeSense.SpeechToText
{
    public class Recognizer
    {
        private bool _enabled;
        private readonly Context _context;

        public Recognizer(Context context)
        {
            _context = context; 
        }

        public void Setup()
        {
            if (MicrophoneTester.Test(_context))
            {
                _enabled = true;
                Console.WriteLine("Detected microphone!");
            }

        }

        public void HandleRecognizedText(IList<string> recognizedWords)
        {
            foreach (var recognizedWord in recognizedWords)
            {
                Console.WriteLine(recognizedWord);
            }
        }

        private void ProcessSpeechCommand(string command)
        {
        }
    }
}
