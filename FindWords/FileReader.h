#ifndef FILE_FILE_READER_H
#define FILE_FILE_READER_H

#include <filesystem>
#include <vector>

namespace File {
	class FileReader {
	public:
		static std::vector<std::filesystem::path> ReadSubFiles(const std::filesystem::path& filePath);
		static int CountWordsInFile(const std::filesystem::path& filePath, const std::string& word);
	};
}
#endif // !FILE_FILE_READER_H