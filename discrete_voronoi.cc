
#include <iostream>
#include <iomanip>
#include <cmath>

#include "pixel.h"
#include "discrete_voronoi.h"

DiscreteVoronoi::DiscreteVoronoi(int space_height, int space_width, std::vector<Site>& sites)
    : height(space_height), width(space_width), sites(std::move(sites)) {
    closest_site = new int[height*width];
    temp_closest_site = new int[height*width];
    distance = new float[height*width];
    temp_distance = new float[height*width];

#pragma acc enter data create(closest_site[0:height*width])
#pragma acc enter data create(temp_closest_site[0:height*width])
#pragma acc enter data create(distance[0:height*width])
#pragma acc enter data create(temp_distance[0:height*width])
}

DiscreteVoronoi::~DiscreteVoronoi() {
#pragma acc exit data delete(closest_site[0:height*width])
#pragma acc exit data delete(distance[0:height*width])
#pragma acc exit data delete(temp_distance[0:height*width])
#pragma acc exit data delete(temp_closest_site[0:height*width])

    delete [] temp_closest_site;
    delete [] temp_distance;
    delete [] closest_site;
    delete [] distance;
}

void DiscreteVoronoi::compute() {
    init_empty_diagram();

        for(Site site : sites) {
            init_diagram_of_site(site);
            merge_diagrams();
        }
}

void DiscreteVoronoi::init_diagram_of_site(const Site& site) {
    for(int i=0; i < height*width; i++) {
        int i_of_pixel = i / width;
        int j_of_pixel = i % width;

        temp_closest_site[i] = site.index;
        temp_distance[i] = std::sqrt((site.i - i_of_pixel) * (site.i - i_of_pixel) +
                                                   (site.j - j_of_pixel) * (site.j - j_of_pixel));

    }
}

void DiscreteVoronoi::init_empty_diagram() {
    for(int i=0; i < width*height; i++) {
        distance[i] = std::numeric_limits<float>::infinity();
        closest_site[i] = std::numeric_limits<int>::max();
    }
}

void DiscreteVoronoi::merge_diagrams() {
    for(int i=0; i < width*height; i++) {
        if(distance[i] > temp_distance[i]) {
            distance[i] = temp_distance[i];
            closest_site[i] = temp_closest_site[i];
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
