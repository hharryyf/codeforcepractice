#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

struct node {
    node *pre, *nxt;
    ll L, R;
    char ch;
    int tp;
    node(ll L=0, ll R=-1, char ch='a', int tp=0) {
        this->pre = this->nxt = NULL;
        this->L = L, this->R = R;
        this->ch = ch;
        this->tp = tp;
    }
};


struct longstring {
    node *head, *tail;
    longstring() {
        this->head = new node();
        this->tail = new node();
        node *mid = new node(1, 11000000000ll, 'a', 1);
        this->head->nxt = mid;
        mid->pre = this->head;
        mid->nxt = this->tail;
        this->tail->pre = mid;
    }

    void insert(ll pos, char ch) {
        node *curr = this->head;
        pos--;
        ll cnt = 0;
        while (curr != NULL) {
            if (cnt + curr->R - curr->L + 1 == pos) {
                // insert next
                node *nd = new node(0, 0, ch, 2);
                curr->nxt->pre = nd;
                nd->nxt = curr->nxt;
                curr->nxt = nd;
                nd->pre = curr;
                break;
            }

            if (cnt + curr->R - curr->L + 1 > pos) {
                node *nd = new node(0, 0, ch, 2);
                node *nd2 = new node(curr->L + pos - cnt, curr->R, 'a', 1);
                curr->R = curr->L + pos - cnt - 1;
                nd2->nxt = curr->nxt;
                curr->nxt->pre = nd2;
                nd->nxt = nd2;
                nd2->pre = nd;
                curr->nxt = nd;
                nd->pre = curr;
                break;
            }
            cnt = cnt + curr->R - curr->L + 1;
            curr = curr->nxt;
        }
    }

    void del(ll pos) {
        node *curr = this->head;
        ll cnt = 0;
        while (curr != NULL) {
            if (cnt + curr->R - curr->L + 1 >= pos) {
                deletenode(curr, pos - cnt);
                break;
            }

            cnt = cnt + curr->R - curr->L + 1;
            curr = curr->nxt;
        }
    }

    void deletenode(node *curr, ll idx) {
        // cout << "delete node " << curr->L << " " << curr->R << " index= " << idx << endl;
        bool ok = false;

        if (idx == curr->R - curr->L + 1) {
            curr->R--;
            ok = true;
        }

        if (idx == 1) {
            curr->L++;
            ok = true;
        }
        
        if (curr->L > curr->R) {
            curr->pre->nxt = curr->nxt;
            curr->nxt->pre = curr->pre;
            return;
        }

        if (ok) return;
        ll L = curr->L + idx - 1;
        node *nd = new node(L + 1, curr->R, 'a', 1);
        curr->R = L - 1;
        nd->nxt = curr->nxt;
        curr->nxt->pre = nd;
        curr->nxt = nd;
        nd->pre = curr;
    }

    void print() {
        node *curr = this->head;
        while (curr != NULL) {
            cout << "(" << curr->L << ", " << curr->R << ", " << curr->ch << ", " << curr->tp << ")" << " -> "; 
            curr = curr->nxt;
        }
        cout << "X" << endl;
    }

    bool operator ==(longstring other) const {
        vector<node> ret;
        node *curr = this->head;
        while (curr != NULL) {
            if (!ret.empty() && ret.back().tp == 1 && ret.back().R + 1 == curr->L && curr->tp == 1) {
                int sz = ret.size();
                ret[sz-1].R = curr->R;
            } else {
                ret.push_back(node{curr->L, curr->R, curr->ch, curr->tp});
            }
            curr = curr->nxt;
        }

        vector<node> ret2;
        curr = other.head;
        while (curr != NULL) {
            if (!ret2.empty() && ret2.back().tp == 1 && ret2.back().R + 1 == curr->L && curr->tp == 1) {
                int sz = ret2.size();
                ret2[sz-1].R = curr->R;
            } else {
                ret2.push_back(node{curr->L, curr->R, curr->ch, curr->tp});
            }
            curr = curr->nxt;
        }

        if (ret.size() != ret2.size()) return false;
        int i;
        for (i = 0 ; i < (int) ret.size(); ++i) {
            if (ret[i].L != ret2[i].L || ret[i].R != ret2[i].R || ret[i].tp != ret2[i].tp || ret[i].ch != ret2[i].ch) return false;
        }

        return true;
    }
};

longstring s[2];
char op[4];
int idx = 0;

int main() {
    while (idx < 2) {
        scanf("%s", op);
        if (op[0] == 'E') {
            idx++;
            continue;
        } else if (op[0] == 'D') {
            ll pos;
            scanf("%I64d", &pos);
            s[idx].del(pos);
        } else {
            ll pos;
            scanf("%I64d%s", &pos, op);
            s[idx].insert(pos, op[0]);
        }
        // s[idx].print();
    }

    printf("%d\n", 1 ^ (s[0] == s[1]));
    return 0;
}