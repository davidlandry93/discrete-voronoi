
#ifndef DISCRETE_VORONOI_H
#define DISCRETE_VORONOI_H

#include <vector>

#include "site.h"
#include "pixel.h"

class DiscreteVoronoi {
public:
    DiscreteVoronoi(int space_height, int space_width, std::vector<Site>& sites);
    void compute();
    void print_diagram() const;

private:
    int height, width;
    std::vector<Site> sites;
    std::vector<Pixel> diagram;

    std::vector<Pixel> create_default_diagram() const;
    void init_diagram_of_site(const Site& site, std::vector<Pixel>& out);
    void merge_diagrams(const std::vector<Pixel>& lhs, const std::vector<Pixel>& rhs, std::vector<Pixel>& out);
};

#endif
