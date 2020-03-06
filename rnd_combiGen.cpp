#include <iostream>
#include <vector>

using namespace std;

void combiGen(int set, int at, int r, int n, vector<int>& subsets){
  if (r == 0)
   subsets.push_back(set); 
  else {
    for (int i = at; i < n; i++){
      set = set | (1<< i);
      combiGen(set, i+1, r-1, n , subsets);
      set = set & ~(1<<i);
    }
  }
}

void combiGen(int r ,int n){
  vector<int> subsets;
  for (int i = 1; i<= n; i++)
    combiGen(0, 0, i, n, subsets);

  for(auto elem: subsets){
    cout << elem << " " ;
    for (int i  = n-1; i >= 0 ; i--) {
       bool bit = (elem >> i) & 1 ;
       cout << bit << " ";
    }
    cout << endl;
  }
}

int main() {
   // r is no of 1 bits , n is for total number of bits
   int r, n;
   cin >> r >> n;
   combiGen(r, n);
   return(0);
}
