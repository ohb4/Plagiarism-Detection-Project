#ifndef RABINKARPMATCHER_H
#define RABINKARPMATCHER_H

#include <string>
#include <set>
#include <vector>
#include "Document.h"
#include "PlagiarismDetector.h"


class RabinKarpMatcher : public PlagiarismDetector {
public:
    RabinKarpMatcher(std::string corpus_dir);
    std::set<std::string> match(const std::string& sentence) const;

private:
    std::vector<Document> corpus;
    std::string corpus_dir;

    void load_corpus();
    std::vector<std::string> get_file_names(const std::string& directory_path);
};

#endif // RABINKARPMATCHER_H
