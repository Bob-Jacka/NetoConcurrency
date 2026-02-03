#include <mutex>
#include <vector>
#include "Timer.hpp"

std::mutex m1;
std::mutex m2;
std::mutex m3;
std::mutex m4;

static void table_header() {
    std::cout << "#\t" << "id\t\t" << "Progress Bar\t\t" << "Time" << std::endl;
}

static void progress_bar(const int thread_num_now) {
    int progress_bar = 23;
    constexpr int total = 37;
    constexpr int pos_time = 43;

    m2.lock();
    const Timer t1;
    m2.unlock();

    m4.lock();
    consol_parameter::SetPosition(0, thread_num_now + 1);
    std::cout << thread_num_now << "\t" << std::this_thread::get_id() << "\t";
    m4.unlock();

    while (progress_bar < total) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        m1.lock();
        consol_parameter::SetPosition(progress_bar, thread_num_now + 1);
        std::cout << static_cast<char>(219);

        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        ++progress_bar;
        m1.unlock();
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(333));

    m3.lock();
    consol_parameter::SetPosition(pos_time, thread_num_now + 1);
    t1.print();
    m3.unlock();
}

int main() {
    constexpr int threads = 5; //Change thread count
    std::vector<std::thread> threads_vec(threads);
    table_header();
    for (size_t i = 0; i < threads; i++) {
        threads_vec[i] = std::thread(progress_bar, i);
    }
    for (auto &i: threads_vec) {
        i.join();
    }
    consol_parameter::SetPosition(0, threads + 1);
}
