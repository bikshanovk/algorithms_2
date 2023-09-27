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
	int balance;
	int count;
};
const int n=50;
bool toggle= false;				//For "friendly" interface
vertex * root;//= new	vertex;		//Root vertex
vertex * last_leaf= new	vertex; //
vertex * turn= new vertex;

//Lab3 data segment

//End data segment

//Lab2 data segment
int C=0;		//Number of comparisons
int  arr[n];	//Source array
//End data segment

void search (int x, vertex ** p, bool & h);

vertex * hbst(int L, int R);	//Height-balanced binary search tree
void RST (int D, vertex ** root);
bool st(vertex * p);
//bool search (vertex * root, int X);

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

  //LAB 3
  root=NULL; 
  bool tmp=false;
	  for (int i=0; i<n; i++)
  {
	  search(rand()+n, &root, tmp);
  }
 
  printf ("\nSt=%d\n", st(root));
  printf ("\nAvg_Height=%d\n", avg_height());
  printf ("\%f<=Havr>=%f\n", log((float)n+1)/log((float)2), 1.44*log((float)n+2)/log((float)2)-0.328);
  printf ("\nCavg=%f\n", (float)C/n);
  left_to_right(root);

  //END LAB 3

  getchar();

  return 0;
}

//Lab3 Segment

void search (int x, vertex ** p, bool & h)
{
	vertex * p1;// = new vertex;
	vertex * p2;// = new vertex;
	
	if ((*p)==NULL) 
	{
		(*p)= (vertex*) malloc (sizeof(vertex));
		(*p)->count=1;
		(*p)->Data=x; (*p)->left=(*p)->right=NULL;
		(*p)->balance=0; h=true;
	}
	else if ((*p)->Data>x)
	{
		search(x, &((*p)->left), h);
		if (h)//Left tree has grown
		{
			switch ((*p)->balance)
			{
				case 1: (*p)->balance=0; h=false; break;
				case 0: (*p)->balance=-1; break;
				case -1: //Balance reuired:
					p1=(*p)->left;
					if (p1->balance==-1)//Signle LL-turn
					{
						C++;
						(*p)->left=p1->right; p1->right=(*p);
						(*p)->balance=0; (*p)=p1;
					}
					else //Double LR-turn
					{
						C++;
						p2=p1->right;
						p1->right=p2->left; p2->left=p1;
						(*p)->left=p2->right; p2->right=(*p);
						if (p2->balance==-1) (*p)->balance=1; else (*p)->balance=0;
						if (p2->balance==1) p1->balance=-1; else p1->balance=0;
						(*p)=p2;
					}
					(*p)->balance=0; h=false;
					break;
			}
					
		}
	}
	else if ((*p)->Data<x)
	{
		search(x, &((*p)->right), h);
		if (h)//Left tree has grown
		{
			switch ((*p)->balance)
			{
			case 11: (*p)->balance=0; h=false; break;
			case 0: (*p)->balance=1;break;
			case 1: //Balance reuired:
					p1=(*p)->right;
					if (p1->balance==1)//Signle RR-turn
					{
						C++;
						(*p)->right=p1->left; p1->left=(*p);
						(*p)->balance=0; (*p)=p1;
					}
					else //Double RL-turn
					{
						C++;
						p2=p1->left;
						p1->left=p2->right; p2->right=p1;
						(*p)->right=p2->left; p2->left=(*p);
						if (p2->balance==1) (*p)->balance=-1; else (*p)->balance=0;
						if (p2->balance==-1) p1->balance=1; else p1->balance=0;
						(*p)=p2;
					}
					(*p)->balance=0; h=false; break;
			}
		}
	}
	else (*p)->count++;
}
//End lab3 segment

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
//bool search (vertex * root, int X)
//{
//	vertex * p= new vertex;
//	p=root;
//	while (p!=NULL)
//	{
//		
//		if (p->Data<X) { p=p->right;  C++;}
//		else if (p->Data>X) {p=p->left; C++; C++; }
//		else { C++; C++; C++; break; }
//	}
//	if (p != NULL) return true;
//	else return false;
//}
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