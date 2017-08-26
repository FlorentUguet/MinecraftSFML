#ifndef QCHUNKENTITY_H
#define QCHUNKENTITY_H

#define CHUNK_SIDE_BLOCKS 16
#define ZOOM_FACTOR 5.0

#include <iostream>
#include <vector>

class MapEntity;
class BlockEntity;

#include "mapentity.h"
#include "blockentity.h"
#include "znoise/Perlin.hpp"

class ChunkEntity
{
public:
    ChunkEntity(int x, int z, MapEntity* parent = nullptr);
    void generate();
    void generate(unsigned int seed);
    void generateHeightmap(unsigned int seed);
    void getHeightmap(double array[][CHUNK_SIDE_BLOCKS]);

    BlockEntity* getBlockAt(int x, int y, int z);
    int getHeight(int x, int z);

    std::vector<BlockEntity*> getBlocks();

    void updateVisibility();

    bool hasMap();

    MapEntity* getMap();

    int getX();
    int getZ();

private:
    MapEntity* parent;
    int x;
    int z;

    BlockEntity* blocks[CHUNK_SIDE_BLOCKS][MAP_HEIGHT_BLOCKS][CHUNK_SIDE_BLOCKS];
    std::vector<BlockEntity*> blockList;

    double heightmap[CHUNK_SIDE_BLOCKS][CHUNK_SIDE_BLOCKS];
};

#endif // QCHUNKENTITY_H
