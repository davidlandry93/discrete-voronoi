
#include <iostream>
#include <iomanip>
#include <cmath>

#include "pixel.h"
#include "discrete_voronoi.h"

DiscreteVoronoi::DiscreteVoronoi(int space_height, int space_width, std::vector<Site>& sites)
    : height(space_height), width(space_width), sites(std::move(sites)), diagram(height*width) {
    height = space_height;
    width = space_width;
}

void DiscreteVoronoi::compute() {
    std::vector<Pixel> temp_diagram = create_default_diagram();

    for(Site site : sites) {
        init_diagram_of_site(site, temp_diagram);
        merge_diagrams(diagram, temp_diagram, diagram);
    }
}

void DiscreteVoronoi::init_diagram_of_site(const Site& site, std::vector<Pixel>& out) {
    for(int i=0; i < height*width; i++) {
        int i_of_pixel = i / width;
        int j_of_pixel = i % width;

        Pixel pixel;
        pixel.closest_site_index = site.index;
        pixel.distance_to_closest_site = std::sqrt((site.i - i_of_pixel) * (site.i - i_of_pixel) +
                                                   (site.j - j_of_pixel) * (site.j - j_of_pixel));

        out[i] = pixel;
    }
}

std::vector<Pixel> DiscreteVoronoi::create_default_diagram() const {
    return std::vector<Pixel>(width*height);
}

void DiscreteVoronoi::merge_diagrams(const std::vector<Pixel>& lhs, const std::vector<Pixel>& rhs, std::vector<Pixel>& out) {
    for(int i=0; i < lhs.size(); i++) {
        out[i] =
            lhs[i].distance_to_closest_site < rhs[i].distance_to_closest_site ? lhs[i] : rhs[i];
    }
}

void DiscreteVoronoi::print_diagram() const {
    std::cout << std::setprecision(2) << std::fixed;

    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            float value = diagram[i*width + j].distance_to_closest_site;
            if(value == 0.0) {
                std::cout << "  x  ";
            } else {
                std::cout << diagram[i*width + j].distance_to_closest_site << " ";
            }
        }
        std::cout << std::endl;
    }
}
