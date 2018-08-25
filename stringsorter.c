#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
struct node //Node structure used to store our strings
{
	char* info;
	struct node *next;
};
typedef struct node Node;
Node* insertNode(Node*, char*, int);
void printList(Node*);
void freeLinkedList(Node*);
int main(int argc, char ** argv)
{
	if(argc!=2) //Make sure the user enters in the correct number of arguments
    {
		printf("Improper number of arguments\n");
		exit(1);
	}
	char *fullWord = argv[1];
	char *currChar = fullWord;
	int strLength; 	//length of current string component
	strLength=0;
	Node *head = NULL;
	head=(Node*)malloc(sizeof(Node));
	head->info=NULL;
	while(*currChar!='\0') //Until we reach the end of the input
    {
		if(*currChar == '"'){	//Ignore quotation marks
            	continue;
            	}
		while(isalpha(*currChar))
        {		//loop to find length of string component, stringLength
			strLength++;
			currChar=&fullWord[strLength];
			if(*currChar == '\''){
			strLength++;
			currChar=&fullWord[strLength];
			continue;
			}
		}					//strLength now contains number of chars to copy
		if(strLength!=0)
        {
			head=insertNode(head, fullWord, strLength);	//if at least one char was read, add node
			fullWord=&fullWord[strLength];
		}
		else
        {
			fullWord=&fullWord[1];		//if no chars were read, skip non alpabetical char
		}
		
		currChar=&fullWord[0];			//set char = first char in new fullWord addr
		strLength=0;				
    }
	if(head->info!=NULL)
    {
        Node *temp, *prev;
        prev=head;
        temp=head->next;
        while(temp!=NULL)
        {	//loop to find last node which is empty
            prev=prev->next;
            temp=temp->next;
                    //chops off last node
        }
        prev->next=NULL;
        freeLinkedList(temp);
	}
	printList(head);
    freeLinkedList(head);
    head = NULL;
	return 0;
}	//end main
Node* insertNode(Node* head, char* data, int nChars)
{
    if(head->info == NULL) //If we are inserting for the first time
    {
        Node* temp=(Node*)malloc(sizeof(Node));
        temp->info=(char*)malloc((nChars+1)*sizeof(char));
        temp->next=NULL;
        memcpy(temp->info, data, nChars);
        temp->info[nChars]='\0';
        head=temp;
    }
    else
    {
        Node* toInsert = (Node*)malloc(sizeof(Node)); //Node that needs to be put into our linked list
        toInsert->info = (char*)malloc((nChars+1)*sizeof(char)); //Allocate memory and only insert letters and not delimters
        memcpy(toInsert->info, data, nChars);
	toInsert->info[nChars]='\0';
        toInsert->next=NULL;
        Node* cur , *prev;
        cur=head;
        prev=head;
        char* c = (char*)malloc((nChars+1)*sizeof(char));
        c=(char*)memcpy(c, data, nChars);
        c[nChars]='\0';
        int doMiddleInsert = 1; //Check for if we are inserting onto the end or middle of the linked list
        if(strcmp(c, cur->info) < 0) //If the current string comes before the first node
        {
            toInsert->next = head; //Insert as the first node and change the head to the new node
            head = toInsert;
        }
        else //Otherwise the new string belongs after the first node
        {
            while(strcmp(c, cur->info) > 0) //Find the space where the node needs to be put into
            {
                if(cur->next == NULL) //If we are inserting to the end of the linked list
                {
                    doMiddleInsert = 0;
                    cur->next = toInsert; //Attach to the end of the list
                    break;
                }
		if(prev==cur)
                	cur = cur->next; //Continue until we find the proper place to insert
                else{
                	prev=prev->next;
                	cur=cur->next;
                }
            }
            if(doMiddleInsert == 1) //If we have to insert somewhere in the middle of the linked list
            {
                Node *tmp = cur; //Store cur->next temporarily
                prev->next = toInsert; //Insert the new node after cur
                toInsert->next = tmp; //Add the rest of the linked list after the newly inserted node
            }
        }
        free(c);
        //freeLinkedList(toInsert);
        toInsert = NULL;
    }
    return head; //Return our sorted linked list
}
void printList(Node* head) //Run through the list and print it
{
    Node *temp;
    temp=head;
    if(head->info==NULL) //If our list is empty just print a new line
    {
        printf("\n");
    }
    else
    {
        while(temp!=NULL)
        {
            printf("%s\n", temp->info);
            temp=temp->next;
        }
    }
}
void freeLinkedList(Node* head)
{
    Node* tmp;
    while (head != NULL && head->info != NULL)
    {
        tmp = head;
        head = head->next;
        free(tmp);
    }
}
