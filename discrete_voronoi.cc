
#include <iostream>
#include <cmath>

#include "pixel.h"
#include "discrete_voronoi.h"

DiscreteVoronoi::DiscreteVoronoi(int space_height, int space_width, std::vector<Site>& sites)
    : height(space_height), width(space_width), sites(std::move(sites)) {}

void DiscreteVoronoi::compute() {
    std::vector<Pixel> diagram = create_default_diagram();

    for(Site site : sites) {
        std::cout << "Site" << std::endl;

        std::vector<Pixel> diagram_of_site = create_diagram_of_site(site);
        diagram = merge_diagrams(diagram, diagram_of_site);
    }
}

std::vector<Pixel> DiscreteVoronoi::create_diagram_of_site(const Site& site) {
    std::vector<Pixel> pixels(height*width);

    for(int i=0; i < height*width; i++) {
        int i_of_pixel = i / width;
        int j_of_pixel = i % width;

        Pixel pixel;
        pixel.closest_site_index = site.index;
        pixel.distance_to_closest_site = std::sqrt((site.i - i_of_pixel) * (site.i - i_of_pixel) +
                                                   (site.j - j_of_pixel) * (site.j - j_of_pixel));

        pixels[i] = pixel;
    }

    return pixels;
}

std::vector<Pixel> DiscreteVoronoi::create_default_diagram() const {
    return std::vector<Pixel>(width*height);
}

std::vector<Pixel> DiscreteVoronoi::merge_diagrams(const std::vector<Pixel>& lhs, const std::vector<Pixel>& rhs) {
    std::vector<Pixel> merged_diagram = create_default_diagram();

    for(int i=0; i < lhs.size(); i++) {
        merged_diagram[i] = 
            lhs[i].distance_to_closest_site < rhs[i].distance_to_closest_site ? lhs[i] : rhs[i];
    }

    return merged_diagram;
}
