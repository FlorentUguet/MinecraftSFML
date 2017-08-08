#include "blockentity.h"

BlockEntity::BlockEntity(int x, int y, int z, ChunkEntity *parent)
{
    this->parent = parent;
    this->x = x;
    this->z = z;
    this->y = y;

    for(int i=0;i<(int)BlockSides::COUNT;i++)
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
    for(int i=0;i<BlockSides::COUNT;i++)
    {
        this->sides[i]->setVisible(this->parent ==0);
    }

    if(this->parent !=0)
    {
        //Above
        if(this->parent->getBlockAt(this->x,this->y +1, this->z) == 0)
            this->sides[BlockSides::TOP]->show();

        //Under
        if(this->parent->getBlockAt(this->x,this->y - 1, this->z) == 0)
            this->sides[BlockSides::BOTTOM]->show();

        //Back
        if(this->z == CHUNK_SIDE_BLOCKS-1)
        {
            if(this->parent->hasMap())
            {
                if(this->parent->getZ() < MAP_SIDE_CHUNKS-1)
                {
                    ChunkEntity *c = this->parent->getMap()->getChunkAt(this->parent->getX(),this->parent->getZ()+1);
                    if(c->getBlockAt(this->x,this->y,0) == 0)
                        this->sides[BlockSides::BACK]->show();
                }
            }
            else
            {
                this->sides[BlockSides::BACK]->show();
            }
        }
        else
        {
            if(parent->getBlockAt(this->x, this->y, this->z+1) == 0)
                this->sides[BlockSides::BACK]->show();
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
                        this->sides[BlockSides::FRONT]->show();
                }
            }
            else
            {
                this->sides[BlockSides::FRONT]->show();
            }
        }
        else
        {
            if(parent->getBlockAt(this->x, this->y, this->z+1) == 0)
                this->sides[BlockSides::FRONT]->show();
        }

        //Left
        if(this->x == 0){
            if(this->parent->hasMap()){
                if(this->parent->getX() > 0){
                    //If the block is on the X origin
                    ChunkEntity *c = this->parent->getMap()->getChunkAt(this->parent->getX()-1,this->parent->getZ());
                    if(c->getBlockAt(CHUNK_SIDE_BLOCKS-1,this->y,this->z) == 0)
                        this->sides[BlockSides::LEFT]->show();
                }
            }else{
                this->sides[BlockSides::LEFT]->show();
            }
        }else{
            if(parent->getBlockAt(this->x-1,this->y,this->z) == 0)
                this->sides[BlockSides::LEFT]->show();
        }

        //Right
        if(this->x == CHUNK_SIDE_BLOCKS-1){
            if(this->parent->hasMap()){
                if(this->parent->getX() < CHUNK_SIDE_BLOCKS-1){
                    //If the block is on the X origin
                    ChunkEntity *c = this->parent->getMap()->getChunkAt(this->parent->getX()+1,this->parent->getZ());
                    if(c->getBlockAt(0,this->y,this->z) == 0)
                        this->sides[BlockSides::RIGHT]->show();
                }
            }else{
                this->sides[BlockSides::RIGHT]->show();
            }
        }else{
            if(parent->getBlockAt(this->x+1,this->y,this->z) == 0)
                this->sides[BlockSides::RIGHT]->show();
        }
    }

    for(int i=0;i<BlockSides::COUNT;i++)
    {
        if(this->sides[i]->isVisible())
        {
            this->sides[i]->update();
        }
    }

}
