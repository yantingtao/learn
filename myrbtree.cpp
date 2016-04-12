/**********************************
作者:颜廷涛
时间:2016.3.31
内容:红黑树代码实现
**********************************/
#include <iostream>
#include <string>
using namespace std;
#define BLACK 0
#define RED 1
template <class T>
class my_rbtree;//前置声明

template <class T>
class my_rbnode
{
	friend class my_rbtree<T>;//友元
  public:
  	my_rbnode(T _data)
  	{
  		data = _data;
  		colour = RED;//默认为红色
  		left = NULL;
  		right = NULL;
  		parent = NULL;
  	}
 private:
 	T data;
 	int colour;
 	my_rbnode<T>* left;
 	my_rbnode<T>* right;
 	my_rbnode<T>* parent;
};

template <class T>
class my_rbtree
{
   public:
       my_rbtree()
       {
       	  root = NULL;
       	  key = 0;
       }
       /*左旋*/
      void rb_left_rotate(my_rbnode<T> *node)
      {
         my_rbnode<T>* node_right = node->right;
         node->right = node_right->left;
         if ( node->right != NULL)
         {
             node_right->left->parent = node;
         }
         node_right->left = node;
         node_right->parent = node->parent;
         if (node_right->parent != NULL)
         {
         	 if (node == node_right->parent->left)//判断旋转的节点是其父节点的左孩子还是右孩子
         	 {
         	 	node->parent->left = node_right;
         	 }
         	 else
         	 {
         	 	node->parent->right = node_right;
         	 }
         }
         else
         {
         	 root = node_right;
         }
         node->parent = node_right;
      }
      /*右旋*/
      void rb_right_rotate(my_rbnode<T> *node)
      {
      	 my_rbnode<T>* node_left = node->left;
      	 node->left = node_left->right;
      	 if (node->left != NULL)
      	 {
      	 	node_left->right->parent = node;
      	 }
      	 node_left->left = node;
      	 node_left->parent = node->parent;
      	 if (node_left->parent != NULL)
      	 {
             if (node == node->parent->left)
             {
             	node->parent->left = node_left;
             }
             else
             {
             	node->parent->right = node_left;
             }
      	 }
      	 else
      	 {
      	 	root = node_left;
      	 }

      	 node->parent = node_left;
      }

