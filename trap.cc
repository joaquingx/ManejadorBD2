#include <bits/stdc++.h>
using namespace std;

int aleat()
{
  return rand()%999 + 1000;
}

int main()
{
  string a,b;
  int n ,m; cin >> n;
  for(int i = 0; i < n ; ++i)
    {
      cin >> a >> b;
      cout << a << " " << b << "\n";
    }
  cout << "-----\n";
  cin >> m ;
  for(int i = 0 ; i < m ; ++i)
    {
      int cnt = 0;
      cout << "\"" << i+1 << "\" ";
      cnt += to_string(i+1).size() + 2;
      for(int j = 0 ; j < n-1; ++j)
        {
          cout << "\"" << aleat() << "\" ";
          cnt += 6;
        }
      for(int j = 0 ; j < 100-cnt ; ++j )
        cout << "$";
      cout << "\n";
    }
}
