#include <iostream>
using namespace std;

template  <class T> 
class mylist;

template <class T>
class node
 {
 	friend class mylist<T>;
 	template <class T1>
 	friend ostream& operator <<(ostream & out , node<T1> _node);
    public:
    	node(T _data)
    	{
    		data = _data;
    		next = NULL;
    		prev = NULL;
    	}

    private:
    	T data;
    	node<T> *next;
    	node<T> *prev;//指向前一个节点
 };

 template <class T>
ostream& operator <<(ostream & out , node<T> _node)
{
	out<<_node.data<<'\t';
	return out;
}

template<class T>
class mylist
{
public:
	typedef bool (*Unperd)(T value);
	typedef bool (*BinPred)(T value);
	typedef bool (*Comp)(T a,T b);//排序的函数指针
	/*迭代器*/
      class iterator
      {
          public:
          	iterator()
          	{
          		ptr = NULL;
          	}
          	iterator(node<T>* _ptr)
          	{
          		ptr = _ptr;
          	}

          	void operator =(iterator it)
          	{
               this->ptr = it.ptr;
          	}
          	bool operator !=(iterator it)
          	{
               return this->ptr != it.ptr;
          	}
          	bool operator == (iterator it)
          	{
          		return this->ptr == it.ptr;
          	}
          	iterator operator ++(int i)
          	{
          		iterator tmp;
          		tmp = *this;
          		this->ptr = this->ptr->next;
          		return tmp;
          	}
          	node<T> operator *()
          	{
          		return *(this->ptr);
          	}
          private:
          	node<T> *ptr;
      };
    /*反向迭代器*/
    class reserve_iterator
    {
           public:
          	reserve_iterator()
          	{
          		ptr = NULL;
          	}
          	reserve_iterator(node<T>* _ptr)
          	{
          		ptr = _ptr;
          	}

          	void operator =(reserve_iterator it)
          	{
               this->ptr = it.ptr;
          	}
          	bool operator !=(reserve_iterator it)
          	{
               return this->ptr != it.ptr;
          	}
          	bool operator == (reserve_iterator it)
          	{
          		return this->ptr == it.ptr;
          	}
          	reserve_iterator operator ++(int i)
          	{
          		reserve_iterator tmp;
          		tmp = *this;
          		this->ptr = this->ptr->prev;
          		return tmp;
          	}
          	node<T> operator *()
          	{
          		return *(this->ptr);
          	}
          private:
          	node<T> *ptr;
    };
    /*无参缺省构造*/
	mylist()
	{
		head = NULL;
		curr = NULL;
	}
	/*list(int num,T value)*/
	mylist(int num,T value)
	{
	    head = new node<T>(value);
	    curr = head;
	    int i;
	    node<T>* newnode = NULL;
	    for (i = 0; i < num;i++)
	    {
	        newnode = new node<T>(value);
	        curr->next = newnode;
	        newnode->prev = curr;
	    	curr = newnode; 
	   	    newnode = NULL;    	
	    }
	    curr->next = head;
	    head->prev = curr;
	}
    /*list<T>(list)*/
    mylist(mylist & list)
    {
    	node<T>* point = list.head->next;
        this->head = new node<T>(point->data);
        this->curr = this->head;
        node<T> * newnode = NULL;
        while (point != list.head)
        {
           newnode = new node<T>(point->data);
           this->curr->next = newnode;
           newnode->prev = this->curr;
           this->curr = newnode;
           newnode = NULL;
           point = point->next;
        }
        this->curr->next = this->head;
        this->head->prev = this->curr; 
    }


    /*list<T>(list.begin(),list.end())*/
    mylist(iterator start,iterator end)
    {
    	 iterator point = start;
        head = new node<T>(*point);
        curr = head;
        node<T> * newnode = NULL;
        while (point != end)
        {
           newnode = new node<T>(*point);
           curr->next = newnode;
           newnode->prev = curr;
           curr = newnode;
           newnode = NULL;
           point++;
        }
        curr->next = head;
        head->prev = curr; 
    }

