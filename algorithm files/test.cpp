/*#include <iostream>
#include <set>
#include "HammingDistanceMatcher.h"
#include "BoyerMooreMatcher.h"
#include "KMPMatcher.h"
#include "RabinKarpMatcher.h"

using namespace std;

int main() {
    // Create the matcher objects
    HammingDistanceMatcher hammingMatcher("corpus");
    BoyerMooreMatcher boyerMooreMatcher("corpus");
    KMPMatcher kmpMatcher("corpus");
    RabinKarpMatcher rabinKarpMatcher("corpus");

    // Get the document name from the user
    string documentName;
    cout << "Enter the name of the document to check for plagiarism: ";
    cin>>documentName;

    // Perform matching using each algorithm
    set<string> hammingMatches = hammingMatcher.matchDocument(documentName);
    set<string> boyerMooreMatches = boyerMooreMatcher.matchDocument(documentName);
    set<string> kmpMatches = kmpMatcher.matchDocument(documentName);
    set<string> rabinKarpMatches = rabinKarpMatcher.matchDocument(documentName);

    // Print the matches
    cout << "Hamming Distance Matches:" << endl;
    for (const string& match : hammingMatches) {
        cout << "- " << match << endl;
    }

    cout << "Boyer-Moore Matches:" << endl;
    for (const string& match : boyerMooreMatches) {
        cout << "- " << match << endl;
    }

    cout << "KMP Matches:" << endl;
    for (const string& match : kmpMatches) {
        cout << "- " << match << endl;
    }

    cout << "Rabin-Karp Matches:" << endl;
    for (const string& match : rabinKarpMatches) {
        cout << "- " << match << endl;
    }

    return 0;
}
*/