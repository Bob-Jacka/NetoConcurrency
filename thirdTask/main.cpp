#include <iostream>
#include "Data.hpp"

import Libio;

#define NEW_LINE (std::cout << "\n");

#define REGULAR_LOCK
// #define SCOPED_LOCK
// #define UNIQUE_LOCK

int main() {
    using namespace libio::output;
    Data a{1, "Marv"}; //sticky bandits example
    Data b{2, "Harry"};

    println("Before swap:");
    println("A's val: " + std::to_string(a.get_value()));
    println("A's name: " + a.get_name());
    NEW_LINE
    println("B's val: " + std::to_string(b.get_value()));
    println("B's name: " + b.get_name());

#ifdef SCOPED_LOCK
    swap_with_scoped_lock(a, b);
#elifdef REGULAR_LOCK
    swap_with_lock(a, b);
#elifdef UNIQUE_LOCK
    swap_with_unique_lock(a, b);
#else
#pragma message("Select your lock")
#include <stdexcept>
    throw std::runtime_error("Lock is not defined");
#endif

    NEW_LINE
    println("After swap: ");
    println("A's val: " + std::to_string(a.get_value()));
    println("A's name: " + a.get_name());
    NEW_LINE
    println("B's val: " + std::to_string(b.get_value()));
    println("B's name: " + b.get_name());
}
