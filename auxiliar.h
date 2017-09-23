#ifndef AUXILIAR_H
#define AUXILIAR_H
#include <bits/stdc++.h>
using namespace std;

// Alias basicos.
typedef vector< pair<string, string > > vFields;
typedef vector< vector< pair<string, string> >  > vectorVFields;
typedef map<string , int > mapSI;
typedef map<string , regex> mapSR;
typedef vector<string> vString;

#include <regex>
/* #include "lexical.h" */
#include "table.h"
/* #include "operations.h" */

/* class lexicalAnalizer; */
/* lexicalAnalizer * analizer; */

class auxiliar{
  public:
  auxiliar();
  mapSI giveDispatcher();
  mapSR giveVerify();
  void printLexemes(vString myLexemes);
  void getOption(string sentence);
};

#endif
