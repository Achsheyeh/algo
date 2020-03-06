#include <iostream>
#include <string>
#include <algorithm>
#include <map>
#include <set>
#include <vector>

using namespace std;

class SALessOpr {

  public:

  bool operator()(const size_t& pos1 ,const size_t& pos2) const {
       return lexicographical_compare(inpRef.begin()+pos1, inpRef.end(), inpRef.begin()+pos2, inpRef.end());
  }
    
  static string inpRef;
};
string SALessOpr::inpRef = "";

int main()
{

   string inp;

   cin >> inp;
 
   SALessOpr::inpRef = inp;
   string unqInp{inp};

   sort(unqInp.begin(), unqInp.end());
   auto p = unique(unqInp.begin(), unqInp.end());
   unqInp.erase(p, unqInp.end());

   map <char, int> idxMap;
   int idx=0;
   for (auto& elem : unqInp)
     idxMap[elem] =  idx++;


   //cout << inp << "  " << unqInp << endl;
   //for (auto& elem : idxMap)
     // cout << elem.first << " " << elem.second << endl;


   map<int , set<size_t, SALessOpr>> sffxArray;

   for_each (inp.begin(), inp.end(), [&idxMap, &sffxArray](auto& elem) {    
                  static size_t pos = 0;
                  sffxArray[idxMap[elem]].insert(pos++);    
                  //cout << " char is " << elem <<  " its is idx is " << idxMap[elem] << endl;
             });

   for_each(idxMap.begin(), idxMap.end(), [&sffxArray, &inp](const pair<char , int>& p) {
             for_each(sffxArray[p.second].begin(), sffxArray[p.second].end(), [&inp](int pos) {
                      cout << inp.substr(pos) << endl; 
                      });
             });

   return(0);
}
