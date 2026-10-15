#include <iostream>
#include <stdio.h>
#include <vector>
using namespace std;

int init_map(char a, vector<pair<char, int>>* b) {
    for (int i = 0; i < b->size(); i++) {
        if (a == (*b)[i].first) {
            return 0;
        }
    }
    b->push_back({ a, 0 });
    return 0;
}

int search(char a, vector<pair<char, int>> b) {
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

int summ(vector<pair<char, int>> b, char a[100]) {
    for (int i = 0; i < b.size(); i++) {
        for (int j = i + 1; j < b.size(); j++) {
            if (b[i].second == b[j].second) return 0;
        }
    }

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

    int ans2 = 0;
    vector<int> num2;
    now_number = 0;
    if (search(a[i], b) == 0) return 0;
    while (a[i] != '\n') {
        now_number *= 10;
        now_number += search(a[i], b);
        i++;
    }
    ans2 += now_number;
    num2.push_back(now_number);

    if (ans1 == ans2) {
        print(num1);
        cout << " = ";
        print(num2);
        cout << "\n";
    }
    return 0;
}

int all(vector<pair<char, int>> b, char a[100], int index) {
    if (index == b.size()) {
        summ(b, a);
        return 0;
    }
    for (int i = 0; i < 10; i++) {
        b[index].second = i;
        all(b, a, index + 1);
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
    fgets(a, sizeof(a), stdin);
    clean(a);
    int i = 0;
    while (a[i] != '\n') {
        if (a[i] == '+' || a[i] == '=') { i++; continue; }
        init_map(a[i], &map);
        i++;
    }
    if (map.size() > 10) return 0;
    all(map, a, 0);
}