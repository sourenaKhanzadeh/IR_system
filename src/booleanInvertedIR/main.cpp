//
// Created by sourena khanzadeh on 2023-06-20.
//
#include <IR/BooleanIR.hpp>



int main(){
    FileHandler fileHandler;
    InvertedIndex invertedIndex;
    BooleanRetrievalII booleanRetrievalII;
    fileHandler.walk("../../../documents/mini");
    std::vector<Document> documents = fileHandler.getDocuments();
    for (int i = 0; i < fileHandler.getDocuments().size(); ++i) {
        invertedIndex.addDocument(documents[i].title, documents[i].content);
    }
    invertedIndex.makeInvertedIndex();
    invertedIndex.printInvertedIndex();
    booleanRetrievalII.setInvertedIndex(&invertedIndex);
    std::vector<Document> result = booleanRetrievalII.search("Hyderabad");
    for (auto & i : result) {
        std::cout << i.title << std::endl;
    }
    return 0;
}