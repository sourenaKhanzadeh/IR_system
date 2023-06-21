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
#include <utility>
#include <map>

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
    std::map<std::string, int> wordIndexMap;
};



class InvertedIndex{
public:
    InvertedIndex();
    ~InvertedIndex();
    void addDocument(std::string title, std::string content);
    void printDocuments();
    void printInvertedIndex();
    void makeInvertedIndex();
    Document* getDocuments(){return documents;}
    std::map<std::string, std::vector<int>> getInvertedIndex(){return invertedIndex;}
protected:
private:
    Document* documents;
    int documentCount;
    int documentCapacity;
    std::map<std::string, std::vector<int>> invertedIndex;
    std::map<std::string, int> wordIndexMap;
};


class BooleanRetrievalII {
public:
    BooleanRetrievalII();
    ~BooleanRetrievalII();
    std::vector<Document> search(std::string query);
    void setInvertedIndex(InvertedIndex *invertedIndex);
protected:
private:
    InvertedIndex *invertedIndex;
};


class FileHandler{
public:
    FileHandler();
    ~FileHandler();
    void walk(const std::string& path);
    std::string* getLines();
    std::vector<Document> getDocuments();
protected:
    void addDocument(std::string title, std::string content);
private:
    std::string* lines{};
    int lineCount;
    std::vector<Document> documents;
};

std::vector<std::string> split(std::string str, char delimiter);


#endif //SEARCH_ENGINE_BOOLEANSIMPLE_HPP
