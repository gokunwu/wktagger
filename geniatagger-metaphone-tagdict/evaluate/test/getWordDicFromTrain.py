#!/usr/bin/env python

import signal,sys

def splitSent2Word(snt):
	list = []
	word_pos_list = snt.split(" ")
	for word_pos in word_pos_list:
		word_list = word_pos.split("_")
		if(len(word_list) != 2):
			print snt
		else:
			list.append(word_list[0])	
	return list

def getWordDicFromTrain(ifilename,ofilename):
	dict = {} 
	ifile = open(ifilename)
	ofile = open(ofilename,"w")
	for line in ifile:
		line = line.strip()
		word_list = splitSent2Word(line)	
		for word in word_list:
			if word not in dict.keys():
				dict[word]=word
	for word in dict.keys():
		ofile.write(word+"\n")	

def main():
	ifilename = "train.pos.cikuu"
	ofilename = "word.dic.train"
	getWordDicFromTrain(ifilename,ofilename)

if __name__ == "__main__":
	signal.signal(signal.SIGINT,lambda x,y:sys.exit())
	main()
