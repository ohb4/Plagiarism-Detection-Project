#include "PlagiarismDetector.h"
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <fstream>
class KMPMatcher : public PlagiarismDetector
{
public:
    KMPMatcher(std::string corpus_dir); //constructor
    std::set<std::string> match(std::string sentence); //matches sentence using KMP algorithm

private:
    std::string matcher;
};