      /*插入的修复*/
     void rbtree_insert_rebalance(my_rbnode<T>* node)
      {
      	  my_rbnode<T>* node_parent = NULL;
          my_rbnode<T>* node_grandparent = NULL;
          my_rbnode<T>* node_uncle = NULL;
          my_rbnode<T>* tmp = NULL;//tmp为临时变量
          node_parent = node->parent;
      	 while (node_parent != NULL &&node_parent->colour == RED)
      	 {
              node_grandparent = node_parent->parent;
              if (node_parent == node_grandparent->left)
              {
              	   node_uncle = node_grandparent->right;
              	   if (node_uncle != NULL && node_uncle->colour == RED)
              	   {
                      node_parent->colour = BLACK;
                      node_uncle->colour = BLACK;
                      node_grandparent->colour = RED;
                      node = node_grandparent;//转移不平衡点
                      node_parent = node->parent;
              	   }
              	   else
              	   {
                     /*情况2 叔叔节点为黑色 且 当前节点的父节点为右孩子*/
                     if (node == node_parent->right)
                     {
                        rb_left_rotate(node_parent);
                        tmp = node_parent;
                        node_parent = node;
                        node = tmp;
                     }
                        node_parent->colour = BLACK;
                        node_grandparent->colour = RED;
                        rb_right_rotate(node_grandparent);
              	   }
              }
              else
              { 
                  node_uncle = node_grandparent->left;
                  if (node_uncle != NULL && node_uncle->colour == RED)
                  {
                      node_parent->colour = BLACK;
                      node_uncle->colour = BLACK;
                      node_grandparent->colour = RED;
                      node = node_grandparent;//转移不平衡点
                      node_parent = node->parent;
                  }
                  else
                  {
                       if (node == node_parent->left)
                       {
                       	    rb_right_rotate(node_parent);
                            tmp = node_parent;
                            node_parent = node;
                            node = tmp;
                       }
                       node_parent->colour = BLACK;
                       node_grandparent->colour = RED;
                       rb_left_rotate(node_grandparent);
                  }
              }
      	 }

      	 root->colour = BLACK;
      }
      /*插入*/
      void rbtree_insert(T _data)
      {
         my_rbnode<T>* newnode = new my_rbnode<T>(_data);
         if (root == NULL)
         {
           root = newnode;
           root->colour = BLACK;
         }
         else
         {
            my_rbnode<T>* curr = root;
            my_rbnode<T>* tmp = NULL;
            while (curr != NULL)
            {   
                 tmp = curr;
                if (curr->data > _data)
                {
                    curr = curr->left;
                }
                else
                {
                   curr = curr->right;
                }
            }
          newnode->parent = tmp;
          if (tmp->data > _data)
          {
             tmp->left = newnode;
          }
          else
          {
             tmp->right = newnode;
          }
            rbtree_insert_rebalance(newnode);
         }
       
      }
      /*创建一棵树*/
       void input_tree(T a[],int length)
      {
         int i;
         for (i = 0; i < length; i++)
         {
            rbtree_insert(a[i]);
         }        
      }
      /*查找*/
      my_rbnode<T>* rbtree_find(T _data)
       {
           my_rbnode<T>* curr = root;
           while (curr != NULL)
           { 
              if (curr->data > _data)
              {
                  curr = curr->left;
              }
              else if (curr->data < _data)
              {
                 curr = curr->right;
              }
              else
              {
                 return curr;
              }
           }
           return NULL;
       }
       /*删除*/
      void rbtree_delete(T _data)
      {
          my_rbnode<T>* tmp = rbtree_find(_data);
          if (tmp == NULL)
          {
             return;
          }
          my_rbnode<T>* replace = tmp;//后继点
          my_rbnode<T>* node_child = NULL;
          my_rbnode<T>* node_parent = NULL;
          int node_colour = RED;
        if ( tmp->left != NULL && tmp->right != NULL)
        {
               //找后继点
              replace = tmp->right;
              while (replace->left != NULL)
              {
                 replace = replace->left;
              }
              node_child = replace->right;
              node_parent = replace->parent;
              node_colour = replace->colour;

              if (tmp->parent != NULL)
              {
                   if (tmp->parent->left == tmp)
                   {
                       tmp->parent->left = replace;
                   }
                   else
                   {
                       tmp->parent->right = replace;
                   }
              }
              else
               {
                    root = replace;
               }
              //删除的节点是后继节点的父节点
               if (node_parent == tmp)
               {
                  node_parent = replace;
               }
               else
               {    //后继节点子节点不为空
                  if (node_child != NULL)
                  {
                     node_child->parent = node_parent;
                  }
                  node_parent->left = node_child;
                  replace->right = tmp->right;
                  tmp->right->parent = replace;
               }

               replace->parent = tmp->parent;
               replace->colour = tmp->colour;
               replace->left = tmp->left;
               tmp->left->parent = replace;
               if (node_colour == BLACK)
               {
                  rbtree_delete_rebalance(node_child,node_parent);
               }
               delete tmp;
               return;
        }
        if (tmp->left != NULL)
        {
            node_child = tmp->left;
        }
        else
        {
            node_child = tmp->right;
        }

        node_parent = tmp->parent;
        node_colour = tmp->colour;
        if (node_child != NULL)
        {
           node_child->parent = node_parent;
        }

        if (node_parent != NULL)
        {
            if (node_parent->left == tmp)
            {
                node_parent->left = node_child;
            }
            else
            {
               node_parent->right = node_child;
            }
        }
        else
        {
           root = node_child;
        }

        if (node_colour == BLACK)
        {
          rbtree_delete_rebalance(node_child,node_parent);
        }
        delete tmp;
      }
       
