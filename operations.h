#ifndef OPERATIONS_H
#define OPERATIONS_H

#include "auxiliar.h"
#include "table.h"

class operations{
 public:
  table * t;
  operations(string tName);
  void printStructure();
  void getDataInTable(vString conditions);
  void selectResult(vString qLexemes);
  bool insertInTable(vString qLexemes);
};

#endif
