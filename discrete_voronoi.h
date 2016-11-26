
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
    int n_sites;
    int *closest_site;
    float *distance;
    Site *sites;
};

#endif
