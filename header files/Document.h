#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <string>
#include <vector>

class Document {
public:
    Document(std::string file_path);

    void parse_sentences();
    std::vector<std::string> get_sentences();
    bool search_pattern(const std::string &pattern) const;
    std::string get_file_path() const;
    void set_plagiarism_percentage(float percentage);
    float get_plagiarism_percentage();

private:
    std::string file_path;
    std::vector<std::string> sentences;
    float plagiarism_percentage;
};

#endif // DOCUMENT_H
