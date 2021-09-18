#include "util.h"

std::vector<std::string> split(const std::string &str,
                               const std::string &delimiter){
    std::vector<std::string> res;
    std::string::size_type last_index = str.find_first_not_of(delimiter, 0);
    std::string::size_type index = str.find_first_of(delimiter, last_index);

    while (std::string::npos != index || std::string::npos != last_index)
    {
        res.push_back(str.substr(last_index, index - last_index));
        last_index = str.find_first_not_of(delimiter, index);
        index = str.find_first_of(delimiter, last_index);
    }
    return res;
}

bool EndWith(const std::string &original,
             const std::string &pattern) {
  return original.length() >= pattern.length() &&
         original.substr(original.length() - pattern.length()) == pattern;
}

std::vector<std::string> readFileName(std::string dirpath){
    DIR* dir = opendir(dirpath.c_str());
    if (dir == NULL)
    {
        cout << "Error: cann't open the " << dirpath << endl;
    }

    std::vector<std::string> allName;
    // vector<size_t> sizeOffile;
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL)
    {
        //cout << "name = " << entry->d_name << ", len = " << entry->d_reclen << ", entry->d_type = " << (int)entry->d_type << endl;
        string name = entry->d_name;
        // string imgdir = dirpath +"/"+ name;
        //sprintf("%s",imgdir.c_str());
        allName.push_back(name);
        // sizeOffile.push_back(entry->d_reclen); 这个获取的是文件名的长度
    }
    closedir(dir);
    return allName;
}