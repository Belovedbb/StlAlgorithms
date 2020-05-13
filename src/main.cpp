#include <iostream>
#include <algorithm>
#include "arraylist.h"

using a_list::arraylist;
using namespace std;

int main(){
   //arraylist<int> a {2, 6,8,5,3,7,2,8};
   /* for(int i = 0; i < a.size(); i++){
      cout<<a.at(i)<<endl;
   }*/
   /*cout<<a.size()<<" "<<a.capacity()<<endl;
   a.clear();
   cout<<a.size()<<endl;
   a.push_back(5);
   cout<<a.size()<<" "<<a.at(0)<<endl;
   cout<<a.empty()<<endl;*/
   /*for(auto iter = a.begin(); iter != a.end(); ++iter){
      cout<<*iter<<endl;
   }*/
   
   /*arraylist<int>::iterator it = find_if (a.begin(), a.end(), [](int aa) -> bool{
      return aa%2 != 0;
   });
   cout << "The first odd value is " << *it << '\n';

   arraylist<int>::const_iterator ci = a.cbegin();
   ++ci;
   ++ci;
   a.insert(ci, 700);
   for(auto iter = a.begin(); iter != a.end(); ++iter){
      cout<<*iter<<endl;
   }*/

   /*arraylist<int> aa {2, 6,8,5,3,7,2,8};
   bool s = a <= aa;
   cout<<s;
   */

}
