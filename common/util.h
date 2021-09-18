#ifndef MODULE_UTIL_H
#define MODULE_UTIL_H

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <vector>

using namespace std;

std::vector<std::string> split(const std::string &str,
                               const std::string &delimiter);

bool EndWith(const std::string &original,
             const std::string &pattern);

std::vector<std::string> readFileName(std::string dirpath);
#endif


