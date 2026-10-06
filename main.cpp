#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <cctype>

using namespace std;

// word -> (document -> frequency)
using InvertedIndex =
    unordered_map<string, unordered_map<string, int>>;


// Clean a word
string cleanWord(string word) {

    string result;

    for (char c : word) {

        if (isalnum(static_cast<unsigned char>(c))) {
            result += tolower(static_cast<unsigned char>(c));
        }
    }

    return result;
}


// Add one document to the index
bool indexDocument(
    const string& filename,
    InvertedIndex& index
) {

    ifstream file(filename);

    if (!file) {
        cout << "Could not open: "
             << filename << endl;
        return false;
    }

    string word;

    while (file >> word) {

        word = cleanWord(word);

        if (!word.empty()) {
            index[word][filename]++;
        }
    }

    file.close();
    return true;
}


// Search documents
vector<pair<string, int>> search(
    const string& query,
    const InvertedIndex& index
) {

    // document -> score
    unordered_map<string, int> scores;

    string word;
    stringstream ss(query);

    while (ss >> word) {

        word = cleanWord(word);

        if (word.empty())
            continue;

        auto it = index.find(word);

        // Word does not exist
        if (it == index.end())
            continue;

        // Add frequency to document score
        for (const auto& item : it->second) {

            const string& document = item.first;
            int frequency = item.second;

            scores[document] += frequency;
        }
    }


    // Convert map to vector
    vector<pair<string, int>> results(
        scores.begin(),
        scores.end()
    );


    // Sort highest score first
    sort(
        results.begin(),
        results.end(),
        [](const auto& a, const auto& b) {
            return a.second > b.second;
        }
    );

    return results;
}


int main() {

    InvertedIndex index;


    // Documents to index
    vector<string> documents = {
        "docs/cpp.txt",
        "docs/dsa.txt",
        "docs/ai.txt",
        "docs/networking.txt"
    };


    cout << "====================================\n";
    cout << "          MINISEARCH\n";
    cout << "====================================\n\n";


    cout << "Indexing documents...\n\n";


    // Index every document
    int indexedCount = 0;
    for (const string& document : documents) {

        if (indexDocument(document, index)) {
            cout << "Indexed: "
                 << document
                 << endl;
            indexedCount++;
        }
    }


    cout << "\nDocuments indexed: "
         << indexedCount
         << endl;

    cout << "Unique words: "
         << index.size()
         << endl;


    cout << "\n------------------------------------\n";
    cout << "Enter a search query.\n";
    cout << "Type 'exit' to quit.\n";
    cout << "------------------------------------\n";


    while (true) {

        cout << "\nSearch: ";

        string query;

        getline(cin, query);


        if (query == "exit")
            break;


        if (query.empty())
            continue;


        vector<pair<string, int>> results =
            search(query, index);


        if (results.empty()) {

            cout << "No results found.\n";

            continue;
        }


        cout << "\nResults:\n\n";


        int rank = 1;


        for (const auto& result : results) {

            cout << rank
                 << ". "
                 << result.first
                 << " | Score: "
                 << result.second
                 << endl;

            rank++;


            if (rank > 5)
                break;
        }
    }


    cout << "\nSearch engine closed.\n";

    return 0;
}