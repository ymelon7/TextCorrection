/*************************************************************************
	> File Name: test_main.cpp
	> Author: Melon
	> Mail:ymelon7@gmail.com 
	> Created Time: Fri 31 Oct 2014 04:10:38 AM PDT
 ************************************************************************/

#include "TextQuery.h"
#include <iostream>

int main (int argc, char *argv[])
{
    TextQuery query("../dict/en.dict");

    std::string word;
    while(std::cin >> word)
    {
        std::cout << query.queryWord(word) << std::endl;  
    }
}
