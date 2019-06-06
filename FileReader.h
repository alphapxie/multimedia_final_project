//
// Created by victo on 06/06/2019.
//
#ifndef MULTIMEDIA_FINAL_PROJECT_FILEREADER_H
#define MULTIMEDIA_FINAL_PROJECT_FILEREADER_H

#include <iostream>
#include <vector>

using namespace std;

#include "tinyfiledialogs-master/tinyfiledialogs.h"


class FileReader {
    static vector<string> splitString(string src, string delimiter);
public:
    static char const* getFile(char const *lFilterPatterns[], int multi = 0);
    static vector<string> getFiles(char const *lFilterPatterns[]);
};


#endif //MULTIMEDIA_FINAL_PROJECT_FILEREADER_H
