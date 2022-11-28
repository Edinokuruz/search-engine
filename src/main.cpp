#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <thread>
#include <functional>
#include "nlohmann/json.hpp"
#include "SearchServer.h"
#include "InvertedIndex.h"
#include "ConverterJSON.h"

//------------------------------------------------------------------------------
nlohmann::json get_data_from_file(std::ifstream &file)
{
    if(file.is_open())
    {
        nlohmann::json configDataReceive;
        file >> configDataReceive;
        return configDataReceive;
    }else
    {
        throw CheckFileExistence();
    }
};
//----------------------------------------------------------------------------
DataFromConfigFile get_data_from_config(nlohmann::json &data)
{
    DataFromConfigFile dataFromConfigFile;
    bool configStatus = false;
    for(auto i = data.begin(); i != data.end(); ++i)
    {
        if(i.key() == "config")
        {
            for(auto j = data["config"].begin(); j != data["config"].end(); ++j)
            {
                if(j.key() == "name")
                {
                    dataFromConfigFile.name = j.value();
                }else if(j.key() == "version")
                {
                    dataFromConfigFile.version = j.value();
                }else if(j.key() == "max_responses")
                {
                    dataFromConfigFile.maxResponses = j.value();
                }
            }
            configStatus = true;
            break;
        }
    }

    if(configStatus)
    {
        return dataFromConfigFile;
    }else
    {
        throw CheckConfigDataExistence();
    }
};

//------------------------------------------------------------------------------
int main(int argc, char ** argv)
{

    std::ifstream configFileRead("config.json");
    nlohmann::json dataFromConfig;
    try
    {
        dataFromConfig = get_data_from_file(configFileRead);
    }
    catch(const CheckFileExistence &x)
    {
        std::cerr << "Message: " << x.what() << std::endl;
        return 0;
    }

    DataFromConfigFile dataFromConfigFile;
    try
    {
        dataFromConfigFile = get_data_from_config(dataFromConfig);
    }catch(const CheckConfigDataExistence &x)
    {
        std::cerr << "Message: " << x.what() << std::endl;
        return 0;
    }
    std::cout << "Project name: " << dataFromConfigFile.name << std::endl;

    ConverterJSON X(dataFromConfig, dataFromConfigFile);
    std::vector<std::string> part1ConverterJSONResult;
    try
    {
        part1ConverterJSONResult = X.GetTextDocuments();
    }catch(const CheckFilesDataExistence &x)
    {
        std::cerr << "Message: " << x.what() << std::endl;
    }

    //InvertedIndex result--------------------------------------
    InvertedIndex part2InvertedIndex;
    part2InvertedIndex.UpdateDocumentBase(part1ConverterJSONResult);
    std::map<std::string, std::vector<Entry>> part2InvertedIndexResult;
    part2InvertedIndexResult = part2InvertedIndex.GetDictionary();

    //SearchServer result---------------------------------------
    std::vector<std::string> fromRequestsFile = X.GetRequests();
    SearchServer part3SearchServer(part2InvertedIndexResult, fromRequestsFile, part1ConverterJSONResult);

    std::vector<std::vector<RelativeIndex>> temporaryResult = part3SearchServer.search();
    std::vector<std::vector<std::pair<int, float>>> result;

    //RelativeIndex to std::pair<int, float>-------------------
    for(auto it_a = temporaryResult.begin(); it_a != temporaryResult.end(); ++it_a)
    {
        std::vector<std::pair<int, float>> result_a;
        for(auto it_b = it_a->begin(); it_b != it_a->end(); ++it_b)
        {
            std::pair<int, float> pair_a = std::make_pair(it_b->docId, it_b->rank);
            result_a.push_back(pair_a);
        }
        result.push_back(result_a);
    }

    for(int i = 0; i < result.size(); ++i)
    {
        std::sort(result[i].begin(), result[i].end(), [](std::pair<int,float> &left, std::pair<int,float> &right)
        {
            return left.second > right.second;
        });
    }

    X.putAnswers(result);

    return (0);
}
