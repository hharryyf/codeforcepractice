#include <bits/stdc++.h>

using namespace std;

class sparsetable {
public:
	
	sparsetable(int n) {
		this->capacity = n;
		this->table = new int* [30];
		for (int i = 0 ; i < 30; i++) {
			this->table[i] = new int[n+1];
		}
		this->logtable = vector<int>(n + 1, 0);
		for (int i = 0 ; i < n + 1; i++) {
			if (i <= 1) {
				this->logtable[i] = 0;
			} else {
				this->logtable[i] = this->logtable[i / 2] + 1;
			}
		}
	}
	
	~sparsetable(){
		int i;
		for (i = 0 ; i < 30; i++) {
			delete[] this->table[i];
		}
		delete this->table;
	}
	
	void build(vector<int> &arr) {
		this->n = arr.size();
		this->arr = arr;
		int i, j;
		for (i = 0 ; i < 30; i++) {
			for (j = 0 ; j < n; j++) {
				if (i == 0) {
					table[i][j] = j;
				} else {
					if (j + (1 << i) > this->n) break;
					if (arr[table[i-1][j]] <= arr[table[i-1][j + (1 << (i-1))]]) {
						table[i][j] = table[i-1][j];
					} else {
						table[i][j] = table[i-1][j + (1 << (i-1))];
					}
				}
			}
		}
	}
	
	int query(int st, int ed) {
		assert(st <= ed);
		assert(st >= 0 && ed < this->n);
		int k = this->logtable[ed - st + 1];
		return min(arr[table[k][st]], arr[table[k][ed + 1 - (1 << k)]]);
	}
private:
	int capacity;
	int n;
	int col;	
	int **table;
	vector<int> arr;
	vector<int> logtable;
};

void test1();
void test2();

int main(int argc, char *argv[]) {
	test1();
	test2();
	return 0;
}

int ans(int st, int ed, vector<int> &arr) {
	int ret = arr[st];
	for (int i = st; i <= ed; i++) {
		ret = min(ret, arr[i]);
	}
	return ret;
}

void test1() {
	sparsetable s = sparsetable(10);
	vector<int> arr{1, -1, 2, 4, 5, -2, 3, 8, 9, 10};
	s.build(arr);
	int i, j;
	for (i = 0 ; i < 10; i++) {
		for (j = i; j < 10; j++) {
			assert(s.query(i, j) == ans(i, j, arr));
		}
	}
	cout << "pass test 1" << endl;
}

void test2() {
	sparsetable s = sparsetable(10);
	vector<int> arr{1, 1,1,-1,0,5,-4,3,2,-9};
	s.build(arr);
	int i, j;
	for (i = 0 ; i < 10; i++) {
		for (j = i; j < 10; j++) {
			assert(s.query(i, j) == ans(i, j, arr));
		}
	}
	cout << "pass test 2" << endl;
}


