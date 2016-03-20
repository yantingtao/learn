#include <iostream>
//#include <vector>
#include "mystring.h"
using namespace std;

int main(int argc, char const *argv[])
{    
	char buf[] = "fadsefwcdsafkm";
   strbuf s1;
   s1.push(buf);
 //  cout<<mystrlen(buf)<<endl;
  char bdf[20] = "dasdad";
   s1.assign(bdf);
	char* a = s1; 
  cout <<a<<endl;
  cout<<bdf<<endl;

}
