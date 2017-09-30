#include <bits/stdc++.h>

using namespace std;

int main()
{
  int n ; cin >> n;
  int m ; cin >> m;
  for(int i= 0 ; i <n ; ++i )
    {
      for(int j = 0 ; j < m ; ++j)
        {
          cout << rand() % 10 << " ";
        }
      cout << "\n";
    }
}
