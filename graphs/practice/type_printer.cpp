
/*
  given a N words you have to minimize the number of operations, printing can be
  done in any order. Even if you have all words in a trie, how do you know from
  where to start and how to traverse it. where I'm stuck is: after storing words
  in trie, I found it is beneficial to print words that are near the parents
  first before going down the path, since we remove letters unnecessarily.

  if we assume the type printer should have no letters at the end, then the
  number of operations are equal, we can use dfs without worrying about the
  order.
*/
#include <cassert>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

// ToDo: create a Trie Iterator
using namespace std;
vector<char> container;
struct Trie {
  bool isEnd;
  unordered_map<char, Trie *> next;
  bool isSpecial;

public:
  Trie() : isEnd(false), isSpecial(false), next() {}
  Trie(const Trie &) = delete;
  Trie(Trie &&) = delete;

  void addWord(const string &word);
  bool searchWord(const string &word);
  void markNode(const string &word);
  void dfs();
};

// O(length(word)) * N
void Trie::addWord(const string &word) {
  Trie *curr = this;
  for (auto &ch : word) {
    auto it = curr->next.find(ch);
    if (it == curr->next.end()) {
      // create a new node.
      Trie *node = new Trie();
      curr->next[ch] = node;
    }
    curr = curr->next[ch];
  }
  curr->isEnd = true;
}

// O(length(word)) * N
bool Trie::searchWord(const string &word) {
  Trie *curr = this;
  for (auto &ch : word) {
    auto it = curr->next.find(ch);
    if (it == curr->next.end())
      return false;
    curr = it->second;
  }
  return curr->isEnd;
}

void Trie::markNode(const string &word) {
  Trie *curr = this;
  for (auto &ch : word) {
    auto it = curr->next.find(ch);
    if (it == curr->next.end())
      assert(false);
    curr = it->second;
    curr->isSpecial = true;
  }
}

void Trie::dfs() {
  unordered_map<char, Trie *>::iterator specialChild = next.end();
  if (isEnd)
    container.push_back('P');
  for (unordered_map<char, Trie *>::iterator it = next.begin();
       it != next.end(); it++) {
    if (it->second->isSpecial) {
      specialChild = it;
      continue;
    }
    container.push_back(it->first);
    it->second->dfs();
  }
  if (specialChild != next.end()) {
    container.push_back(specialChild->first);
    specialChild->second->dfs();
  }
  container.push_back('-');
}

int main() {
  Trie *root = new Trie();
  /*
  vector<const string> words{"canwatch", "watch", "prefix", "prefixOf"};

  for (auto const &ch : words)
    root->addWord(ch);

  for (auto const &ch : words)
    cout << root->searchWord(ch);
  cout << root->searchWord("canw");

  root->markNode("canwatch");
  root->dfs();
  */
  int n, len = 0;
  cin >> n;
  string word, bigword;
  while(n-- > 0) {
    cin >> word;
    root->addWord(word);
    if (word.size() > len) {
      len = word.size();
      bigword = word;
    }
  }
  root->markNode(bigword);
  root->dfs();

  while (container.back() != 'P')
    container.pop_back();

  cout << container.size();
  cout << "\n";
  for (auto &p : container)
    cout << p << "\n";
  return 0;
}