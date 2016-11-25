
#include <time.h>
#include <iostream>
#include <random>
#include <vector>

#include "site.h"
#include "discrete_voronoi.h"

int main(int argc, char** argv) {
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

    return 0;
}
