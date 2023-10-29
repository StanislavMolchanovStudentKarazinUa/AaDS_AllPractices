#include <iostream>
#include <string>
using namespace std;

struct t_tree {
    int info;
    t_tree* left;
    t_tree* right;
};
typedef t_tree* ptree;

ptree formTree()
{
    ptree t;
    string info;
    cin >> info;
    if (info == "x")
        return NULL;
    t = new t_tree;
    t->info = stoi(info);
    t->left = formTree();
    t->right = formTree();
    return t;
}
void freeTree(ptree t) {
    if (t != NULL) {
        freeTree(t->left);
        freeTree(t->right);
        delete t;
    }
}

int main(){

}
