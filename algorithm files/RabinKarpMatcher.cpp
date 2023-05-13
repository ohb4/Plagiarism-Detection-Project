#include <cstring>
#include <iostream>
#include <fstream>
#include "RabinKarpMatcher.h"
#include "Document.h"
#include "PlagiarismDetector.h"

RabinKarpMatcher::RabinKarpMatcher(std::string corpus_dir) : PlagiarismDetector(corpus_dir){
}

std::set<std::string> RabinKarpMatcher::match(const std::string& sentence) const {
    std::set<std::string> matched_files;

    for (const auto& doc : corpus) {
        if (doc.search_pattern(sentence)) {
            matched_files.insert(doc.get_file_path());
        }
    }

    return matched_files;
}


void RabinKarpMatcher::load_corpus() {
    std::vector<std::string> filenames = get_file_names(corpus_dir);
    for (const auto& filename : filenames) {
        Document doc(filename);
        corpus.push_back(doc);
    }
}

std::vector<std::string> RabinKarpMatcher::get_file_names(const std::string& directory_path) {
    std::vector<std::string> filenames;
    for (const auto& entry : std::filesystem::directory_iterator(directory_path)) {
        if (entry.is_regular_file()) {
            filenames.push_back(entry.path().string());
        }
    }
    return filenames;
}
