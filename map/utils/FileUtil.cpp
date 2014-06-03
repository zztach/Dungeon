/* 
 * File:   FileUtil.cpp
 * Author: zisis
 * 
 * Created on April 13, 2014, 5:40 PM
 */

#include "FileUtil.h"

FileUtil::FileUtil() {
}

FileUtil::FileUtil(const FileUtil& orig) {
}

std::string FileUtil::readFile(const char* filePath) {
    std::string content;
    std::ifstream fileStream(filePath, std::ios::in);

    if (!fileStream.is_open()) {
        std::cerr << "Could not read file " << filePath << ". File does not exist." << std::endl;
        return "";
    }

    std::string line = "";
    while (!fileStream.eof()) {
        getline(fileStream, line);
        content.append(line + "\n");
    }

    fileStream.close();
    return content;
}

FileUtil::~FileUtil() {
}

