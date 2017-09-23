#include "lexical.h"


lexicalAnalizer::lexicalAnalizer()
{};
bool lexicalAnalizer::isAString(char x)
{
  if(x == 34)// es un "
    {
      return true;
    }
  return false;
}

vString lexicalAnalizer::giveMeLexemes(string sentence)
{
  bool inString = 0;
  vString res;
  sentence += " ";
  string separators=" \n";
  string actLexeme = "";
  for(int i = 0 ; i < sentence.size() ; ++i)
    {
      if(isAString(sentence[i]))
        {
          if(inString)
            {
              res.push_back(actLexeme);
              inString = 0;
              actLexeme = "";
              continue;
            }
          else
            {
              inString = 1;
            }
        }
      if(!inString)
      {
        if(separators.find(sentence[i]) == string::npos) // es valido
          {
            actLexeme += sentence[i];
          }
        else
          {
            if(actLexeme != "")
              {
                res.push_back(actLexeme);
              }
            actLexeme = "";
          }
      }
      else
        {
          if(!isAString(sentence[i]))
            actLexeme += sentence[i];
        }
    }
  return res;
}


