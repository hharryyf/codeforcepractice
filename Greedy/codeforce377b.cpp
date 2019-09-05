#include <bits/stdc++.h>

typedef long long Long;

using namespace std;

typedef struct stu {
	int id;
	int able;
	Long pass;
} Student;

// bugs[i].first means bug's difficulty, bugs[i].second means the bug's
// id
vector<pair<int, int> > bugs;

vector<Student> student;

vector<int> ans;

void fill(int day);

bool valid(int day, Long money);

static bool cmp(const pair<int, int> &a, const pair<int, int> &b) {
	if (a.first != b.first) return a.first > b.first;
	return a.second < b.second;
}


static bool scmp(const Student &a, const Student &b) {
	if (a.able != b.able) return a.able > b.able;
	return a.pass < b.pass;
}

struct qcmp {
	bool operator()(const Student &a, const Student &b) {
		return a.pass > b.pass;
	}
};

int main(int argc, char *argv[]) {
	int n, m, i;
	Long s;
	scanf("%d%d%lld", &n, &m, &s);
	ans = vector<int>(m, -1);
	student = vector<Student>(n, Student{0, 0,0ll});
	
	for (i = 0 ; i < m; i++) {
		int v;
		scanf("%d", &v);
		bugs.push_back(pair<int, int>(v, i));
	}
	
	for (i = 0 ; i < n; i++) {
		student[i].id = i + 1;
		scanf("%d", &student[i].able);
	}
	
	for (i = 0 ; i < n; i++) {
		scanf("%lld", &student[i].pass);
	}
	
	sort(bugs.begin(), bugs.end(), cmp);
	
	sort(student.begin(), student.end(), scmp);
	int low = 0, high = m;
	int day = m + 1;
	while (low <= high) {
		int mid = low + (high - low) / 2;
		if (valid(mid, s)) {
			day = min(mid, day);
			high = mid - 1;
		} else {
			low = mid + 1;
		}
	}
	
	if (day < m + 1) {
		fill(day);
		cout << "YES" << endl;
		for (i = 0 ; i < m; i++) {
			printf("%d ", ans[i]);
		}
		cout << endl;	
	} else {
		cout << "NO" << endl;
	}
	return 0;
}

void fill(int day) {
	priority_queue<Student, vector<Student>, qcmp> q;
	int i = 0, j = 0, k;
	while (i < (int) bugs.size()) {
		while (j < (int) student.size()) {
			if (student[j].able >= bugs[i].first) {
				q.push(student[j]);
				j++;
			} else {
				break;
			}
		}
		
		Student stu = q.top();
		q.pop();
		
		for (k = 0; k < day && (i + k < (int) bugs.size()); k++) {
			ans[bugs[i + k].second] = stu.id;
		}
		i = i + day;
	}
}

bool valid(int day, Long money) {
	priority_queue<Student, vector<Student>, qcmp> q;
	int i = 0, j = 0;
	while (i < (int) bugs.size()) {
		while (j < (int) student.size()) {
			if (student[j].able >= bugs[i].first) {
				q.push(student[j]);
				j++;
			} else {
				break;
			}
		}
		
		if (q.empty()) return false;
		Student stu = q.top();
		q.pop();
		if (stu.pass > money) {
			return false;
		}
		
		money = money - stu.pass;
		i = i + day;
	}
	
	return true;
}
