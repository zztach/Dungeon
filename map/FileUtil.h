/* 
 * File:   FileUtil.h
 * Author: zisis
 *
 * Created on April 13, 2014, 5:40 PM
 */

#ifndef FILEUTIL_H
#define	FILEUTIL_H

#include <string>
#include <fstream>
#include <iostream>

class FileUtil {
public:
    static std::string readFile(const char* filePath);
    ~FileUtil();
private:
    FileUtil();
    FileUtil(const FileUtil& orig);
};

#endif	/* FILEUTIL_H */

