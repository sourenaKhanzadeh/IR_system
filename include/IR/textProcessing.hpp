//
// Created by sourena khanzadeh on 2023-06-25.
//

#ifndef SEARCH_ENGINE_TEXTPROCESSING_HPP
#define SEARCH_ENGINE_TEXTPROCESSING_HPP

#include <string>
#include <vector>
#include <map>

class Stemmer {
public:
    Stemmer() = default;
    ~Stemmer() = default;
    virtual std::string stem(std::string word) = 0;
private:
protected:
    std::string word;
};

class PorterStemmer : public Stemmer {
public:
    PorterStemmer() = default;
    ~PorterStemmer() = default;
    std::string stem(std::string word) override;
private:
    void step1a();
    void step1b();
    void step1c();
    void step2();
    void step3();
    void step4();
    void step5a();
    void step5b();
};


#endif //SEARCH_ENGINE_TEXTPROCESSING_HPP
