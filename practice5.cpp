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
struct t2node {
    Footbolist footbolist;
    t2node* prev = NULL;
    t2node* next = NULL;
};
typedef t2node* p2node;

/////////////////////////////////////////////////////////////////////

void formLIFO(int n, p2node& head, p2node& tail) {
    p2node cur = NULL;
    Footbolist footbolist;
    if (n > 0) {
        footbolist = SetFootbolist();
        n--;
        cur = new t2node;
        if (tail == NULL) tail = cur;
        else head->prev = cur;
        cur->footbolist = footbolist;
        cur->next = head;
        head = cur;
        formLIFO(n, head, tail);
    }
}

void formFIFO(int n, p2node& head, p2node& tail, p2node cur = NULL) {
    if (head == NULL || cur == NULL){
        cur = new t2node;
        if (n > 0) {
            cur->footbolist = SetFootbolist();
            head = cur;
            n--;
        }
    }
    Footbolist footbolist;
    if (n > 0) {
        footbolist = SetFootbolist();
        n--;
        cur->next = new t2node;
        cur->next->footbolist = footbolist;
        cur->next->prev = cur;
        cur = cur->next;
        tail = cur;
        formFIFO(n, head, tail, cur);
    }
}

/////////////////////////////////////////////////////////////////////
bool delete2Node(p2node& head, p2node& tail, p2node p, p2node cur = NULL) {
    if (cur == NULL) {
        cur = head;
        if (head == p) {
            if (head == NULL) return false;
            if (head->next == NULL) {
                delete head;
                head = NULL;
                tail = NULL;
                return true;
            }
            head = head->next;
            delete cur->next;
            return true;
        }
    }
    if (cur->next != NULL) {
        if (cur->next == p) {
            if (p == tail) {
                tail = cur;
                cur->next = NULL;
                delete p;
                return true;
            }
            cur->next = p->next;
            p->next->prev = cur;
            delete p;
            return true;
        }
        return delete2Node(head, p, cur->next);
    }
    return false;
}
bool insert2Before(p2node* head, p2node p, Footbolist f, p2node cur = NULL) {
    if (cur == NULL) {
        cur = *head;
        if (cur == p) {
            if (p == NULL) return false;
            *head = new t2node;
            (*head)->footbolist = f;
            (*head)->next = p;
            p->prev = *head;
            return true;
        }
    }
    if (cur->next != NULL) {
        if (cur->next == p) {
            cur->next = new t2node;
            cur->next->footbolist = f;
            cur->next->next = p;
            cur->next->prev = cur;
            p->prev = cur->next;
            return true;
        }
        return insert2Before(head, p, f, cur->next);
    }
    return false;
}
bool insert2After(p2node* tail, p2node p, Footbolist f, p2node cur = NULL) {
    if (cur == NULL) {
        cur = *tail;
        if (cur == p) {
            if (p == NULL) return false;
            *tail = new t2node;
            (*tail)->footbolist = f;
            (*tail)->prev = p;
            p->next = *tail;
            return true;
        }
    }
    if (cur->prev != NULL) {
        if (cur->prev == p) {
            cur->prev = new t2node;
            cur->prev->footbolist = f;
            cur->prev->prev = p;
            cur->prev->next = cur;
            p->next = cur->prev;
            return true;
        }
        return insert2After(tail, p, f, cur->prev);
    }
    return false;
}
/////////////////////////////////////////////////////////////////////

