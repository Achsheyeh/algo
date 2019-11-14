#include <iostream>
#include <cstring> 
using namespace std;

template <typename T>
inline void kpswap(T &a, T &b){
    auto t = a;
    a = b;
    b = t;
} 

template <typename T1, typename T2, typename T3 >
void permutations(T1 *a, const T2  k , const T3 m){
   
   if (k == m) {
     for (auto l = 0; l < strlen(a); ++l)
       cout << a[l] << " ";
     cout << endl;
   }
  else { 
    for (auto i = k; i<m; i++){
      kpswap(a[k], a[i]);
      permutations(a, k + 1, m);
      kpswap(a[k], a[i]);
    }
  }
}
int main() {

  char  inp[100];
  cout << " Enter the string to generate permutations " << endl; 
  cin >> inp;
  permutations(inp, 0, strlen(inp));
  return(0);
}
