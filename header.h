#ifndef header_h
#define header_h
#define max_story_words 1000
#define max_word_length 100
typedef struct node
{
    struct node *prev;
    char data[max_word_length];
    struct node *next;
} node;
void insertLast(char* data);
void display();
node* create(node* temp,char* data);
int stop(node* temp);
void fileHandle(int argc, char **argv);

#endif
