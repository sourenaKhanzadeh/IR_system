//
// Created by sourena khanzadeh on 2023-06-19.
//

#include <IR/BooleanIR.hpp>

BooleanRetrievalSimple::BooleanRetrievalSimple() {
    documentCount = 0;
    documentCapacity = 10;
    documents = new Document[documentCapacity];
    indexSize = 0;
    indexCapacity = 10;
    index = new int[indexCapacity];
    booleanTableSize = 0;
    booleanTableCapacity = 10;
    booleanTable = new bool*[booleanTableCapacity];
}

BooleanRetrievalSimple::~BooleanRetrievalSimple() {
    delete[] documents;
    delete[] index;
    for (int i = 0; i < booleanTableSize; ++i) {
        delete[] booleanTable[i];
    }
    delete[] booleanTable;
}

std::vector<Document> BooleanRetrievalSimple::search(std::string query) {
    std::vector<Document> result;
    std::vector<std::string> words = split(std::move(query), ' ');
    bool* queryBooleanTable = new bool[indexSize];
    for (const auto & word : words) {
        if (wordIndexMap.find(word) != wordIndexMap.end()) {
            int wordIndex = wordIndexMap[word];
            for (int i = 0; i < indexSize; ++i) {
                queryBooleanTable[i] = booleanTable[wordIndex][i];
            }
        }
    }


    for (int i = 0; i < booleanTableSize; ++i) {
        bool found = true;
        for (int j = 0; j < indexSize; ++j) {
            if (queryBooleanTable[j] != booleanTable[i][j]) {
                found = false;
                break;
            }
        }
        if (found) {
            result.push_back(documents[i]);
        }
    }
    delete[] queryBooleanTable;
    return result;
}

void BooleanRetrievalSimple::addDocument(std::string title, std::string content) {
    int documentSize = documentCount;
    if (documentCount == documentCapacity) {
        documentCapacity *= 2;
        Document* temp = new Document[documentCapacity];
        for (int i = 0; i < documentSize; ++i) {
            temp[i] = documents[i];
        }
        delete[] documents;
        documents = temp;
    }
    documents[documentCount].title = std::move(title);
    documents[documentCount++].content = std::move(content);
}

void BooleanRetrievalSimple::printDocuments() {
    for (int i = 0; i < documentCount; ++i) {
        std::cout << documents[i].title << std::endl;
        std::cout << documents[i].content << std::endl;
    }
}


void BooleanRetrievalSimple::printBooleanTable() {
    for (int i = 0; i < booleanTableSize; ++i) {
        for (int j = 0; j < indexSize; ++j) {
            std::cout << std::to_string(booleanTable[i][j]) << " ";
        }
        std::cout << std::endl;
    }
}

void BooleanRetrievalSimple::makeBooleanTable() {
    for (int i = 0; i < documentCount; ++i) {
        std::vector<std::string> words = split(documents[i].content, ' ');
        for (const auto & word : words) {
            bool found = false;
            for (int k = 0; k < indexSize; ++k) {
                if (word == documents[index[k]].content) {
                    found = true;
                    booleanTable[i][k] = true;
                }
            }
            wordIndexMap[word] = i;
            if (!found) {
                if (indexSize == indexCapacity) {
                    indexCapacity *= 2;
                    int* temp = new int[indexCapacity];
                    for (int k = 0; k < indexSize; ++k) {
                        temp[k] = index[k];
                    }
                    delete[] index;
                    index = temp;
                }
                index[indexSize++] = i;
                if (booleanTableSize == booleanTableCapacity) {
                    booleanTableCapacity *= 2;
                    bool** temp = new bool*[booleanTableCapacity];
                    for (int k = 0; k < booleanTableSize; ++k) {
                        temp[k] = booleanTable[k];
                    }
                    delete[] booleanTable;
                    booleanTable = temp;
                }
                booleanTable[booleanTableSize] = new bool[indexCapacity];
                for (int k = 0; k < indexSize; ++k) {
                    booleanTable[booleanTableSize][k] = false;
                }
                booleanTable[booleanTableSize][indexSize - 1] = true;
                booleanTableSize++;
            }
        }
    }
}

