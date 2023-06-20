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
    std::vector<std::string> words = split(query, ' ');
    bool* queryBooleanTable = new bool[indexSize];
    for (int i = 0; i < indexSize; ++i) {
        queryBooleanTable[i] = false;
    }
    for (int i = 0; i < words.size(); ++i) {
        for (int j = 0; j < indexSize; ++j) {
            if (words[i] == documents[index[j]].title) {
                queryBooleanTable[j] = true;
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
    documents[documentCount].title = title;
    documents[documentCount++].content = content;
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
        for (int j = 0; j < words.size(); ++j) {
            bool found = false;
            for (int k = 0; k < indexSize; ++k) {
                if (words[j] == documents[index[k]].title) {
                    found = true;
                    booleanTable[i][k] = true;
                }
            }
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
    documentCount = 0;
    documentCapacity = 10;
}

FileHandler::~FileHandler() {
    delete[] lines;
    delete[] documents;
}

void FileHandler::walk(std::string path) {
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
    documents[documentCount].title = title;
    documents[documentCount++].content = content;
}

std::string* FileHandler::getLines() {
    return lines;
}

Document* FileHandler::getDocuments() {
    return documents;
}

int FileHandler::getLineCount() {
    return lineCount;
}

int FileHandler::getDocumentCount() {
    return documentCount;
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

