//
// Created by sourena khanzadeh on 2023-06-18.
//

#include <IR/BooleanIR.hpp>

int main(){
    FileHandler fileHandler;
    fileHandler.walk("../../../documents/mini");
    BooleanRetrievalSimple booleanRetrievalSimple;
    std::vector<Document> documents = fileHandler.getDocuments();
    for (int i = 0; i < fileHandler.getDocuments().size(); ++i) {
        booleanRetrievalSimple.addDocument(documents[i].title, documents[i].content);
    }
    booleanRetrievalSimple.makeBooleanTable();
//    booleanRetrievalSimple.printDocuments();
//    booleanRetrievalSimple.printBooleanTable();
    std::vector<Document> result = booleanRetrievalSimple.search("Muslim.");
    for (auto & i : result) {
        std::cout << i.title << std::endl;
    }
    return 0;
}