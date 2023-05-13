#include <fstream>
#include <sstream>
#include "Document.h"

Document::Document(std::string file_path) {
    this->file_path = file_path;
}

void Document::parse_sentences() {
    // Clear any existing sentences
    sentences.clear();
    // Open file
    std::ifstream file(file_path);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file: " + file_path);
    }
    // Read file line by line and split each line into sentences
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string sentence;
        while (std::getline(iss, sentence, '.')) {
            // Remove leading/trailing whitespace (spaces, tabs, newlines, carriage returns, form feeds, vertical tabs)
            sentence.erase(0, sentence.find_first_not_of(" \t\n\r\f\v"));
            sentence.erase(sentence.find_last_not_of(" \t\n\r\f\v") + 1);
            // Add sentence to vector (if it's not empty)
            if (!sentence.empty()) {
                sentences.push_back(sentence);
            }
        }
    }
}

std::vector<std::string> Document::get_sentences() {
    return sentences;
}


void Document::set_plagiarism_percentage(float percentage) {
    plagiarism_percentage = percentage;
}

float Document::get_plagiarism_percentage() {
    return plagiarism_percentage;
}
std::string Document::get_file_path() const {
    return file_path;
}

bool Document::search_pattern(const std::string& pattern) const {
    for (const auto& sentence : sentences) {
        if (sentence.find(pattern) != std::string::npos) {
            return true; // Pattern found in the sentence
        }
    }
    return false; // Pattern not found in any sentence
}
