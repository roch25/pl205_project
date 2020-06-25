// header file
#define CHAR_SIZE 55

struct trie
{
  struct trie *next[CHAR_SIZE];
  int isLeaf;
  char phone_number[3][20];
};
typedef struct trie trie;

struct contact
{
  char name[25];
  char phone_num[12];
};
typedef struct contact contact;

int add_contact(trie *);
int validate_name(char name[25]);
int validate_phone_number(char value[]);
int insert(trie *root, char name[], char phone_num[]);
void display(trie *, char *, int);
void write_to_file(contact *new);
int check_dupilcate_contact_details(char *name, char *phone_num);
