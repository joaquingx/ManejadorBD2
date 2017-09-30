#ifndef ARCHIVOS_H
#define ARCHIVOS_H
#include "auxiliar.h"


class file{
 public:
  file();
  void createTable(vString lexemes);
  void appendInTable(string name , string toInsert);
  void deleteTable(string toDelete);
  void replaceInTable(string name , string toInsert);
};

#endif