       /*删除修复*/
       void rbtree_delete_rebalance(my_rbnode<T>* node,my_rbnode<T>* node_parent)
       {
          my_rbnode<T>* other = NULL;
          my_rbnode<T>* o_left = NULL;
          my_rbnode<T>* o_right = NULL;

          while ((!node || node->colour == BLACK) && node != root)
          {
               if (node_parent->left == node)
               {
                  other = node_parent->right;
                  if (other->colour == RED)
                  {
                     other->colour = BLACK;
                     node_parent->colour = RED;
                     rb_left_rotate(node_parent);
                     other = node_parent->right;
                  }

                  if ((!other->left || other->left->colour == BLACK) &&
                     (!other->right || other->right->colour == BLACK))
                  {
                     other->colour = RED;
                     node = node_parent;
                     node_parent = node->parent;
                  }
                  else
                  {
                    if (!other->right || other->right->colour == BLACK)
                    {    
                       o_left = other->left;
                        if (o_left != NULL)
                        {
                           o_left->colour = BLACK;
                        }
                        other->colour = RED;
                        rb_right_rotate(other);
                        other = node_parent->right;
                    }

                    other->colour = node_parent->colour;
                    node_parent->colour = BLACK;
                    if (other->right != NULL)
                    {
                       other->right->colour = BLACK;
                    }
                    rb_left_rotate(node_parent);
                    node = root;
                    break;
                  }
               }
               else
               {
                  other = node_parent->left;
                  if (other->colour == RED)
                  {
                     other->colour = BLACK;
                     node_parent->colour = RED;
                     rb_right_rotate(node_parent);
                     other = node_parent->left;
                  }
                  if ((!other->left || other->left->colour == BLACK) &&
                     (!other->right || other->right->colour == BLACK))
                  {
                      other->colour = RED;
                      node = node_parent;
                      node_parent = node->parent;
                  }
                  else
                  {
                        if (!other->left || other->left->colour == BLACK)
                        {  
                            o_right = other->right;
                           if (o_right != NULL)
                           {
                             o_right->colour = BLACK;
                           }

                           other->colour = RED;
                           rb_left_rotate(other);
                           other = node_parent->left;
                        }
                        other->colour = node_parent->colour;
                        node_parent->colour = BLACK; 
                        if (other->left != NULL)
                       {
                         other->left->colour = BLACK;
                       }
                       rb_left_rotate(node_parent);
                       node = root;
                       break;  
                  }
               }
          }

          if (node != NULL)
          {
             node->colour = BLACK;
          }
       }

       /*前序遍历*/
      void pretree(my_rbnode<T>* node)
      {
      	  if (node != NULL)
      	  {
      	  	  cout<<node->data<<'\t';
      	  	  if (node->colour == BLACK)
      	  	  {
      	  	  	 cout<<"黑色"<<endl;
      	  	  }
      	  	  else
      	  	  {
      	  	  	 cout<<"红色"<<endl;
      	  	  }
      	  	  pretree(node->left);
      	  	  pretree(node->right);
      	  }
      }
      void pretree()
      {
         pretree(root);
      }
   private:
   	my_rbnode<T>* root;
   	key_t key;
};
int main(int argc, char const *argv[])
{
	my_rbtree<char>  rb1;
	char ch[] = "1234456789";
    rb1.input_tree(ch,strlen(ch));
    rb1.pretree();
    rb1.rbtree_delete(8);
    rb1.pretree();
    // if (rb1.rbtree_find('a'))
    // {
    //    cout<<"find"<<endl;
    // }
    // else
    // {
    //    cout<<"not find"<<endl;
    // }
	return 0;
}