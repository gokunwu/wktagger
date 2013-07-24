
if __name__ == "__main__":
	ifile = open("word2meta","r")
	ofile = open("meta2word", "w")
	metadict = dict()
	for line in ifile:
		line = line.strip()
		word_meta = line.split(" ")
		if(len(word_meta) != 2):
			continue
		else:
			word = word_meta[0]
			meta = word_meta[1]
		if meta not in metadict.keys():
			metadict[meta] = set()
			metadict[meta].add(word)
		if meta in metadict.keys():
			if(word not in metadict[meta]):
				metadict[meta].add(word)
	for meta in metadict.keys():
		s = meta + " "
		for word in metadict[meta]:
			s = s + word + " "
		s = s.strip()
		ofile.write(s + "\n")


