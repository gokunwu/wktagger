

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
        int findWordInWord2Pos(std::map<std::string, double> & poses, std::string &str);
        static bool mapInitialized;
        static std::map<std::string, std::map< std::string, double> > word2pos;
};





#endif
