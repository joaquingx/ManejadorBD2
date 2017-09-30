#include "operations.h"
#include "table.h"
#include "lexical.h"
#include "archivos.h"
#define MAXN 200

operations::operations(string tName)
{
  t = new table(tName);
  // map<string,bool(operations::*)(string)> mapping;
  mapping["="] = &operations::igual;
  mapping[">"] = &operations::mayor;
  mapping["<"] = &operations::menor;

};

bool operations::igual(string a, string b)
{
  return a == b;
}

bool operations::mayor(string a, string b)
{
  int aa = stoi(a);
  int bb = stoi(b);
  return aa > bb;
}

bool operations::menor(string a, string b)
{
  int aa = stoi(a);
  int bb = stoi(b);
  return aa < bb;
}


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


void operations::getDataInTable(vString conditions, bool noCondition)
{
  lexicalAnalizer * analizer = new lexicalAnalizer();
  FILE * pFile;
  string nName = t->name;
  char buffer[MAXN];
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
  // for(int i = 0 ;i < conditions.size();++i)
  //   cout << conditions[i] << " ";
  // cout << "\n";
  if(pFile == NULL) perror("La tabla no existe!\n");
  else
    {
      int idx = searchInFields(conditions,t);
      while ( ! feof (pFile) )
        {
          memset(buffer,0,sizeof buffer);
          if ( fgets (buffer , MAXN , pFile) == NULL ) break;
          if(buffer[0] == '-') // Fin de la estructura
            {
              isData=1;
              continue;
            }
          if(isData and buffer[0] == '\"')
            {
              string str(buffer);
              vString lexemes = analizer->giveMeLexemes(str);
              // cout << lexemes[idx] << " xD";
              if(noCondition or isTrue(lexemes,conditions,idx))
                {
                  // if(why == 1) // UPDATE
                  //   {

                  //   }
                  for(int i = 0 ;i < lexemes.size()-1 ; ++i)
                    {
                      printf("| %10s ", lexemes[i].c_str());
                    }
                  printf("|\n");
                }
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
  t = new table(lexemes[3]);
  if(iWhere == -1)
    {
      getDataInTable(lexemes,1);
      return;
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
  // cout << tNames[0] << " <- tnames[0]\n";
  for(int i = iWhere+1; i < lexemes.size() ; ++i)
    conditions.push_back(lexemes[i]);
  for(int i = 0 ;i < tNames.size() ; ++i)
    {
      toMemory[i] = new table(tNames[i]);
    }
  for(int i = 0 ; i < tNames.size() ; ++i)
    {
      getDataInTable(conditions,0);
    }
}

// INSERT TABLA TAL TAL TAL TAL
bool operations::insertInTable(vString myLexemes, int extra , string tName)
{
  auxiliar * auxTool = new auxiliar();
  file * manager = new file();
  mapSR verificador = auxTool->giveVerify();
  string nuevo,act;
  if(myLexemes.size() - extra != t->myFields.size())
    return 0;
  for(int i = 0 ;i < myLexemes.size() - extra ; ++i)
    {
      act = myLexemes[i+extra];
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
  int actual = nuevo.size();
  for(int i  = 0; i < 100-actual ; ++i )
    nuevo += 36;
  nuevo += "\n";
  manager->appendInTable(tName,nuevo);
  return 1;
}

// bool giveMeConditions(vString conditions)
// {
//   for(int i = 0 ;i < t->myFields.size() ; ++i)
//     {
//       t->myFields
//         }
// }

int operations::insertInBlock(vString myLexemes)
{
  lexicalAnalizer * analizer = new lexicalAnalizer();
  FILE * pFile;
  char buffer[MAXN];
  pFile = fopen(myLexemes[3].c_str() , "r");
  bool isData = 0;
  // cout << "Aqui toy\n";
  if(pFile == NULL) perror("La tabla no existe!\n");
  else
    {
      while ( ! feof (pFile) )
        {
          memset(buffer,0,sizeof buffer);
          if ( fgets (buffer , MAXN , pFile) == NULL ) break;
          string str(buffer);
          vString lexemes = analizer->giveMeLexemes(str);
          insertInTable(lexemes,0,myLexemes[2]);
          // auxiliar * xd = new auxiliar();
          // xd->printLexemes(lexemes);
        }
      fclose (pFile);
    }
}

int operations::searchInFields(vString condition, table * tabl)
{
  int idx=-1;
  for(int i = 0 ;i < tabl->myFields.size() ; ++i)
    {
      for(int j = 0 ; j < condition.size() ; ++j)
        if(tabl->myFields[i].second == condition[j])
          {
            idx = i;
            break;
          }
    }
  return idx;
}


bool operations::isTrue(vString line, vString condition, int idx)
{
  if(idx == -1)
    return false;
  if((this->*mapping[condition[1]])(line[idx],condition[2]))
    return true;
  else
    return false;
}


//UPDATE TABLA WHERE TAL TO tal
bool operations::updateInTable(vString myLexemes)
{
  vString conditions;
  for(int i = 3 ;i < 6 ; ++i)
    conditions.push_back(myLexemes[i]);
  int idx = searchInFields(conditions,t);
  lexicalAnalizer * analizer = new lexicalAnalizer();
  FILE * pFile;
  string nName = t->name;
  char buffer[MAXN];
  pFile = fopen(nName.c_str() , "r+b");
  bool isData = 0;
  if(pFile == NULL) perror("La tabla no existe!\n");
  else
    {
      int idx = searchInFields(conditions,t);
      while ( ! feof (pFile) )
        {
          memset(buffer,0,sizeof buffer);
          if ( fgets (buffer , MAXN , pFile) == NULL ) break;
          if(buffer[0] == '-') // Fin de la estructura
            {
              isData=1;
              continue;
            }
          if(isData and buffer[0] == '\"')
            {
              // cout << "cnt\n";
              string str(buffer);
              vString lexemes = analizer->giveMeLexemes(str);
              if(isTrue(lexemes,conditions,idx))
                {
                  // cout << lexemes[idx] << "\n";
                  // cout << myLexemes[7] << "\n";
                  lexemes[idx] = myLexemes[7];
                  int positionInFile = ftell(pFile);
                  string toWrite="";
                  fseek(pFile,positionInFile-101,SEEK_SET);
                  for(int i = 0 ;i < lexemes.size()-1 ; ++i)
                    {
                      string act = lexemes[i];
                      toWrite += "\"";
                      toWrite += act;
                      toWrite += "\"";
                      toWrite += " ";
                    }
                  int actual = toWrite.size();
                  for(int i = 0 ;i < 99 -actual; ++i)
                    toWrite+=36;
                  fputs(toWrite.c_str(),pFile);
                }
            }
        }
      fclose (pFile);
    }

}


//DELETE TABLA WHERE TAL
bool operations::deleteInTable(vString myLexemes)
{
  vString conditions;
  for(int i = 3 ;i < 6 ; ++i)
    conditions.push_back(myLexemes[i]);
  int idx = searchInFields(conditions,t);
  lexicalAnalizer * analizer = new lexicalAnalizer();
  file * manager = new file();
  FILE * pFile;
  string nName = t->name;
  char buffer[MAXN];
  pFile = fopen(nName.c_str() , "r");
  bool isData = 0;
  string blessup="";
  if(pFile == NULL) perror("La tabla no existe!\n");
  else
    {
      int idx = searchInFields(conditions,t);
      while ( ! feof (pFile) )
        {
          memset(buffer,0,sizeof buffer);
          if ( fgets (buffer , MAXN , pFile) == NULL ) break;
          if(buffer[0] == '-') // Fin de la estructura
            {
              isData=1;
              string gg(buffer);
              blessup += gg;
              continue;
            }
          if(isData and buffer[0] == '\"')
            {
              // cout << "cnt\n";
              string str(buffer);
              vString lexemes = analizer->giveMeLexemes(str);
              if(!isTrue(lexemes,conditions,idx))
                {
                  blessup+=str;
                  // cout << lexemes[idx] << "\n";
                  // cout << myLexemes[7] << "\n";
                  // lexemes[idx] = myLexemes[7];
                  // int positionInFile = ftell(pFile);
                  // string toWrite="";
                  // fseek(pFile,positionInFile-101,SEEK_SET);
                  // for(int i = 0 ;i < lexemes.size()-1 ; ++i)
                  //   {
                  //     string act = lexemes[i];
                  //     toWrite += "\"";
                  //     toWrite += act;
                  //     toWrite += "\"";
                  //     toWrite += " ";
                  //   }
                  // int actual = toWrite.size();
                  // for(int i = 0 ;i < 99 -actual; ++i)
                  //   toWrite+=36;
                  // fputs(toWrite.c_str(),pFile);
                }
            }
          else
            {
              string gg(buffer);
              blessup += gg;
            }
        }
      fclose (pFile);
    }
  manager->replaceInTable(nName,blessup);
}
