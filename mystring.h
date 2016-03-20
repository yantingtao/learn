#ifndef MYSTRING_H
#define MYSTRING_H
#include <stdio.h>
/*strcat函数*/
void mystrcat(char *s1,char *s2)
{
   char *p = s1;
   char *q = s2;
   while ('\0' != *p)
   {
   		++p;
   }
   while ('\0' != *q)
   {
   	  *p = *q;
   	  p++;
   	  q++;
   }
   *p = '\0';
}

/*strcmp函数*/
 int mystrcmp(char *s1,char *s2)
 {
    char *p = s1;
    char *q = s2;
    int flag = 0;
    while (*q != '\0' || *p != '\0')
    {
    	 if (*p > *q)
    	 {   
    	 	flag = 1;
            return 1;
            break;
    	 }
    	 if (*p < *q)
    	 {
    	 	flag = 1;
    	 	return -1;
    	 	break;
    	 }
    	 p++;
    	 q++;
    } 
    if (flag == 0)
    {
    	return 0;
    }
 }
 /*strcpy函数*/
 void mystrcpy(char *s1,char *s2)
 {   
     char *p = s1;
     char *q = s2;
     while (*q != '\0')
     {
          *p = *q;
          q++;
          p++;

     }
    *p = '\0';  
 }
 /*strlen函数*/
 int mystrlen(char *s)
{
   if ('\0' == *s)
    return 0;
  else
    return mystrlen(s+1)+1;
}
class strbuf
{
  public:
    strbuf()
    {
       data = NULL;
       len = 0;
       maxlen = 0;
    }
   /*输入数据*/    
    void push(char * _data)
    {
       int i = mystrlen(_data);
      if (maxlen == 0)
      {
        if (i <= 4)
        {
           len = i;
           maxlen = i;
        }
        if (i > 4 && i <= 8)
        {
            len = i;
            maxlen = 8;
        }
        if (i > 8 && i <= 16)
        {
            len = i;
            maxlen = 16;
        }
        int j = i/16;
        if (i > 16)
        {
           len = i;
           maxlen = (j+1)*16;
        }
      }
      else
      {   
          len = i;
          maxlen+=i;
      }
        data = new char[maxlen];
        mystrcpy(data,_data);
    }
  /*append() 在字符串的末尾添加文本*/
  void  append(char *str)
  {    
        mystrcat(data,str);  
  }


  /*assign() 为字符串赋新值*/
  void assign(char *str)
  {
      mystrcpy(data,str);
  }


  /*返回一个指针，指向第一个字符*/
  char * begin()
   {   
        char *p = data;
        return p;
    }
/*at() 按给定索引值返回字符*/
 char at(int index);
 {
      if (index > len-1)
      { 
       std::cout<<"out of range";
       return 0;
      }
      else
      {
        return data[index];
      }
      
 }


 /*c_str() 将字符串以C字符数组的形式返回*/
  char* c_str()
 {   
   char *p = data;
   return p;
 }
 /*capacity() 返回重新分配空间前的字符容量 */
     int capacity()
     {
       return maxlen;
     }
 /*data()函数返回指向自己的第一个字符的指针.*/
 char* mydata()
 {   
   char *p = data;
   return p;
 }

  /*compare() 比较两个字符串 */
 int compare(char *str)
 {
    char *p = data;
    char *q = str;
    int flag = 0;
    while (*q != '\0' || *p != '\0')
    {
       if (*p > *q)
       {   
        flag = 1;
            return 1;
            break;
       }
       if (*p < *q)
       {
        flag = 1;
        return -1;
        break;
       }
       p++;
       q++;
    } 
    if (flag == 0)
    {
      return 0;
    }
 }



