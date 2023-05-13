#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <fstream>
#include "PlagiarismDetector.h"
class HammingDistanceMatcher : public PlagiarismDetector {
public:
    int hammingDistance(char* text, char* pattern, int n/*std::string corpus_dir*/); //constructor
    std::set<std::string> match(std::string sentence); //matches sentence using hamming distance algorithm

private:
    std::string matcher;
};