FileHandler::FileHandler() {
    lineCount = 0;
}

FileHandler::~FileHandler() {
    delete[] lines;
}

void FileHandler::walk(const std::string& path) {
    // walk a path and get all .txt files as a document
    // using the filesystem library
    for (const auto & entry : std::filesystem::directory_iterator(path)) {
        if (entry.path().extension() == ".txt") {
            std::ifstream file(entry.path());
            std::string line;
            std::string content;
            while (std::getline(file, line)) {
                content += line;
            }
            addDocument(entry.path().filename(), content);
        }
    }
}

void FileHandler::addDocument(std::string title, std::string content) {
    Document document;
    document.title = std::move(title);
    document.content = std::move(content);
    documents.push_back(document);
}

std::string* FileHandler::getLines() {
    return lines;
}

std::vector<Document> FileHandler::getDocuments() {
    return documents;
}


std::vector<std::string> split(std::string str, char delimiter) {
    std::vector<std::string> result;
    std::string temp;
    for (int i = 0; i < str.size(); ++i) {
        if (str[i] == delimiter) {
            result.push_back(temp);
            temp = "";
        } else {
            temp += str[i];
        }
    }
    result.push_back(temp);
    return result;
}


InvertedIndex::InvertedIndex() {
    documentCount = 0;
    documentCapacity = 10;
    documents = new Document[documentCapacity];
}

InvertedIndex::~InvertedIndex() {
    delete[] documents;
}

void InvertedIndex::addDocument(std::string title, std::string content) {
    int documentSize = documentCount;
    if (documentCount == documentCapacity) {
        documentCapacity *= 2;
        Document* temp = new Document[documentCapacity];
        for (int i = 0; i < documentSize; ++i) {
            temp[i] = documents[i];
        }
        delete[] documents;
        documents = temp;
    }
    documents[documentCount].title = std::move(title);
    documents[documentCount++].content = std::move(content);
}

void InvertedIndex::printDocuments() {
    for (int i = 0; i < documentCount; ++i) {
        std::cout << documents[i].title << std::endl;
        std::cout << documents[i].content << std::endl;
    }
}

void InvertedIndex::printInvertedIndex() {
    for (auto & it : invertedIndex) {
        std::cout << it.first << ": ";
        for (int i : it.second) {
            std::cout << i << " ";
        }
        std::cout << std::endl;
    }
}

void InvertedIndex::makeInvertedIndex() {
    for (int i = 0; i < documentCount; ++i) {
        std::vector<std::string> words = split(documents[i].content, ' ');
        for (const auto & word : words) {
            invertedIndex[word].push_back(i);
        }
    }
}

BooleanRetrievalII::BooleanRetrievalII() {
}

BooleanRetrievalII::~BooleanRetrievalII() {

}

void BooleanRetrievalII::setInvertedIndex(InvertedIndex *invertedIndex) {
    this->invertedIndex = invertedIndex;
}

std::vector<Document> BooleanRetrievalII::search(std::string query) {
    std::vector<Document> result;
    std::vector<std::string> words = split(query, ' ');
    std::vector<int> documentIds;
    for (const auto & word : words) {
        if (invertedIndex->getInvertedIndex().find(word) != invertedIndex->getInvertedIndex().end()) {
            std::vector<int> temp = invertedIndex->getInvertedIndex()[word];
            if (documentIds.empty()) {
                documentIds = temp;
            } else {
                std::vector<int> intersection;
                std::set_intersection(documentIds.begin(), documentIds.end(), temp.begin(), temp.end(), std::back_inserter(intersection));
                documentIds = intersection;
            }
        }
    }
    for (int documentId : documentIds) {
        result.push_back(invertedIndex->getDocuments()[documentId]);
    }
    return result;
}
