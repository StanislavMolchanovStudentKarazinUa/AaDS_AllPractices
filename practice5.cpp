#include <iostream>
using namespace std;
/////////////////////////////////////////////////////////////////////
enum Role {
    Goalkeeper,
    Defender,
    Midfielder,
    Forward
};
Role SetRole() {
    string a = "";
    cout << "Footbolist's role: ";
    cin >> a;
    if (a == "Goalkeeper") return Goalkeeper;
    else if (a == "Defender") return Defender;
    else if (a == "Midfielder") return Midfielder;
    else if (a == "Forward") return Forward;
    else {
        cout << "WRONG!!!\n";
        return SetRole();
    }
}
Role SetRole(int a) {
    switch (a) {
    case 0: return Goalkeeper;
    case 1: return Defender;
    case 2: return Midfielder;
    case 3: return Forward;
    default:
        cout << "Error!\n";
        return Forward;
    }
}
void OutputRole(Role role) {
    switch (role) {
    case 0: cout << "Goalkeeper"; break;
    case 1: cout << "Defender"; break;
    case 2: cout << "Midfielder"; break;
    default: cout << "Forward"; break;
    }
}

struct Footbolist {
    string surname = "";
    Role role = Forward;
    short age = 0;
    short games_count = 0;
    int goal_count = 0;
};
Footbolist SetFootbolist() {
    Footbolist footbolist;
    cout << "\nFootbolist's surname: ";
    cin >> (&footbolist)->surname;
    (&footbolist)->role = SetRole();
    cout << "Footbolist's age: ";
    cin >> (&footbolist)->age;
    cout << "Footbolist's games count: ";
    cin >> (&footbolist)->games_count;
    cout << "Footbolist's goal count: ";
    cin >> (&footbolist)->goal_count;
    return footbolist;
}
Footbolist SetOtherFootbolist() {
    Footbolist footbolist;
    cout << "New footbolist:\nFootbolist's surname: ";
    cin >> (&footbolist)->surname;
    (&footbolist)->role = SetRole();
    cout << "Footbolist's age: ";
    cin >> (&footbolist)->age;
    cout << "Footbolist's games count: ";
    cin >> (&footbolist)->games_count;
    cout << "Footbolist's goal count: ";
    cin >> (&footbolist)->goal_count;
    return footbolist;
}
struct tnode {
    Footbolist footbolist;
    tnode* next = NULL;
};
typedef tnode* pnode;

/////////////////////////////////////////////////////////////////////

pnode formLIFO_1(int n, pnode head = NULL) {
    pnode cur = NULL;
    Footbolist footbolist;
    if (n > 0) {
        footbolist = SetFootbolist();
        n--;
        cur = new tnode;
        cur->footbolist = footbolist;
        cur->next = head;
        head = cur;
        return formLIFO_1(n, head);
    }
    return head;
}
void formLIFO_2(int n, pnode* p, pnode head = NULL) {
    pnode cur = NULL;
    Footbolist footbolist;
    if (n > 0) {
        footbolist = SetFootbolist();
        n--;
        cur = new tnode;
        cur->footbolist = footbolist;
        cur->next = head;
        head = cur;
        formLIFO_2(n, p, head);
    }
    else *p = head;
}

/////////////////////////////////////////////////////////////////////

pnode formFIFO_1(int n, pnode head = NULL, pnode* cur = NULL) {
    if (head == NULL || cur == NULL) cur = &head;
    Footbolist footbolist;
    if (n > 0) {
        footbolist = SetFootbolist();
        n--;
        *cur = new tnode;
        (*cur)->footbolist = footbolist;
        cur = &(*cur)->next;
        return formFIFO_1(n, head, cur);
    }
    return head;
}
void formFIFO_2(int n, pnode* p, pnode head = NULL, pnode* cur = NULL) {
    if (head == NULL || cur == NULL) cur = &head;
    Footbolist footbolist;
    if (n > 0) {
        footbolist = SetFootbolist();
        n--;
        *cur = new tnode;
        (*cur)->footbolist = footbolist;
        cur = &(*cur)->next;
        formFIFO_2(n, p, head, cur);
    }
    else *p = head;
}

