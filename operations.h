#ifndef OPERATIONS_H
#define OPERATIONS_H

#include "auxiliar.h"
#include "table.h"

class operations{
 public:
  map<string,bool(operations::*)(string,string)> mapping;
  table * t;
  operations(string tName);
  void printStructure();
  void getDataInTable(vString conditions, bool noCondition);
  void selectResult(vString qLexemes);
  bool insertInTable(vString myLexemes, int extra , string tName);
  bool igual(string a, string b);
  bool mayor(string a, string b);
  bool menor(string a, string b);
  int searchInFields(vString condition, table * tabl);
  bool isTrue(vString line, vString condition, int idx );
  bool deleteInTable(vString myLexemes);
  bool updateInTable(vString myLexemes);
  int insertInBlock(vString myLexemes);
};

#endif
