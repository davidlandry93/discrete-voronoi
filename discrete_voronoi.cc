
#include <iostream>
#include <iomanip>
#include <cmath>

#include "pixel.h"
#include "discrete_voronoi.h"

DiscreteVoronoi::DiscreteVoronoi(int space_height, int space_width, std::vector<Site>& _sites)
    : height(space_height), width(space_width), n_sites(_sites.size()) {
    closest_site = new int[height*width];
    distance = new float[height*width];
    sites = new Site[n_sites];

    for(int i=0; i < n_sites; i++) {
        sites[i] = _sites[i];
    }

#pragma acc enter data create(closest_site[0:height*width])
#pragma acc enter data create(distance[0:height*width])
#pragma acc enter data create(sites[0:n_sites])
}

DiscreteVoronoi::~DiscreteVoronoi() {
#pragma acc exit data delete(closest_site[0:height*width])
#pragma acc exit data delete(distance[0:height*width])
#pragma acc exit data delete(sites[0:n_sites])

    delete [] closest_site;
    delete [] distance;
    delete [] sites;
}

void DiscreteVoronoi::compute() {
    #pragma acc kernels
    {
        for(int i = 0; i < width*height; i++) {
            float min_distance = std::numeric_limits<float>::infinity();
            int best_site = std::numeric_limits<int>::max();

            int i_of_pixel = i / width;
            int j_of_pixel = i % width;

            for(int j = 0; j < n_sites; j++) {
                float distance_to_site = std::sqrt((sites[j].i - i_of_pixel) * (sites[j].i - i_of_pixel) +
                                                   (sites[j].j - j_of_pixel) * (sites[j].j - j_of_pixel));

                if(distance_to_site < min_distance) {
                    min_distance = distance_to_site;
                    best_site = j;
                }
            }

            closest_site[i] = best_site;
            distance[i] = min_distance;
        }
    }
}

void DiscreteVoronoi::print_diagram() const {
    std::cout << std::setprecision(2) << std::fixed;

    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            float value = distance[i*width + j];
            if(value == 0.0) {
                std::cout << "  x  ";
            } else {
                std::cout << value << " ";
            }
        }
        std::cout << std::endl;
    }
}