	/*void assign( input_iterator start, input_iterator end );
	assign()函数以迭代器start和end指示的范围为list赋值*/
      void assign(iterator start,iterator end)
      {
         iterator point = start;
         if (NULL == head)
         {
             this->head = new node<T>(*point);
             curr = head;
         }
         else
         {
             curr = head->prev;
         }
           
            node<T> * newnode = NULL;
            while (point != end)
           {
             newnode = new node<T>(*point);
             curr->next = newnode;
             newnode->prev = curr;
             curr = newnode;
             newnode = NULL;
             point++;
           }
           curr->next = head;
           head->prev = curr;
      }
     /*void assign( size_type num, const TYPE &val );*/
      void assign(int num,const T & value)
      {
         if (NULL == head)
         {
         	head = new node<T>(value);
	        curr = head;
         }
         else
         {
         	curr = head->prev;
         }
	    int i;
	    node<T>* newnode = NULL;
	    for (i = 0; i < num;i++)
	    {
	        newnode = new node<T>(value);
	        curr->next = newnode;
	        newnode->prev = curr;
	    	curr = newnode; 
	   	    newnode = NULL;    	
	    }
	    curr->next = head;
	    head->prev = curr;
      }
   /*back()函数返回一个引用，指向list的最后一个元素*/
     T& back()
    {
      return head->prev->data;
    }
    /*clear()函数删除list的所有元素*/
    void clear()
    {
    	curr = head->next;
    	head->next = NULL;
    	node<T>* tmp;
    	while (curr != head)
    	{
    		tmp = curr;
    		curr = curr->next;
    		head->next = curr;
    		if (NULL != curr)
    		{
    			curr->prev = head;
    		}
    		free(tmp); 
    		tmp = NULL;
    	}
    }
    /*empty()函数返回真(true)如果链表为空，否则返回假*/
    bool empty()
    {
    	if (head->next == head)
    		return true;
    	return false;
    }
   /*起始位置*/
	iterator begin()
	{
       return  iterator(head->next);
	}
	/*末尾的下一个*/
	iterator end()
	{
       return  iterator(head);
	}

	/*rbegin()函数返回一个逆向迭代器，指向链表的末尾。*/
	reserve_iterator rebegin()
	{
		return reserve_iterator(head->prev);
	}

	/*rend()函数迭代器指向链表的头部。*/
	reserve_iterator rend()
	{
		return reserve_iterator(head);
	}

	/*find查找指定元素的第一个位置没找到则返回NULL*/
	iterator find(const T &value)
	{
		curr = head->next;
		int flag = 0;
        while (curr != head)
        {
        	if (curr->data == value)
        	{   
        		flag = 1;
        		return iterator(curr);
        		break;
        	}
        	curr = curr->next;
        }
        if (flag == 0)
        {
        	return iterator();
        }
	}


	/*erase()函数删除以pos指示位置的元素
	  iterator erase( iterator pos );*/
	iterator erase(iterator pos)
	{
	    node<T>* tmp = head;
	    curr = head->next;
	    while (curr != head)
	    {
	    	 if (iterator(curr) == pos)
	    	 {
	    	 	tmp->next = curr->next;
	    	 	curr->next->prev = tmp;
	    	 	return iterator(curr->next);
	    	 	free(curr);
	    	 	curr = NULL;
	    	 	break;
	    	 }
	    	 else
	    	 {
	    	 	tmp = curr;
	    	 }
	    	 curr = curr->next;
	    }
	}
     /* iterator erase( iterator start, iterator end );
     删除start和end之间的元素。 返回值是一个迭代器，
     指向最后一个被删除元素的下一个元素*/
     iterator erase(iterator start,iterator end)
     {
     	node<T>* tmp = head;
     	curr = head->next;
     	while (curr != head)
     	{
     		if (iterator(tmp) == start)
     		{
                while (iterator(curr) != end)
                {
                	tmp->next = curr->next;
                	curr->next->prev = tmp;
                	free(curr);
                	curr = NULL;
                	curr = tmp->next;
                }
                return iterator(curr);
                break;
     		}
     		else
     		{
              tmp = curr;
     		}
     		curr = curr->next;
     	}
     }

     /*front()函数返回一个引用，指向链表的第一个元素。*/
     T & front()
     {
     	return head->next->data;
     }

