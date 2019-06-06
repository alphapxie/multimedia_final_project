//
// Created by victo on 06/06/2019.
//

#include "FileReader.h"

vector<string> FileReader::splitString(string src, string delimiter) {
    size_t pos = 0;
    vector<string> result;
    while ((pos = src.find(delimiter)) != std::string::npos) {
        result.push_back(src.substr(0, pos));
        src.erase(0, pos + delimiter.length());
    }
    result.push_back(src);
    return result;
}

char const* FileReader::getFile(char const *lFilterPatterns[], int multi) {
    char const *lTheOpenFileName;
    FILE *lIn;
    lTheOpenFileName = tinyfd_openFileDialog(
            "Please select your picture ",
            "",
            2,
            lFilterPatterns,
            NULL,
            multi);

    if (!lTheOpenFileName) {
        tinyfd_messageBox(
                "Error",
                "Open file name is NULL",
                "ok",
                "error",
                1);
        return NULL;
    }
    if (multi == 0) {
        lIn = fopen(lTheOpenFileName, "r");

        if (!lIn) {
            tinyfd_messageBox(
                    "Error",
                    "Can not open this file in read mode",
                    "ok",
                    "error",
                    1);
            return NULL;
        }
        fclose(lIn);
    }
    return lTheOpenFileName;
}

vector<string> FileReader::getFiles(const char *lFilterPatterns[]) {
    string fileString = getFile(lFilterPatterns, 1);
    return splitString(fileString, "|");

}