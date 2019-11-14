#include <iostream>
#include <algorithm>
#include <memory>
#include <fstream>
#include <cassert>
#include <queue>

using namespace std;
template <typename T> class MSList;
template <typename T> void equivalence(char *inpfile);

template <typename T>
class Node{

  static int counter;
  T data;
  unique_ptr<Node<T>> link;

  private:
    Node(T data) {
      this->data = data; 
      this->link.reset();
      cout << " object " << ++counter << "got created with data " << data << endl;
    }

  public:
     friend void equivalence<T>(char *);
     friend class MSList<T>;
     static void setCounter(int);
    ~Node(){
      this->link.reset();
      cout << "Object " << counter-- << "destructor called for " << data << endl;
    }
};

template <typename T>
class MSList {

  static int counter;
  unique_ptr<Node<T>> head;

  public:
  
  friend void equivalence<T>(char *);
  static void setCounter(int);

  MSList(){
    head.reset();
  }


  void insert(T data) {
    unique_ptr<Node<T>> temp{new Node<T>(data)};
    
    if (head)
      temp->link = std::move(head);
    head = std::move(temp);
    
     /* 
    auto wq = wp.lock();
    if(wq)
      this->link = *wq;
    *wq = *this;
    */
  }
  
  void display() {
    Node<T>* temp_head = head.get();
    
    while (temp_head){
      cout << " -> " << temp_head->data;
      temp_head = (temp_head->link).get();
    }
    cout << endl;
  }
  
  ~MSList() {
     cout << "destructor got called for List with data " << head->data << endl;
  }
};

template<typename T> int Node<T>::counter = 0;
template <typename T>
void Node<T>::setCounter(int start){
 
  counter = start;
}

template <typename T>
void equivalence(char *inpfile){

  Node<T>::setCounter(0);
  ifstream ifs(inpfile, ios::in); 
  if (!ifs) throw "Cannot open input file";

  int i, j, n;

  ifs >> n; // no of objects;
  
  //auto first = new shared_ptr<Node<T>>[n]; // remove release statment at line no 122 if heap allocation is required
  MSList<T> mylist_ptr[n]; 
//  unique_ptr<MSList<int>[]> first {new MSList<T>[n]};
  unique_ptr<MSList<int>[]> first {mylist_ptr};
  auto out = new bool[n];
  auto complete = new bool[n];

  //fill( first, first+n , nullptr);
  fill( out ,  out+n , false);
  fill( complete ,  complete+n , false);

  //for (int i = 0; i < n ; i++ )
    //first[i]= MSList<T>();
  ifs >> i >> j;

  while (ifs.good()) {
     first[i].insert(j);
     first[j].insert(i);
     ifs >> i >> j;
  }
  
  for (i = 0; i < n; i++) {
    cout << " list " << i ;
    first[i].display();
  }
  
  //process all lists
 
  Node<T>* x;
  bool popped;
  queue<Node<T>*> myQueue;
  for (i = 0; i < n; i++) {
     
     if (!out[i]) { //printing lead 
       cout << endl << i ;
       out[i] = true;
     }
     popped = false; 
     
     x = first[i].head.get(); 
     while(1) {
       while (x) { 
         if (!out[x->data]) { // displayed linked content
           cout << " , " << x->data;
           out[x->data] = true;
           myQueue.push(x);// queueing for future reference
         }
         //myQueue.push_back(x); // 
         x = x->link.get(); 
       } 
         
       if (!myQueue.empty()){
         Node<T>* temp = myQueue.front();   //fetching from queue
         myQueue.pop();
         popped = true; 
         x = first[temp->data].head.get();
         temp = nullptr;
       }
       else {
         break;
       }
     }
  }
  cout << endl;
 
  x = nullptr;
  first.release(); // release static pointer
  //delete[] first;
  delete[] out;
  delete[] complete;
};

int main(int argc, char**argv) {

   assert(argc == 2);  

   equivalence<int>(argv[1]);
   
   return(0); 
}
