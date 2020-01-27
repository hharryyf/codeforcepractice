#pragma GCC optimize(3)
#include <bits/stdc++.h>
#define REP(i,s,e) for(i=(s); i < (e); i++)
#define REB(i,s,e) for(i=(s); i >= (e); i--)
using namespace std;
#define MAX_SIZE 1000111 
// stores the key that each item holds at the moment
vector<int> pos[MAX_SIZE];
bool visited[MAX_SIZE];

inline void out(int x){
    if(x>=10){
        out(x/10);
    }
    putchar(x%10+'0');
}

inline int read()
{
    int fu=1,k=0;
    char a=getchar();
    while(a<'0'||a>'9')
    {
        if(a=='-')fu=-1;
        a=getchar();
    }
    while(a>='0'&&a<='9')
    {
        k=k*10+a-'0';
        a=getchar();
    }
    return fu*k;
}

struct SBST {
    struct node {
    	struct node *left, *right;
    	int value;
    	int id;
    	int size;
    	short height;
    	node(int val, int id) {
    		this->left = this->right = NULL;
    		this->value = val;
    		this->id = id;
    		this->height = 0;
    		this->size = 1;
    	}
    };

    short height(node *t) {
    	if (t == NULL) return -1;
    	return t->height;
    }
    
    int size(node *t) {
    	if (t == NULL) return 0;
    	return t->size;
    }
    
    node *leftrotate(node *t) {
    	if (t == NULL || t->right == NULL) return t;
    	node *tmp = t->right;
    	t->right = tmp->left;
    	t->height = 1 + max(height(t->left), height(t->right));
    	t->size = 1 + size(t->left) + size(t->right);
    	tmp->left = t;
    	tmp->height = 1 + max(height(tmp->left), height(tmp->right));
    	tmp->size = 1 + size(tmp->left) + size(tmp->right);
    	return tmp;
    }
    
    node *rightrotate(node *t) {
    	if (t == NULL || t->left == NULL) return t;
    	node *tmp = t->left;
    	t->left = tmp->right;
    	t->height = 1 + max(height(t->left), height(t->right));
    	t->size = 1 + size(t->left) + size(t->right);
    	tmp->right = t;
    	tmp->height = 1 + max(height(tmp->left), height(tmp->right));
    	tmp->size = 1 + size(tmp->left) + size(tmp->right);
    	return tmp;
    }
    
    node *balance(node *t) {
    	if (t == NULL) return t;
    	t->height = 1 + max(height(t->left), height(t->right));
    	t->size = 1 + size(t->left) + size(t->right);
    	int hl = height(t->left), hr = height(t->right);
    	if (hl - hr > 1) {
    		if (height(t->left->left) < height(t->left->right)) {
    			t->left = leftrotate(t->left);
    		}
    		t = rightrotate(t);
    	} else if (hr - hl > 1) {
    		if (height(t->right->right) < height(t->right->left)) {
    			t->right = rightrotate(t->right);
    		}
    		t = leftrotate(t);
    	}
    	return t;
    }
    
    
    node *getval(node *t, int val) {
    	if (t == NULL) return NULL;
    	if (t->value == val) return t;
    	if (t->value < val) {
    		return getval(t->right, val);
    	}
    	
    	return getval(t->left, val);
    }
    
    node *insertion(node *t, int val, int id) {
    	if (t == NULL) return new node(val, id);
    	if (t->value == val) return t;
    	if (t->value < val) {
    		t->right = insertion(t->right, val, id);
    	} else {
    		t->left = insertion(t->left, val, id);
    	}
    	
    	t = balance(t);
    	return t;	
    }
    
    node *deletion(node *t, int val) {
    	if (t == NULL) return t;
    	if (t->value == val) {
    		node * tmp;
    		if (t->left == NULL && t->right == NULL) {
    			//delete t;
    			return NULL;
    		} else if (t->left == NULL) {
    			tmp = t->right;
    			//delete t;
    			return tmp;	
    		} else if (t->right == NULL) {
    			tmp = t->left;
    			//delete t;
    			return tmp;
    		} else {
    			tmp = t->left;
    			while (tmp->right != NULL) {
    				tmp = tmp->right;
    			}
    			t->value = tmp->value;
    			t->id = tmp->id;
    			t->left = deletion(t->left, tmp->value);
    		}
    	} else if (t->value < val) {
    		t->right = deletion(t->right, val);
    	} else {
    		t->left = deletion(t->left, val);
    	}
    	t = balance(t);
    	return t;
    }
    
    node *getkth(node *t, int k) {
    	if (t == NULL) return NULL;
    	if (size(t->left) + 1 == k) {
    		return t;
    	} else if (size(t->left) + 1 < k) {
    		return getkth(t->right, k - size(t->left) - 1);
    	}
    	return getkth(t->left, k);
    }
    
    node *root = NULL;
    
    int n;
    void init(int n) {
        this->n = n;
        int i;
        REP(i, 0, n) {
            root = insertion(root, i, 0);
        }
    }
    
    // return whether this operation has a contradiction
    bool movefront(int id, int k) {
        auto c = getkth(root, k);
        if (!visited[id]) {
            pos[id].push_back(c->value);
        }
        // add code here for invalid cases
        // case 1, the kth position contains a cup with different id
        if (c->id != 0 && id != c->id) {
            
            return false;
        }
        // case 2, the cup already has a position, but now the position
        // is not k
        if (!pos[id].empty() && pos[id].back() != c->value) {
            
            return false;
        }
        visited[id] = true;
        // erase the key and insert it at the front
        int v = getkth(root, 1)->value;
        root = insertion(root, v - 1, id);
        pos[id].push_back(v-1);
        root = deletion(root, c->value);
        return true;
    }
    
    // note that this function can only be called when id is the 1st cup
    void movecorrect(int id) {
        root = deletion(root, pos[id].back());
        pos[id].pop_back();
        root = insertion(root, pos[id].back(), id);
    }
    
    int idx = 0;
    int curr[MAX_SIZE];
    
    void preorder(node *t) {
        if (t == NULL) return;
        preorder(t->left);
        if (t->id == 0) {
            out(curr[idx++]);
            putchar(' ');
        } else {
            out(t->id);
            putchar(' ');
        }
        preorder(t->right);
    }
    
    void print() {
        int i, j = 0;
        REP(i, 1, n + 1) {
            if (!visited[i]) {
                curr[j++] = i;
            }
        }
        
        idx = 0;
        preorder(root);
        printf("\n");
    }
};

SBST st;
int oper[MAX_SIZE];

int main() {
    int i, n, m;
    int v, pos;
    n = read(), m = read();
    st.init(n);
    REP(i, 0, m) {
        v = read(), pos = read();
        oper[i] = v;
        if (!st.movefront(v, pos)) {
            printf("-1\n");
            return 0;
        }
    }
    
    REB(i, m-1, 0) {
        st.movecorrect(oper[i]);
    }
    
    st.print();
    return 0;
}
