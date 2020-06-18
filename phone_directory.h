// header fill

struct trie
{
  char value;
  struct trie *next[26];
};
typedef struct trie trie;

struct contact
{
  trie name;
  int phone_number[3][12];
};
typedef struct contact contact;