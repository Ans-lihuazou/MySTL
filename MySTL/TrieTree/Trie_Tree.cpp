#include "Trie_Tree.h"
#include <string>

MyTree::trie_tree::trie_tree() {

    m_bIsEnd = false;
    m_cData = 0;
}

MyTree::trie_tree::trie_tree(const char& c_cData, bool bIsEnd) :m_cData(c_cData), m_bIsEnd(bIsEnd) {

}

MyTree::trie_tree::~trie_tree() {

    std::map<char, pointer>::iterator iter = m_mapNext.begin();
    while (iter != m_mapNext.end()) {
        delete iter->second;
        iter->second = nullptr;
        iter = m_mapNext.erase(iter);
    }
}

void MyTree::trie_tree::setString(const std::string& str) {
    
    pointer ptr = this;

    for (const char& c : str) {
        
        ptr = ptr->setNext(c);
    }
    ptr->m_bIsEnd = true;
}

bool MyTree::trie_tree::findString(const std::string& str) {

    pointer ptr = this;

    for (const char& c : str) {
        
        ptr = ptr->findNext(c);
        if (ptr == nullptr) {
            return false;
        }
    }

    return ptr->isExixt();
}

bool MyTree::trie_tree::isExixt() {
    return this->m_bIsEnd;
}

MyTree::trie_tree::pointer MyTree::trie_tree::findNext(const char& c_cData) {
    
    pointer pResult = nullptr;

    if (m_mapNext.count(c_cData)) {
        pResult = m_mapNext[c_cData];
    }

    return pResult;
}

MyTree::trie_tree::pointer MyTree::trie_tree::setNext(const char& c_cData) {

    pointer pResult = nullptr;

    if (m_mapNext.count(c_cData)) {
        pResult = m_mapNext[c_cData];
    }
    else {
        pResult = new trie_tree(c_cData);
        m_mapNext[c_cData] = pResult;
    }

    return pResult;
}

#include <iostream>

int main() {

    int n; std::cin >> n;
    MyTree::trie_tree* first = new MyTree::trie_tree();
    MyTree::trie_tree* second = new MyTree::trie_tree();
    std::string str;
    for (int i = 1; i <= n; i++) {
        std::cin >> str;
        first->setString(str);
    }

    int m; std::cin >> m;
    for (int i = 1; i <= m; i++) {
        std::cin >> str;
        bool isExist = first->findString(str);
        if (false == isExist) {
            std::cout << "WRONG\n";
        }
        else {
            bool isRepeat = second->findString(str);
            if (false == isRepeat) {
                std::cout << "OK\n";
                second->setString(str);
            }
            else {
                std::cout << "REPEAT\n";
            }
        }
    }

    delete first;
    delete second;

    return 0;
}