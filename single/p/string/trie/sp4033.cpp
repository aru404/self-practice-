// // 
// # PHONELST - Phone List

// ## 题面翻译

// **【题目来源】**

// 	Poj3630

// **【问题描述】**

// 	给定n个长度不超过10的数字串，问其中是否存在两个数字串S，T，使得S是T的前缀。有多组数据，数据组数不超过40。n<=10000。

// **【输入格式】**

// 	第一行，一个整数T，表示数据组数。
// 	对于每组数据，第一行一个数n，接下去n行，输入n个数字串。

// **【输出格式】**

// 	对于每组数据，若存在两个数字串S，T，使得S是T的前缀，则输出“NO”，否则输出“YES”。

// **【数据规模】**

// 	n<=10000

// ## 题目描述

// Phone List
// ----------

//  Given a list of phone numbers, determine if it is consistent in the sense that no number is the prefix of another. Let’s say the phone catalogue listed these numbers:

// - Emergency 911
// - Alice 97 625 999
// - Bob 91 12 54 26

// In this case, it’s not possible to call Bob, because the central would direct your call to the emergency line as soon as you had dialled the first three digits of Bob’s phone number. So this list would not be consistent.

// ## 输入格式

// The first line of input gives a single integer, 1 <= t <= 40, the number of test cases. Each test case starts with n, the number of phone numbers, on a separate line, 1 <= n <= 10000. Then follows n lines with one unique phone number on each line. A phone number is a sequence of at most ten digits.

// ## 输出格式

// For each test case, output “YES” if the list is consistent, or “NO” otherwise.

// ## 样例 #1

// ### 样例输入 #1

// ```
// 2
// 3
// 911
// 97625999
// 91125426
// 5
// 113
// 12340
// 123440
// 12345
// 98346
// ```

// ### 样例输出 #1

// ```
// NO
// YES
// ```
#include <iostream>
#include <bits/stdc++.h>

struct node{
    bool isEnd = 0;
    node** next;

    node(){
        next = new node*[10]{nullptr};
    }
};

class Trie{
private:
    node* root;
public:
    Trie(){
        root = new node;
    }

    ~Trie(){
        delete root;
    }

    inline bool ins(std::string& s){
        node* r = root;
        bool isPre = 0;
        for(auto c:s){
            if(r->next[c - '0'] == nullptr) isPre |= r->isEnd, r->next[c - '0'] = new node;
            r = r->next[c - '0'];
        }
        r->isEnd = 1;
        return isPre;
    }
};

inline void sort(std::vector<std::string>& arr){
    std::vector<size_t> cnt(11, 0);
    auto key = [&](std::string& s, size_t bit){
        return bit >= s.size()? 1:s[s.size() - bit - 1] - '0' + 1; 
    };

    size_t n = std::max_element(arr.begin(), arr.end(), 
    [](const std::string& a, const std::string& b){
        return a.size() < b.size();
    })->size();

    auto cpy = arr;
    for(size_t i = 0; i < n; ++i){
        for(auto s:arr) ++cnt[key(s, i)];
        for(size_t j = 1; j <= 10; ++j) cnt[j] += cnt[j - 1];
        for(auto s:arr) cpy[cnt[key(s, i) - 1]++] = s;
        for(size_t j = 0; j <= 10; ++j) cnt[j] = 0;
        arr = cpy;
    }
}

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t, n;
    std::string s;
    std::vector<std::string> arr;

    std::cin >> t;
    for(int i = 0; i < t; ++i){
        std::cin >> n;
        arr.resize(n);
        for(size_t i = 0; i < n; ++i) std::cin >> s, arr[i] = s;
        sort(arr);
        bool res = false;
        Trie trie;
        for(int i = 0; i < n; ++i){
            res |= trie.ins(arr[i]);
            if(res) break;
        }
        std::cout << (res? "NO":"YES") << '\n';
    }

    return 0;
}