// CPP program to find  
// difference between  
// sums of odd level  
// and even level nodes  
// of binary tree 
#include <bits/stdc++.h> 
using namespace std; 
  
// tree node 
struct Node  
{ 
    int data; 
    Node *left, *right; 
}; 
  
// returns a new 
// tree Node 
Node* newNode(int data) 
{ 
    Node* temp = new Node(); 
    temp->data = data; 
    temp->left = temp->right = NULL; 
    return temp; 
} 
  
int getLevelDiff(Node *root)
{
   //Your code here
   int lvl = 0;
   int sum_odd =0, sum_even =0;
   stack<Node*> st_odd, st_even;
   if (root == nullptr)
        return 0;
   
   st_odd.push(root);
   Node * cur = nullptr;

   while (!st_odd.empty() || !st_even.empty()){
       if (lvl == 0){
       while(!st_odd.empty()){
           cur = st_odd.top();
           sum_odd += cur->data;
            if (cur->left != nullptr)
               st_even.push(cur->left);
            if (cur->right != nullptr)
               st_even.push(cur->right);
            //cout << cur ->data << " " << st_even.size() << '\n';
           st_odd.pop();
       }
       lvl = 1;
   }
   else {
       while(!st_even.empty()){
           cur = st_even.top();
           sum_even += cur->data;
           if (cur->left != nullptr)
              st_odd.push(cur->left);
           if (cur->right != nullptr)
              st_odd.push(cur->right);
           //cout << cur ->data << '\n';
           st_even.pop();
       }
       lvl = 0;
   }
  } 
  
   return (sum_odd - sum_even);
}


// driver program 
int main() 
{ 
    // construct a tree 
    Node* root = newNode(5); 
    root->left = newNode(2); 
    root->right = newNode(6); 
    root->left->left = newNode(1); 
    root->left->right = newNode(4); 
    root->left->right->left = newNode(3); 
    root->right->right = newNode(8); 
    root->right->right->right = newNode(9); 
    root->right->right->left = newNode(7); 
  
    int result = getLevelDiff(root); 
    cout << "diffence between sums is :: "; 
    cout << result << endl; 
    return 0; 
} 

