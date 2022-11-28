#include "InvertedIndex.h"

//----------------------------------------------------------------------------
void InvertedIndex::UpdateDocumentBase(std::vector<std::string> &inputDocs)
{
    docs = inputDocs;
    for(int i = 0; i < docs.size(); ++i)
    {
        documentThreadPool.emplace_back(&InvertedIndex::WorkWithDocument, this, i);
    }
    std::for_each(documentThreadPool.begin(),documentThreadPool.end(), std::mem_fn(&std::thread::join));
};
//----------------------------------------------------------------------------
void InvertedIndex::WorkWithDocument(int i)
{
    std::string wordFromSequence;
    int readSymbolPosition = 1;
    for(const auto j : docs[i])
    {
        if((j == ' ') || (readSymbolPosition == docs[i].length()))
        {
            if(readSymbolPosition == docs[i].length() && (j != ' '))
            {
                wordFromSequence += j;
            }
            bool findDocId = false;

            if(wordFromSequence.length() > 0)
            {
                freqDictionary_access.lock();
                for(auto it = freqDictionary[wordFromSequence].begin(); it != freqDictionary[wordFromSequence].end(); ++it)
                {
                    if(it->docId == i)
                    {
                        it->count++;
                        findDocId = true;
                        break;
                    }
                }

                if(findDocId == false)
                {
                    Entry entry;
                    entry.docId = i;
                    entry.count = 1;
                    freqDictionary[wordFromSequence].push_back(entry);
                }
                freqDictionary_access.unlock();
            }
            wordFromSequence.resize(0);
        }else
        {
            wordFromSequence += j;
        }

        ++readSymbolPosition;
    }
};
//-------------------------------------------------------------------------
std::map<std::string, std::vector<Entry>> InvertedIndex::GetDictionary() const
{
    return freqDictionary;
}
//-------------------------------------------------------------------------



