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
#include <filesystem>
#include "gtest/gtest.h"

class CheckFileExistence : public std::exception
{
public:
    const char* what() const noexcept override;
};
//----------------------------------------------------------------------------
class CheckConfigDataExistence : public std::exception
{
public:
    const char* what() const noexcept override;
};
//----------------------------------------------------------------------------
class CheckFilesDataExistence : public std::exception
{
public:
    const char* what() const noexcept override;
};
//----------------------------------------------------------------------------
struct WriteJSON
{
    std::map<std::string, std::vector<std::pair<int, float>>> rankSequence;
};
//-----------------------------------------------------------------------------
class DataFromConfigFile
{
public:
    std::string name;
    float version;
    int maxResponses;
};
//----------------------------------------------------------------------------
class ConverterJSON
{
public:
    ConverterJSON() = default;
    ConverterJSON(nlohmann::json &mData, DataFromConfigFile &mDataFromConfigFile) : data(mData), dataFromConfigFile(mDataFromConfigFile) {};
    std::vector<std::string> GetTextDocuments() const;
    int getResponsesLimit() const;
    std::vector<std::string> GetRequests() const;
    void putAnswers(std::vector<std::vector<std::pair<int, float>>> &answers) const;
private:
    nlohmann::json data;
    DataFromConfigFile dataFromConfigFile;
};
//--------------------------------------------------------------------------------