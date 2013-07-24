
#include "wordListFeatures.h"

extern void DoubleMetaphone(const string &str, vector<string> *codes);

int
wordListFeatures::genPosTagFeature(std::string & str, std::vector<std::pair<std::string, double> > & rvfeatures){
    std::map<std::string,double> poses;
    //std::map<std::string, std::vector<std::string> >::iterator word2posit;
    //word2posit = tagDictionary::word2pos.find(str);
    int flag = tagdic->findWordInWord2Pos(poses, str);
    if(flag == 0){
        std::vector<std::string> fuzz;
        featureutil->fuzztoken(str, fuzz);
        if(fuzz.size() != 0){
            for(std::vector<std::string>::iterator fuzzit = fuzz.begin(); fuzzit != fuzz.end(); ++fuzzit){
                int flag1 = tagdic->findWordInWord2Pos(poses, *fuzzit);
                if(flag1 == 1){
                    break;
                }
            }
        }
    }
    if(flag == 1){        std::map<std::string, double>::iterator posesit;        for(posesit = poses.begin(); posesit != poses.end(); ++posesit){            rvfeatures.push_back(std::pair<std::string, double>("POSTagDict|" + posesit->first, posesit->second));        }
    }
}

int
wordListFeatures::genMetaphoneTagFeature(std::string & str, std::vector<std::pair<std::string, double> > & rvfeatures){
    std::map<std::string, double> poses;
    //std::map<std::string, std::vector<std::string> >::iterator word2posit;
    //word2posit = tagDictionary::word2pos.find(str);
    std::vector<std::string> codes;
    std::string code;
    DoubleMetaphone(str, &codes);
    code = "**MP**" + codes[0];
    int flag = tagdic->findWordInWord2Pos(poses, code);
    if(flag == 1){
        std::map<std::string, double>::iterator posesit;        for(posesit = poses.begin(); posesit != poses.end(); ++posesit){            rvfeatures.push_back(std::pair<std::string, double>("metaph_POSDict|" + posesit->first,posesit->second));        }    }
}



