// header file

struct trie
{
  char value;
  struct trie *next[26];
};
typedef struct trie trie;

struct contact
{
  trie name;
  char phone_number[3][20];
};
typedef struct contact contact;

int add_contact();
int validate_phone_number(char value[]);
