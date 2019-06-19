/*
文字列集合Sを管理し、以下のクエリにO(|t|)で答える
- 検索クエリ：文字列 t が含まれるか？
- 追加クエリ：文字列 t を追加する
- 削除クエリ：文字列 t を削除する
- prefixクエリ：文字列 t をprefixとしてもつものがいくつあるか？
- 辞書順前後クエリ：文字列 t の辞書順で次/前であるような文字列はなにか？
- LCPクエリ：文字列 t とのLCPが最大になるような文字列はなにか？
- 辞書順クエリ：文字列 t は辞書順で何番目か？
また、以下のクエリにも対応する
- 辞書順クエリ2：辞書順で N 番目の文字列はなにか？
*/

#include<iostream>
#include<vector>
#include<string>
#include<map>
using namespace std;

class TrieTree{
private:
    struct Node{
        map<char,Node*> child;
        Node* parent = nullptr; //親のノード
        int self = 0; //自身で終わる文字列がいくつあるか
        int children = 0; //子孫で終わる文字列がいくつあるか
        int ind = -1; //先頭から何文字目か
        char ch = '*';
    };

    Node* root;

    void print_dfs(Node* node,string s){
        for(int i = 0; i < node->ind; i++)cout << "-";
        cout << node->ch << "(" << node->self << "," << node->children << ")";
        if(node->self)cout << " " << s;
        cout << endl;
        for(auto itr = node->child.begin(); itr != node->child.end(); itr++){
            print_dfs(itr->second,s+itr->first);
        }
    }

public:
    TrieTree(){
        root = new Node;
        root->ind = 0;
    }
    TrieTree(vector<string> &vs){
        root = new Node;
        root->ind = 0;
        for(int i = 0; i < vs.size(); i++){
            insert(vs[i]);
        }
    }
    int insert(string s){
        Node* node = root;
        node->children++;
        for(int i = 0; i < s.size(); i++){//nodeとs[i]が対応してる
            auto itr = node->child.find(s[i]);
            if(itr == node->child.end()){//ノードが存在しない
                node->child[s[i]] = new Node;
                itr = node->child.find(s[i]);
                itr->second->parent = node;
                node = itr->second;
                node->ind = i+1;
                node->ch = s[i];
            }else{//たどる
                node = itr->second;
            }
            node->children++;
        }
        return ++node->self;//追加後のsの数
    }
    int erase(string s){
        Node* node = root;
        for(int i = 0; i < s.size(); i++){//nodeとs[i]が対応してる
            auto itr = node->child.find(s[i]);
            if(itr == node->child.end()){//ノードが存在しない
                return -1;
            }else{//たどる
                node = itr->second;
            }
        }
        if(node->self == 0)return -1;
        int ret = --node->self;
        while(true){
            node->children--;
            if(node->children == 0 && node != root){
                char c = node->ch;
                node = node->parent;
                delete(node->child[c]);//ノードの削除
                node->child.erase(c);//mapの削除
            }else{
                if(node == root)break;
                node = node->parent;
            }
        }
        return ret;//削除後のsの数(sが存在しない場合は-1を返す)
    }

    void print(void){
        print_dfs(root,"");
    }
};

int main(){
    TrieTree trie;
    trie.insert("ba");
    trie.insert("abcde");
    trie.insert("ab");
    trie.insert("ba");
    trie.print();
    cout << trie.erase("ba") << endl;
    trie.print();
}
