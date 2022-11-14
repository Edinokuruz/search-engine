#include "SearchServer.h"

//Add the following script to main if you want to launch tests.
//Google test---------------------------------------------------------------
//testing::InitGoogleTest(&argc, argv);
//RUN_ALL_TESTS();
//--------------------------------------------------------------------------

//----------------------------------------------------------------------------------------
void TestSearchServerFunctionality
        (
                std::map<std::string, std::vector<Entry>> &invertedIndexResult,
                std::vector<std::string> &requests,
                std::vector<std::string> &dataFromEachFile,
                std::vector<std::vector<RelativeIndex>> &expected
        )
{
    std::vector<std::vector<RelativeIndex>> result;
    SearchServer searchServer(invertedIndexResult, requests, dataFromEachFile);
    result = searchServer.search();

    ASSERT_EQ(result, expected);
}
//------------------------------------------------------------------------------------------
TEST(SearchServer, Test1) {

    std::vector<std::string> dataFromEachFile = {
            {"minsk"}, {"water water"}, {"is water"}, {"americano cappuccino"} };

    std::map<std::string, std::vector<Entry>> invertedIndexResult = {
            { {"americano"},  {{3, 1}} }, { {"cappuccino"},  {{3, 1}} }, { {"is"}, {{2, 1}} },
            { {"minsk"}, {{0, 1}} }, { {"water"}, {{1, 2}, {2, 1}} } };

    std::vector<std::string> requests = {
            {{"minsk"}, {"is d cappuccino"}, {"milk water vodka"}}
    };

    std::vector<std::vector<RelativeIndex>> expected = {
            { {0, 1} },
            { {2, 1}, {3, 1} },
            { {1, 1}, {2, 0.5} }
    };

    TestSearchServerFunctionality(invertedIndexResult, requests, dataFromEachFile, expected);
}
//------------------------------------------------------------------------------------------
TEST(SearchServer, Test2) {

    std::vector<std::string> dataFromEachFile = {
            {"is water water water water milk  bbbbb"}, {"vodka against water water"} };

    std::map<std::string, std::vector<Entry>> invertedIndexResult = {
            { {"against"},  {{1, 1}} }, { {"bbbbb"},  {{0, 1}} }, { {"is"}, {{0, 1}} },
            { {"water"}, {{0, 4}, {1, 2}} }, { {"vodka"}, {{1, 1}} } };

    std::vector<std::string> requests = {
            {{"water and water"}, {"again vodka with water"}}
    };

    std::vector<std::vector<RelativeIndex>> expected = {
            { {0, 1}, {1, 0.5} },
            { {0, 1}, {1, 0.75} }
    };

    TestSearchServerFunctionality(invertedIndexResult, requests, dataFromEachFile, expected);
}
//------------------------------------------------------------------------------------------