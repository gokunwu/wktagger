

#ifndef __TAGDICTIONARY_H_
#define __TAGDICTIONARY_H_

#include <iostream>
#include <map>
#include <string>
#include <vector>

class tagDictionary{
    public:
        tagDictionary(){
        }
        ~tagDictionary(){
        }
        void loadTagDic();
        int findWordInWord2Pos(std::vector<std::string> & poses, std::string &str);
        static bool mapInitialized;
        static std::map<std::string, std::vector<std::string> > word2pos;
};





#endif
