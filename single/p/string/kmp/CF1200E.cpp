// # Compress Words

// ## 题面翻译

// Amugae 有 $n$ 个单词，他想把这个 $n$ 个单词变成一个句子，具体来说就是从左到右依次把两个单词合并成一个单词。合并两个单词的时候，要找到最大的 $i(i\ge 0)$，满足第一个单词的长度为 $i$ 的后缀和第二个单词长度为 $i$ 的前缀相等，然后把第二个单词第 $i$ 位以后的部分接到第一个单词后面。输出最后那个单词。

// 注：题中的字符串存在大小写字母和数字。

// ## 题目描述

// Amugae has a sentence consisting of $ n $ words. He want to compress this sentence into one word. Amugae doesn't like repetitions, so when he merges two words into one word, he removes the longest prefix of the second word that coincides with a suffix of the first word. For example, he merges "sample" and "please" into "samplease".

// Amugae will merge his sentence left to right (i.e. first merge the first two words, then merge the result with the third word and so on). Write a program that prints the compressed word after the merging process ends.

// ## 输入格式

// The first line contains an integer $ n $ ( $ 1 \le n \le 10^5 $ ), the number of the words in Amugae's sentence.

// The second line contains $ n $ words separated by single space. Each words is non-empty and consists of uppercase and lowercase English letters and digits ('A', 'B', ..., 'Z', 'a', 'b', ..., 'z', '0', '1', ..., '9'). The total length of the words does not exceed $ 10^6 $ .

// ## 输出格式

// In the only line output the compressed word after the merging process ends as described in the problem.

// ## 样例 #1

// ### 样例输入 #1

// ```
// 5
// I want to order pizza
// ```

// ### 样例输出 #1

// ```
// Iwantorderpizza
// ```

// ## 样例 #2

// ### 样例输入 #2

// ```
// 5
// sample please ease in out
// ```

// ### 样例输出 #2

// ```
// sampleaseinout
// ```
#include <iostream>
#include <bits/stdc++.h>

const int maxN = 1E6 + 5;
int kmp[maxN];

inline void merger(std::string& s1, std::string& s2){
    std::function<void(std::string& )> KMP = [&](std::string& s)->void{
        kmp[0] = -1;
        for(unsigned int i = 1; i < s.size(); i++){
            int j = kmp[i - 1];
            while(~j && s[j + 1] != s[i]) j = kmp[j];
            kmp[i] = j + (s[j + 1] == s[i]);
        }
    };

    int k = std::min(s1.size(), s2.size());
    auto s = s2.substr(0, k);
    s.push_back('#');
    s.append(s1.substr(s1.size() - k, k));

    KMP(s);
    s1.append(s2.substr(kmp[k << 1] + 1, s2.size() - kmp[k << 1] - 1));
}

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;
    std::string s1, s2;
    std::cin >> s1;
    for(int i = 1; i < n; i++) std::cin >> s2, merger(s1, s2);
    std::cout << s1;
    return 0;
}