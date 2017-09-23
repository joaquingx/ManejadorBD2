#include <bits/stdc++.h>
#include "auxiliar.h"
using namespace std;

int main()
{
  auxiliar * auxTools = new auxiliar();
  string sentence;
  cout << "Welcome to the NeeChan-Database\n";
  while(1){
    cout << ">> ";
    getline(cin,sentence);
    auxTools->getOption(sentence);
  }
  return 0;
}
