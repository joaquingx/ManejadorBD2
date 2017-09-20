#include <bits/stdc++.h>
#include "lexical.cc"
#include <regex>
using namespace std;
map<string , int > dispatcher;
map<string , regex > verificar;

void setDispatcher()
{
  dispatcher["CREATE"] = 1;
  dispatcher["DELETE"] = 2;
  dispatcher["SELECT"] = 3;
  dispatcher["UPDATE"] = 4;
  dispatcher["STATUS"] = 5;
  dispatcher["INSERT"] = 6;
  dispatcher["CHECK"] = 7;
}

void setVerify()
{
  verificar["int"] = regex("[[:digit:]]+");
  verificar["date"] = regex("[[:digit:]]{2}/[[:digit:]]{2}/[[:digit:]]{4}");
  verificar["varchar"] = regex("([[:alnum:]]| )+");
}


// SELECT TIKI,TAKA,TEKE FROM FASDDSFASA WHERE 1=1;



void  writeTable(vector<string> lexemes)
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

void addInTable(string name , string toInsert)
{
  FILE * pFile;
  string nName = name;
  nName += ".table";
  pFile = fopen(nName.c_str(), "a");
  if(pFile != NULL)
    {
      fputs(toInsert.c_str(),pFile);
      fclose(pFile);
    }
}

void deleteTable(string toDelete)
{
  toDelete += ".table";
  if(remove(toDelete.c_str()) != 0)
    cout << "La tabla no existe!\n";
  else
    cout << "La tabla fue borrada\n";
}


void printStructure(string tabla, vector< pair<string, string > > S)
{
  printf("\n\n");
  printf("Estructura de %s\n", tabla.c_str());
  printf("---------------------------\n");
  printf("---------------------------\n");
  printf("| %-10s | %-10s |\n", "Tipo" , "Nombre");
  printf("---------------------------\n");
  for(int i = 0 ; i < S.size() ; ++i)
    {
      printf("| %10s | %10s |\n", S[i].first.c_str() , S[i].second.c_str());
      printf("---------------------------\n");
    }
  printf("\n\n");
}

vector< pair<string , string > >  checkTable(string tabla)
{
  vector< pair < string , string > > S;
  FILE * pFile;
  string nName = tabla;
  nName += ".table";
  // cout << nName << "<--\n";
  char buffer[100];
  pFile = fopen(nName.c_str() , "r");
  if(pFile == NULL) perror("La tabla no existe!\n");
  else
    {
      while ( ! feof (pFile) )
        {
          memset(buffer,0,sizeof buffer);
          if ( fgets (buffer , 100 , pFile) == NULL ) break;
          if(buffer[0] == '-') // Fin de la estructura
            break;
          string first,second;
          int i = 0;
          for(; i < 100 and buffer[i] != ' ' ; ++i)
            {
              first += buffer[i];
            }
          ++i;
          for(; i < 100 and buffer[i] != 0 and buffer[i] != '\n' ; ++i)
            {
              second += buffer[i];
            }
          S.push_back({first,second});
        }
      fclose (pFile);
    }
  return S;
}


void getDataInTable(vector<string> conditions, vector< pair< string , string > > fields, string table )
{
  FILE * pFile;
  string nName = table;
  nName += ".table";
  char buffer[100];
  pFile = fopen(nName.c_str() , "r");
  bool isData = 0;
  printf("\n\n");
  printf("Resultado de Consulta\n", table.c_str());
  for(int i = 0 ; i < fields.size() ; ++i)
    {
      printf("-------------");
    }
  printf("\n");
  for(int i = 0 ; i < fields.size() ; ++i)
    {
      printf("-------------");
    }
  printf("\n");
  for(int i = 0 ; i < fields.size() ; ++i)
    {
      printf("| %-10s ",fields[i].second.c_str());
    }
  printf("|\n");
  for(int i = 0 ; i < fields.size() ; ++i)
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
              vector<string> lexemes = giveMeLexemes(str);
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

void selectResult(vector<string> lexemes)
{
  int iFrom=-1,iWhere=-1;
  for(int i = 0;i < lexemes.size() ; ++i)
    {
      if(lexemes[i] == "FROM")
        iFrom = i;
      if(lexemes[i] == "WHERE")
        iWhere = i;
    }
  vector<string> tNames;
  tNames.resize(iWhere-iFrom-1);
  vector< vector< pair<string, string> >  > toMemory;
  vector< string > conditions;
  toMemory.resize(iWhere-iFrom-1);
  for(int i = iFrom + 1, j = 0 ; i < iWhere; ++i, ++j )
    {
      tNames[j] = lexemes[i];
      // cout << tNames[j] << "\n";
    }

  for(int i = iWhere; i < lexemes.size() ; ++i)
    conditions.push_back(lexemes[i]);
  for(int i = 0 ;i < tNames.size() ; ++i)
    {
      toMemory[i] = checkTable(tNames[i]);
    }
  for(int i = 0 ; i < tNames.size() ; ++i)
    getDataInTable(conditions,toMemory[i],tNames[i]);

}

bool insertInTable(vector<string> myLexemes , vector< pair < string ,string > > types)
{
  string nuevo,act;
  if(myLexemes.size() - 2 != types.size())
    return 0;
  for(int i = 0 ;i < myLexemes.size() - 2 ; ++i)
    {
      act = myLexemes[i+2];
      // cout << act << types[i].first << "\n";
      if(!regex_match(act,verificar[types[i].first]))
        {
          return 0;
        }
      nuevo += "\"";
      nuevo += act;
      nuevo += "\"";
      nuevo += " ";
    }
  nuevo += "\n";
  addInTable(myLexemes[1],nuevo);
  return 1;
}


void printLexemes(vector<string> myLexemes)
{
  for(int i =0 ; i < myLexemes.size() ; ++i)
    cout << myLexemes[i] << "\n";
}

void getOption(string sentence)
{
  setDispatcher();
  setVerify();
  vector<string> myLexemes = giveMeLexemes(sentence);
  // printLexemes(myLexemes);
  switch(dispatcher[myLexemes[0]])
    {
    case 1: // CREATE
      writeTable(myLexemes);
      break;
    case 2: // DELETE
      if(myLexemes[1] == "TABLE")
        deleteTable(myLexemes[2]);
      break;
    case 3: // SELECT
      {
        selectResult(myLexemes);
        break;
      }
    case 4:
      break;
    case 5://STATUS
      system("ls *.table");
      break;
    case 6 ://INSERT
      {
        vector< pair < string , string > > types = checkTable(myLexemes[1]);
        if(insertInTable(myLexemes,types))
          cout << "Se inserto correctamente!\n";
        else
          cout << "Existe un error en la insercion\n";
        break;
      }
    case 7 : // CHECK
      {
        vector< pair<string, string > > tipos = checkTable(myLexemes[1]);
        printStructure(myLexemes[1],tipos);
        break;
      }
    default:
      cout << "Sentencia incorrecta, escriba denuevo!\n";
    }
}
