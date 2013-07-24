#!/usr/bin/env python
import sys,signal

class Stat:
	def __init__(self):
		self.ifilename1 = "gold.pos.cikuu"
		self.ifilename2 = "test.word.dict.meta"
		self.ifilename3 = "test.word.dict"
		self.ofilename = "sent.not.equal"
	
	def evalSent(self):
		ifile1 = open(self.ifilename1,"r")
		ifile2 = open(self.ifilename2,"r")
		ifile3 = open(self.ifilename3,"r")
		ofile = open(self.ofilename, "w")
		line1 = ifile1.readline()
		line1 = line1.strip()
		line2 = ifile2.readline()	
		line2 = line2.strip()
		line3 = ifile3.readline()	
		line3 = line3.strip()
		while(line1 and line2 and line3):
			#if(line2 != line3 and line1 != line2 and line1 == line3):
			if(line1 != line2):
				ofile.write("gold: " + line1 + "\n")
				ofile.write("3: " + line2 + "\n")
				#ofile.write("2: " + line3 + "\n")
			line1 = ifile1.readline()
			line1 = line1.strip()
			line2 = ifile2.readline()	
			line2 = line2.strip()
			line3 = ifile3.readline()	
			line3 = line3.strip()

def main():
	stat = Stat()
	stat.evalSent()

if __name__ == "__main__":
	signal.signal(signal.SIGINT,lambda x,y:sys.exit())
	main()
