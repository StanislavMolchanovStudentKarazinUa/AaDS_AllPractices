#include <iostream>
#include "individual_work1.h"
using namespace std;

struct tnode {
    int a = 0;
    tnode* next = NULL;
};
typedef tnode* pnode;

struct tnode_ {
    int i = 0;
    pnode p = NULL;
    tnode_* next = NULL;
};
typedef tnode_* pnode_;

pnode form_cycle_list(int n, int i, pnode& key) {
    pnode head = NULL;
    pnode* cur = &head;
    int a;
    while (n > 0) {
        cin >> a;
        *cur = new tnode;
        if (i == 0) key = *cur;
        (*cur)->a = a;
        if (n == 1) (*cur)->next = key;
        else cur = &(*cur)->next;
        n--;
        i--;
    }
    return head;
}

int find_cycle_tail(pnode cur, pnode_ past = NULL) {
    if (cur == NULL) return -1;
    pnode_ cur_ = past;
    while (cur_ != NULL) {
        if (cur == cur_->p) return cur_->i;
        cur_ = cur_->next;
    }
    cur_ = new tnode_;
    cur_->p = cur;
    cur_->next = past;
    if (past == NULL) cur_->i = 0;
    else cur_->i = past->i + 1;
    return find_cycle_tail(cur->next, cur_);
}

void free(pnode p, pnode key = NULL) {
    if (p->next != key) free(p->next, key);
    delete p;
}

int main()
{
    cout << "Input amount of nodes: ";
    int n;
    cin >> n;
    cout << "Input index where cycle begins: ";
    int i;
    cin >> i;
    pnode key = NULL;
    cout << "Input " << n << " nodes: ";


    ////////////////////////////////////////////////////////////


    pnode head = form_cycle_list(n, i, key);

    int i_ = find_cycle_tail(head);
    if (i_ == -1) cout << "No cycle" << endl;
    else cout << "Tail connects to node index " << i_ << endl;

    /*
    pnode cur = head;
    while (cur != NULL) {
        cout << cur->a << " " << cur->next << endl;
        cur = cur->next;
    }
    */
    free(head, key);
}