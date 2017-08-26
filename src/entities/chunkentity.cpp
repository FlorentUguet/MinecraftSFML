#include "chunkentity.h"

ChunkEntity::ChunkEntity(int x, int z, MapEntity* parent)
{
    this->parent = parent;
    this->x = x;
    this->z = z;
}

void ChunkEntity::generate()
{
    generate(parent->getSeed());
}

void ChunkEntity::generate(unsigned int seed)
{
    Perlin pn(seed);

    for(int i=0;i<CHUNK_SIDE_BLOCKS;i++) //X
    {
        for(int k=0;k<CHUNK_SIDE_BLOCKS;k++) //Z
        {
            float absX = (float)(i + (this->x * CHUNK_SIDE_BLOCKS)) / ZOOM_FACTOR;
            float absZ = (float)(k + (this->z * CHUNK_SIDE_BLOCKS)) / ZOOM_FACTOR;

            double h = pn.Get({absX, absZ}, 0.5f);
            int heightBlocks = (h * (MAP_HEIGHT_BLOCKS-MAP_SEA_LEVEL_BLOCKS)) + MAP_SEA_LEVEL_BLOCKS;

            this->heightmap[i][k] = h;

            for(int j=0;j<heightBlocks;j++) //Y
            {
                BlockEntity *b = new BlockEntity(i,j,k,this);
                this->blocks[i][j][k] = b;
                this->blockList.push_back(b);
            }
        }
    }
}

void ChunkEntity::updateVisibility()
{
    for(int i=0;i<this->blockList.size();i++)
    {
        this->blockList[i]->updateVisibility();
    }
}

int ChunkEntity::getHeight(int x, int z)
{
    return this->heightmap[x][z] * MAP_HEIGHT_BLOCKS;
}

std::vector<BlockEntity*> ChunkEntity::getBlocks()
{
    return this->blockList;
}

void ChunkEntity::generateHeightmap(unsigned int seed)
{
    Perlin pn(seed);

    for(int i=0;i<CHUNK_SIDE_BLOCKS;i++) //X
    {
        for(int k=0;k<CHUNK_SIDE_BLOCKS;k++) //Z
        {
            float absX = (float)(i + (this->x * CHUNK_SIDE_BLOCKS)) / ZOOM_FACTOR;
            float absZ = (float)(k + (this->z * CHUNK_SIDE_BLOCKS)) / ZOOM_FACTOR;

            this->heightmap[i][k] = pn.Get({absX, absZ}, 0.5f);
        }
    }
}

void ChunkEntity::getHeightmap(double array[][CHUNK_SIDE_BLOCKS])
{
    for(int i=0;i<CHUNK_SIDE_BLOCKS;i++)
    {
        for(int j=0;j<CHUNK_SIDE_BLOCKS;j++)
        {
            array[i][j] = this->heightmap[i][j];
        }
    }
}

BlockEntity* ChunkEntity::getBlockAt(int x, int y, int z)
{
    if(x < 0 || y < 0 || z < 0 || x >= CHUNK_SIDE_BLOCKS || y >= MAP_HEIGHT_BLOCKS || z >= CHUNK_SIDE_BLOCKS)
    {
        return 0;
    }
    else
    {
        return this->blocks[x][y][z];
    }
}

bool ChunkEntity::hasMap()
{
    return this->parent != 0;
}

MapEntity* ChunkEntity::getMap()
{
    return this->parent;
}

int ChunkEntity::getX()
{
    return this->x;
}

int ChunkEntity::getZ()
{
    return this->z;
}
