#include "wordClusterPath.h"
#include <cstdlib>

std::map<std::string,std::string> wordClusterPath::word2path;bool wordClusterPath::word2pathInitialized = false;


void
wordClusterPath::split(std::vector<std::string> & pathwordcnt, std::string & line)
{
	std::string buf;
	std::stringstream ss(line);
	while(ss >> buf)
	{
		pathwordcnt.push_back(buf);
	}
	return;
}

void
wordClusterPath::loadWord2PathDict()
{    if(word2pathInitialized == false){        word2pathInitialized = true;
        std::string clusterResourceName = "./resources/word2path.txt";
        std::ifstream infile(clusterResourceName.c_str());
        if(!infile){
            std::cout<<"could not open the wordclusterpath file : ./resources/word2path.txt to read !"<<std::endl;
        }
        std::string line;
        while(getline(infile,line))
        {
            std::vector<std::string> pathwordcnt;
            split(pathwordcnt,line);
            if(pathwordcnt.size() != 3)
            {
                std::cout<<"pathwordcnt error!"<<std::endl;
                std::cout<<line<<std::endl;
                exit(-1);
            }
            else
            {
                wordClusterPath::word2path.insert(std::pair<std::string,std::string>(pathwordcnt[1], pathwordcnt[0]));
            }
        }    }

}


int
wordClusterPath::genClusterFeature(std::string & str,
std::vector<std::string> & clusterFeature)
{
	std::string bitstring = "";
	std::map<std::string,std::string>::iterator word2pathit;
	word2pathit = word2path.find(str);
	if(word2pathit == word2path.end()){//current word not in word cluster, construct a fuzz list for it
        std::vector<std::string> fuzz;
        featureutil->fuzztoken(str, fuzz);
        //std::cout<<"ONLYSHIT!"<<std::endl;
        //exit(1);
        if(fuzz.size() != 0){
            for(int i = 0; i < fuzz.size(); ++i){
                word2pathit = word2path.find(fuzz[i]);
                if(word2pathit != word2path.end()){
                    bitstring = word2pathit->second;
                    break;
                }
            }
        }
	}
	else{
        bitstring = word2pathit->second;
	}
	//std::cout<<bitstring<<std::endl;

	if(bitstring != "")
	{
        int i = 0;
		char tmp[17];
		for(;i < bitstring.size();++i)
		{
			tmp[i] = bitstring[i];
		}
		while(i <= 16)
		{
			tmp[i] = '0';
			i++;
		}
		bitstring = tmp;

		int j;
		for(j = 2; j <= 16; j+=2)
		{
			clusterFeature.push_back("BigCluster|" + bitstring.substr(0,j));
		}
	}
}

int
wordClusterPath::genPreClusterFeature(std::string & str,
std::vector<std::string> & clusterFeature)
{
	std::string bitstring = "";
	std::map<std::string,std::string>::iterator word2pathit;
	word2pathit = word2path.find(str);
	if(word2pathit == word2path.end()){//current word not in word cluster, construct a fuzz list for it
        std::vector<std::string> fuzz;
        featureutil->fuzztoken(str, fuzz);
        if(fuzz.size() != 0){
            for(int i = 0; i < fuzz.size(); ++i){
                word2pathit = word2path.find(fuzz[i]);
                if(word2pathit != word2path.end()){
                    bitstring = word2pathit->second;
                    break;
                }
            }
        }
	}
	else{
        bitstring = word2pathit->second;
	}

	if(bitstring != "")
	{
        int i = 0;
		char tmp[17];
		for(;i < bitstring.size();++i)
		{
			tmp[i] = bitstring[i];
		}
		while(i <= 16)
		{
			tmp[i] = '0';
			i++;
		}
		bitstring = tmp;

		int j;
		for(j =4; j <= 12; j+=4)
		{
			clusterFeature.push_back("PreBigCluster|" + bitstring.substr(0,j));
		}
	}
}

int
wordClusterPath::genNextClusterFeature(std::string & str,
std::vector<std::string> & clusterFeature)
{
	std::string bitstring = "";
	std::map<std::string,std::string>::iterator word2pathit;
	word2pathit = word2path.find(str);
	if(word2pathit == word2path.end()){//current word not in word cluster, construct a fuzz list for it
        std::vector<std::string> fuzz;
        featureutil->fuzztoken(str, fuzz);
        if(fuzz.size() != 0){
            for(int i = 0; i < fuzz.size(); ++i){
                word2pathit = word2path.find(fuzz[i]);
                if(word2pathit != word2path.end()){
                    bitstring = word2pathit->second;
                    break;
                }
            }
        }
	}
	else{
        bitstring = word2pathit->second;
	}

	if(bitstring != "")
	{
        int i = 0;
		char tmp[17];
		for(;i < bitstring.size();++i)
		{
			tmp[i] = bitstring[i];
		}
		while(i <= 16)
		{
			tmp[i] = '0';
			i++;
		}
		bitstring = tmp;

		//int i;
		for(i =4; i <= 12; i+=4)
		{
			clusterFeature.push_back("NextBigCluster|" + bitstring.substr(0,i));
		}
	}
}

#if 0

int
wordClusterPath::genPreClusterFeature(std::string & str,
std::vector<std::string> & clusterFeature)
{
	std::string bitstring = "";
	std::map<std::string,std::string>::iterator word2pathit;
	word2pathit = word2path.find(str);
	if(word2pathit != word2path.end())
	{
		bitstring = word2pathit->second;
		int i = 0;
		char tmp[17];
		for(;i < bitstring.size();++i)
		{
			tmp[i] = bitstring[i];
		}
		while(i <= 16)
		{
			tmp[i] = '0';
			i++;
		}
		bitstring = tmp;
	}
	else
	{
		bitstring = "1111111111111111";
	}
	if(bitstring != "")
	{
		int i;
		for(i =4; i <= 12; i+=4)
		{
			clusterFeature.push_back("PreBigCluster|" + bitstring.substr(0,i));
		}
	}
}

int
wordClusterPath::genNextClusterFeature(std::string & str,
std::vector<std::string> & clusterFeature)
{
	std::string bitstring = "";
	std::map<std::string,std::string>::iterator word2pathit;
	word2pathit = word2path.find(str);
	if(word2pathit != word2path.end())
	{
		bitstring = word2pathit->second;
		int i = 0;
		char tmp[17];
		for(;i < bitstring.size();++i)
		{
			tmp[i] = bitstring[i];
		}
		while(i <= 16)
		{
			tmp[i] = '0';
			i++;
		}
		bitstring = tmp;
	}
	else
	{
		bitstring = "1111111111111111";
	}
	if(bitstring != "")
	{
		int i;
		for(i =4; i <= 12; i+=4)
		{
			clusterFeature.push_back("NextBigCluster|" + bitstring.substr(0,i));
		}
	}
}

#endif






