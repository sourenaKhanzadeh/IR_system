//
// Created by sourena khanzadeh on 2023-06-25.
//
#include "IR/textProcessing.hpp"


std::string PorterStemmer::stem(std::string word) {
    this->word = word;
    step1a();
    step1b();
    step1c();
    step2();
    step3();
    step4();
    step5a();
    step5b();
    return this->word;
}

void PorterStemmer::step1a() {
    if (word[word.length() - 1] == 's') {
        if (word[word.length() - 2] == 's' || word[word.length() - 2] == 'u') {
            word.erase(word.length() - 2, 2);
        } else {
            word.erase(word.length() - 1, 1);
        }
    }
}

void PorterStemmer::step1b() {
    if (word[word.length() - 1] == 'd') {
        if (word[word.length() - 2] == 'e') {
            if (word[word.length() - 3] == 'e') {
                word.erase(word.length() - 3, 3);
            } else {
                word.erase(word.length() - 2, 2);
            }
        } else {
            word.erase(word.length() - 1, 1);
        }
    } else if (word[word.length() - 1] == 'g') {
        if (word[word.length() - 2] == 'n') {
            if (word[word.length() - 3] == 'i') {
                word.erase(word.length() - 3, 3);
            } else {
                word.erase(word.length() - 2, 2);
            }
        } else {
            word.erase(word.length() - 1, 1);
        }
    }
}

void PorterStemmer::step1c() {
    if (word[word.length() - 1] == 'y') {
        if (word[word.length() - 2] == 'a' || word[word.length() - 2] == 'e' || word[word.length() - 2] == 'i' ||
            word[word.length() - 2] == 'o' || word[word.length() - 2] == 'u') {
            word.erase(word.length() - 1, 1);
        }
    }
}

void PorterStemmer::step2() {
    if (word[word.length() - 1] == 'e') {
        if (word[word.length() - 2] == 'a' || word[word.length() - 2] == 'e' || word[word.length() - 2] == 'i' ||
            word[word.length() - 2] == 'o' || word[word.length() - 2] == 'u') {
            word.erase(word.length() - 1, 1);
        } else if (word[word.length() - 2] == 'l') {
            word.erase(word.length() - 2, 2);
        }
    }
}

void PorterStemmer::step3() {
    if (word[word.length() - 1] == 'l') {
        if (word[word.length() - 2] == 'a' || word[word.length() - 2] == 'e' || word[word.length() - 2] == 'i' ||
            word[word.length() - 2] == 'o' || word[word.length() - 2] == 'u') {
            word.erase(word.length() - 1, 1);
        }
    }
}

void PorterStemmer::step4() {
    if (word[word.length() - 1] == 's') {
        if (word[word.length() - 2] == 'e') {
            word.erase(word.length() - 2, 2);
        }
    }
}

void PorterStemmer::step5a() {
    if (word[word.length() - 1] == 'e') {
        if (word.length() > 2) {
            if (word[word.length() - 2] == 'e') {
                word.erase(word.length() - 2, 2);
            }
        }
    }
}

void PorterStemmer::step5b() {
    if (word[word.length() - 1] == 'l') {
        if (word[word.length() - 2] == 'l') {
            word.erase(word.length() - 2, 2);
        }
    }
}


