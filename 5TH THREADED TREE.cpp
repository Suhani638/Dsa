#include <iostream>
using namespace std;

struct Node{
int data;
Node*left,*right;
bool leftThread, rightThread;

Node(int d)
:data(d),left(NULL),right(NULL),
leftThread(false),rightThread(false){}
};


Node*createTree(){
int val;
cin >>val;
if(val == -1)
return NULL;

Node*root=new Node(val);

root->left =createTree();
root->right = createTree();
return root;	
}

void createThreaded(Node* root, Node*&prev){
if(root==NULL)
return;
createThreaded(root->left,prev);

if(root->left==NULL){
root->left=prev;
root->leftThread=true;	
}

if(prev!=NULL&&prev->right==NULL)
{
prev->right=root;
prev->rightThread=true;	
}

prev = root;
createThreaded(root->right,prev);	
}

void convertToThreaded(Node*root){
Node*prev=NULL;
createThreaded(root,prev);	
}

Node*leftmost(Node*node){
if(node==NULL)
return NULL;
while(node->left != NULL && !node->leftThread)
node = node->left;
return node;	
}

void inorderThreaded(Node*root){
Node*cur = leftmost(root);
while(cur!=NULL){
cout<<cur->data<<"";

if(cur->rightThread)
cur=cur->right;
else
cur=leftmost(cur->right);
}
cout<<endl;
}

int main(){
cout<<"Enter tree nodes in pre-order(-1 for NULL):\n";

Node*root=createTree();
convertToThreaded(root);

cout<<"Inorder traversal of the double-threaded binary tree:\n";
inorderThreaded(root);

return 0;	
}

