#ifndef QSURFACEENTITY_H
#define QSURFACEENTITY_H

class BlockEntity;

#include "blockentity.h"
#include <cmath>

class BlockSideEntity
{
public:
    BlockSideEntity(int side, BlockEntity *parent = nullptr);

    bool isVisible();
    void hide();
    void show();
    void setVisible(bool status);
    void update();

private:
    bool visible;
    int side;
    BlockEntity *parent;
};

#endif // QSURFACEENTITY_H
