#include "ConverterJSON.h"

//---------------------------------------------------------------------------
const char* CheckFileExistence::what() const noexcept
{
    return ("file is missing");
}
//----------------------------------------------------------------------------
const char* CheckConfigDataExistence::what() const noexcept
{
    return ("file is empty");
}
//----------------------------------------------------------------------------
const char* CheckFilesDataExistence::what() const noexcept
{
    return ("files are missing");
}
//-----------------------------------------------------------------------------
std::vector<std::string> ConverterJSON::GetTextDocuments() const
{
    //Receive file paths and check for existence
    std::vector<std::string> filePath;
    int filesQuantity = 0;

    if(data["files"] != nullptr)
    {
        for (auto i = data["files"].begin(); i != data["files"].end(); ++i)
        {
            std::string checkTxtFileExistence = i.value();
            std::filesystem::path pathOfTheConsideredFile = checkTxtFileExistence;
            if(pathOfTheConsideredFile.extension() == ".txt")
            {
                filePath.push_back(i.value());
                ++filesQuantity;
            }
        }
    }else
    {
        throw CheckFilesDataExistence();
    }

    if(filesQuantity == 0)
    {
        throw CheckFilesDataExistence();
    }

    //Receive info from files
    std::vector<std::string> dataFromFiles;
    for(const std::string &i : filePath)
    {
        std::ifstream loadFromFile(i);
        if(loadFromFile.is_open())
        {
            std::string resultData;
            while(loadFromFile)
            {
                std::string fileData;
                getline(loadFromFile, fileData);
                resultData += fileData;
            }
            dataFromFiles.push_back(resultData);
            loadFromFile.close();
        }else
        {
            std::cout << "Error!" << std::endl;
        }
    }
    return dataFromFiles;
};
//---------------------------------------------------------------------------
int ConverterJSON::getResponsesLimit() const
{
    return (dataFromConfigFile.maxResponses);
};
//---------------------------------------------------------------------------
std::vector<std::string> ConverterJSON::GetRequests() const
{
    std::vector<std::string> receivedDataFromRequestsFile;

    std::ifstream requestsFileRead("requests.json");
    nlohmann::json dataFromRequests;
    try
    {
        if(requestsFileRead.is_open())
        {
            requestsFileRead >> dataFromRequests;
            try
            {
                bool requestsStatus = false;
                for(auto i = dataFromRequests.begin(); i != dataFromRequests.end(); ++i)
                {
                    if(i.key() == "requests")
                    {
                        try
                        {
                            for (auto j = dataFromRequests["requests"].begin(); j != dataFromRequests["requests"].end(); ++j)
                            {
                                receivedDataFromRequestsFile.push_back(j.value());
                            }
                            if(receivedDataFromRequestsFile.size() == 0)
                            {
                                throw CheckFilesDataExistence();
                            }
                        }catch(const CheckFilesDataExistence &x)
                        {
                            std::cerr << "Message: " << x.what() << std::endl;
                            return (receivedDataFromRequestsFile);
                        }
                        requestsStatus = true;
                        break;
                    }
                }

                if(!requestsStatus)
                {
                    throw CheckConfigDataExistence();
                }
            }catch(const CheckConfigDataExistence &x)
            {
                std::cerr << "Message: " << x.what() << std::endl;
                return (receivedDataFromRequestsFile);
            }
        }else
        {
            throw CheckFileExistence();
        }
    }
    catch(const CheckFileExistence &x)
    {
        std::cerr << "Message: " << x.what() << std::endl;
        return (receivedDataFromRequestsFile);
    }

    return (receivedDataFromRequestsFile);
};
//---------------------------------------------------------------------------
void ConverterJSON::putAnswers(std::vector<std::vector<std::pair<int, float>>> &answers) const
{
    //Check file existence or clear an existing file-------------------------
    std::string answersFilePath = "answers.json";
    std::ifstream receivedDataRead(answersFilePath.c_str());
    if (receivedDataRead.is_open())
    {
        std::ofstream fileClear("answers.json");
        fileClear << " ";
        fileClear.close();
        std::cout << "File opened and cleared!" << std::endl;
    }else{
        std::cout << "File created and opened!" << std::endl;
    }

    std::ofstream receivedDataWrite("answers.json");
    nlohmann::json dataWrite;
    receivedDataWrite << "{" << std::endl;
    receivedDataWrite << std::setw(8) << "\"answers\": " << "{" << std::endl;
    for(int i = 0; i < answers.size(); ++i)
    {
        std::string request = "request" + std::to_string(i);
        receivedDataWrite << std::setw(8) << "\"" << request << "\": " << "{" << std::endl;
        if(answers[i].size() != 0)
        {
            receivedDataWrite << std::setw(31) << "\"result\": \"true\", " << std::endl;
            if(answers[i].size() != 1)
            {
                receivedDataWrite << std::setw(26) << "\"relevance\": " << "{" << std::endl;
            }
        }else
        {
            receivedDataWrite << std::setw(31) << "\"result\": \"false\"" << std::endl;
        }

        for(int j = 0; j < answers[i].size(); ++j)
        {
            if(j == answers[i].size() - 1)
            {
                receivedDataWrite << std::setw(29) << "\"docid\": \"" << answers[i][j].first << "\", \"rank\": \"" << answers[i][j].second << "\"" << std::endl;
            }else
            {
                receivedDataWrite << std::setw(29) << "\"docid\": \"" << answers[i][j].first << "\", \"rank\": \"" << answers[i][j].second << "\"," << std::endl;
            }
        }

        if((answers[i].size() != 0) && (answers[i].size() != 1))
        {
            receivedDataWrite << std::setw(14) << "}" << std::endl;
        }

        if(i == answers.size() - 1)
        {
            receivedDataWrite << std::setw(8) << "}" << std::endl;
        }else
        {
            receivedDataWrite << std::setw(9) << "}," << std::endl;
        }
    }

    receivedDataWrite << std::setw(4) << "}" << std::endl << "}" << std::endl;
    receivedDataWrite.close();

    std::cout << "File successfully written!" << std::endl;
};
//---------------------------------------------------------------------------
