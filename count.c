#include<stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[]){
	
	FILE *fp;
	char *name = argv[1];
	fp=fopen(name, "r");
	int count=0;
	
	struct node{
		unsigned long num; //data
		struct node *next; //points to next node
	}node;

	struct node* hash[1000]={NULL}; //Create the hashtable. Size 1000. Everything is set to NULL
	
	if(!fp){ //If file doesn't exist
		printf("error\n");
		return 1;
	}
		
	while(1){
		
		char hex[64]; 
		fscanf(fp,"%s",hex);//read in hex as string(array of chars)
		
		if(feof(fp)){ //break at end of text file
			printf("%d\n",count);
			return 1;
		}
		
		//printf("%s\n",hex);
		unsigned long n = strtoul(hex, NULL, 16); //Convert hex to decimal
		//printf("%lu\n", n);
		
		struct node *insert;
		insert=(struct node*)malloc(sizeof(struct node)); //Create node that we want to insert into hash table
		insert->num=n;
		insert->next=NULL;
		//printf("Insert num:");
		//printf("%lu\n",insert->num);  ***%lu
		
		int pos=n%1000; //Hash Function, gives us position of number in hash table
		//printf("position: ");
		//printf("%d\n",pos);
		
		if(hash[pos]==NULL){ //If null, insert into front of LL at hash[pos]
			hash[pos]=insert;
			//printf("inserted\n");
			count++;
		}
		
		else{
			//printf("Number at front of hash table: ");
			//printf("%lu\n",hash[pos]->num);
			
			
			struct node *ptr; //Pointer that will traverse the linked list
			ptr=(struct node*)malloc(sizeof(struct node)*10);
			ptr=hash[pos]; //Set pointer equal to front of hash position
			
			while(ptr->num!=n){ //Keep traversing LL until you find wanted element
				if(ptr->next==NULL){
					break; //If search is not in LL
				}
				else{ 
				//Advance prev
					ptr=ptr->next; //Advance ptr
				}
			}
			
			if(ptr->num==n){
				//printf("duplicate\n");
				continue;
			}
			else{
				insert->next=hash[pos];
				hash[pos]=insert;
				count++;
				//printf("inserted at front\n"); //This works
				
			}
			}
		}
		
}
