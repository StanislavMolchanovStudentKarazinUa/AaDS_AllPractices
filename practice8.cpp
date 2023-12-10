#include <iostream>
using namespace std;

struct ae_tree {        //arithmetic expression tree
    char symbol;
    ae_tree* left = NULL;
    ae_tree* right = NULL;
};
typedef ae_tree* ptree_ae;

struct t_tree {
    int info;
    t_tree* left = NULL;
    t_tree* right = NULL;
};
typedef t_tree* ptree;

//////////////////////////////////////////////////

ptree_ae FormAETree(string ae, int* i = NULL) {
    if (i == NULL) {
        i = new int;
        *i = 0;
    }
    ptree_ae tae = new ae_tree;
    tae->symbol = ae[*i];
    if (ae[*i] == '+' || ae[*i] == '-' || ae[*i] == '*' || ae[*i] == '/') {
        (*i)++;
        tae->left = FormAETree(ae, i);
        tae->right = FormAETree(ae, i);
        (*i)--;
    }
    (*i)++;
    return tae;
}

void displayTLR_AE(ptree_ae ae_tree)             //������ �����
{
    if (ae_tree != NULL)
    {
        cout << ae_tree->symbol;
        displayTLR_AE(ae_tree->left);
        displayTLR_AE(ae_tree->right);
    }
}
void displayLTR_AE(ptree_ae ae_tree)             //����������� �����
{
    if (ae_tree != NULL)
    {
        if (ae_tree->symbol == '*' || ae_tree->symbol == '/') {
            if (ae_tree->left->symbol == '+' || ae_tree->left->symbol == '-'
                || ae_tree->left->symbol == '*' || ae_tree->left->symbol == '/') {
                cout << '(';
                displayLTR_AE(ae_tree->left);
                cout << ')';
            }
            else displayLTR_AE(ae_tree->left);
        }
        else displayLTR_AE(ae_tree->left);
        cout << ae_tree->symbol;
        if (ae_tree->symbol == '*' || ae_tree->symbol == '/') {
            if (ae_tree->right->symbol == '+' || ae_tree->right->symbol == '-'
                || ae_tree->right->symbol == '*' || ae_tree->right->symbol == '/') {
                cout << '(';
                displayLTR_AE(ae_tree->right);
                cout << ')';
            }
            else displayLTR_AE(ae_tree->right);
        }
        else displayLTR_AE(ae_tree->right);
    }
}

//////////////////////////////////////////////////
/*
void insertInSearchTree(ptree* tree, int info)
{
    if (*tree == NULL) { // ���� ������ ������, ��������� �����
        *tree = new t_tree; // ��� ����� �� ����� (������� ����)
        (*tree)->info = info;
    }
    else {
        if (info < (*tree)->info)
            insertInSearchTree(&((*tree)->left), info);
        else
            insertInSearchTree(&((*tree)->right), info);
    }
}

bool deleteFromSearchTree(ptree* tree, int info)
{
    if (*tree == NULL) return false;
    else if ((*tree)->info == info) {
        if ((*tree)->left == NULL) {
            if ((*tree)->right == NULL) {
                delete* tree;
                *tree = NULL;
                return true;
            }
            else {
                ptree tree_ = (*tree)->right;
                (*tree)->info = (*tree)->right->info;
                (*tree)->left = (*tree)->right->left;
                (*tree)->right = (*tree)->right->right;
                delete tree_;
                return true;
            }
        }
        else {
            if ((*tree)->right == NULL) {
                ptree tree_ = (*tree)->left;
                (*tree)->info = tree_->info;
                (*tree)->left = tree_->left;
                (*tree)->right = tree_->right;
                delete tree_;
                return true;
            }
            else {
                ptree* tree_ = &(*tree)->left;
                while ((*tree_)->right != NULL) tree_ = &(*tree_)->right;
                (*tree)->info = (*tree_)->info;
                return deleteFromSearchTree(tree_, (*tree_)->info);
            }
        }
    }
    else {
        if ((*tree)->left == NULL && (*tree)->right == NULL) return false;
        else {
            if (deleteFromSearchTree(&((*tree)->left), info)) return true;
            else if (deleteFromSearchTree(&((*tree)->right), info)) return true;
            else return false;
        }
    }
    /*
      ���� ������ ������, ��� �� ���������� �� �����
      (*tree == NULL), �� ������ �������� info � ����� ����

      ���������� �������������, ������ ������� info

      ����������, ������ � ����� ������� :
        ���� 0, ��������� ������,
        ���� 1, � �������� �� ����� �� ��������� ������
        ���� 2 �������, -�������� ���� � ���������
}

ptree formIdeallyBalanced(int n) // n � �������� ������� �����
{
    ptree tree = NULL;
    if (n <= 0) return NULL;
    for (int i = 1; i <= n; i++) {
        cout << "Student number " << i << ":\n";
        int info;
        cin >> info;
        insertInSearchTree(&tree, info);
    }
    return tree;
}

void freeTree(ptree t) {
    if (t != NULL) {
        freeTree(t->left);
        freeTree(t->right);
        delete t;
    }
}

void displayLTR(ptree tree)             //����������� �����
{
    if (tree != NULL)
    {
        displayLTR(tree->left);
        cout << tree->info << endl;
        displayLTR(tree->right);
    }
}
*/

//////////////////////////////////////////////////

int main()
{
    string str = "";
    cout << "Enter arithmetic expression using prefix entry: ";
    cin >> str;
    ptree_ae ae_tree = FormAETree(str);
    displayTLR_AE(ae_tree);
    cout << endl;
    displayLTR_AE(ae_tree);
    cout << endl;
    /*
    int command = 0;
    cout << "Enter command (, any other key - exit): ";
    while (true) {
        cin >> command;
        if (command == 1) {

        }
        else if (command == 2) {

        }
        else if (command == 3) {

        }
        else if (command == 4) {
            
        }
        else break;
        cout << "Enter command (): ";
    }
    */
    //freeTree(tree);
}