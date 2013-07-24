
#ifndef __FEATUREUTIL_H_
#define __FEATUREUTIL_H_

#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <map>

class featureUtil{
    public :
        featureUtil(){};
        void loadSpellError();
        void loadSet();
        int split(std::vector<std::string> & spellerror, std::string & str, std::string s);
        void toLowerCase(std::string & str);
        void replace(std::string & s, const std::string & s1, const std::string & s2, const char skip = 0);
        int fuzztoken(std::string & str, std::vector<std::string> & fuzz);

        static bool setInitialized;
        static bool mapInitialized;
        static std::set<std::string> specStr;
        static std::map<std::string,std::string> spellError;
};

#endif
