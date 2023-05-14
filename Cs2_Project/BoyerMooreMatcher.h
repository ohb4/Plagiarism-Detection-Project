#ifndef BOYERMOOREMATCHER_H
#define BOYERMOOREMATCHER_H

#include <string>
#include <cstring>
#include <algorithm>
#include <set>
#include "mainwindow.h"

using namespace std;

class BoyerMooreMatcher : public MainWindow {
public:
    BoyerMooreMatcher(string corpus_dir);
    set<string> match(string sentence) override;

private:
    void preProcess(char* pattern, int m, int* border, int* shift);
    void boyerMoore(char* text, char* pattern, int n, int m, int* shift, set<string>& matchesFound);
};

#endif // BOYERMOOREMATCHER_H
