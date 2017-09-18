#include <bits/stdc++.h>
#include "archivos.cc"
using namespace std;

int main()
{
  string sentence;
  cout << "Welcome to the lulDatabase\n";
  while(1){
    cout << ">> ";
    getline(cin,sentence);
    getOption(sentence);
  }
  return 0;
}
