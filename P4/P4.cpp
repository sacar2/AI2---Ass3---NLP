// builds Add-Delta language model
#include "P4.h"

typedef std::string T;

//collect the ngrams for a file
std::unordered_map<std::vector<T>, int> getNgrams(std::vector<T> words, int n) {
	std::unordered_map<std::vector<T>, int> grams;
	int count = 0;

	//go through each word (up until the n-th last word because that would eb the last gram)
	for (auto i = words.begin(); i != words.end() - n + 1; i++)
	{
		//create a vector of the ngram for the corresponding word in the string
		std::vector<T> ngram(n);
		for (int m = 0; m < n; m++)
		{
			//add the word to the vector
			ngram[m] = words[count + m];
		}
		//value of the ngram is equal to it's place
		grams[ngram] = count;
		++count;
	}
	return grams;
}

void P4(std::string modelLangFile, std::string sentanceFile, int n, double delta) {
	
	double didnotoccur = 0;
	std::string strOneLine;
	std::vector<T> modelVec, sentanceVec;
	std::ifstream inFile(modelLangFile), inFile2(sentanceFile);

	//put all words into vectors
	while (getline(inFile, strOneLine))
	{
		std::stringstream streamOfWordsInLine(strOneLine);
		std::string word;
		while (streamOfWordsInLine >> word)
		{
			std::transform(word.begin(), word.end(), word.begin(), ::tolower);
			modelVec.push_back(word);
		}
	}

	while (getline(inFile2, strOneLine))
	{
		std::stringstream streamOfWordsInLine(strOneLine);
		std::string word;
		while (streamOfWordsInLine >> word)
		{
			std::transform(word.begin(), word.end(), word.begin(), ::tolower);
			sentanceVec.push_back(word);
		}
	}

	////get the ngrams for each text
	//std::unordered_map<std::vector<T>, int> text1Ngrams = getNgrams(modelVec, n);
	//std::unordered_map<std::vector<T>, int> text2Ngrams = getNgrams(sentanceVec, n);

	////analyze each ngram - for each ngram in the map, 
	//for (auto i = text2Ngrams.begin(); i != text2Ngrams.end(); i++)
	//{
	//	std::vector<T> gram = i->first;

	//	//if the gram isn't in the first text, add it to the count of no occurances
	//	if (text1Ngrams.count(gram) == 0) {
	//		didnotoccur++;
	//	}
	//	else if (delta == 1) { // if it's in there and print is true, print it!
	//		for (std::vector<T>::iterator it = gram.begin(); it != gram.end(); ++it) {
	//			std::cout << *it << " ";
	//		}
	//		std::cout << std::endl;
	//	}
	//}
	////print percentage of ngrams in second text file not occuring in the first
	//double percent = didnotoccur * 100 / text2Ngrams.size();
	//std::cout << percent << std::endl;
}

int main(int argc, char** argv)
{
	std::string modelLangFile = argv[1];
	std::string sentanceFile = argv[2];
	int n = atoi(argv[3]);
	double delta = atoi(argv[4]);

	P4(modelLangFile, sentanceFile, n, delta);
	std::cout << "press any key to end program";
	std::cin.get();

	return 0;
}