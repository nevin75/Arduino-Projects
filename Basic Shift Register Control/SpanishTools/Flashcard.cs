using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SpanishTools
{
    class Flashcard
    {

        public string SpanishWord { get; set; } = "Hola";
        public string EnglishWord { get; set; } = "Hello";
        public bool isVerb { get; set; } = false;
        public bool isNoun { get; set; } = false;
        public bool isPhrase { get; set; } = false;
        public bool isAdjective { get; set; } = false;
        public bool needsFixing { get; set; } = false;

        private int numberOfWords = 0;


        public int timesViewed { get; set; } = 0;
        public int timesCorrect { get; set; } = 0;
        public int timesWrong { get; set; } = 0;
        public int ID = 0;

        public Flashcard (string spanishWord, string englishWord)
        {
            SpanishWord = spanishWord;
            EnglishWord = englishWord;
            ID = numberOfWords;
            numberOfWords++;
        }
        public void TagWord(string identifier)
        {
            if (identifier == "noun")
            {
                isNoun = true;
            }
            if (identifier == "verb")
            {
                isVerb = true;
            }
            if (identifier == "adjective")
            {
                isAdjective = true;
            }
            if (identifier == "phrase")
            {
                isPhrase = true;
            }
            if (identifier == "error")
            {
                needsFixing = true;
            }
            else return;
        }
    }
}
