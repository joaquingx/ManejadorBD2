#include "operations.h"
#include "table.h"
#include "lexical.h"
#include "archivos.h"

operations::operations(string tName)
{
  t = new table(tName);
};



void operations::printStructure()
{
  printf("\n\n");
  printf("Estructura de %s\n", t->name.c_str());
  printf("---------------------------\n");
  printf("---------------------------\n");
  printf("| %-10s | %-10s |\n", "Tipo" , "Nombre");
  printf("---------------------------\n");
  for(int i = 0 ; i < t->myFields.size() ; ++i)
    {
      printf("| %10s | %10s |\n", t->myFields[i].first.c_str() , t->myFields[i].second.c_str());
      printf("---------------------------\n");
    }
  printf("\n\n");
}


void operations::getDataInTable(vString conditions)
{
  lexicalAnalizer * analizer = new lexicalAnalizer();
  FILE * pFile;
  string nName = t->name;
  nName += ".table";
  char buffer[100];
  pFile = fopen(nName.c_str() , "r");
  bool isData = 0;
  printf("\n\n");
  printf("Resultado de Consulta\n", t->name.c_str());
  for(int i = 0 ; i < t->myFields.size() ; ++i)
    {
      printf("-------------");
    }
  printf("\n");
  for(int i = 0 ; i < t->myFields.size() ; ++i)
    {
      printf("-------------");
    }
  printf("\n");
  for(int i = 0 ; i < t->myFields.size() ; ++i)
    {
      printf("| %-10s ",t->myFields[i].second.c_str());
    }
  printf("|\n");
  for(int i = 0 ; i < t->myFields.size() ; ++i)
    {
      printf("-------------");
    }
  printf("\n");
  if(pFile == NULL) perror("La tabla no existe!\n");
  else
    {
      while ( ! feof (pFile) )
        {
          memset(buffer,0,sizeof buffer);
          if ( fgets (buffer , 100 , pFile) == NULL ) break;
          if(buffer[0] == '-') // Fin de la estructura
            {
              isData=1;
              continue;
            }
          if(isData)
            {
              string str(buffer);
              vString lexemes = analizer->giveMeLexemes(str);
              for(int i = 0 ;i < lexemes.size() ; ++i)
                {
                  printf("| %10s ", lexemes[i].c_str());
                }
              printf("|\n");
            }
        }
      fclose (pFile);
    }
  printf("\n\n");
}

void operations::selectResult(vString lexemes)
{
  int iFrom=-1,iWhere=-1;
  for(int i = 0;i < lexemes.size() ; ++i)
    {
      if(lexemes[i] == "FROM")
        iFrom = i;
      if(lexemes[i] == "WHERE")
        iWhere = i;
    }
  vString tNames;
  tNames.resize(iWhere-iFrom-1);
  vector< table * > toMemory;
  vString conditions;
  toMemory.resize(iWhere-iFrom-1);
  for(int i = iFrom + 1, j = 0 ; i < iWhere; ++i, ++j )
    {
      tNames[j] = lexemes[i];
    }

  for(int i = iWhere; i < lexemes.size() ; ++i)
    conditions.push_back(lexemes[i]);
  for(int i = 0 ;i < tNames.size() ; ++i)
    {
      toMemory[i] = new table(tNames[i]);
    }
  for(int i = 0 ; i < tNames.size() ; ++i)
    getDataInTable(conditions);
}


bool operations::insertInTable(vString myLexemes)
{
  auxiliar * auxTool = new auxiliar();
  file * manager = new file();
  mapSR verificador = auxTool->giveVerify();
  string nuevo,act;
  if(myLexemes.size() - 2 != t->myFields.size())
    return 0;
  for(int i = 0 ;i < myLexemes.size() - 2 ; ++i)
    {
      act = myLexemes[i+2];
      // cout << act << t->myFields[i].first << "\n";
      if(!regex_match(act,verificador[t->myFields[i].first]))
        {
          return 0;
        }
      nuevo += "\"";
      nuevo += act;
      nuevo += "\"";
      nuevo += " ";
    }
  nuevo += "\n";
  manager->appendInTable(myLexemes[1],nuevo);
  return 1;
}

