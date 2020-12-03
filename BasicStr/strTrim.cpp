#include <iostream>
#include <string>


void trim(std::string& str)
{
    while (std::isspace(str.front()))
    {
        str.erase(str.begin());
    }

    while (std::isspace(str.back()))
    {
        str.pop_back();
    }
}


int main()
{
    std::string str = "   string trim ";

    trim(str);
    std::cout << str << std::endl;
}