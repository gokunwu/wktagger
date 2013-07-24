#!/usr/bin/env python
import sys,signal

class Stat:
	def __init__(self):
		self.ifilename1 = "gold.pos.cikuu"
		self.ifilename2 = "test.pos.cikuu"
		self.ofilename = "unknown.words"
		self.dictfilename = "word.dic.train"
		self.dict = {}
		self.worddict = {}
		self.count = 0
	
	def readDic(self):
		ifile = open(self.dictfilename,"r")
		for line in ifile:
			line = line.strip()
			if line not in self.dict.keys():
				self.dict[line] = line
	
	def sent2List(self,line):
		list = line.split(" ")
		return list

	def wordPos2Word(self,word_pos):
		word_pos_list = word_pos.split("_")
		if(len(word_pos_list) != 2):
			print "word_pos can not be split !"
			print word_pos
		return word_pos_list[0]
		 
	def evalWordPos(self):
		ifile1 = open(self.ifilename1,"r")
		ifile2 = open(self.ifilename2,"r")
		line1 = ifile1.readline()
		line1 = line1.strip()
		line2 = ifile2.readline()	
		line2 = line2.strip()
		while(line1 and line2):
			list1 = self.sent2List(line1)			
			list2 = self.sent2List(line2)			
			if(len(list1) != len(list2)):
				print "the size of line1 is not equal with the size of line2!"
				print "line1 lenth : " + str(len(line1))
				print "line2 lenth : " + str(len(line2))
				print line1
				print line2
				sys.exit()
			for i in range(len(list1)):
				word_pos1 = list1[i]
				word_pos2 = list2[i]
				word1 = self.wordPos2Word(word_pos1)
				word2 = self.wordPos2Word(word_pos2)
				if(word1 != word2 and word1 != "\""):
					print "word1 is not equal word2!"
					print line1
					print line2
					print word1
					print word2
				else:
					if word1 not in self.dict.keys():
						self.count += 1
						if word1 not in self.worddict.keys():
							self.worddict[word1] = word1
						
			line1 = ifile1.readline()
			line1 = line1.strip()
			line2 = ifile2.readline()	
			line2 = line2.strip()
		return
	def writeDownWords(self):
		ofile = open(self.ofilename,"w")
		for word in self.worddict.keys():
			ofile.write(word + "\n")


def main():
	stat = Stat()
	print "1"
	stat.readDic()
	print "2"
	stat.evalWordPos()
	print "4"
	stat.writeDownWords()

if __name__ == "__main__":
	signal.signal(signal.SIGINT,lambda x,y:sys.exit())
	main()
