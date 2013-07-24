#!/usr/bin/env python
import sys,signal

class Stat:
	def __init__(self):
		self.ifilename1 = "gold.pos.cikuu"
		self.ifilename2 = "test.pos.cikuu"
		self.ofilename = "sent.not.equal"
	
	def evalSent(self):
		ifile1 = open(self.ifilename1,"r")
		ifile2 = open(self.ifilename2,"r")
		ofile = open(self.ofilename, "w")
		line1 = ifile1.readline()
		line1 = line1.strip()
		line2 = ifile2.readline()	
		line2 = line2.strip()
		while(line1 and line2):
			print line1
			if(line1 != line2):
				print line1
				ofile.write("gold: " + line1 + "\n")
				ofile.write("test: " + line2 + "\n")
			line1 = ifile1.readline()
			line1 = line1.strip()
			line2 = ifile2.readline()	
			line2 = line2.strip()

def main():
	stat = Stat()
	stat.evalSent()

if __name__ == "__main__":
	signal.signal(signal.SIGINT,lambda x,y:sys.exit())
	main()
