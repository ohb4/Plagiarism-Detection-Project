
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <fstream>
#include "PlagiarismDetector.h"
class BoyerMooreMatcher : public PlagiarismDetector
{
public:
    BoyerMooreMatcher(std::string corpus_dir); //constructor
    std::set<std::string> match(std::string sentence); //matches sentence using Boyer Moore algorithm

private:
    std::string matcher;
};