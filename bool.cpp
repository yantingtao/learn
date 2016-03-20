#include <iostream>
using namespace std;
class A
{
public:
      A(int _len)
      {  
      	 int i;
      	 len = _len;
      	 data = new int[len];
         for (i = 0; i < len ; i++)
         {
         	 cin >> data[i];
         }
      }
      int operator [](int index)
      {
      	  return data[index];
      }
      bool operator == (A a)
      {
      	bool ret = true;
      	if (this->len != a.len)
      	{
      		 ret = false;
      	}
      	 int i;
         for (i = 0; i < a.len;i++)
         {
         	 if (a[i] != (*this)[i])
         	 {
         	 	 ret = false;
         	 	 break;
         	 }
         }
        return ret;
      }
  private:
  	int *data;
  	int len;
};
int main(int argc, char const *argv[])
{
	A a1(5);
	A a2(5);
	if (a1 == a2)
	{
        cout << "a1 = a2"<<endl;
	}
	else
	{
		cout << "a1!= a2"<<endl;
	}
	return 0;
}
