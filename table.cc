#include "table.h"

table::table(string tName)
{
  FILE * pFile;
  name = tName;
  name += ".table";
  char buffer[100];
  pFile = fopen(name.c_str() , "r");
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
          myFields.push_back({first,second});
        }
      fclose (pFile);
    }
}
