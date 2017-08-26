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
    case BlockEntity::Sides::TOP:
        break;
    case BlockEntity::Sides::BOTTOM:
        break;
    case BlockEntity::Sides::FRONT:
        break;
    case BlockEntity::Sides::BACK:
        break;
    case BlockEntity::Sides::LEFT:
        break;
    case BlockEntity::Sides::RIGHT:
        break;
    }
}
