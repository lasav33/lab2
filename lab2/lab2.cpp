#include <iostream>
#include <stdio.h>
#include <vector>
#include <string> 
#include <time.h>
using namespace std;

vector<string> L;                              
string R;                                    
int need_k[128];                     

int init_map(char a, vector<pair<char, int>>* b) {
    for (int i = 0; i < b->size(); i++) {
        if (a == (*b)[i].first) {
            return 0;
        }
    }
    b->push_back({ a, 0 });
    return 0;
}

int search(char a, const vector<pair<char, int>>& b) {
    for (int i = 0; i < b.size(); i++) {
        if (a == b[i].first) {
            return b[i].second;
        }
    }
    return 0;
}

void print(vector<int> num) {
    for (int i = 0; i < num.size() - 1; i++) {
        cout << num[i];
        cout << " + ";
    }
    cout << num[num.size() - 1];
}

long long val(const string& w, const vector<pair<char, int>>& b, int k) {
    long long v = 0, p = 1;
    int len = w.size();
    for (int j = len - 1; j >= 0 && len - 1 - j < k; j--) {
        v += search(w[j], b) * p;
        p *= 10;
    }
    return v;
}

bool check(const vector<pair<char, int>>& b, int k) {
    long long mod = 1;
    for (int i = 0; i < k; i++) mod *= 10;
    long long s = 0;
    for (int i = 0; i < L.size(); i++) s += val(L[i], b, k);
    return s % mod == val(R, b, k);
}

int summ(const vector<pair<char, int>>& b, char a[100]) {
    int ans1 = 0;
    vector<int> num1;
    int now_number = 0;
    int i = 0;
    if (search(a[i], b) == 0) return 0;
    while (a[i] != '=') {
        if (a[i] == '+') {
            if (search(a[i + 1], b) == 0) return 0;
            ans1 += now_number;
            num1.push_back(now_number);
            now_number = 0;
            i++;
            continue;
        }
        now_number *= 10;
        now_number += search(a[i], b);
        i++;
    }
    ans1 += now_number;
    num1.push_back(now_number);
    i++;

    int res = 0;
    if (search(a[i], b) == 0) return 0;
    while (a[i] != '\n') {
        res *= 10;
        res += search(a[i], b);
        i++;
    }

    if (ans1 == res) {
        print(num1);
        cout << " = " << res << "\n";
    }
    return 0;
}


int all(vector<pair<char, int>>& b, char a[100], int index, int cool[10]) {
    if (index == b.size()) {
        summ(b, a);
        return 0;
    }
    for (int i = 0; i < 10; i++) {
        if (cool[i] == 1) {
            b[index].second = i;
            cool[i] = 0;
            int k = need_k[index + 1];
            if (k == 0 || check(b, k)) all(b, a, index + 1, cool);
            cool[i] = 1;
        }

    }
    return 0;

}

void clean(char a[100]) {
    int j = 0;
    for (int i = 0; a[i] != '\0'; i++) {
        if (a[i] == ' ' || a[i] == '\t' || a[i] == '\r' || a[i] == '\n') continue;
        a[j++] = a[i];
    }
    a[j++] = '\n';
    a[j] = '\0';
}

int main()
{
    vector<pair<char, int>> map;
    char a[100];
    int cool[10] = { 1,1,1,1,1,1,1,1,1,1 };
    fgets(a, sizeof(a), stdin);
    clean(a);

    string cur;
    for (int i = 0; a[i] != '\n'; i++) {
        if (a[i] == '+' || a[i] == '=') { L.push_back(cur); cur = ""; }
        else cur += a[i];
    }
    R = cur;
    int maxlen = R.size();
    for (int i = 0; i < L.size(); i++) if ((int)L[i].size() > maxlen) maxlen = L[i].size();
    for (int col = 0; col < maxlen; col++) {
        for (int i = 0; i < L.size(); i++)
            if (col < (int)L[i].size()) init_map(L[i][L[i].size() - 1 - col], &map);
        if (col < (int)R.size()) init_map(R[R.size() - 1 - col], &map);
        need_k[map.size()] = col + 1;
    }
    if (map.size() > 10) return 0;

    clock_t start = clock();

    all(map, a, 0, cool);

    clock_t end = clock();
    double elapsed = double(end - start) / CLOCKS_PER_SEC;

    printf("\nTime: %.6f seconds\n", elapsed);
}