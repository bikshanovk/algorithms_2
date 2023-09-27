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
#include <clocale>
#include <time.h>
#include <Windows.h>
#include <stdlib.h>
struct locality 
	{
		struct locality *next;
		unsigned char Name [32];
		unsigned char addr [20];
		int house;
		int room;
		char date[8];
	};
struct vertex
{
int Data;
unsigned char key [3];			//Search key.
vertex *left, *right;			//
	int balance;
	bool VR, VH;
};

unsigned char key [3];			//Search key
	
const int L=7;					//Sorting mask lenght
const int m=255;				//For digital sort
locality * head, *tail, *S, *p,  *pred, *Q_head[m], *Q_tail[m], *temp, tmp;
const int lenght=4000;			//Amount of DB
struct locality Array[lenght];	//Index array
int  d=0, C, M;					
FILE *tf;						//Pointer to DB
struct vertex * root, * root2;

void init_digital_sort (struct locality **head) //Prepare data for:
{
	struct locality *p; 
	*head=pred=p=(locality *)malloc(sizeof(locality));
	//Fill with data to p structure:
	int	k=0;
	for (int i=0; i<64; i++)
	{
		if (i>=0 && i<52)
		{
			p->Name[i]=getc(tf);
		}
		
		else if (i==52) {p->house = getc(tf);}
		else if (i==54) {p->room = getc(tf);}

		else if (i>55)  {p->date[k]=getc(tf); k++;}
		else  getc(tf);
	}
	//END Fill with data to p structure:
	for (int i=1; i<lenght; i++)
	{
		p=(locality *)malloc(sizeof(locality));
	//Fill with data p structure:
	int	k=0;
	for (int i=0; i<64; i++)
	{
		if (i>=0 && i<52)
		{
			p->Name[i]=getc(tf);
		}
		
		else if (i==52) {p->house = getc(tf);}
		else if (i==54) {p->room = getc(tf);}

		else if (i>55)  {p->date[k]=getc(tf); k++;}
		else  getc(tf);
	}
	//END Fill with data to p structure:
		pred->next=p;
		pred=p;
	}
	p->next=NULL;
	tail=p;
}

void print_digital_sort (struct locality *head)
{
	struct locality *p;
	p=head;
	while (p->next!=NULL)
	{
		for (int j=0; j<52; j++)
		{
			printf ("%c", p->Name[j]);
		}
		printf ("%2d %3d ",  p->house, p->room); 
		for (int j=0; j<8; j++)
		{
			printf ("%c", p->date[j]);
		}
		printf("\n");
		p=p->next;
	}
//	p=p->next;
	for (int j=0; j<52; j++)
		{
			printf ("%c", p->Name[j]);
		}
		printf ("%2d %3d ",  p->house, p->room); 
		for (int j=0; j<8; j++)
		{
			printf ("%c", p->date[j]);
		}
		printf("\n");	
}

void digital_sort ()
{
	for (int j=L-1; j>=0; j--)			//Modified++++++++++++++++
	{
		//Initialisation of m queues:
		for (int i=0; i<m; i++)
		{
			Q_head[i]=(Q_tail[i]=NULL);
		}
		p=S;
		//Divide source list to m queues:
		while (p!=NULL)
		{
			//Modified++++++++++++++++++++++++++++++++++++++++++++++
			//Search mask:
			if (j>=4 && j<=6)			//
				d=p->addr[j-4];			//Street
			else if (j>=0 && j<=2)		//
				d=p->Name[j];			//Credentials
			else d=p->house;			//House #
			//Modified++++++++++++++++++++++++++++++++++++++++++++++
			
			temp=Q_tail[d];
			if (Q_head[d]==NULL) Q_head[d]=p;
			else temp->next=p;
			temp=Q_tail[d]=p;
			p=p->next;
			temp->next=NULL;
		}
		p=S;
		//Create new list using m queues:
		p=(S=NULL);
		for (d=0; d<m; d++)
		{
			if (Q_head[d]!=NULL) break;
		}
		p=Q_head[d];
		temp=Q_tail[d];
		for (int k=d+1; k<m; k++)
			{
				if (Q_head[k]!=NULL){
				temp->next=Q_head[k];
				temp=Q_tail[k];
				}
			}
		temp->next=NULL;
		S=p;
	}
}

void BBtree (int D, vertex ** p)
{
	bool VR; 
	bool HR;
	VR=HR=true;
	if ((*p)==NULL)
	{
		(*p)= (vertex*) malloc (sizeof(vertex));
		//(*p)->count=1;
		//ADD search key value to the tree:
		int i=0;
		for (int j=0; j<32; j++)
			if (Array[D].Name[j]>=128 && Array[D].Name[j]<=159)
				{
					(*p)->key[i]=Array[D].Name[j];
					i++;
				}
		//END ADD
		//ADD data to tree:
			(*p)->Data=D;
		(*p)->left=(*p)->right=NULL;
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

int  size(vertex *P)
{
	if (P==NULL) {
		return 0;
	} else {
		int temp=1+size(P->left) + size(P->right);
		return temp;
	}
}

void search (vertex *P)
{
	if (P!=NULL)
	{
	//Tree round
		search(P->left);
		if (P->key[0]==key[0] && P->key[1]==key[1] && P->key[2]==key[2])
			{
				//Continue search Build queue
				if (S==NULL) S=pred=&Array[P->Data];
				else 
				{
					pred->next=&Array[P->Data];
					pred=&Array[P->Data];

				}

			}
		search(P->right);
	}
}

int  main    (int argc, char* argv[])
{
	//locality  
	//locality p = (locality)malloc(sizeof(locality));
	//p=NULL;
	using namespace std;
	locality * head=NULL;
	char temp;
	
	tf=fopen ("base4.dat","r");

	//Initialize queue:
	init_digital_sort (&S);
//print_digital_sort(S);
	digital_sort();
//Prepare Array:
pred=S;
tmp=*S;
	for (int i=0; i<lenght-1; i++)
	{
		Array[i]=tmp;
		tmp=*tmp.next;
	}
	Array[lenght-1]=tmp;
//END Prepare index Array.

	free(S); free (tail);// free(Q_head); free(Q_tail);
//Build B-tree:
	do
	for (int i=0; i<lenght; i++)
	{
		BBtree(rand() % lenght, &root);
	}

	while (size(root)!=lenght);
//END Build B-tree.

//Search in tree segment;
	key[0]=128; key[1]=128; key[2]=128; //Initialize search key
	S=NULL;								//Initialize search result queue
	
	//Start build search queue:
	search(root);
	pred->next=NULL; 
	//End build search queue.
//END Search in tree segment.
	print_digital_sort(S);

	//fread(&p,sizeof(p),1,tf);
	fclose(tf);
	getchar();
  return 0;
}

