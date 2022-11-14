#include "InvertedIndex.h"

//Add the following script to main if you want to launch tests.
//Google test---------------------------------------------------------------
//testing::InitGoogleTest(&argc, argv);
//RUN_ALL_TESTS();
//--------------------------------------------------------------------------

//------------------------------------------------------------------------------
void TestInvertedIndexFunctionality
        (
                std::vector<std::string> &docs,
                std::map<std::string, std::vector<Entry>> &expected
        )
{
    std::map<std::string, std::vector<Entry>> result;
    InvertedIndex invertedIndex;
    invertedIndex.UpdateDocumentBase(docs);
    result = invertedIndex.GetDictionary();

    ASSERT_EQ(result, expected);
}
//------------------------------------------------------------------------------
TEST(InvertedIndex, Test1) {

    std::vector<std::string> docs = {
            {"minsk"}, {"water water"}, {"is water"}, {"americano cappuccino"} };

    std::map<std::string, std::vector<Entry>> expected = {
            { {"americano"},  {{3, 1}} }, { {"cappuccino"},  {{3, 1}} }, { {"is"}, {{2, 1}} },
            { {"minsk"}, {{0, 1}} }, { {"water"}, {{1, 2}, {2, 1}} } };

    TestInvertedIndexFunctionality(docs, expected);
}
//------------------------------------------------------------------------------