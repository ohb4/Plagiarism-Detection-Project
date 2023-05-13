#include "KMPMatcher.h"
#include <iostream>
#include <string>
#include "PlagiarismDetector.h"
#include <set>
#include <vector>

KMPMatcher::KMPMatcher(std::string corpus_dir) : PlagiarismDetector(corpus_dir) {}

void lps_func(std::string txt, std::vector<int>& Lps) {
    Lps[0] = 0;
    int len = 0;
    int i = 1;
    while (i < txt.length()) {
        if (txt[i] == txt[len]) {
            len++;
            Lps[i] = len;
            i++;
            continue;
        } 
        else {
            if (len == 0) {
                Lps[i] = 0;
                i++;
                continue;
            } else {
                len = Lps[len - 1];
                continue;
            }
        }
    }
}

std::set<std::string> KMPMatcher::match(std::string sentence) {
    std::set<std::string> matchesFound;
    int n = sentence.length();
    char text[n+1];
    strcpy(text, sentence.c_str());
    for (auto& document : corpus) {
        std::vector<std::string> sentences = document.get_sentences();
        for (auto& s : sentences) {
            int m = s.length();
            std::vector<int> Lps(m);
            lps_func(s, Lps);

            int i = 0, j = 0;
            while (i < n) {
                if (s[j] == text[i]) { i++; j++; } 

                if (j == m) {
                    matchesFound.insert(s);
                    break;
                } else if (i < n && s[j] != text[i]) {
                    if (j == 0)
                        i++;
                    else
                        j = Lps[j - 1];
                }
            }
        }
    }
    return matchesFound;
}
