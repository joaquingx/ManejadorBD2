#ifndef LEXICAL_H
#define LEXICAL_H
#include "auxiliar.h"

class lexicalAnalizer{
 public:
  lexicalAnalizer();
  bool isAString(char x);
  vString giveMeLexemes(string sentence);
};

#endif
