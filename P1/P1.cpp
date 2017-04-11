#include "P1.h"

// Driver function to sort the vector elements
// by second element of pairs
bool sortBySecondElement(const std::pair<std::string, int> &a,
	const std::pair<std::string, int> &b)
{
	return (a.second < b.second);
}

void P1(std::string fileName, int k) {
	double numOfWords = 0, totalTopK = 0, percentAmongTopK = 0;
	std::string strOneLine;
	std::unordered_map<std::string, int> wordMap;
	std::ifstream inFile(fileName);

	while (getline(inFile, strOneLine))
	{
		std::stringstream streamOfWordsInLine(strOneLine);
		std::string word;
		while (streamOfWordsInLine >> word)
		{
			std::transform(word.begin(), word.end(), word.begin(), ::tolower);
			std::unordered_map<std::string, int>::const_iterator it = wordMap.find(word);

			if (it == wordMap.end()) //if the word isn't in the map, yet, add it.
				wordMap.emplace(word, 1);
			else // if it is, increase number value of that word
				wordMap[word] += 1;

			//increase total number of words
			numOfWords += 1;
		}
	}

	std::vector<std::pair<std::string, int>> wordVector(wordMap.begin(), wordMap.end());
	std::sort(wordVector.begin(), wordVector.end(), sortBySecondElement);
	std::reverse(wordVector.begin(), wordVector.end());

	for (int i = 0; i < k; i++)
	{
		std::cout << wordVector[i].first << "," << wordVector[i].second << std::endl;
		totalTopK += wordVector[i].second;
	}

	percentAmongTopK = totalTopK / numOfWords * 100;
	std::cout << percentAmongTopK << "%" << std::endl;
}

int main(int argc, char** argv)
{
	std::string file = argv[1];
	int k = atoi(argv[2]);

	P1(file, k);
	//P1("p1_text.txt", 4);
	std::cout << "press any 'Enter' to end program";
	std::string hello;
	std::cin.get();

	return 0;
}