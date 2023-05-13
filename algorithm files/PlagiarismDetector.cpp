#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <fstream>
#include "Document.h"
#include "PlagiarismDetector.h"

PlagiarismDetector::PlagiarismDetector(std::string corpus_dir){
    this->corpus_dir = corpus_dir;
    load_corpus();
}
void PlagiarismDetector::load_corpus() {
    std::vector<std::string> filenames = get_file_names(corpus_dir);
    for (const auto& filename : filenames) {
        Document doc(filename);
        corpus.push_back(doc);
    }
}

std::vector<std::string> PlagiarismDetector::get_file_names(const std::string& directory_path) {
    std::vector<std::string> filenames;
    for (const auto& entry : fs::directory_iterator(directory_path)) {
        if (entry.is_regular_file()) {
            filenames.push_back(entry.path().string());
        }
    }
    return filenames;
}
