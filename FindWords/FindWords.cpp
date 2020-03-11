#include <iostream>
#include <fstream>
#include <string>
#include <iterator>
#include <thread>
#include <filesystem>

#include "ThreadPool.h"
// 네임스페이스 사용
using namespace std;

void work(int t, int id) {
    printf("%d start \n", id);
    std::this_thread::sleep_for(std::chrono::seconds(t));
    printf("%d end after %ds\n", id, t);
}
// 메인 함수
int main(void) {
    ThreadPool::ThreadPool pool(3);

    for (int i = 0; i < 100; i++) {
        pool.EnqueueJob([i]() { work(i % 3 + 1, i); });
        printf("@@%d@@", i);
    }
    printf("fgfff");
}