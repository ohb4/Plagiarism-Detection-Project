#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include "RabinKarpMatcher.h"
const int d = 256; // Assuming ASCII character set
int search_counter = 0; // Counter to keep track of the number of searches
void rabinKarp(const std::string& pattern, const std::string& text, bool& found) {
    int q = text.length();
    int m = pattern.length();
    int n = text.length();
    int i, j;
    int p = 0, t = 0, h = 1;
    for (i = 0; i < m - 1; i++)
        h = (h * d) % q;

    for (i = 0; i < m; i++) {
        p = (d * p + pattern[i]) % q;
        t = (d * t + text[i]) % q;
    }

    for (i = 0; i <= n - m; i++) {
        if (p == t) {
            for (j = 0; j < m; j++) {
                if (text[i + j] != pattern[j])
                    break;
            }

            if (j == m) {
                found = true;
                std::cout << "Pattern found at index " << i + 1 << std::endl;
            }
        }

        if (i < n - m) {
            t = (d * (t - text[i] * h) + text[i + m]) % q;

            if (t < 0)
                t = (t + q);
        }
    }
}

int main() {
    RabinKarpMatcher matcher("corpus_dir");
    std::string documentName;
    std::cout << "Enter the name of the document: ";
    std::cin >> documentName;

    std::ifstream documentFile(documentName);
    if (!documentFile) {
        std::cerr << "Failed to open the document file: " << documentName << std::endl;
        return 1;
    }

    std::set<std::string> matchedFiles;
    std::string line;
    std::string pattern;
    while (getline(documentFile, line)) {
        std::cout << line << std::endl;
        std::cout << "Enter the pattern to search (or 'q' to quit): ";
        std::cin >> pattern;

        if (pattern == "q") {
            break;
        }

        bool found = false;
        rabinKarp(pattern, line, found);
        if (found) {
            matchedFiles.insert(documentName);
            search_counter++;
        }
    }

    std::cout << "Number of searches performed: " << search_counter << std::endl;

    std::cout << "Matched files: " << std::endl;
    for (const auto& file : matchedFiles) {
        std::cout << file << std::endl;
    }

    return 0;
}
