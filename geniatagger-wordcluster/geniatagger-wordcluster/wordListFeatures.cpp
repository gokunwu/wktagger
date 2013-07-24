
#include "wordListFeatures.h"

extern void DoubleMetaphone(const string &str, vector<string> *codes);

int
wordListFeatures::genPosTagFeature(std::string & str, std::vector<std::pair<std::string, double> > & rvfeatures){
    std::vector<std::string> poses;
    std::map<std::string, std::vector<std::string> >::iterator word2posit;
    //word2posit = tagDictionary::word2pos.find(str);
    tagdic->findWordInWord2Pos(poses, str);
    if(poses.size() == 0){
        std::vector<std::string> fuzz;
        featureutil->fuzztoken(str, fuzz);
        if(fuzz.size() != 0){
            for(std::vector<std::string>::iterator fuzzit = fuzz.begin(); fuzzit != fuzz.end(); ++fuzzit){
                tagdic->findWordInWord2Pos(poses, *fuzzit);
                if(poses.size() != 0){
                    break;
                }
            }
        }
    }
    if(poses.size() != 0){
        rvfeatures.push_back(std::pair<std::string, double>("POSTagDict|" + poses[0], 1.0));
        for(int i = 1; i < poses.size(); ++i){
            rvfeatures.push_back(std::pair<std::string, double>("POSTagDict|" + poses[i], (poses.size() - double(i))/poses.size()));
        }
    }
}

int
wordListFeatures::genMetaphoneTagFeature(std::string & str, std::vector<std::pair<std::string, double> > & rvfeatures){
    std::vector<std::string> poses;
    std::map<std::string, std::vector<std::string> >::iterator word2posit;
    //word2posit = tagDictionary::word2pos.find(str);
    std::vector<std::string> codes;
    std::string code;
    DoubleMetaphone(str, &codes);
    code = "**MP**" + codes[0];
    tagdic->findWordInWord2Pos(poses, code);
    if(poses.size() != 0){
        rvfeatures.push_back(std::pair<std::string, double>("metaph_POSDict|" + poses[0], 1.0));
        for(int i = 1; i < poses.size(); ++i){
            rvfeatures.push_back(std::pair<std::string, double>("metaph_POSDict|" + poses[i], (poses.size() - double(i))/poses.size()));
        }
    }
}



