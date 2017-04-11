#include "P2.h"

typedef std::string T;

// Driver function to sort the vector elements
// by second element of pairs
bool sortBySecondElement(const std::pair<std::string, int> &a,
	const std::pair<std::string, int> &b)
{
	return (a.second < b.second);
}

//collect the ngrams for a file
std::unordered_map<std::vector<T>, int> getNgrams(std::vector<T> words, int n) {
	std::unordered_map<std::vector<T>, int> grams;
	int count = 0;
	
	//go through each word (up until the n-th last word because that would eb the last gram)
	for (auto i = words.begin(); i != words.end() - n + 1 ; i++)
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

void P2(std::string fileName, std::string fileName2, int n, int print) {

	double didnotoccur = 0;
	std::string strOneLine;
	std::vector<T> wordVector1, wordVector2;
	std::ifstream inFile(fileName), inFile2(fileName2);

	//put all words into vectors
	while (getline(inFile, strOneLine))
	{
		std::stringstream streamOfWordsInLine(strOneLine);
		std::string word;
		while (streamOfWordsInLine >> word)
		{
			std::transform(word.begin(), word.end(), word.begin(), ::tolower);
			wordVector1.push_back(word);
		}
	}

	while (getline(inFile2, strOneLine))
	{
		std::stringstream streamOfWordsInLine(strOneLine);
		std::string word;
		while (streamOfWordsInLine >> word)
		{
			std::transform(word.begin(), word.end(), word.begin(), ::tolower);
			wordVector2.push_back(word);
		}
	}

	//get the ngrams for each text
	std::unordered_map<std::vector<T>, int> text1Ngrams = getNgrams(wordVector1, n);
	std::unordered_map<std::vector<T>, int> text2Ngrams = getNgrams(wordVector2, n);

	//analyze each ngram - for each ngram in the map, 
	for (auto i = text2Ngrams.begin(); i != text2Ngrams.end(); i++)
	{
		std::vector<T> gram = i->first;

		//if the gram isn't in the first text, add it to the count of no occurances
		if (text1Ngrams.count(gram) == 0) {
			didnotoccur++;
		}
		else if (print == 1) { // if it's in there and print is true, print it!
			for (std::vector<T>::iterator it = gram.begin(); it != gram.end(); ++it) {
				std::cout << *it << " ";
			}
			std::cout << std::endl;
		}
	}
	//print percentage of ngrams in second text file not occuring in the first
	double percent = didnotoccur * 100 / text2Ngrams.size() ;
	std::cout << percent << std::endl;
}

int main(int argc, char** argv)
{
	std::string file1 = argv[1];
	std::string file2 = argv[2];
	int n = atoi(argv[3]);
	int print = atoi(argv[4]);

	P2(file1, file2, n, print);
	std::cout << "press any key to end program";
	std::cin.get();

	return 0;
}

