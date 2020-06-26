// header file
#define CHAR_SIZE 55
#define RED "\e[1;31m"    //Error messages
#define RESET "\x1b[0m"   //reset to white
#define BLUE "\x1b[37m"   //Normal messages
#define YELLOW "\x1b[33m" //warning messages
#define GREEN "\x1b[34m"  // success

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
int insert(trie *root, char name[], char phone_num[]);
void display(trie *, char *, int);
void write_to_file(contact new);
int modify_contact(trie *);
