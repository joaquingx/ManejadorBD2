#include "archivos.h"


file::file()
{};

void file::createTable(vString lexemes)
{
  FILE * pFile;
  string nName = lexemes[1], data;
  nName += ".table";
  pFile = fopen (nName.c_str() , "w");
  for(int i = 0 ; i < stoi(lexemes[2])*2 ; i+=2 )
    {
      data += lexemes[3+i];
      data += " ";
      data += lexemes[4+i];
      data += "\n";
    }
  data += "-----\n";
  if(pFile != NULL)
    {
      fputs(data.c_str(),pFile);
      fclose(pFile);
    }
}

void file::replaceInTable(string name , string toInsert)
{
  FILE * pFile;
  string nName = name;
  pFile = fopen(nName.c_str(), "w");
  if(pFile != NULL)
    {
      fputs(toInsert.c_str(),pFile);
      fclose(pFile);
    }
}



void file::appendInTable(string name , string toInsert)
{
  FILE * pFile;
  string nName = name;
  nName += ".table";
  // cout << nName << "<--\n";
  pFile = fopen(nName.c_str(), "a");
  if(pFile != NULL)
    {
      fputs(toInsert.c_str(),pFile);
      fclose(pFile);
    }
}

void file::deleteTable(string toDelete)
{
  toDelete += ".table";
  if(remove(toDelete.c_str()) != 0)
    cout << "La tabla no existe!\n";
  else
    cout << "La tabla fue borrada\n";
}




