
#ifndef __WORDLISTFEATURES_H_
#define __WORDLISTFEATURES_H_

#include <string>
#include <vector>
#include <utility>
#include "tagDictionary.h"
#include "featureUtil.h"
#include "double_metaphone.h"

class wordListFeatures{
    public:
        wordListFeatures(){
            tagdic = new tagDictionary();
            tagdic->loadTagDic();
            featureutil = new featureUtil();
            featureutil->loadSet();
            featureutil->loadSpellError();
        }
        ~wordListFeatures(){
            if(tagdic != NULL){
                delete tagdic;
                tagdic = NULL;
            }
            if(featureutil != NULL){
                delete featureutil;
                featureutil = NULL;
            }
        }
        //int genPosTagFeature(std::string & str, std::vector<std::pair<std::string, double> & rvfeatures>);
        int genPosTagFeature(std::string & str, std::vector<std::pair<std::string, double> > & rvfeatures);
        int genMetaphoneTagFeature(std::string & str, std::vector<std::pair<std::string, double> > & rvfeatures);
        tagDictionary * tagdic;
        featureUtil * featureutil;
};




#endif
