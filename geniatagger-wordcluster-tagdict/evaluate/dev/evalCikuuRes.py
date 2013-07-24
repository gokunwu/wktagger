#!/usr/bin/env python
import sys,signal

class Stat:
	def __init__(self):
		self.ifilename1 = "gold.dev.cikuu"
		self.ifilename2 = "test.dev.cikuu"
		self.ofilename = "result.eval"
		self.dictfilename = "word.dic.train"
		self.dict = {}
		self.n_known_word_correct = 0
		self.n_known_word_total = 0
		self.n_unknown_word_correct = 0
		self.n_unknown_word_total = 0
		self.n_snt_correct = 0
		self.n_snt_total = 0	
	
	def readDic(self):
		ifile = open(self.dictfilename,"r")
		for line in ifile:
			line = line.strip()
			if line not in self.dict.keys():
				self.dict[line] = line
	
	def evalSent(self):
		ifile1 = open(self.ifilename1,"r")
		ifile2 = open(self.ifilename2,"r")
		line1 = ifile1.readline()
		line1 = line1.strip()
		line2 = ifile2.readline()	
		line2 = line2.strip()
		while(line1 and line2):
			self.n_snt_total = self.n_snt_total + 1
			if(line1 == line2):
				self.n_snt_correct = self.n_snt_correct + 1
			line1 = ifile1.readline()
			line1 = line1.strip()
			line2 = ifile2.readline()	
			line2 = line2.strip()
				
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
					if word1 in self.dict.keys():
						self.n_known_word_total = self.n_known_word_total + 1
						if(word_pos1 == word_pos2):
							self.n_known_word_correct = self.n_known_word_correct + 1
					else:
						self.n_unknown_word_total += 1 
						if(word_pos1 == word_pos2):
							self.n_unknown_word_correct += 1
			line1 = ifile1.readline()
			line1 = line1.strip()
			line2 = ifile2.readline()	
			line2 = line2.strip()
		return

	def word_acc(self):	
		return float(self.n_known_word_correct + self.n_unknown_word_correct) /\
					(self.n_known_word_total + self.n_unknown_word_total)

	def known_word_acc(self):
		return float(self.n_known_word_correct) / self.n_known_word_total

	def unknown_word_acc(self):
		return float(self.n_unknown_word_correct) / self.n_unknown_word_total 

	def snt_acc(self):
		return float(self.n_snt_correct) / self.n_snt_total

	def stat_res(self):
		return """Statistics of POS result:
					Total words: %d\tKnown words: %d\tUnknown words: %d
					Total acc: %.2f%%\tKnown acc: %.2f%%\tUnknown acc: %.2f%%
					Total sentences: %d\tCorrect sentences: %d\tSent acc:%.2f%%
					""" % (self.n_known_word_total + self.n_unknown_word_total, 
						self.n_known_word_total, self.n_unknown_word_total, 
						self.word_acc()*100, self.known_word_acc()*100, 
						self.unknown_word_acc()*100, 
						self.n_snt_total, self.n_snt_correct, self.snt_acc()*100)

def main():
	stat = Stat()
	print "1"
	stat.readDic()
	print "2"
	stat.evalSent()
	print "3"
	stat.evalWordPos()
	print "4"
	res = stat.stat_res()
	ofile = open(stat.ofilename,"w")
	ofile.write(res)
	print res

if __name__ == "__main__":
	signal.signal(signal.SIGINT,lambda x,y:sys.exit())
	main()
