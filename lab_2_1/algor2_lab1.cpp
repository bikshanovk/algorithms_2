// inf_th_l1.cpp:
#include "stdafx.h"
#include <math.h> 
#include <cmath>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <conio.h>
#include <locale.h> 
#include <time.h>
using namespace std;


struct vertex
{
    int Data;	   //Info field
    vertex *left, *right; //Left and right parts of a tree
};
int i=0;
bool toggle= false;				//For "friendly" interface
vertex * root= new	vertex;		//Root vertex
vertex * last_leaf= new	vertex; //
vertex * turn= new vertex;	
void put(int left_right);
int  size(vertex *P);
int  height(vertex *P);
int  BST(vertex *P, int L);		//balanced search tree
int  avg_height();
void left_to_right(vertex *P);
int checksum(vertex *P);
int  main    (int argc, char* argv[])
{
   // Seed the random-number generator with the current time so that
   // the numbers will be different every time we run:
   srand( (unsigned)time( NULL ) );
   
   //Keeping the tree:
   root->Data=rand();					//0
   root->left=root->right=NULL;
   last_leaf=root;
   put(0);								//1
   put(1);								//2
   turn=last_leaf; 
   put(0);								//3
   last_leaf=turn;
   put(1);								//4
   put(0);								//5
  
   //Examine the tree:
   printf("Tree traversal:\n{");
   left_to_right(root);
   printf("}\n");
   printf("Size of tree=%d;\n",size(root));
   printf("Height of tree=%d;\n",height(root));
   printf("Average height=%d;\n",avg_height());
   printf("Checksum=%d;\n",checksum(root));
   
	getchar();

   return 0;
}
void put(int left_right) //1- left, 2- right.
{
	vertex * leaf= new vertex;		//Create new vertex
	i++;
	leaf->Data=rand();
	leaf->left=leaf->right=NULL;	//with pointers to NULL
	if (left_right==0) 
	{
		last_leaf->left=leaf;
	} else {
		last_leaf->right=leaf;
	}
	last_leaf=leaf;
}
void push(int a, vertex **t)
{
    if ((*t)==NULL) //If the tree does not exist
    {
        (*t)=new vertex;   //Allocate memory
        (*t)->Data=rand(); //Place argument a in the allocated place
        (*t)->left=(*t)->right=NULL;	//Clear memory for next growth
        return;							//We planted a seed, let's go out
    }
       //There is a tree
        if (a=1) push(a,&(*t)->right);	//If argument a is greater than the current element, put it to the right
        else push(a,&(*t)->left);		//Otherwise we put it to the left
}
void left_to_right(vertex *P)
{
	
	if (P!=NULL)
	{
		left_to_right(P->left);
		if (!toggle) {
			printf("%d",P->Data);
			toggle=true;
		} else 
		printf(", %d",P->Data);
		left_to_right(P->right);
	}
}
int  size(vertex *P)
{
	if (P==NULL) {
		return 0;
	} else {
		int temp=1+size(P->left) + size(P->right);
		return temp;
	}
}
int  height(vertex *P)
{
	if (P==NULL) {
		return 0;
	} else {
		int temp=1+max(height(P->left), height(P->right));
		return temp;
	}
}
int  BST(vertex *P, int L)
{
	if (P==NULL) {
		return 0;
	} else {
		int temp=L+BST(P->left, L+1)+BST(P->right, L+1);
		return temp;
	}
}
int  avg_height()
{
	int temp= BST(root, 1)/size(root);
	return temp;
}
int  checksum(vertex *P)
{
	if (P==NULL) {
		return 0;
	} else {
		int temp = P->Data+checksum(P->left)+checksum(P->right);
		return temp;
	}
}