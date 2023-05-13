#include "HammingDistanceMatcher.h"
#include "Document.h"
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <fstream>

using namespace std;
// write the code to a hamming distance algorithm to detect plagirism here 

//int HammingDistanceMatcher::hammingDistance(std::string corpus_dir) : PlagiarismDetector(corpus_dir) {}

std::set<std::string> HammingDistanceMatcher::match(std::string sentence) {
    set<string> matchesFound;
    int n = sentence.length();
    char text[n+1];
    strcpy(text, sentence.c_str());
    
    for (auto& document : corpus) {
        vector<string> sentences = document.get_sentences();
        for (auto& s : sentences) {
            if (s.length() != n) continue;
            char pattern[n+1];
            strcpy(pattern, s.c_str());
            if (hammingDistance(text, pattern, n) == 1) {
                matchesFound.insert(s);
            }
        }
    }
    return matchesFound;
}

int HammingDistanceMatcher::hammingDistance(char* text, char* pattern, int n) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (text[i] != pattern[i]) {
            count++;
        }
    }
    return count;
}


/* example of hamming distance brute force approach from geeks for geeks
#include <iostream>
using namespace std;

void search(char* pat, char* txt) {
    int M = strlen(pat);
    int N = strlen(txt);

    for (int i = 0; i <= N - M; i++) {
        int j;
        for (j = 0; j < M; j++)
            if (txt[i + j] != pat[j])
                break;

        if (j == M) 
            cout << "pattern is found at " << i << endl;
    }
}

int main() {
    char txt[] = "AAAAAAAAAAAAAAAAAA";
    char pat[] = "AAAAA";
    search(pat, txt);
    return 0;
}*/