     /*  iterator insert( iterator pos, const TYPE &val );*/
      iterator insert(iterator pos,const T& value)
      {
      	 node<T>* newnode = new node<T>(value);
      	 curr = head->next;
      	 while (curr != head)
      	 {

      	 	if (iterator(head) == pos)
      	 	{
                 head->prev->prev->next = newnode;
                 newnode->prev = head->prev->prev;
                 head->prev->prev = newnode;
                 newnode->next = head->prev;
                 return iterator(head->prev);
                 break;
      	 	}
      	 	if (iterator(curr) == pos)
      	 	{
      	 		curr->prev->next = newnode;
      	 		newnode->prev = curr->prev;
      	 		curr->prev = newnode;
      	 		newnode->next = curr;
      	 		break;
      	 	}
      	 	curr = curr->next;
      	 }
      }
      /*  void insert( iterator pos, size_type num, const TYPE &val );*/
      void insert(iterator pos,int num,const T &value)
      {
      	 node<T>* newnode;
      	 curr = head->next;
      	 node<T>* tmp = head;
      	 if (iterator(head) == pos)
      	 {   
      	 	 tmp = head->prev->prev;
      	 	 curr = head->prev;
             while (0 != num)
             {
                newnode = new node<T>(value);
                tmp->next = newnode;
                newnode->prev = tmp;
                tmp = newnode;
                newnode = NULL;
                num--; 
             }
             tmp->next = curr;
             curr->prev = tmp;
      	 }
      	 else
      	 {
      	   while (curr != head)
      	   {    	 	
      	 	  if (iterator(curr) == pos)
      	 	 {
      	 	    while (0 != num)
      	 	    {
      	 	    	newnode = new node<T>(value);
      	 	    	tmp->next = newnode;
      	 	    	newnode->prev = tmp;
      	 	    	tmp = newnode;
      	 	    	newnode = NULL;
      	 	    	num--;
      	 	    }
      	 	    tmp->next = curr;
      	 	    curr->prev = tmp;
      	 	    break;
      	 	 }
      	 	 else
      	 	 {
      	 		tmp =curr;
      	 	 }
      	 	curr = curr->next;
      	  }
      	 }
      }
      /*pop_back()函数删除链表的最后一个元素。*/
      void pop_back()
      {
      	 curr = head->prev;
      	 node<T>* tmp = head->prev->prev;
      	 tmp->next = head;
      	 head->prev = tmp;
      	 free(curr);
      	 curr = NULL;
      }
      /*pop_front()函数删除链表的第一个元素。*/
      void pop_front()
      {
      	 curr = head->next;
      	 node<T>* tmp = head->next->next;
         head->next = tmp;
         tmp->prev = head;
         free(curr);
         curr = NULL;
      }
     /* push_back()将val连接到链表的最后*/
      void push_back(const T& value)
      {
      	node<T>* newnode = new node<T>(value) ;
      	if (head == NULL)
      	{
           head = new node<T>(value);
           curr = head;
      	}
      	else
      	{
      		curr = head->prev;
      	}
      	 curr->next = newnode;
         newnode->prev = curr;
         curr = newnode;
         newnode = NULL;
         curr->next = head;
         head->prev = curr;
      }
      /*push_front函数将val连接到链表的头部。*/
      void push_front(const T& value)
      {
      	node<T>* newnode = new node<T>(value) ;
      	if (head == NULL)
      	{
           head = new node<T>(value);
           curr = head;
           curr->next = newnode;
           newnode->next = curr;
           curr = newnode;
           newnode = NULL;
           curr->next = head;
           head->prev = curr;
      	}
        else
        {
           curr = head;
           newnode->next = curr->next;
      	   curr->next = newnode;
      	   curr = newnode;
      	   newnode = NULL;
           curr->prev = head;
           curr->next->prev = curr;
        }
      }
      /*remove()函数删除链表中所有值为val的元素*/
      void remove(const T & value)
      { 
          node<T>* tmp = head;
          curr = head->next;
          while (curr != head)
          {
          	if (curr->data == value)
          	{
                tmp->next = curr->next;
                curr->next->prev = tmp;
                free(curr);
                curr = NULL;
                curr = tmp;
          	}
          	else
          	{
          		tmp = curr;
          	}
          	curr = curr->next;
          }
      }
      /*remove_if()以一元谓词pr为判断元素的依据，遍历整个链表
      如果pr返回true则删除该元素。*/
      void remove_if(Unperd pr)
      {
      	   node<T>* tmp = head;
          curr = head->next;
          while (curr != head)
          {
          	if (pr(curr->data))
          	{
                tmp->next = curr->next;
                curr->next->prev = tmp;
                free(curr);
                curr = NULL;
                curr = tmp;
          	}
          	else
          	{
          		tmp = curr;
          	}
          	curr = curr->next;
          }
      }

      /*resize()函数把list的大小改变到num。被加入的多余的元素都被赋值为val*/
      void resize(int num,T value)
      {      	
        int record = 0;
        curr = head->next;
        iterator point;
        while (curr != head)
        {
        	 ++record;
        	if (record == num)
        	{
        		point = iterator(curr);
        	}
           curr = curr->next;
        }
        if (record < num)
        {  	
        	while (record != num)
        	{
        		node<T>* newnode = new node<T>(value);
        		curr = head->prev;
        	    curr->next = newnode;
                newnode->prev = curr;
                curr = newnode;
                newnode = NULL;
                curr->next = head;
                head->prev = curr;
                record++;
        	}
        }
        if (record > num)
        {
           erase(point,iterator(head));
        }
      }

