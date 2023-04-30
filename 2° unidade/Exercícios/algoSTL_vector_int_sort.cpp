#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
  vector<float> V;

  V.push_back(-4);
  V.push_back(4);
  V.push_back(-9);
  V.push_back(-12);
  V.push_back(40);

  cout << "IMPRIMINDO..." << endl;
  for (int i=0; i<V.size(); i++)
    cout << V[i] << endl;

  sort (V.begin(), V.end());
  cout << "IMPRIMINDO EM ORDEM..." << endl;
  for (int i=0; i<V.size(); i++)
    cout << V[i] << endl;

  return 0;
}
