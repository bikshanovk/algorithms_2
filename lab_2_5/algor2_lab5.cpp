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

struct A
{
	int Data;
	bool use;
	int w;
};

struct vertex
{
    int Data;			  //
    vertex *left, *right; //
	struct A V;
};

const int n=400;
bool toggle= false;				//For "friendly" interface
vertex * root;//= new	vertex;		//Root vertex

//LAB5 segment
A  V[n];
void A1 (vertex ** root);
void RST (A V, vertex ** root);		//balanced search tree
void A2 (vertex ** root, int L, int R);
int h_avg ();
int P (vertex * p, int Lev);
int W (A * V);
//END LAB5 Segment

//Test Segment

//end test segment

void left_to_right(vertex *P);	//Tree traversal

int  main    (int argc, char* argv[])
{
  // Seed the random-number generator with the current time so that
  //the numbers will be different every time we run:
  srand( (unsigned)time( NULL ) );
	
	//LAB5 A1 Algor
	vertex * root;
	root=NULL;
	int tmp=n;
	for (int i=0; i<n; i++)
	{
		V[i].Data= i;
		V[i].w=1 + rand () % n;
		tmp--;
	}
	A1(&root);

	//left_to_right(root);

	float del = P(root, 1);
	float delt = W(V);
	float result = del/delt;
	printf ("\nResult A1=%f\n", result);
////	
////	//END LAB5 A1 Algor

	//LAB5 A2 Algor
	root=NULL;
	tmp=n;
	for (int i=0; i<n; i++)
	{
		//Init array:
		V[i].use= false;
	}
	A2(&root, 0, n-1);
	
	del = P(root, 1);
	delt = W(V);
	result = del/delt;
	printf ("\nResult A2=%f\n", result);
	
	//END LAB5 A2 Algor
  getchar();
  return 0;
}

//LAB5 segment
void RST (A V, vertex ** root)
{
	int D=V.Data;
	
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
		(*p)->V.w=V.w;
		(*p)->right=NULL;
		(*p)->left=NULL;
	}
}
void A1 (vertex ** root)
{
	(*root)=NULL;
	for (int i=0; i<n; i++)
	{
		V[i].use=false;
	}
	for (int i=0; i<n; i++)
	{
		int max=0; int index=0;
		for (int j=0; j<n; j++)
		{
			if(V[j].w>max && V[j].use==false)
			{
				max=V[j].w;
				index=j;
			}
		}
		V[index].use=true;
		RST(V[index], &(*root));
	}
}
void A2 (vertex ** Root, int L, int R)
{
	float wes=0; float summa=0;
	if (L<=R)
	{
		for (int i=L; i<=R; i++)
		{
			wes=wes+V[i].w;
		}
		int i=L;
		for (i=L; i<=R; i++)
		{
			if ((summa<(wes/2)) && (summa+V[i].w>=(wes/2))) break;
			summa=summa+V[i].w;
		}
		RST(V[i], &(*Root));
		A2(&(*Root), L, i-1);
		A2(&(*Root), i+1, R);
	}
}
int P (vertex * p, int  Lev)
{
	if (p==NULL)
		return 0;
	else
	{
		int temp= Lev*p->V.w + P(p->left, Lev+1) + P(p->right, Lev+1);
		return temp;
	}
}
int h_avg ()
{
	int temp= P(root, 1);
	return temp;
}
int W (A * V)
{
	int temp=0;
	for ( int i=0; i<n; i++)
	{
		temp = temp + V[i].w;
	}
	return temp;
}
//END LAB5 Segment
