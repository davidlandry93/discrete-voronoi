
#include <time.h>
#include <iostream>
#include <random>
#include <vector>
#include <chrono>

#include "site.h"
#include "discrete_voronoi.h"

int main(int argc, char** argv) {
    auto start = std::chrono::steady_clock::now();

    std::cout << "Hello world" << std::endl;

    int N_SITES = 100;
    int HEIGHT = 1024;
    int WIDTH = 1024;

    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(0, HEIGHT*WIDTH);

    std::vector<Site> sites(N_SITES);
    for(int i=0; i < N_SITES; i++) {
        int random_int = distribution(generator);

        Site site;
        site.index = i;
        site.i = random_int / WIDTH;
        site.j = random_int % WIDTH;

        sites.push_back(site);
    }

    DiscreteVoronoi dv(HEIGHT, WIDTH, sites);
    dv.compute();

    auto end = std::chrono::steady_clock::now();
    std::cout << "Execution time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << std::endl;

    // dv.print_diagram();

    return 0;
}
