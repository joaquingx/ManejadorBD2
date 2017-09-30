#include "auxiliar.h"
#include "archivos.h"
#include "lexical.h"
#include "operations.h"


auxiliar::auxiliar()
{}

mapSI auxiliar::giveDispatcher()
{
  mapSI dispatcher;
  dispatcher["CREATE"] = 1;
  dispatcher["DELETE"] = 2;
  dispatcher["SELECT"] = 3;
  dispatcher["UPDATE"] = 4;
  dispatcher["STATUS"] = 5;
  dispatcher["INSERT"] = 6;
  dispatcher["CHECK"] = 7;
  return dispatcher;
}


mapSR auxiliar::giveVerify()
{
  mapSR verificar;
  verificar["int"] = regex("[[:digit:]]+");
  verificar["date"] = regex("[[:digit:]]{2}/[[:digit:]]{2}/[[:digit:]]{4}");
  verificar["varchar"] = regex("([[:alnum:]]| )+");
  return verificar;
}


void auxiliar::printLexemes(vString myLexemes)
{
  for(int i =0 ; i < myLexemes.size() ; ++i)
    cout << myLexemes[i] << " ";
  cout << "\n";
}

void auxiliar::getOption(string sentence)
{
  lexicalAnalizer * analizer = new lexicalAnalizer();
  file * manager = new file();
  mapSI dispatcher = giveDispatcher();
  vString myLexemes = analizer->giveMeLexemes(sentence);
  operations * operador;
  // printLexemes(myLexemes);
  switch(dispatcher[myLexemes[0]])
    {
    case 1: // CREATE
      manager->createTable(myLexemes);
      break;
    case 2: // DELETE
      {
        if(myLexemes[1] == "TABLE")
          manager->deleteTable(myLexemes[2]);
        else
          {
            operador = new operations(myLexemes[1]);//tamal
            operador->deleteInTable(myLexemes);
          }
        break;
      }
    case 3: // SELECT
      {
        operador = new operations(myLexemes[1]);//tamal
        operador->selectResult(myLexemes);
        break;
      }
    case 4:
      {
        operador = new operations(myLexemes[1]);
        operador->updateInTable(myLexemes);
        break;
      }
    case 5://STATUS
      system("ls *.table");
      break;
    case 6 ://INSERT
      {
        if(myLexemes[1] == "BLOCK")
          {
            operador = new operations(myLexemes[2]);
            operador->insertInBlock(myLexemes);
          }
        else{
          operador = new operations(myLexemes[1]);
          if( operador->insertInTable(myLexemes,2,myLexemes[1]) )
            cout << "Se inserto correctamente!\n";
          else
            cout << "Existe un error en la insercion\n";
        }
        break;
      }
    case 7 : // CHECK
      {
        operador = new operations(myLexemes[1]);
        operador->printStructure();
        break;
      }
    default:
      cout << "Sentencia incorrecta, escriba denuevo!\n";
    }
}
