#ifndef PIXEL_H
#define PIXEL_H

#include <limits>

struct Pixel{
    int closest_site_index;
    float distance_to_closest_site;

    Pixel()
        : closest_site_index(std::numeric_limits<int>::max()),
          distance_to_closest_site(std::numeric_limits<float>::infinity())
        {}
};

#endif
