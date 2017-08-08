#include "mapentity.h"

MapEntity::MapEntity(std::string name, unsigned int seed)
{
    this->name = name;
    this->seed = seed;
}

unsigned int MapEntity::getSeed()
{
    return this->seed;
}

ChunkEntity* MapEntity::getChunkAt(int x, int z)
{
    return this->chunks[x][z];
}
