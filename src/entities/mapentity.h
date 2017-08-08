#ifndef QMAPENTITY_H
#define QMAPENTITY_H

#define MAP_SIDE_CHUNKS 128
#define MAP_HEIGHT_BLOCKS 64
#define MAP_SEA_LEVEL_BLOCKS (MAP_HEIGHT_BLOCKS/2)

class ChunkEntity;

#include "chunkentity.h"

class MapEntity
{
public:
    MapEntity(std::string name, unsigned int seed);
    unsigned int getSeed();

    ChunkEntity *getChunkAt(int x, int z);

private:
    ChunkEntity *chunks[MAP_SIDE_CHUNKS][MAP_SIDE_CHUNKS];
    std::string name;
    unsigned int seed;
};

#endif // QMAPENTITY_H
