
#ifndef __WORDCLUSTERPATH_H_
#define __WORDCLUSTERPATH_H_

#include <cstdlib>
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include "featureUtil.h"


class wordClusterPath
{
	public:
		wordClusterPath(){
            //featureUtil feat;
            //featureutil = &feat;
            featureutil = new featureUtil();
            featureutil->loadSet();
            featureutil->loadSpellError();
		}
		~wordClusterPath(){
            if(featureutil != NULL){
                delete featureutil;
                featureutil = NULL;
            }
		}
		void loadWord2PathDict();
		void split(std::vector<std::string> & pathwordcnt, std::string & line);
		int genClusterFeature(std::string & str, std::vector<std::string> &
		clusterFeature);
		int genPreClusterFeature(std::string & str, std::vector<std::string> &
		clusterFeature);
		int genNextClusterFeature(std::string & str, std::vector<std::string> &
		clusterFeature);

		static std::map<std::string,std::string> word2path;		static bool word2pathInitialized;
        featureUtil * featureutil;


};

#endif



















