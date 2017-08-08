#ifndef BLOCKENTITY_H
#define BLOCKENTITY_H

#define BLOCK_SIDE 16

class ChunkEntity;
class BlockSideEntity;

#include "chunkentity.h"
#include "blocksideentity.h"

enum BlockSides{
    TOP = 0,
    BOTTOM,
    LEFT,
    RIGHT,
    FRONT,
    BACK,
    COUNT
};


class BlockEntity
{
public:
    BlockEntity(int x, int y, int z, ChunkEntity *parent = nullptr);
    bool isVisible();
    void setVisible(bool visible);

    void updateBlockVisibility();
    void updateVisibility();

private:
    bool visible;

    ChunkEntity* parent;
    int x;
    int y;
    int z;

    BlockSideEntity *sides[BlockSides::COUNT];
};

#endif // QBLOCKENTITY_H
