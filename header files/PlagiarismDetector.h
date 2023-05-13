#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <fstream>
#include <filesystem>
#include "Document.h"

namespace fs = std::filesystem;

class PlagiarismDetector
{
public:
    PlagiarismDetector::PlagiarismDetector(std::string corpus_dir);
    PlagiarismDetector(std::string corpus_dir); //constructor
    void load_corpus(); //loads all the documents in the corpus
    virtual std::set<std::string> match(std::string sentence) = 0; //matches senctence with the corpus

protected:
    std::string corpus_dir;
    std::vector<Document> corpus;

private:
    std::vector<std::string> get_file_names(const std::string& directory_path);
};

PlagiarismDetector::PlagiarismDetector(std::string corpus_dir)
    : corpus_dir(corpus_dir)
{};

