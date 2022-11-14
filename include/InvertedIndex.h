#pragma once

#include <iostream>
#include "nlohmann/json.hpp"
#include <string>
#include <cstring>
#include <memory>
#include <vector>
#include <map>
#include <exception>
#include <fstream>
#include <stdio.h>
#include <thread>
#include <mutex>
#include <iterator>
#include <algorithm>
#include <functional>
#include <ctime>
#include "gtest/gtest.h"

//-----------------------------------------------------------------------------------
struct Entry
{
    size_t docId;
    size_t count;

    bool operator == (const Entry& other) const
    {
        return (docId == other.docId &&
                count == other.count);
    }
};
//-----------------------------------------------------------------------------------
class InvertedIndex
{
public:
    InvertedIndex() = default;
    void UpdateDocumentBase(std::vector<std::string> &inputDocs);
    void WorkWithDocument(int i);
    std::map<std::string, std::vector<Entry>> GetDictionary() const;
private:
    std::vector<std::string> docs;
    std::map<std::string, std::vector<Entry>> freqDictionary;
    std::vector<std::thread> documentThreadPool;
    std::mutex freqDictionary_access;
};
//-----------------------------------------------------------------------------------
void TestInvertedIndexFunctionality
        (
                std::vector<std::string> &docs,
                std::map<std::string, std::vector<Entry>> &expected
        );
//-----------------------------------------------------------------------------------
