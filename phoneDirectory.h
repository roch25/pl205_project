// header file
#define CHAR_SIZE 55

struct trie
{
  struct trie *next[CHAR_SIZE];
  int isLeaf;
};
typedef struct trie trie;

struct contact
{
  trie *name;
  char phone_number[3][20];
};
typedef struct contact contact;

int add_contact();
int validate_phone_number(char value[]);
int write_to_file(contact *new);
int insert(trie *root, char name[]);
