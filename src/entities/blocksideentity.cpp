#include "blocksideentity.h"

BlockSideEntity::BlockSideEntity(int side, BlockEntity *parent)
{
    this->side = side;
    this->parent = parent;
    this->visible = false;
    update();
}

bool BlockSideEntity::isVisible()
{
    return this->visible;
}

void BlockSideEntity::hide()
{
    setVisible(false);
}

void BlockSideEntity::show()
{
    setVisible(true);
}

void BlockSideEntity::setVisible(bool status)
{
    this->visible = status;
}

void BlockSideEntity::update()
{
    int hb = BLOCK_SIDE / 2;

    switch(this->side)
    {
    case BlockSides::TOP:
        break;
    case BlockSides::BOTTOM:
        break;
    case BlockSides::FRONT:
        break;
    case BlockSides::BACK:
        break;
    case BlockSides::LEFT:
        break;
    case BlockSides::RIGHT:
        break;
    }
}
