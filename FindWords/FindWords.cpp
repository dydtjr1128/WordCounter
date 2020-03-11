#include <iostream>
#include <fstream>
#include <string>
#include <iterator>
#include <thread>
#include <vector>
#include <sstream>
#include <filesystem>

#include "ThreadPool.h"
#include "FileReader.h"

// 메인 함수
int main(void) {
	std::string filePath, findWord;
	std::cout << "Input findWord>>";
	std::cin >> findWord;
	std::cout << "Input filePath>>";
	std::cin >> filePath;

	auto filePaths = File::FileReader::ReadSubFiles(std::filesystem::path(filePath));

	std::cout << "========== Start read file ==========" << std::endl;

	size_t coreSupportNumber = std::thread::hardware_concurrency();
	ThreadPool::ThreadPool pool(coreSupportNumber);
	std::vector<std::string> resultVector;
	for (auto& path : filePaths) {
		pool.EnqueueJob([path, findWord, resultVector]() {
			int count = File::FileReader::CountWordsInFile(path, findWord);
			std::stringstream ss;
			ss.width(40);
			ss << path.filename().string() << " : ";
			ss.fill('*');
			ss.width(10);
			ss << count << std::endl;
			std::cout << ss.str();
			});
	}
	std::cin >> filePath;
}