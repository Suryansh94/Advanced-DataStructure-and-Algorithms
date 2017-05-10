#include<bits/stdc++.h>
typedef long long int  ll;
using namespace std;

struct node
{
	ll data;
	struct node* left;
	struct node* right;
	int height;
	int count;
};

node* new_node(ll data)
{
	node* p=(node* )malloc(sizeof(node));
	p->data=data;
	p->right=NULL;
	p->left=NULL;
	return p;
}


int getbalance(node* root)
{
	if(!root)
		return 0;
	else
		return height(root->left)-height(root->right);
}

node *left_rotate(node *root){

	node *p=root->right;
	node *q=root->left;

	p->left=root;
	root->right=q;

	root->height=max(height(root->left), height(root->right))+1;
	p->height=max(height(p->left), height(p->right))+1;

}
node *right_rotate(node *root){

	node *p=root->left;
	node *q=root->right;

	p->right=root;
	root->left=q;

	root->height=max(height(root->left), height(root->right))+1;
	p->height=max(height(p->left), height(p->right))+1;

	return p;
}

node* insert(node* root, int key){
	if(root==NULL){
		root=newnode(data);
		return root;
	}
	if(key<root->val)
		root->left=insert(root->left,key);
	else
		root->right=insert(root->right,key);


	root->height=max(height(root->left),height(root->right))+1;

	int bal=getbalance(root);

	if(bal>1 &&root->left->data>key)
		return leftrotate(root);
	if(bal<-1&&root->right->data<key)
		return root->left=rotate;

	if(bal>1 &&root->left->data<key){
		root->left=left_rotate(root->left);
		return right_rotate(root);
	}
	if(bal<-1 &&root->right->data>key){
		root->right=right_rotate(root->right);
		return left_rotate(root);
	}

	return root;
}
node* delet(node* root,int key){
	if(root==NULL){
		return root;
	}
	if(key<root->val)
		root->left=delet(root->left,key);
	 else if(root->data<key)
		root->right=delet(root->right,key);

	if(!root->left&&root->right)
	{
		node *temp=root->right;
		free(root);
		root=root->right;
		return root;
	}
	if(!root->right&&root->left)
	{
		node *temp=root->left;
		free(root);
		root=root->left;
		return root;
	}
	if(root->left&&!root->right){

		  // node with two children: Get the inorder successor (smallest
		  //             // in the right subtree)
		  node *temp=root->left;
		  while(temp->right!=NULL)
			  temp=temp->right;
		  root->data=temp->data;
		  root->left=delet(root->left,temp->data);
	}

	if(!root)
		return root;

	root->height=max(height(root->left),height(root->right))+1;

	int bal=getbalance(root);

	if(bal>1 &&root->left->data>key)
		return leftrotate(root);
	if(bal<-1&&root->right->data<key)
		return root->left=rotate;

	if(bal>1 &&root->left->data<key){
		root->left=left_rotate(root->left);
		return right_rotate(root);
	}
	if(bal<-1 &&root->right->data>key){
		root->right=right_rotate(root->right);
		return left_rotate(root);
	}

	return root;
}

int main()
{

}