      /*reverse()函数把list所有元素倒转。*/
      void reverse()
      { 
         mylist<T> list(*this);
        node<T>* tmp = list.head->prev;
         this->curr = this->head->next;
         while (this->curr != this->head)
         {
         	this->curr->data = tmp->data;
         	tmp = tmp->prev;
         	this->curr = this->curr->next;
         }
      }

      /*size()函数返回list中元素的数量。*/
      int size()
      {
      	curr = head->next;
      	int num = 0;
      	while (curr != head)
      	{
      		num++;
      		curr = curr->next;
      	}
      	return num;
      }

      /*sort()函数为链表排序，默认是升序*/
      void sort()
      {
      	curr = head->next;
      	node<T>* tmp;
      	tmp =  head->next->next;
      	int temp = 0;
      	int n = size();
      	int i = 0;
      	int flag = 0;
        while (tmp != head)
        {              
        	if (curr->data > tmp->data)
        	{
        		flag = 1;
        		temp = tmp->data;
        		tmp->data = curr->data;
        		curr->data = temp;
        	}
        	i++;
        	curr = curr->next;
        	tmp = tmp->next;
            if ((i == n-1)&&(flag == 1))
        	{
        		flag = 0;
        		i = 0;
        		curr = head->next;
                tmp = head->next->next;
        	} 
        }
      }

      /* void sort( Comp compfunction );
      如果指定compfunction的话，就采用指定函数来判定两个元素的大小*/
      void sort(Comp compfunction)
      {
      	curr = head->next;
      	node<T>* tmp;
      	tmp =  head->next->next;
      	int temp = 0;
      	int n = size();
      	int i = 0;
      	int flag = 0;
        while (tmp != head)
        {              
        	if (compfunction(curr->data,tmp->data))
        	{
        		flag = 1;
        		temp = tmp->data;
        		tmp->data = curr->data;
        		curr->data = temp;
        	}
        	i++;
        	curr = curr->next;
        	tmp = tmp->next;
            if ((i == n-1)&&(flag == 1))
        	{
        		flag = 0;
        		i = 0;
        		curr = head->next;
                tmp = head->next->next;
        	} 
        }
     }
      /*void splice( iterator pos, list &lst );splice()函数把lst连接到pos的位置*/
     void splice(iterator pos,mylist & list)
     {
     	this->curr = this->head->next;
     	node<T>* tmp = this->head;
     	while (this->curr != this->head)
     	{
     		if (iterator(this->curr) == pos)
     		{
                tmp->next = list.head->next;
                list.head->prev->next = this->curr->next;
                this->curr->next->prev = list.head->prev;
                list.head->prev = tmp;
                free(this->curr);
                this->curr = NULL;
                free(list.head);
                list.head = NULL;
                break;
     		}
     		else
     		{
     			tmp = this->curr;
     		}
     		this->curr = this->curr->next;
     	}
     }

     /* void splice( iterator pos, list &lst, iterator del );*/
     void splice(iterator pos,mylist & list,iterator del)
     {
     	this->curr = this->head->next;
     	list.curr = list.head->next;
     	node<T>* tmp = list.head;
     	while (this->curr != this->head)
     	{
     		if (iterator(this->curr) == pos)
     		{
                 while (list.curr != list.head)
                 {
                 	if (iterator(list.curr) == del)
                 	{
                         this->curr->data = list.curr->data;
                         tmp->next = list.curr->next;
                         curr->next->prev = tmp;
                         free(list.curr);
                         list.curr;
                         break;
                 	}
                 	else
                 	{
                 		tmp = list.curr;
                 	}
                  list.curr = list.curr->next;
                 }
                 break;
     		}
     		this->curr = this->curr->next;
     	}
     }