/////////////////////////////////////////////////////////////////////
bool deleteNode(pnode* head, pnode p, pnode cur = NULL) {
    if (cur == NULL) {
        cur = *head;
        if (*head == p) {
            if (*head == NULL) return false;
            if ((*head)->next == NULL) {
                delete* head;
                *head = NULL;
                return true;
            }
            *head = (*head)->next;
            delete cur->next;
            return true;
        }
    }
    if (cur->next != NULL) {
        if (cur->next == p) {
            cur->next = p->next;
            delete p;
            return true;
        }
        return deleteNode(head, p, cur->next);
    }
    return false;
}
bool insertBefore(pnode* head, pnode p, Footbolist f, pnode cur = NULL) {
    if (cur == NULL) {
        cur = *head;
        if (cur == p) {
            if (p == NULL) return false;
            *head = new tnode;
            (*head)->footbolist = f;
            (*head)->next = p;
            return true;
        }
    }
    if (cur->next != NULL) {
        if (cur->next == p) {
            cur->next = new tnode;
            cur->next->footbolist = f;
            cur->next->next = p;
            return true;
        }
        return insertBefore(head, p, f, cur->next);
    }
    return false;
}
bool insertAfter(pnode* head, pnode p, Footbolist f, pnode cur = NULL) {
    if (cur == NULL) {
        pnode cur = *head;
        if (p == NULL) return false;
    }
    if (cur != NULL) {
        if (cur == p) {
            cur = cur->next;
            p->next = new tnode;
            p->next->footbolist = f;
            p->next->next = cur;
            return true;
        }
        else return insertAfter(head, p, f, cur->next);
    }
    return false;
}
/////////////////////////////////////////////////////////////////////

void free(pnode p) {
    if (p != NULL) {
        free(p->next);
        delete p;
    }
}

/////////////////////////////////////////////////////////////////////

bool SameFootbolist(Footbolist footbolist1, Footbolist footbolist2) {
    return (&footbolist1)->surname == (&footbolist2)->surname &&
        (&footbolist1)->age == (&footbolist2)->age &&
        (&footbolist1)->games_count == (&footbolist2)->games_count &&
        (&footbolist1)->goal_count == (&footbolist2)->goal_count;
}
pnode FindFootbolist(pnode p, Footbolist footbolist0) {
    if (p != NULL) {
        if (SameFootbolist(p->footbolist, footbolist0)) {
            return p;
        }
        FindFootbolist(p->next, footbolist0);
    }
    return NULL;
}

/////////////////////////////////////////////////////////////////////

void PrintFootbolist(pnode footbolist) {
    cout << "surname: " << footbolist->footbolist.surname
        << " role: ";
    OutputRole(footbolist->footbolist.role);
    cout << " age: "
        << footbolist->footbolist.age << " games count: "
        << footbolist->footbolist.games_count <<
        " goal count: " << footbolist->footbolist.goal_count << endl;
}
void PrintAll(pnode footbolist) {
    PrintFootbolist(footbolist);
    if (footbolist->next != NULL) PrintAll(footbolist->next);
}

/////////////////////////////////////////////////////////////////////

pnode BestForward(pnode footbolist, pnode bestForward) {
    if (1.0f * footbolist->footbolist.goal_count / footbolist->footbolist.games_count >
        1.0f * bestForward->footbolist.goal_count / bestForward->footbolist.games_count)
        bestForward = footbolist;
    if (footbolist->next == NULL) return bestForward;
    else return BestForward(footbolist->next, bestForward);
}
bool isLessThanFiveGames(pnode footbolist) {
    return footbolist->footbolist.games_count < 5;
}
void LessThanFiveGames(pnode footbolist) {
    if (isLessThanFiveGames(footbolist))
        PrintFootbolist(footbolist);
    if (footbolist->next != NULL) LessThanFiveGames(footbolist->next);
}

/////////////////////////////////////////////////////////////////////

