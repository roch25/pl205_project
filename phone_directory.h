// header fill
struct trie
{
  char value;
  struct trie *next[26];
};
typedef struct trie trie;
