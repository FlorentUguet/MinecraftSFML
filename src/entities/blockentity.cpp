#include "blockentity.h"

BlockEntity::BlockEntity(int x, int y, int z, ChunkEntity *parent)
{
    this->parent = parent;
    this->x = x;
    this->z = z;
    this->y = y;

    this->sides = std::vector<BlockSideEntity*>(Sides::COUNT);

    for(int i=0;i<Sides::COUNT;i++)
    {
        this->sides[i] = new BlockSideEntity(i,this);
    }
}

bool BlockEntity::isVisible()
{
    return this->visible;
}

void BlockEntity::setVisible(bool visible)
{
    this->visible = visible;
}

int BlockEntity::getX()
{
    return this->x;
}

int BlockEntity::getY()
{
    return this->y;
}

int BlockEntity::getZ()
{
    return this->z;
}

int BlockEntity::getAbsX()
{
    if(this->parent)
        return (this->parent->getX() * CHUNK_SIDE_BLOCKS) + this->getX();
    else
        this->getX();
}

int BlockEntity::getAbsY()
{
    return this->getY();
}

int BlockEntity::getAbsZ()
{
    if(this->parent)
        return (this->parent->getZ() * CHUNK_SIDE_BLOCKS) + this->getZ();
    else
        this->getZ();
}

std::vector<BlockSideEntity*> BlockEntity::getSides()
{
    return this->sides;
}

void BlockEntity::updateBlockVisibility()
{
    bool enabled = false;

    if(this->parent->getBlockAt(this->x,this->y +1, this->z) == 0)
    {
        enabled = true;
    }
    else if(this->parent->getBlockAt(this->x,this->y -1 , this->z) == 0)
    {
        enabled = true;
    }
    else if(this->parent->getBlockAt(this->x,this->y, this->z+1) == 0)
    {
        enabled = true;
    }
    else if(this->parent->getBlockAt(this->x,this->y, this->z-1) == 0)
    {
        enabled = true;
    }
    else if(this->parent->getBlockAt(this->x+1,this->y, this->z) == 0)
    {
        enabled = true;
    }
    else if(this->parent->getBlockAt(this->x-1,this->y, this->z) == 0)
    {
        enabled = true;
    }

    this->visible = enabled;
}

void BlockEntity::updateVisibility()
{
    for(int i=0;i<Sides::COUNT;i++)
    {
        this->sides[i]->setVisible(this->parent == 0);
    }

    if(this->parent !=0)
    {
        //Above
        if(this->parent->getBlockAt(this->x,this->y +1, this->z) == 0)
            this->sides[Sides::TOP]->show();

        //Under
        if(this->parent->getBlockAt(this->x,this->y - 1, this->z) == 0)
            this->sides[Sides::BOTTOM]->show();

        //Back
        if(this->z == CHUNK_SIDE_BLOCKS-1)
        {
            if(this->parent->hasMap())
            {
                if(this->parent->getZ() < MAP_SIDE_CHUNKS-1)
                {
                    ChunkEntity *c = this->parent->getMap()->getChunkAt(this->parent->getX(),this->parent->getZ()+1);
                    if(c->getBlockAt(this->x,this->y,0) == 0)
                        this->sides[Sides::BACK]->show();
                }
            }
            else
            {
                this->sides[Sides::BACK]->show();
            }
        }
        else
        {
            if(parent->getBlockAt(this->x, this->y, this->z+1) == 0)
                this->sides[Sides::BACK]->show();
        }

        //Front
        if(this->z == 0)
        {
            if(this->parent->hasMap())
            {
                if(this->parent->getZ() > 0)
                {
                    ChunkEntity *c = this->parent->getMap()->getChunkAt(this->parent->getX(),this->parent->getZ()-1);
                    if(c->getBlockAt(this->x,this->y,CHUNK_SIDE_BLOCKS-1) == 0)
                        this->sides[Sides::FRONT]->show();
                }
            }
            else
            {
                this->sides[Sides::FRONT]->show();
            }
        }
        else
        {
            if(parent->getBlockAt(this->x, this->y, this->z+1) == 0)
                this->sides[Sides::FRONT]->show();
        }

        //Left
        if(this->x == 0){
            if(this->parent->hasMap()){
                if(this->parent->getX() > 0){
                    //If the block is on the X origin
                    ChunkEntity *c = this->parent->getMap()->getChunkAt(this->parent->getX()-1,this->parent->getZ());
                    if(c->getBlockAt(CHUNK_SIDE_BLOCKS-1,this->y,this->z) == 0)
                        this->sides[Sides::LEFT]->show();
                }
            }else{
                this->sides[Sides::LEFT]->show();
            }
        }else{
            if(parent->getBlockAt(this->x-1,this->y,this->z) == 0)
                this->sides[Sides::LEFT]->show();
        }

        //Right
        if(this->x == CHUNK_SIDE_BLOCKS-1){
            if(this->parent->hasMap()){
                if(this->parent->getX() < CHUNK_SIDE_BLOCKS-1){
                    //If the block is on the X origin
                    ChunkEntity *c = this->parent->getMap()->getChunkAt(this->parent->getX()+1,this->parent->getZ());
                    if(c->getBlockAt(0,this->y,this->z) == 0)
                        this->sides[Sides::RIGHT]->show();
                }
            }else{
                this->sides[Sides::RIGHT]->show();
            }
        }else{
            if(parent->getBlockAt(this->x+1,this->y,this->z) == 0)
                this->sides[Sides::RIGHT]->show();
        }
    }

    for(int i=0;i<Sides::COUNT;i++)
    {
        if(this->sides[i]->isVisible())
        {
            this->sides[i]->update();
        }
    }

}
