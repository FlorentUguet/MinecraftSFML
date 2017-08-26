#ifndef BLOCKENTITY_H
#define BLOCKENTITY_H

#define BLOCK_SIDE 16

class ChunkEntity;
class BlockSideEntity;

#include "chunkentity.h"
#include "blocksideentity.h"


class BlockEntity
{
public:
    BlockEntity(int x, int y, int z, ChunkEntity *parent = nullptr);
    bool isVisible();
    void setVisible(bool visible);

    void updateBlockVisibility();
    void updateVisibility();

    int getX();
    int getY();
    int getZ();

    int getAbsX();
    int getAbsY();
    int getAbsZ();

    std::vector<BlockSideEntity*> getSides();

    enum Sides{
        TOP = 0,
        BOTTOM,
        LEFT,
        RIGHT,
        FRONT,
        BACK,
        COUNT
    };

private:
    bool visible;

    ChunkEntity* parent;
    int x;
    int y;
    int z;

    std::vector<BlockSideEntity*>sides;
};

#endif // QBLOCKENTITY_H
