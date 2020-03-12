#include "FileReader.h"
#include <iostream>
#include <string>
#include <fstream>

namespace File {

	std::vector<std::filesystem::path> FileReader::ReadSubFiles(const std::filesystem::path& filePath) {
		std::vector<std::filesystem::path> files;

		for (auto& directoryEntry : std::filesystem::recursive_directory_iterator(filePath)) {
			if (directoryEntry.is_regular_file()) {
				std::cout << "Read file : " << directoryEntry.path().string() << std::endl;
				files.emplace_back(directoryEntry.path());
			}
		}
		return files;
	}

	bool equal(const std::string& line, std::size_t pos, const std::string& word) {
		if (word.size() > line.size() - pos) return false;		
		
		for (std::size_t i = 0; i < word.size(); ++i)
			if (word[i] != line[pos + i]) return false;

		return true;
	}

	int countWords(std::string line, std::string word)	{
		int count = 0;
		std::transform(line.begin(), line.end(), line.begin(), ::tolower);
		std::transform(word.begin(), word.end(), word.begin(), ::tolower);

		for (std::size_t i = 0; i < line.size(); ++i) {
			if (equal(line, i, word)) {
				++count;				
			}
		}

		return count;
	}

	int FileReader::CountWordsInFile(const std::filesystem::path& filePath, const std::string& word) {
		//std::stringstream sstr <<
		int count = 0;
		std::ifstream stream(filePath, std::ios::binary);
		std::string line;
		if (stream.is_open()) {						
			while (std::getline(stream, line)) // for each line in the file
			{				
				count += countWords(line, word);
					
			}

		}
		return count;
	}
}