#include <thread>

import Libio;

using namespace std;
std::atomic<int> current_clients = 1;
int max_clients = 10;

int main() {

    std::thread client([&]() {
        while (true) {
            libio::concurrency::sleep(1);
            if (current_clients == max_clients) {
                libio::output::println("I am fed up of this world");
                break;
            }
            ++current_clients;
            libio::output::println("Current clients are: " + std::to_string(current_clients));
        }
    });

    std::thread operatorist([]() {
        while (true) {
            libio::concurrency::sleep(2);
            if (current_clients == 1) {
                libio::output::println("Operatorist finish");
                break;
            }
            --current_clients;
            libio::output::println("Current clients are: " + std::to_string(current_clients));
        }
    });

    client.join();
    operatorist.join();
}
