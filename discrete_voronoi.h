
#ifndef DISCRETE_VORONOI_H
#define DISCRETE_VORONOI_H

#include <vector>

#include "site.h"
#include "pixel.h"

class DiscreteVoronoi {
public:
    DiscreteVoronoi(int space_height, int space_width, std::vector<Site>& sites);
    ~DiscreteVoronoi();
    void compute();
    void print_diagram() const;

private:
    int height, width;
    std::vector<Site> sites;
    int *closest_site, *temp_closest_site;
    float *distance, *temp_distance;

    void init_empty_diagram();
    void init_diagram_of_site(const Site& site);
    void merge_diagrams();
};

#endif