 /*copy()函数拷贝自己的num个字符到str中（从索引index开始）。返回值是拷贝的字符数*/
int copy(char * str,int num,int index)
{
    char *p = str;
    int i = 0;
    if (index > len)
    {
       std::cout<<"error"<<std::endl;
    }
    else
    {
          char *q = &data[index];
  
          while ((num > 0)&& (*q != '\0'))
         {
               *p = *q;
                p++;
                q++;
                num--;
                i++; 
          }
          *p = '\0';     
    }
    return i;
}

/*如果字符串为空则empty()返回真(true)，否则返回假(false).*/
bool empty()
{
    if (data == NULL)
      return true;
    return false;
}

/*end()函数返回一个迭代器，指向字符串的末尾(最后一个字符的下一个位置).*/
char * end()
{
   char *p = data;
   while (*p != '\0')
   {
      p++;
   }

   return p;
}

void erase(int start,int num)
{
    if ((start + num ) > len )
    {
        std::cout<<"error";
    }
    else
    {
         char* p = &data[start+1];
         char* q = &data[start+num+1];
         while (*q != '\0')
         {
            *p = *q;
            p++;
            q++;
         }
         char * h = &data[len-num];
         while (*h != '\0')
         {
            *h = '\0';
            h++;
         }

    }
}

/*find()返回str在字符串中第一次出现的位置（从index开始查找，长度为length）。如果没找到就返回*/
int find(char *str,int index)
{
    char *p = &data[index];
    char *q = str;
   int flag = 0;
   int indexq = 0;
    while (*p != '\0')
    {
        if (*q == '\0')
        {
           break;
        }
       if (*p != *q)
       {
         q = str;
         flag =0;
       }
       if (*p == *q)
       {
         flag = 1;
         q++;
       }
       p++;
       indexq++;
    }
    if (flag == 1)
    {
       return index+indexq-mystrlen(str);
    }
    else
    {
       return -1;
    }
}
/*find_first_of() 查找第一个与value中的某值相等的字符 */
int find_first_of(char *str,int index = 0)
{
  int flag = 0;
    int indexq = mystrlen(str);
    for (int i = index; i < len; i++)
    {
       for (int j = 0;j < indexq;j++)
       {
          if (data[i] == str[j])
          {
             flag = 1;
             return i;
             break;
          }
       }
    }
    if (flag == 0)
    {
      return -1;
    }
}

/*find_first_not_of() 查找第一个与value中的所有值都不相等的字符 */
int find_first_not_of(char *str,int index = 0)
{
    int flag = 0;
    int indexq = mystrlen(str);
    for (int i = index; i < len; i++)
    {
       flag = 0;
       for (int j = 0;j < indexq;j++)
       {
          if (data[i] == str[j])
          {  
               flag = 1; 
               continue; 
          }
       }
      if (flag == 0)
      {
          return i;
          break;  
      }
    }
    if (flag == 1)
    {
       return -1;
    }
   
}

/*find_last_of() 查找最后一个与value中的某值相等的字符*/
int find_last_of(char *str,int index = 0)
{
     int flag = 0;
    int indexq = mystrlen(str);
    for (int i = len-1; i >= index; i--)
    {
       for (int j = 0; j < indexq;j++)
       {
          if (data[i] == str[j])
          {
             flag = 1;
             return i;
             break;
          }
       }
    }
    if (flag == 0)
    {
      return -1;
    }

}

/*find_last_not_of() 查找最后一个与value中的所有值都不相等的字符 */
int find_last_not_of(char *str ,int index = 0)
{
     int flag = 0;
    int indexq = mystrlen(str);
    for (int i = len-1; i >= index; i--)
    {
       flag = 0;
       for (int j = 0;j < indexq;j++)
       {
          if (data[i] == str[j])
          {  
               flag = 1; 
               continue; 
          }
       }
      if (flag == 0)
      {
          return i;
          break;  
      }
    }
    if (flag == 1)
    {
       return -1;
    }
   
}

/*get_allocator() 返回配置器 */
class get_allocator
{
    public:
      get_allocator()
      {
         data2 = NULL;
         num = 0;
      }
      char* allocate(int _num)
      {
           num = _num;
          data2 = new char[num];
          return data2;
      }
      
    private:
      char *data2;
      int num;
};

/*insert() 插入字符*/
void insert(char *str,int index)
{
   data1 = new char[len];
   mystrcpy(data1,data);
   len = len + mystrlen(str);
   delete data;
   data = NULL;
   data = new char[len];
   int i;
   for (i = 0; i <= index ; i++)
   {
      data[i] = data1[i];
   }
   mystrcat(data,str);
   for (i =index+1; i < mystrlen(data1);i++)
   {
      data[i+mystrlen(str)] = data1[i];
   }
   data[len] = '\0';
}

/*length() 返回字符串的长度 */
int length()
{
   return len;
}

/*rbegin() 返回一个逆向迭代器，指向最后一个字符 */
char * rbegin()
{
   char *p = data;
   while (*p != '\0')
   {
      p++;
   }
   return --p;
}

/*rend()函数返回一个逆向迭代器，指向字符串的开头（第一个字符的前一个位置）。*/
char * rend()
{
   char * p = data;
   return p;
}

/*replace() 替换字符*/
void replace(char *str,int num , int index)
{
   if ((num+index) > len)
   {
      std::cout<<"error";
   }
   else
   {
       for (int i = index; i < index + num; i++)
     {
        data[i] = str[i-index];
     }
   }
}

/*reserve() 保留一定容量以容纳字符串*/
void reserve(int num )
{
   maxlen = num;
}
/*resize() 重新设置字符串的大小 */
void resize(int num ,char ch)
{
   if (num < len)
   {
        std::cout<<"error";
   }
   else
   {
        if (num <= maxlen)
        {
            for (int i = len; i < num;i++)
            {
                data[i] = ch;
            }
        }
        else
        {
            data1 = new char[len];
            mystrcpy(data1,data);
            delete data;
            data = NULL;
            data = new char[num];
            mystrcpy(data,data1);
            for (int i = len;i < num; i++)
            {
               data[i] = ch;
            }
        }
   }
}

/*rfind() 查找最后一个与value相等的字符（逆向查找）*/
int rfind(char * str ,int index)
{ 
    char *p = &data[len-1];
    int num = mystrlen(str);
    char *q =&str[mystrlen(str)-1];
   int flag = 0;
   int indexq = len-1;
    while (indexq != (index-1))
    {   
        if (num == 0)
        {
           break;
        }
       if (*p != *q)
       {
         q = &str[mystrlen(str)-1];
         flag =0;
         num = mystrlen(str);
       }
       if (*p == *q)
       {
         flag = 1;
         q--;
         num--;
       }
       p--;
       indexq--;
    }
    if (flag == 1&& num == 0)
    {
      ++indexq;
       return indexq;
    }
    else
    {
       return -1;
    }

}

/*size() 返回字符串中字符的数量 */
int size()
{
   return len;
}

/*substr() 返回某个子字符串 */
char * substr(int index,int num = 2)
{
     if (index + num > len)
     {
        return 0;
     }
     else
     {
             data1 = new char[num];
            for (int i = index;i < index+num;i++)
            {
               data1[i-index] = data[i]; 
            }
            return data1;
     }
}

/*swap() 交换两个字符串的内容 */
void swap(char *str)
{
    data1 = new char[len];
    mystrcpy(data1,data);
    mystrcpy(data,str);
    mystrcpy(str,data1);
    delete data1;
    data1 = NULL;
}

/* operator char*() 实现类型转换*/
  operator char*()
  {
          return data;
  }
  private:
    char *data;
    char *data1;
    int maxlen;
    int len;    
};

#endif
