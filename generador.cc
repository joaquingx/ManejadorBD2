#include <bits/stdc++.h>

using namespace std;

int main()
{
  int n ; cin >> n;
  // int m ; cin >> m;
  for(int i= 0 ; i <n ; ++i )
    {
      cout << rand() % 10 << " ";
      cout << char(rand()%10+'A') << char(rand()%10+'A') << char(rand()%10+'A') << " ";
      cout << rand()%3 << rand()%10 << "/"  << rand()%3 << rand()%10 << "/" << rand()%2+1 << rand()%10 << rand()%10<< rand()%10;
      cout << "\n";
    }
}
