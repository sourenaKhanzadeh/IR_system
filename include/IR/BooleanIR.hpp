//
// Created by sourena khanzadeh on 2023-06-19.
//

#ifndef SEARCH_ENGINE_BOOLEANSIMPLE_HPP
#define SEARCH_ENGINE_BOOLEANSIMPLE_HPP

#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <filesystem>

struct Document {
    std::string title;
    std::string content;
};


class BooleanRetrievalSimple {
public:
    BooleanRetrievalSimple();
    ~BooleanRetrievalSimple();
    std::vector<Document> search(std::string query);
    void addDocument(std::string title, std::string content);
    void printDocuments();
    void printBooleanTable();
    void makeBooleanTable();
private:
protected:
    Document* documents;
    int documentCount;
    int documentCapacity;
    int* index;
    int indexSize;
    int indexCapacity;
    bool** booleanTable;
    int booleanTableSize;
    int booleanTableCapacity;
};

class FileHandler{
public:
    FileHandler();
    ~FileHandler();
    void walk(std::string path);
    std::string* getLines();
    int getLineCount();
    Document* getDocuments();
    int getDocumentCount();
protected:
    void addDocument(std::string title, std::string content);
private:
    std::string* lines;
    int lineCount;
    Document* documents;
    int documentCount;
    int documentCapacity;
};

std::vector<std::string> split(std::string str, char delimiter);


#endif //SEARCH_ENGINE_BOOLEANSIMPLE_HPP