bool isSorted(Footbolist f1, Footbolist f2) {
    if (f1.role > f2.role) return false;
    else if (f1.role == f2.role && f1.surname > f2.surname) return false;
    else if (f1.role == f2.role && f1.surname == f2.surname
        && f1.age > f2.age) return false;
    else if (f1.role == f2.role && f1.surname == f2.surname
        && f1.age == f2.age && f1.games_count > f2.games_count) return false;
    else if (f1.role == f2.role && f1.surname == f2.surname
        && f1.age == f2.age && f1.games_count == f2.games_count
        && f1.goal_count > f2.goal_count) return false;
    return true;
}

void insertSorted(pnode& cur, Footbolist footbolist) {
    if (cur == NULL) {
        cur = new tnode;
        cur->footbolist = footbolist;
        cur->next = NULL;
    }
    else {
        if (isSorted(footbolist, cur->footbolist)) {
            pnode nevv = new tnode;
            nevv->footbolist = cur->footbolist;
            nevv->next = cur->next;
            cur->footbolist = footbolist;
            cur->next = nevv;
        }
        else insertSorted(cur->next, footbolist);
    }
}

pnode formSorted(int n, pnode head = NULL) {
    if (n > 0) {
        Footbolist footbolist = SetFootbolist();
        insertSorted(head, footbolist);
        return formSorted(n - 1, head);
    }
    return head;
}

int main()
{
    int n = 0;
    pnode footbolist = NULL;
    int command = 0;
    while (true) {
        cout << "0 for help" << endl;
        cin >> command;
        if (command == 0) cout << "0 - help\n1 - new list\n2 - continue with existing\n3 - exit" << endl;
        else if (command == 3) {
            break;
        }
        else {
            if (command == 1) {
                cout << "Enter count: ";
                cin >> n;
                if (n < 1) {
                    cout << "n must be bigger than 0" << endl;
                    continue;
                }
                cout << "1 - LIFO_1; 2 - LIFO_2; 3 - FIFO_1; 4 - FIFO_2; 5 - sorted" << endl;
                cin >> command;
                if (command == 1) footbolist = formLIFO_1(n);
                else if (command == 2) formLIFO_2(n, &footbolist);
                else if (command == 3) footbolist = formFIFO_1(n);
                else if (command == 4) formFIFO_2(n, &footbolist);
                else if (command == 5) footbolist = formSorted(n);
                else cout << "Unknown command" << endl;
            }
            else if (command == 2) {
                int i = 0;
                cout << "0 for help" << endl;
                while (true) {
                    if (footbolist == NULL) {
                        cout << "n must be bigger than 0" << endl;
                        break;
                    }
                    cin >> command;
                    if (command == 0) cout << "0 - help\n1 - find best forward\n2 - show all less than 5 games footbolist\n3 - remove footbolist\n4 - add footbolist before other\n5 - add footbolist after other\n6 - add footbolist in order(sorted list)\n7 - print all\n8 - go back" << endl;
                    else if (command == 1) PrintFootbolist(BestForward(footbolist, footbolist));
                    else if (command == 2) LessThanFiveGames(footbolist);
                    else if (command == 3) if (!deleteNode(&footbolist, FindFootbolist(footbolist, SetFootbolist()))) cout << "Error!Requested footbolist can't be found" << endl; else { cout << "Footbolist was successfully deleted" << endl; }
                    else if (command == 4) if (!insertBefore(&footbolist, FindFootbolist(footbolist, SetFootbolist()), SetOtherFootbolist())) cout << "Error!Requested footbolist can't be found" << endl; else { cout << "Footbolist was successfully inserted" << endl; }
                    else if (command == 5) if (!insertAfter(&footbolist, FindFootbolist(footbolist, SetFootbolist()), SetOtherFootbolist())) cout << "Error!Requested footbolist can't be found" << endl; else { cout << "Footbolist was successfully inserted" << endl; }
                    else if (command == 6) insertSorted(footbolist, SetFootbolist());
                    else if (command == 7) PrintAll(footbolist);
                    else if (command == 8) break;
                    else cout << "Unknown command" << endl;
                }

            }
            else cout << "Unknown command" << endl;
        }
    }
    free(footbolist);
}