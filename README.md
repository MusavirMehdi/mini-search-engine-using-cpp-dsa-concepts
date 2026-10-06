# Mini Search Engine (C++ & DSA)

A lightweight, terminal-based search engine implemented in **C++** utilizing foundational **Data Structures and Algorithms (DSA)** concepts, notably an **Inverted Index**, **Hash Maps**, and **Frequency-Based Ranking**.

---

## Table of Contents

- [Overview](#overview)
- [Key DSA Concepts Used](#key-dsa-concepts-used)
- [How It Works](#how-it-works)
- [Project Structure](#project-structure)
- [Getting Started](#getting-started)
  - [Prerequisites](#prerequisites)
  - [Build and Run](#build-and-run)
- [Example Usage](#example-usage)
- [Future Enhancements](#future-enhancements)

---

## Overview

Modern search engines rely on specialized data structures to efficiently search through large text corpora without scanning every document linearly on each query.

This project indexes a collection of text documents upon launch into an **Inverted Index**, normalizes search terms, and calculates relevance scores for multi-word queries to return the most relevant matching documents in ranked order.

---

## Key DSA Concepts Used

| Concept | Implementation in C++ | Purpose |
|---|---|---|
| **Inverted Index** | `unordered_map<string, unordered_map<string, int>>` | Maps each unique vocabulary word to the set of documents where it appears and its frequency within each document. |
| **Hash Tables / Maps** | `std::unordered_map` | Provides average $O(1)$ constant time lookup for terms and document scores. |
| **String Normalization** | Two-pointer traversal, `isalnum()`, `tolower()` | Cleans tokens by stripping punctuation and converting text to lower case for case-insensitive matching. |
| **Scoring & Accumulation** | Map-based term frequency summation | Aggregates relevance scores per document across multiple search query tokens. |
| **Sorting & Ranking** | `std::sort` with custom lambda comparator | Sorts matching documents in descending order of their relevance score ($O(K \log K)$ where $K$ is the number of matching documents). |

---

## How It Works

1. **Indexing Phase**:
   - The engine opens and reads each document in the `docs/` directory.
   - Text is tokenized into individual words.
   - Each token is sanitized to lowercase alphanumeric characters via `cleanWord()`.
   - The inverted index updates the count: `index[word][document]++`.

2. **Query Phase**:
   - The user inputs an arbitrary search phrase.
   - The phrase is split into tokens and sanitized using the same normalization logic.
   - For every token present in the index, each document containing that token has its score incremented by the token's frequency.

3. **Ranking Phase**:
   - The aggregated `(document, score)` pairs are converted into a `vector`.
   - The results are sorted by score in descending order.
   - The top 5 matching results are formatted and displayed.

---

## Project Structure

```text
WordRank/
├── docs/
│   ├── ai.txt           # Sample document on Artificial Intelligence
│   ├── cpp.txt          # Sample document on C++
│   ├── dsa.txt          # Sample document on Data Structures & Algorithms
│   └── networking.txt   # Sample document on Computer Networking
├── .gitignore           # Ignores compiled binaries and temporary editor files
├── main.cpp             # Core search engine implementation
└── README.md            # Project documentation
```

---

## Getting Started

### Prerequisites

You need a C++ compiler supporting **C++17** or higher:
- **GCC / MinGW**: `g++` 7.0+
- **Clang**: `clang++` 5.0+
- **MSVC**: Visual Studio 2017+

### Build and Run

1. **Clone the repository:**
   ```bash
   git clone https://github.com/MusavirMehdi/mini-search-engine-using-cpp-dsa-concepts.git
   cd mini-search-engine-using-cpp-dsa-concepts
   ```

2. **Compile the source code:**
   - **Linux / macOS**:
     ```bash
     g++ -std=c++17 main.cpp -o search
     ```
   - **Windows (MinGW / PowerShell)**:
     ```powershell
     g++ -std=c++17 main.cpp -o search.exe
     ```

3. **Run the search engine:**
   - **Linux / macOS**:
     ```bash
     ./search
     ```
   - **Windows**:
     ```powershell
     .\search.exe
     ```

---

## Example Usage

```text
====================================
          MINISEARCH
====================================

Indexing documents...

Indexed: docs/cpp.txt
Indexed: docs/dsa.txt
Indexed: docs/ai.txt
Indexed: docs/networking.txt

Documents indexed: 4
Unique words: 63

------------------------------------
Enter a search query.
Type 'exit' to quit.
------------------------------------

Search: programming
Results:

1. docs/cpp.txt | Score: 2
2. docs/dsa.txt | Score: 2

Search: machine learning
Results:

1. docs/ai.txt | Score: 2

Search: exit

Search engine closed.
```

---

## Future Enhancements

- [ ] **TF-IDF Scoring**: Implement Term Frequency-Inverse Document Frequency to penalize ubiquitous terms.
- [ ] **Stop Words Filtering**: Remove common noise words (e.g., "the", "is", "at") during indexing.
- [ ] **Stemming / Lemmatization**: Use algorithms like the Porter Stemmer to reduce words to their base root (e.g., "programs" $\rightarrow$ "program").
- [ ] **Dynamic Directory Indexing**: Automatically discover all `.txt` files in a designated folder using C++17 `std::filesystem`.
- [ ] **Boolean Queries**: Support `AND`, `OR`, and `NOT` operators.

---

## License

This project is open source and available under the [MIT License](LICENSE).
