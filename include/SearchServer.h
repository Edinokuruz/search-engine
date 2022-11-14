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
#include <InvertedIndex.h>
#include "gtest/gtest.h"


//----------------------------------------------------------------------------
struct RelativeIndex
{
    size_t docId;
    float rank;

    bool operator == (const RelativeIndex& other) const
    {
        return (docId == other.docId &&
                rank == other.rank);
    }
};
//------------------------------------------------------------------------------
class SearchServer
{
public:
    SearchServer
            (
                    std::map<std::string, std::vector<Entry>> &freqDictionary,
                    std::vector<std::string> &fromRequests,
                    std::vector<std::string> &inFiles
            ) : AFreqDictionary(freqDictionary), requests(fromRequests), files(inFiles) {};

    std::vector<std::vector<RelativeIndex>> search() const;

private:
    std::map<std::string, std::vector<Entry>> AFreqDictionary;
    std::vector<std::string> requests;
    std::vector<std::string> files;
};

//----------------------------------------------------------------------------

void TestSearchServerFunctionality
        (
                std::map<std::string, std::vector<Entry>> &invertedIndexResult,
                std::vector<std::string> &requests,
                std::vector<std::string> &dataFromEachFile,
                std::vector<std::vector<RelativeIndex>> &expected
        );
//----------------------------------------------------------------------------