void free(p2node p) {
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
p2node FindFootbolist(p2node p, Footbolist footbolist0) {
    if (p != NULL) {
        if (SameFootbolist(p->footbolist, footbolist0)) {
            return p;
        }
        return FindFootbolist(p->next, footbolist0);
    }
    return NULL;
}

/////////////////////////////////////////////////////////////////////

void PrintFootbolist(p2node footbolist) {
    cout << "surname: " << footbolist->footbolist.surname
        << " role: ";
    OutputRole(footbolist->footbolist.role);
    cout << " age: "
        << footbolist->footbolist.age << " games count: "
        << footbolist->footbolist.games_count <<
        " goal count: " << footbolist->footbolist.goal_count << endl;
}
void PrintAll(p2node footbolist) {
    PrintFootbolist(footbolist);
    if (footbolist->next != NULL) PrintAll(footbolist->next);
}
void PrintAllBackwards(p2node footbolist) {
    PrintFootbolist(footbolist);
    if (footbolist->prev != NULL) PrintAllBackwards(footbolist->prev);
}

/////////////////////////////////////////////////////////////////////

p2node BestForward(p2node footbolist, p2node bestForward) {
    if (1.0f * footbolist->footbolist.goal_count / footbolist->footbolist.games_count >
        1.0f * bestForward->footbolist.goal_count / bestForward->footbolist.games_count)
        bestForward = footbolist;
    if (footbolist->next == NULL) return bestForward;
    else return BestForward(footbolist->next, bestForward);
}
bool isLessThanFiveGames(p2node footbolist) {
    return footbolist->footbolist.games_count < 5;
}
void LessThanFiveGames(p2node footbolist) {
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

void insertSorted(Footbolist footbolist, p2node& head, p2node& tail, p2node* cur) {
    if (*cur == NULL) {
        if (tail != NULL) {
            if (head == tail) {
                *cur = new t2node;
                (*cur)->footbolist = footbolist;
                (*cur)->prev = head;
                tail = *cur;
            }
            else {
                cur = &tail->prev;
                (*cur)->next = new t2node;
                (*cur)->next->footbolist = footbolist;
                (*cur)->next->footbolist = tail->footbolist;
                (*cur)->next->prev = *cur;
                (*cur)->next->next = tail;
                tail->footbolist = footbolist;
                tail->prev = (*cur)->next;
            }
        }
        else {
            (*cur) = new t2node;
            (*cur)->footbolist = footbolist;
            head = *cur;
            tail = *cur;
        }
    }
    else {
        if (isSorted(footbolist, (*cur)->footbolist)) {
            p2node nevv = new t2node;
            nevv->footbolist = (*cur)->footbolist;
            nevv->next = (*cur)->next;
            nevv->prev = *cur;
            (*cur)->footbolist = footbolist;
            if ((*cur)->next != NULL) (*cur)->next->prev = nevv;
            else tail = nevv;
            (*cur)->next = nevv;
        }
        else insertSorted(footbolist, head, tail, &(*cur)->next);
    }
}

void formSorted(int n, p2node& head, p2node& tail) {
    if (n > 0) {
        Footbolist footbolist = SetFootbolist();
        insertSorted(footbolist, head, tail, &head);
        formSorted(n - 1, head, tail);
    }
}

/////////////////////////////////////////////////////////////////////

bool isSymmetrical(p2node head, p2node tail) {
    if (head == NULL && tail == NULL) return true;
    else if (head == NULL || tail == NULL) return false;
    else if (SameFootbolist(head->footbolist, tail->footbolist))
        return isSymmetrical(head->next, tail->prev);
    else return false;
}

int main()
{
    int n = 0;
    p2node footbolist_head = NULL;
    p2node footbolist_tail = NULL;
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
                free(footbolist_head);
                footbolist_head = footbolist_tail = NULL;
                cout << "Enter count: ";
                cin >> n;
                if (n < 1) {
                    cout << "n must be bigger than 0" << endl;
                    continue;
                }
                cout << "1 - LIFO; 2 - FIFO; 3 - sorted" << endl;
                cin >> command;
                if (command == 1) formLIFO(n, footbolist_head, footbolist_tail);
                else if (command == 2) formFIFO(n, footbolist_head, footbolist_tail);
                else if (command == 3) formSorted(n, footbolist_head, footbolist_tail);
                else cout << "Unknown command" << endl;
            }
            else if (command == 2) {
                int i = 0;
                cout << "0 for help" << endl;
                while (true) {
                    if (footbolist_head == NULL) {
                        cout << "n must be bigger than 0" << endl;
                        break;
                    }
                    cin >> command;
                    if (command == 0) cout << "0 - help\n1 - find best forward\n2 - show all less than 5 games footbolist\n3 - remove footbolist\n4 - add footbolist before other\n5 - add footbolist after other\n6 - add footbolist in order(sorted list)\n7 - print all\n8 - print all backwards\n9 - check symmetry of list\n 10 - go back" << endl;
                    else if (command == 1) PrintFootbolist(BestForward(footbolist_head, footbolist_head));
                    else if (command == 2) LessThanFiveGames(footbolist_head);
                    else if (command == 3) if (!delete2Node(footbolist_head, footbolist_tail, FindFootbolist(footbolist_head, SetFootbolist()))) cout << "Error!Requested footbolist can't be found" << endl; else { cout << "Footbolist was successfully deleted" << endl; }
                    else if (command == 4) if (!insert2Before(&footbolist_head, FindFootbolist(footbolist_head, SetFootbolist()), SetOtherFootbolist())) cout << "Error!Requested footbolist can't be found" << endl; else { cout << "Footbolist was successfully inserted" << endl; }
                    else if (command == 5) if (!insert2After(&footbolist_tail, FindFootbolist(footbolist_head, SetFootbolist()), SetOtherFootbolist())) cout << "Error!Requested footbolist can't be found" << endl; else { cout << "Footbolist was successfully inserted" << endl; }
                    else if (command == 6) insertSorted(SetFootbolist(), footbolist_head, footbolist_tail, &footbolist_head);
                    else if (command == 7) PrintAll(footbolist_head);
                    else if (command == 8) PrintAllBackwards(footbolist_tail);
                    else if (command == 9) if (isSymmetrical(footbolist_head, footbolist_tail)) cout << "List is symmetrical" << endl; else cout << "List is not symmetrical" << endl;
                    else if (command == 10) break;
                    else cout << "Unknown command" << endl;
                }

            }
            else cout << "Unknown command" << endl;
        }
    }
    free(footbolist_head);
}
