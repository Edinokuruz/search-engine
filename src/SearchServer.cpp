#include "SearchServer.h"

//------------------------------------------------------------------------
std::vector<std::vector<RelativeIndex>> SearchServer::search() const
{
    //Get words from request.txt------------------
    std::vector<std::vector<std::string>> wordPool;
    for (int m = 0; m < requests.size(); ++m)
    {
        wordPool.push_back(std::vector<std::string>());
        std::string findWord;
        int symbolPosition = 1;
        for (const char i: requests[m])
        {
            if ((i == ' ') || (symbolPosition == requests[m].length()))
            {
                if ((symbolPosition == requests[m].length()) && (i != ' '))
                {
                    findWord += i;
                }
                if (findWord.length() > 0)
                {
                    wordPool[m].push_back(findWord);
                    findWord.resize(0);
                }
            }else
            {
                findWord += i;
            }
            ++symbolPosition;
        }
    }

    //Get total quantity of the searched words in all files-------------------
    std::vector<std::multimap<int, std::string>> numberOfSearchedWord;
    for (int m = 0; m < requests.size(); ++m)
    {
        numberOfSearchedWord.push_back(std::multimap<int, std::string>());
        for (const auto &i: wordPool[m])
        {
            int wordQuantityInAllDocuments = 0;
            for (auto it = AFreqDictionary.begin(); it != AFreqDictionary.end(); ++it)
            {
                if (i == it->first)
                {
                    for (const auto j: it->second)
                    {
                        wordQuantityInAllDocuments += j.count;
                    }
                    break;
                }
            }
            bool iterationCheck = false;
            for (auto it = numberOfSearchedWord[m].begin(); it != numberOfSearchedWord[m].end(); ++it)
            {
                if((it->first == wordQuantityInAllDocuments) && (it->second == i))
                {
                    iterationCheck = true;
                    break;
                }
            }
            if(!iterationCheck)
            {
                numberOfSearchedWord[m].insert(std::pair<int, std::string>(wordQuantityInAllDocuments, i));
            }
        }
    }

    //Get relevance and return data---------------------
    std::vector<std::vector<RelativeIndex>> finalResult;
    for (int m = 0; m < requests.size(); ++m)
    {
        finalResult.push_back(std::vector<RelativeIndex>());
        std::vector<float> relevanceForEachDocument;
        int maxValue = 0;
        for (int i = 0; i < files.size(); ++i)
        {
            relevanceForEachDocument.push_back(0.00000f);
        }
        int findMatches = 0;
        for (auto it_a = numberOfSearchedWord[m].begin(); it_a != numberOfSearchedWord[m].end(); ++it_a)
        {
            for (auto it_b = AFreqDictionary.begin(); it_b != AFreqDictionary.end(); ++it_b)
            {
                if(it_a->second == it_b->first)
                {
                    ++findMatches;
                    for (auto it_c = it_b->second.begin(); it_c != it_b->second.end(); ++it_c)
                    {
                        relevanceForEachDocument[it_c->docId] += it_c->count;
                        if (relevanceForEachDocument[it_c->docId] > maxValue)
                        {
                            maxValue = relevanceForEachDocument[it_c->docId];
                        }
                    }
                    break;
                }
            }
        }

        if(findMatches == 0)
        {
            maxValue = 1;
            for (int i = 0; i < relevanceForEachDocument.size(); ++i) {
                relevanceForEachDocument[i] = 0;
            }
        }

        for (int i = 0; i < relevanceForEachDocument.size(); ++i)
        {
            RelativeIndex relativeIndex;
            relativeIndex.docId = i;
            relativeIndex.rank = relevanceForEachDocument[i] / maxValue;
            if(relativeIndex.rank != 0)
            {
                finalResult[m].push_back(relativeIndex);
            }
        }
    }

    return (finalResult);
};
//-----------------------------------------------------------------------



