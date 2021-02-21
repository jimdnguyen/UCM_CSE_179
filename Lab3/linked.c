#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

#ifndef N
#define N 5
#endif
#ifndef FS
#define FS 38
#endif

struct node {
   int data;
   int fibdata;
   struct node* next;
};
// from OpenMp 3.1 standard exA. 15.4C
int fib(int n) {
   int x, y;
   if (n < 2) {
      return (n);
   } else {
      //#pragma omp task shared(x)
         x = fib(n - 1);
      //#pragma omp task shared(y)
         y = fib(n - 2);
      //#pragma omp taskwait
	      return (x + y);
   }
}

void processwork(struct node* p) 
{
   int n;
   n = p->data;
   p->fibdata = fib(n);
}

struct node* init_list(struct node* p) {
    int i;
    struct node* head = NULL;
    struct node* temp = NULL;
    
    //head = malloc(sizeof(struct node));
    head = (struct node *)malloc(sizeof(struct node));
    p = head;
    p->data = FS;
    p->fibdata = 0;
    for (i=0; i< N; i++) {
       //temp  = malloc(sizeof(struct node));
       temp = (struct node *)malloc(sizeof(struct node));
       p->next = temp;
       p = temp;
       p->data = FS + i + 1;
       p->fibdata = i+1;
    }
    p->next = NULL;
    return head;
}

int main(int argc, char *argv[]) {
   omp_set_num_threads(4);
     double start, end;
     struct node *p=NULL;
     struct node *temp=NULL;
     struct node *head=NULL;
     struct node *parr[100];
     int i, counter = 0;
     
     printf("Process linked list\n");
     printf("  Each linked list node will be processed by function 'processwork()'\n");
     printf("  Each ll node will compute %d fibonacci numbers beginning with %d\n",N,FS);      
 
     p = init_list(p);
     head = p;

     start = omp_get_wtime();

      /*                           This is the serial code
     {
        while (p != NULL) {
		   processwork(p);
		   p = p->next;
        }
     }
     */
 
    ///*                             Parallelize the program using loop worksharing contructs
      while (p != NULL) {
		   p = p->next;
         counter++;
        }

        p = head;
      
      for(i = 0; i < counter; i++){
         parr[i] = p;
         p = p->next;
      }

      #pragma omp parallel for
         for(i = 0; i < counter; i++){
            processwork(parr[i]);
         }

     //*/
    /*
      #pragma omp parallel      //Parallelize program using OpenMP Tasks
      {
         #pragma omp single
         {
            p = head;
            while(p){
               #pragma omp task firstprivate(p)
               {
                  processwork(p);
               }
               p = p->next;
            }
         }
      }
      */

     end = omp_get_wtime();
     p = head;
	 while (p != NULL) {
        printf("%d : %d\n",p->data, p->fibdata);
        temp = p->next;
        free (p);
        p = temp;
     }  
	 free (p);

     printf("Compute Time using loop worksharing constructs: %f seconds\n", end - start);

     return 0;
}