     /* void splice( iterator pos, list &lst, iterator start, iterator end );*/
     void splice(iterator pos,mylist & list,iterator start,iterator end)
     {  
     	list.curr = list.head;
        node<T>* point = list.head;
        node<T>* point1 = list.head;
        iterator it = this->erase(pos);
     	while (iterator(list.curr) != start)
     	{
            list.curr = list.curr->next;
     	}
     	point = list.curr->prev;
     	while(iterator(list.curr->prev) != end)
     	{
           this->insert(it,list.curr->data);
           list.curr = list.curr->next;
     	}
     	point1 = list.curr;
     	list.erase(point,point1);
     }
     /*swap()函数交换lst和现链表中的元素*/
     void swap(mylist & list)
     {
     	int flag1 = 0;//记录交换时那个链表过长需要删除
     	int flag2 = 0;//这里其实只要一个标志  但是为了方便故设置两个
        mylist<T> tmp(list);
        list.curr = list.head->next;
        this->curr = this->head->next;
        while (this->curr != this->head)
        {   
        	if (list.curr != list.head)
        	{
        	  list.curr->data =  this->curr->data;
        	  list.curr = list.curr->next;
        	}
        	else
        	{
        		flag1 = 1;
               list.push_back(this->curr->data);
        	}	
        	this->curr = this->curr->next;
        }
        if ((list.curr != list.head)&& (flag1 == 0))
        {
        	list.erase(iterator(list.curr->prev),iterator(list.head));
        }
         tmp.curr = tmp.head->next;
        this->curr = this->head->next;
       while (tmp.curr != tmp.head)
        {   
        	if (this->curr != this->head)
        	{
        	  this->curr->data =  tmp.curr->data;
        	  this->curr = this->curr->next;
        	}
        	else
        	{
        		flag2 = 1;
               this->push_back(tmp.curr->data);
        	}	
        	tmp.curr = tmp.curr->next;
        }
        if ((this->curr != this->head)&& (flag2 == 0))
        {
        	this->erase(iterator(this->curr->prev),iterator(this->head));
        }
     }

     /* void unique();unique()函数删除链表中所有重复的元素。*/
        void unique()
        {
           curr = head->next->next;
           node<T>* tmp = head->next;
           while (curr != head)
           {
              if (tmp->data == curr->data)
              {
              	   tmp->next = curr->next;
              	   curr->next->prev = tmp;
              	   free(curr);
              	   curr = NULL;
              	   curr = tmp->next;
              }
              tmp = tmp->next;
              curr = curr->next;
           }
        }
        /* void unique( BinPred pr );
     指定pr，则使用pr来判定是否删除*/
        void unique(BinPred pr)
        {
           curr = head->next->next;
           node<T>* tmp = head->next;
           while (curr != head)
           {
              if ((tmp->data == curr->data)&&pr(curr->data))
              {
              	   tmp->next = curr->next;
              	   curr->next->prev = tmp;
              	   free(curr);
              	   curr = NULL;
              	   curr = tmp->next;
              }
              tmp = tmp->next;
              curr = curr->next;
           }
        }
private:
    node<T> *head;
    node<T> *curr;
};

template <class T>
bool dis_tinet( T value)
{
	if (9 == value)
		return true;
	return false;
}
template <class T>
bool sortfunction(T a,T b)
{
	if (a < b)
		return true;
	return false;
}
template <class T>
bool unique_t( T value)
{
	if (8 == value)
		return true;
	return false;
}

int main(int argc, char const *argv[])
{
	mylist<int> list1(5,8);
	mylist<int>::iterator it;
	mylist<int> list2;
	mylist<int>::iterator a;
	mylist<int>::iterator b;
	//list2.assign(5,6);
	// mylist<int>::iterator a = list2.find(8);
	// mylist<int>::iterator b = list2.find(6);
 //    list2.erase(a,b);
	int i;
	for (i = 0; i < 15;i++)
		{
     		list2.push_back(i);
		}
	mylist<int> list3;
     list3.push_front(88);
     list3.push_front(60);
     list3.push_back(9);
    list3.push_back(7);
    list3.push_back(8);
    list3.push_back(0);
    list3.push_back(60);
      list3.push_back(8);
    a = list2.find(6);
    b = list2.find(10);
    it = list3.find(8);
   // list3.splice(a,list1);
    //list3.splice(it,list2,a,b);
    //list3.remove_if(dis_tinet);
    //list3.resize(10,10);
   // list3.reverse();
    //cout<<list3.size()<<endl;
	//cout<<list2.empty()<<endl;
	// list3.sort();
	// list3.sort(sortfunction);
    //list3.swap(list2);
  // mylist<int> list4(list2);
    list3.sort();
    //list3.unique();
    list3.unique(unique_t);
	for (it = list3.begin();it != list3.end();it++)
	{
		cout<<*it<<endl;
	}
 //   for (it = list2.begin();it != list2.end();it++)
	// {
	// 	cout<<*it<<endl;
	// }
 //   for (it = list4.begin();it != list4.end();it++)
	// {
	// 	cout<<*it<<endl;
	// }
	//cout<<list1.back()<<endl;
	return 0;
}

