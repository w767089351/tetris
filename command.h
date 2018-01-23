#ifndef command_hpp
#define command_hpp

#include <string>
#include <vector>
#include <iostream>

class Command{
    int size;
    std::vector<std::string> slist;
    std::vector<std::string> orglist;
    
public:
    Command();
    void interpreter(std::string& command,int& count);
    void changeName(std::string old_n,std::string new_n);
};

#endif /* command_hpp */

