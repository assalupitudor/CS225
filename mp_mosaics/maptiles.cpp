/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"
//#include "cs225/RGB_HSL.h"

using namespace std;


Point<3> convertToXYZ(LUVAPixel pixel) {
    return Point<3>( pixel.l, pixel.u, pixel.v );
}

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage>& theTiles)
{
    /**
     * @todo Implement this function!
     */

    if (!theTiles.size() || !theSource.getRows() || !theSource.getColumns()) {
        return NULL;
    }

    MosaicCanvas * canvas = new MosaicCanvas(theSource.getRows(), theSource.getColumns());
    
    vector<Point<3>> average_color(theTiles.size());
    map<Point<3>, int> tile_map;
    for (size_t i = 0; i < theTiles.size(); i++) {
      average_color[i] = convertToXYZ(theTiles[i].getAverageColor());
      tile_map[average_color[i]] = i;
    }
    KDTree<3> sourceTree(average_color);
    
    for (int x = 0; x < theSource.getRows(); x++){
      for (int y = 0; y < theSource.getColumns(); y++) {
        int a = tile_map[sourceTree.findNearestNeighbor(convertToXYZ(theSource.getRegionColor(x, y)))];
        canvas->setTile(x, y, &theTiles[a]);

      }

    }

    return canvas;
}
