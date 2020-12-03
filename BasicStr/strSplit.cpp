#include <iostream>
#include <string>
#include <vector>
#include <cstring>


std::vector<std::string> split(std::string& str, std::string& delim)
{
    std::vector<std::string> ret;

    char c_string[str.length() + 1];

    str.copy(c_string, str.npos);
    c_string[str.length()] = '\0';

    char* token = strtok(c_string, delim.c_str());

    while (token)
    {
        ret.push_back(token);
        token = strtok(nullptr, delim.c_str());
    }

    return ret;

}


int main()
{
    std::string str = "cat,dog,bird";
    // std::cin >> str;
    std::string delim = ",";
    auto splitted = split(str, delim);

    for (auto& s : splitted)
    {
        std::cout << s << std::endl;
    }
}