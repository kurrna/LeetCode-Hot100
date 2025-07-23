//
// Created by Kurna on 25-7-8.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int lengthOfLongestSubstring(char* s) {
    int len = strlen(s);
    int ans = 0, temp = 0;
    int hash[129] = {0};
    int left = 0, right = 0;
    while (right < len) {
        if (hash[s[right]] == 0) {
            temp += 1;
            hash[s[right]] = 1;
            right += 1;
        } else {
            while (hash[s[right]]) {
                hash[s[left]] = 0;
                temp -= 1;
                left += 1;
            }
        }
        if (temp > ans) ans = temp;
    }
    return ans;
}

void test() {
    char s[] = "abcabcbb";
    printf("%d", lengthOfLongestSubstring(s));
}