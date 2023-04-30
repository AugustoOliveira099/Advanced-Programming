#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
  double A[6] = { 1.2, 1.3, 1.4, 1.5, 1.6, 1.7 };

  // Reverte a ordem do array
  reverse(A, A+6); // Usando ponteiros como iterators

  for (int i = 0; i < 6; ++i)
    cout << "A[" << i << "] = " << A[i] << endl;
  return 0;
}
