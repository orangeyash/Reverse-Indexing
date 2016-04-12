#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "header.h"

node* head = NULL;
node* last = NULL;
int num_words = 0;

void fileHandle(int argc, char **argv)
{
	if (argc < 2 )
	{
		fprintf (stderr, "Error: insufficient input, usage: %s filename\n", argv[0]);
		return ;
	}
	char data[max_word_length];
	char line[max_story_words] = {0};
	char *p;
	char *punct="\n ,!.:;?-";
	FILE *file_story = fopen (argv[1], "r");

	if (file_story==NULL)
	{
		printf("Unable to open '%s'\n",argv[1]);
	return ;
	}

	/* you already read file_story to EOF, so you must rewind to
		reset the EOF condition and place the file pointer at the start */
	rewind (file_story);

	
	/* read each line in file */
	while (fgets (line, max_word_length, file_story) != NULL) 
	{
		/* tokenize line into words removing punctuation chars in punct */
		for (p = strtok (line, punct); p != NULL; p = strtok (NULL, punct))
		{
			char *c = p;       /* save start address of p */
			for (; *c; c++)
				if ('A' <= *c && *c <= 'Z')
					*c += 32;

			if(p[0] != 13 && p[0] != 0)
			{
				strcpy(data,p);
				//printf("%s\n",data);
				insertLast(data);
			}
		}
	}
	display();
	printf("Total words: %d\n",num_words);
	return ;

}

void insertLast(char* data)
{
	node* temp = NULL;
	node* q=head;
	node* p= NULL;
	int checker;
	temp = create(temp,data);
	checker = stop(temp);
	if(checker == 1)
	{
		while((q != NULL) && (strcmp (q -> data, data) < 0))//traversing
		{
				p=q;
            q=q->next;
		}
		if(q == NULL)
		{
			if(p== NULL)//list is empty
			{
				head = temp;
				last = head;
			}
			else//insert last
			{
				p -> next = temp;
				last = temp;
			}
		}
		else
		{
			if(p== NULL)
			{
				temp -> next = q;
				head = temp;
			}
			else
			{
				p -> next = temp;
				temp -> next = q;
			}
		}
	}
}

node* create(node* temp,char* data)
{
	temp = (node*)malloc(sizeof(node));
	temp->prev = NULL;
	temp->next = NULL;
	strcpy(temp -> data, data);
	return temp;
}

int stop(node* temp)
{
	char keys[][max_word_length] = {"the", "a", "there", "answer", "any", "if", "and", "no", "had",
                     "by", "bye", "their", "i", "am", "is", "who", "where", "was"};
	int i;
	int total = (sizeof(keys) / max_word_length);
	for(i=0;i<total;i++)
	{
		//printf("%s ",temp->data);
		if(strcmp(keys[i], temp->data) == 0)
		{
			//printf("%s\n", temp->data);
			return -1;
		}
	}
	num_words++;
	return 1;
}

void display()
{
 	 node* temp = head;
    if (temp == NULL)
    {
        printf("\nList empty to display ");
        return;
    }
    printf("\nLinked list elements from begining : ");
 
    while (temp->next != NULL)
    {
        printf("\n %s ", temp->data);
        temp = temp->next;
    }
    printf("\n %s \n", temp->data);
}
