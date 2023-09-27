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
    int Data;			  //
    vertex *left, *right; //
};
const int n=10;
bool toggle= false;	//For "friendly" interface
vertex * root;		//= new	vertex;		//Root vertex
vertex * last_leaf= new	vertex;
vertex * turn= new vertex;	


//Lab2 data segment
int C=0;		//Number of comparisons
int  arr[n];	//Source array

//End data segment

vertex * hbst(int L, int R);	//Height-balanced binary search tree
void RST (int D, vertex ** root);
bool st(vertex * p);
bool search (vertex * root, int X);

void put(int left_right);
int  size(vertex *P);			//of tree
int  height(vertex *P);			//of tree
int  RST(vertex *P, int L);		//balanced search tree
int  avg_height();				
void left_to_right(vertex *P);	//Tree traversal
int checksum(vertex *P);		//
int  main    (int argc, char* argv[])
{
   // Seed the random-number generator with the current time so that
   // the numbers will be different every time we run:
   srand( (unsigned)time( NULL ) );
   //Initialize array
   for	(int i=0; i<n; i++)
   {
	   arr[i]=i;
	   //printf(" %d ", arr[i]);
   }
  printf("\n");
  
  //Height balanced search tree 
  root=hbst(0, n-1);
  printf("\n"); left_to_right(root); printf("\n");
  printf("\nSearch tree=%d;\n", st(root));
  printf("\nSearch result=%d;\n", search(root, 5));
  printf("\nHeight=%d; Comparison operations count=%d; Cmax=%f\n", height(root), C, 2*log((float)n+1)/log((float)2));
  printf("\nAverage height=%d\n", avg_height());
  //End Height balanced search tree 
  printf("\n\n-------------------------------------------------\n\n");
  
  //Random search tree
  root=NULL; C=0;
  for (int i=0; i<n; i++)
  {
	  RST(i, &root);
  }
  // 
  left_to_right(root); printf("\n");
  printf("\nSearch tree=%d;\n", st(root));
  printf("\nSearch result=%d;\n", search(root, 5));
  printf("\nAverage height=%d\n", avg_height());
  printf("\nHeight=%d; Comparison operations count=%d; Cavg=%f\n", height(root), C, 1.386*log((float)n)/log((float)2));
  //END random search tree

  //int temp2 = size(root);
  //printf("\nSize=%d\n", temp2);
  //printf("Average height=%d;\n", avg_height());
  getchar();

  return 0;
}

//Lab 2 segment
vertex * hbst(int L, int R)//Height-balanced binary search tree
{
	if (L>R) return NULL;
	else
	{
		int m=(L+R)/2;
		vertex * p= new	vertex;
		p->Data=arr[m];
		p->left=hbst(L, m-1);
		p->right=hbst(m+1, R);
		return p;
	}
}
void RST (int D, vertex ** root)
{
	vertex ** p=  root;
	while ((*p) != NULL)
	{
		if (D<(*p)->Data) 
		{
			p=&((*p)->left);
		} 
		else if (D>(*p)->Data)
		{
			p=&((*p)->right);
		}
		else
		{
			break;
		};
	}
	if ((*p) == NULL)
	{
		(*p)= (vertex*) malloc (sizeof(vertex));
		(*p)->Data=D;
		(*p)->right=NULL;
		(*p)->left=NULL;
	}
}
bool st(vertex *p)
{
	return true;

	if (p != NULL && ((p->Data <= p->left->Data || st(p->left))) || (p->right!=NULL && (p->Data >= p->right->Data || !st(p->right))))
	{
		return false;
	}
}
bool search (vertex * root, int X)
{
	vertex * p= new vertex;
	p=root;
	while (p!=NULL)
	{
		
		if (p->Data<X) { p=p->right;  C++;}
		else if (p->Data>X) {p=p->left; C++; C++; }
		else { C++; C++; C++; break; }
	}
	if (p != NULL) return true;
	else return false;
}
//end lab 2 segment

void put(int left_right) //1- left, 2- right.
{
	vertex * leaf= new vertex;		//Create new vertex
	//i++;
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
int  RST(vertex *P, int L)
{
	if (P==NULL) {
		return 0;
	} else {
		int temp=L+RST(P->left, L+1)+RST(P->right, L+1);
		return temp;
	}
}
int  avg_height()
{
	int temp= RST(root, 1)/size(root);
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
