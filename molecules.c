/* The following algorithm represents a chemical molecule in the
form of a linked list. It allows you to create a molucules by adding multiple atoms. 
This information about the type of bond is stored in each node of the linked
list.
*/

#include<stdio.h>
#include<stdlib.h>

struct bondNode;
struct atom;

struct bondNode {
   int strength;
   struct atom *pAtom;
   struct bondNode *pNext;
};

struct atom {
   int atomicNumber;
   struct bondNode *bondList;
};

typedef struct bondNode bondNode;
typedef struct atom atom;
int addBond(atom *pAtom, int strength, atom *pAtom2);
atom *createAtom(int atomicNumber);
int bondList_add(bondNode **ppList, int strength, atom *pAtom);
int printAtom(atom *pAtom,int n);
int printBonds(bondNode *pList,int n);

atom *createAtom(int atomicNumber) {
   atom *p=(atom *)malloc(sizeof(atom));
   p->atomicNumber = atomicNumber;
   p->bondList = NULL;
   return p;
}

int bondList_add(bondNode **ppList, int strength, atom *pAtom) {
   if (ppList == NULL) { return -1; }
   if (*ppList == NULL) {
      *ppList = (bondNode *)malloc(sizeof(bondNode));
      (*ppList)->strength=strength;
      (*ppList)->pAtom=pAtom;
      (*ppList)->pNext=NULL;
      return 0;
   } else {
      return bondList_add( &((*ppList)->pNext), strength, pAtom );
   }
}

int addBond(atom *pAtom, int strength, atom *pAtom2) {
   if (pAtom == NULL) { return -1; }

   return bondList_add( &(pAtom->bondList), strength, pAtom2);
}
int printAtom(atom *pAtom,int n) {
   int i;
   if (pAtom == NULL) {
      printf("black hole sun...\n");
   } else {
      for(i=0;i<n;i=i+1) {
         printf("   ");
      }
      printf("-> atomic number=%d: bonded to:\n",pAtom->atomicNumber);
      printBonds(pAtom->bondList,n);
      for(i=0;i<n;i=i+1) {
         printf("   ");
      }
      printf("<- atomic number=%d\n",pAtom->atomicNumber);

   }
   return 0;
}

int printBonds(bondNode *pList,int n) {
   int i;
   for(i=0;i<n;i=i+1) {
      printf("   ");
   }
   if (pList == NULL) {
      printf("no bonds\n");
   } else {
      printf("strength=%d connected to:\n",pList->strength);
      printAtom(pList->pAtom,n+1);
      printBonds(pList->pNext,n);
   }
   return 0;
int main(void) {
   int r=0;
   atom *S;
   atom *tmp1,*tmp2;

   S = createAtom(16);

   tmp1=createAtom(8);
   r=addBond(S,2,tmp1);

   tmp1=createAtom(8);
   r=addBond(S,2,tmp1);

   tmp1=createAtom(8);
   tmp2=createAtom(1);
   r=addBond(tmp1,1,tmp2);
   r=addBond(S,1,tmp1);

   tmp1=createAtom(8);
   tmp2=createAtom(1);
   r=addBond(tmp1,1,tmp2);
   r=addBond(S,1,tmp1);

   printAtom(S,0);
   return 0;
}
