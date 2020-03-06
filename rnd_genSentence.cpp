#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <string>
#include <algorithm>
using namespace std;

struct LNode{
  int unit;
  int uw; // current unit weight
  int tw; // remainig weight
};

class GenSentence{

public:

GenSentence(){
}

GenSentence(const GenSentence&) = default;

void backTrack(int curIdx) {

   if (curIdx == subStrLen.size())
     return;

   auto& prev = qtyList.back(); // getting last entry from list

   auto  cUnit = subStrLen[curIdx];  // setting current unit parameters
   
   LNode cN;
   uQty[cUnit]++;
   if (prev.unit != cUnit) {// skip if unit already exists in list
     cN = {cUnit, cUnit*uQty[cUnit], 0};
     cN.tw = cN.uw + prev.tw;
   } 
   else {
     prev.uw = prev.uw + cUnit;
     prev.tw = prev.tw + cUnit;
     cN = prev;
   }

   if (uQty[cUnit] <= qty[cUnit]) {
     if(cN.tw == inpLen) {

       vector<int> cResult; 
       for (auto& elem : qtyList)
         for (int i = 0; i< uQty[elem.unit]; i++)
            cResult.push_back(elem.unit);
       if (cN.unit != qtyList.back().unit)
         cResult.push_back(cN.unit);
       result.push_back(cResult);
       ++resIdx;
       curIdx++;
     } else if (cN.tw < inpLen) {

       if (cN.unit != prev.unit)
         qtyList.push_back(cN);
       curIdx++;
     } else {  // greater than case - bound specifications

       if (qtyList.size() == 1) // if list contains only one,  return
         return;
       else if (uQty[prev.unit] == qty[prev.unit]) { // if curent unit still have more units

         qtyList.pop_back();
         for (int tUnit = prev.unit; tUnit <= cN.unit; ++tUnit)
           uQty[tUnit] = 0;
         curIdx= prev.unit; //using prev.unit is index
       } else if (uQty[prev.unit] != qty[prev.unit] && uQty[cN.unit] > 0) {

         curIdx = prev.unit - 1; //extracing pos using prev.unit
         for (int tUnit = prev.unit + 1; tUnit <= cN.unit; ++tUnit) 
           uQty[tUnit] = 0;
       }
       else {

         curIdx++;
         for (int tUnit = prev.unit; tUnit <= cN.unit; ++tUnit)
           uQty[tUnit] = 0;
         qtyList.pop_back();
       }
     }
     backTrack(curIdx);
   } else {

     if (prev.unit == cUnit) {// if max units reached and in list
       qtyList.pop_back();
       curIdx++;
       backTrack(curIdx);
     }
   }
   return;
}

void genSentences(string& input){
 
   if (input.empty()) {
     cout << "Input is empty , returning -1 " << endl;
     exit(-1);
   }
   inp = std::move(input);
     
   inpLen = inp.length();
   
   //possible sustring lengths
   
   for (size_t i = 1; i<= inp.length(); i++)
     subStrLen.push_back(i);

   // map from each entry from vector of  length of possible substring to no of units
   // for ex :if input string length is 7, possible substring lengths are 1, 2 , 3, 4, 5, 6, 7
   // substr length 1 can be used from 1 to 7 units
   //    ..     ..  2  ..    from 1 t0 3 units and so on 

   for (auto elem : subStrLen) 
      qty[elem] = inpLen/elem; 

   for (auto elem : subStrLen) 
      uQty[elem] = 0; 

   int curIdx = 1;
   resIdx = 0;

   for (auto unit : subStrLen) {
      
      qtyList.push_back({unit, unit, unit});
      uQty[unit] = 1;

      while (1) {  // completing all combinations with existing unit
         if (uQty[unit] <= qty[unit]) {
           auto &cR = qtyList.back();
           cR.uw = uQty[unit];
           cR.tw = uQty[unit] * unit;
           if (cR.tw != inpLen)
             backTrack(curIdx);
           else {
             //result.push_back(new vector<int>);
             vector<int> cResult; 
             for (int i = 0; i < uQty[unit] ; i++)
               cResult.push_back(cR.unit);
             result.push_back(cResult);
             ++resIdx;
               //cout << cR.unit << " "; 
            // cout << endl;
           }
             
           uQty[unit]++;
           for (int j = unit +1 ; j <= inpLen; j++)
             uQty[j] = 0;
         }
         else
           break;
      }
      curIdx++;
      if (curIdx > inpLen/2)
        break;
      qtyList.clear();

     

   } // generate the result with substr length combinations

}
   // generate permuatation for each entry from result vector
void genResult() {
   for (auto& cvec : result) { // child vector from result
     bool nprm = true; 
     while (nprm) {
       nprm = next_permutation(cvec.begin(), cvec.end());
       size_t pos = 0;
       #ifdef DEBUG
       for (auto& elem : cvec) {  // element from child vector 
         cout << elem << " ";
       } 
       #endif
       for (auto& elem : cvec) {  // element from child vector 
         cout << inp.substr(pos, elem) << " ";
         pos += elem;
       }
       cout << endl;
     }
 
  }
}

private: 
   string inp;
   size_t inpLen;
   size_t resIdx;
   vector<int> subStrLen;
   map<int, int> qty;
   map<int, int> uQty; // used quantity map
  
   vector<vector<int>> result;
   list<LNode> qtyList;

};

int main() {


   string inp;
   cin >> inp;

   // call genSentences
   GenSentence genSenInst;
   genSenInst.genSentences(inp);
   genSenInst.genResult();

   return (0);

}
