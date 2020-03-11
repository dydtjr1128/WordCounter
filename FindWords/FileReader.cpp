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

	bool equal(const std::string& str, std::size_t pos, const std::string& word)
	{
		if (word.size() > str.size() - pos) return false;

		for (std::size_t i = 0; i < word.size(); ++i)
			if (word[i] != str[pos + i]) return false;

		return true;
	}

	bool contains(const std::string& str, const std::string& word)
	{
		for (std::size_t i = 0; i < str.size(); ++i)
			if (equal(str, i, word)) return true;

		return false;
	}

	int FileReader::CountWordsInFile(const std::filesystem::path& filePath, const std::string& word) {
		//std::stringstream sstr <<
		int count = 0;
		std::ifstream stream(filePath, std::ios::binary);
		std::string line;
		if (stream.is_open()) {
			while (std::getline(stream, line)) // for each line in the file
			{
				if (contains(line, word))
					++count;
			}

		}
		return count;
	}
}