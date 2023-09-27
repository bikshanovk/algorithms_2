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
//Test Segment
//struct Item
//{
//    int Data;			  //
//	struct page * p;
//};
//struct page
//{
//    int k;			  //
//	struct page * p0;
//	struct Item e[100];
//};
//end test segment
struct vertex
{
    int Data;			  //
    vertex *left, *right; //
	int balance;
	bool VR, VH;
};
const int n=10;
bool toggle= false;				//For "friendly" interface
vertex * root;//= new	vertex;		//Root vertex
//Test Segment
//void Bsearch (int D, page ** a);
//void Bbuilt (int D, page * a, bool Rost, Item * V);
//end test segment
void BBtree (int D, vertex ** P);
int  size(vertex *P);			//of tree
//int  height(page *P);			//of tree
int  RST(vertex *P, int L);		//balanced search tree
int  avg_height(vertex * root);				
void left_to_right(vertex *P);	//Tree traversal
bool st(vertex * p);
int  height(vertex *P);	
//int checksum(vertex *P);		//
int  main    (int argc, char* argv[])
{
  // Seed the random-number generator with the current time so that
  // the numbers will be different every time we run:
  srand( (unsigned)time( NULL ) );
  //LAB 4
  vertex * root;
  root=NULL;

  bool tmp=false;
	for (int i=0; i<n; i++)
	{
		BBtree(rand()+n, &root);
	}
	left_to_right(root);
	printf ("\nSt=%d\n", st(root));
	printf ("\nAverage height=%d\n", avg_height(root));
	printf ("\Theoretical height=%f\n", 2*log((float)n+1)/log((float)2));
	printf ("\nHeight=%d\n", height(root));
	
  //END LAB 4
  getchar();
  return 0;
}

//Lab4 Segment
//void Bsearch (int D, page ** a)
//{
//	int L=0;
//	int R=0;
//	if (a==NULL)
//	{
//		printf("\nKey not found!\n");
//	}
//	else
//	{
//		L=1; R=(*a)->k+1;
//		while (L<R)
//		{
//			int i=(L+R)/2;
//			if ((*a)->e[i].Data<=D) L=i+1;
//			else R=i;
//		}
//		R--;
//		if (R>0 && (*a)->e[R].Data==D) printf("\nKey found!\n");
//		else
//		{
//			if (R==0) Bsearch(D, &(*a)->p0);
//			else Bsearch(D, &(*a)->e[R].p);
//		}
//	}
//}
//void Bbuilt (int D, page ** a, bool & Rost, Item ** V)
//{
//	//int R=0;
//	//int L=0;
//	//if	(a==NULL)
//	//{
//	//	(*V)->Data=D;
//	//	(*V)->p=NULL;
//	//	Rost=true;
//	//}
//	//else 
//	//{
//	//	Bsearch(D, &(*a));
//	//	if	(R>0 && (*a)->e[R].Data==D) //D found in tree
//	//	{
//	//		
//	//	}
//	//	else
//	//	{
//	//		if (R==0) Bbuilt(D, &(*a)->p0, Rost, &u);
//	//		else Bbuilt(D, &(*a)->e[R].p, Rost, &u);
//	//		if (Rost)
//	//		{
//	//			if (&(*a)->k<2*m)
//	//			{
//	//				(*a)->k++;
//	//				for (int i=(*a)->k; i>=R+2; i-- )
//	//				{
//	//					(*a)->e[i]=(*a)->e[i-1];
//	//				}
//	//				(*a)->e[R+1]=u;
//	//			}
//	//		}
//	//		else //Page overfill
//	//		{
//	//			page * b = new page();//Creating new page
//	//			if (R<=m) V=u;
//	//			else
//	//			{
//	//				V=(*a)->e[m];
//	//				for (int i=m; i>=R+2; i--)
//	//				{
//	//					(*a)->e[i]=(*a)->e[i-1];
//	//				}
//	//				for (int i=1; i<=m; i++)
//	//				{
//	//					b->e[i]=(*a)->e[i+m];
//	//				}
//	//			}
//	//		}
//
//	//	}
//	//}
//}
//END Lab4 segment


void BBtree (int D, vertex ** p)
{
	bool VR; 
	bool HR;
	VR=HR=true;
	if ((*p)==NULL)
	{
		(*p)= (vertex*) malloc (sizeof(vertex));
		//(*p)->count=1;
		(*p)->Data=D; (*p)->left=(*p)->right=NULL;
		(*p)->balance=0; (*p)->VR=true;
	}
	else
	{
		if ((*p)->Data>D)
		{
			BBtree(D, &(*p)->left);
			if (VR)
			{
				if ((*p)->balance==0)
				{
//SHoud be debugged
					vertex * q=(*p)->left; (*p)->left=q->right;
					q->right=(*p); (*p)=q; q->balance=1;
					VR=true; HR=false;
				}
				else 
				{
					(*p)->balance=0; HR=true;
				}
			}
			else
			{
				HR=false;
			}
		}
		else if ((*p)->Data<D)
		{
			BBtree(D, &(*p)->right);
			if (VR)
			{
				(*p)->balance=1; VR=false;
				HR=true;
			}
			else if (HR)
			{
				if ((*p)->balance>0)
				{
					vertex * q=(*p)->right;
					(*p)->right=q->left;
					(*p)->balance=0; q->balance=0;
					(*p)->left=(*p); (*p)=q;
					VR=true; HR=false;
				}
				else
				{
					HR=false;
				}
			}
		}
	}
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
int  RST(vertex *P, int L)
{
	if (P==NULL) {
		return 0;
	} else {
		int temp=L+RST(P->left, L+1)+RST(P->right, L+1);
		return temp;
	}
}
int  avg_height(vertex * p)
{
	int temp= RST(p, 1)/n;
	return temp;
}
bool st(vertex *p)
{
	return true;

	if (p != NULL && ((p->Data <= p->left->Data || st(p->left))) || (p->right!=NULL && (p->Data >= p->right->Data || !st(p->right))))
	{
		return false;
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