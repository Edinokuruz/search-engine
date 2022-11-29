![GitHub author](https://img.shields.io/badge/made_by-Grigory_Brusnik-purple)
![GitHub repo size](https://img.shields.io/github/repo-size/Edinokuruz/search-engine?color=purple)
![GitHub author](https://img.shields.io/badge/made_on-C++-purple)
![GitHub repo directory count](https://img.shields.io/github/directory-file-count/Edinokuruz/search-engine?color=purple)
## __Название проекта | Project name__ 
![GitHub author](https://img.shields.io/badge/-RUS-red)  
Локальный поисковый движок по файлам.  
![GitHub author](https://img.shields.io/badge/-ENG-red)  
Local search engine for files.
___
## __Технологии | Technologies__ 
![GitHub author](https://img.shields.io/badge/C++-17-darkblue)  
![GitHub author](https://img.shields.io/badge/CMake-3.25-darkblue)
https://cmake.org/  
![GitHub author](https://img.shields.io/badge/JSON-3.11.2-darkblue)
https://github.com/nlohmann/json/releases/download/v3.11.2/json.tar.xz  
![GitHub author](https://img.shields.io/badge/GTest-1.12.1-darkblue)
https://github.com/google/googletest.git 
___
## __Применение проекта | Project usage__
![GitHub author](https://img.shields.io/badge/-RUS-blue)    
На основе запроса(ов) пользователя, приложение последовательно осуществляет поиск среди набора документов наиболее соответствующего данному запросу(ам), а также их сортировку в зависимости от степени релевантности.  
![GitHub author](https://img.shields.io/badge/-ENG-blue)  
Based on the user's request, the program sequentially searches among the set of documents that best matches the given request, as well as sorting them depending on the degree of relevance.  
___
## __Описание работы проекта | Project work description__
![GitHub author](https://img.shields.io/badge/-RUS-green)    
Запуск программы осуществляется при помощи исполнительного файла. Файл config.json содержит данные для запуска консольного приложения, а также пути к документам, среди которых будет осуществляться поиск. Если файл запуска отсутствует или содержит некорректные данные, то программа завершит работу выдав ошибку. Документы должны иметь расширение .txt. Перечень запросов, по которым будет осуществляться поиск в документах, должен быть указан в файле requests.json. Результат работы приложения записывается в файл answers.json. Где, в случае если не найдено ни одного документа по запросу, выводится сообщение false, а если найден хотя бы один документ - true. Если в результате поиска найдено несколько подходящих документов, то ответ будет записан в зависимости от степени релевантности (от большего к меньшему).   
Все документы индиксируются. Далее каждый документ в отдельном потоке трансформируется в список слов, где к каждому слову добавляется индекс этого документа, а также колличество повторений. В результате получается пул уникальных слов по всем документам среди которых осуществляется поиск. Каждому слову добавляется индекс документа и колличество повторений в нем.  
Каждый запрос также как и документ трансформируется и сортируется в массив уникальных слов. Далее последовательно осуществляется поиск в пуле слов документов по каждому запросу. На последнем этапе выполняется рассчет абсолютной и относительной релеватности по каждом документу и результаты записываются в файл answers.json.  
![GitHub author](https://img.shields.io/badge/-ENG-green)  
The program is launched using an executable file. The config.json file contains the data for launching the console application, as well as the paths to the documents among which the search will be performed. If the startup file is missing or contains incorrect data, the program will exit with an error. Documents must have .txt permission. The list of requests for which documents will be searched must be specified in the requests.json file. The result of the application is written to the answers.json file. Where, if no document is found by request, the message is false, and if at least one document is found, true. If several matching documents are found as a result of the search, then the answer will be written depending on the degree of relevance (from largest to smallest).  
All documents are indexed. Further, each document in a separate stream is transformed into a list of words, where the index of this document is added to each word, as well as the number of repetitions. The result is a pool of unique words for all documents among which the search is carried out. Each word is appended with the index of the document and the number of repetitions in it.  
Each request, like the document, is transformed and sorted into an array of unique words. Next, a search is sequentially carried out in the pool of words of documents for each request. The last step is to calculate absolute and relative relevance for each document and write the results to the answers.json file.
___  
## __Спецификация файлов | Files specification__
* File config.json  
![GitHub author](https://img.shields.io/badge/-RUS-brown)  
В файле указаны имя, версия программы, а также пути к файлам среди которых будет осуществляться поиск.  
Содержимое файла по умолчанию:  
![GitHub author](https://img.shields.io/badge/-ENG-brown)  
The file contains the name, version of the program, as well as the paths to the files among which the search will be executed.  
Default file content:
```json
{
  "config":
  {
    "name": "SearchEngineFromGrigorii",
    "version": 0.1,
    "max_responses": 5
  },
  "files":
  [
    "resources/file001.txt",
    "resources/file002.txt",
    "resources/file003.txt",
    "resources/file004.txt",
    "resources/file005.txt",
    "resources/file005.bmp"
  ]
}
```
* File requests.json  
![GitHub author](https://img.shields.io/badge/-RUS-brown)  
Файл, в котором указаны запросы для выпонения поиска. Каждый отдельный запрос следует вводить после ',' на новой строке.  
Пример содержимого:  
![GitHub author](https://img.shields.io/badge/-ENG-brown) 
A file that specifies the queries to perform the search. Each individual request should be entered after the ',' on a new line.  
Content example:
```json
{
  "requests" :
  [
    "minsk is the capital of belarus ",
    "drink vodka with beer",
    "vino",
    "russia water a milk",
    "  d milk salt",
    "f g h water of",
    "john"
  ]

}
```
* File answers.json  
![GitHub author](https://img.shields.io/badge/-RUS-brown)  
Файл, в который будет записан результат поиска в формате JSON.  
Пример содержимого:  
![GitHub author](https://img.shields.io/badge/-ENG-brown)  
File where search result will be written in JSON format.  
Example content:  
```json
{
"answers": {
       "request0": {
             "result": "true", 
             "relevance": {
                   "docid": "0", "rank": "1",
                   "docid": "3", "rank": "0.177778",
                   "docid": "1", "rank": "0.0444444"
             }
       },
       "request1": {
              "result": "false"
       },
       "request2": {
             "result": "true", 
                   "docid": "4", "rank": "1"
       },
       "request3": {
             "result": "true", 
             "relevance": {
                   "docid": "1", "rank": "1",
                   "docid": "2", "rank": "1",
                   "docid": "0", "rank": "0.4",
                   "docid": "4", "rank": "0.2"
             }
       },
       "request4": {
             "result": "true", 
             "relevance": {
                   "docid": "2", "rank": "1",
                   "docid": "4", "rank": "0.6",
                   "docid": "1", "rank": "0.4"
             }
       },
       "request5": {
             "result": "true", 
             "relevance": {
                   "docid": "0", "rank": "1",
                   "docid": "2", "rank": "0.409091",
                   "docid": "1", "rank": "0.181818",
                   "docid": "3", "rank": "0.181818"
             }
       },
       "request6": {
              "result": "false"
       }
   }
}
```  
Note:  
docid - identificator of a relevant document,  
rank - relative index,  
result - true (if relevance is found), or false (if document absolutely not relevant for certain request).
___
## __Сборка и запуск проекта | Project building and running__
* Шаг 1: Сборка проекта | Step 1: Build the project.  
  * Если компилятор Visual Studio будет использован | If Visual Studio compiler will be used:  
    * Для версии x64 | For x64 version:  
`cmake -A x64 -S . -B "build64"`  
`cmake --build build64 --config Release`  
    * Для версии x32 | For x32 version:  
`cmake -A Win32 -S . -B "build32"`  
`cmake --build build32 --config Release`  
  * Если другие компиляторы | In other compilers:  
`cmake -S . -B "build"`  
`cmake --build build --config Release`  
* Шаг 2: скопировать файлы: | Step 2: copy files:  
`.\bin\requests.json`, `.\bin\config.json`, `.\bin\answers.json` and `.\bin\resources` folder  
from `.\bin` folder  
to the `.\bin\Release` folder.  
* Step 3: run the application:  
`.\bin\Release\search-engine`  
___

