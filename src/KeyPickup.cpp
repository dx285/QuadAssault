#include "KeyPickup.h"

#include "GameInterface.h"
#include "Level.h"
#include "TextureManager.h"
#include "Player.h"
#include "Light.h"
#include "Explosion.h"
#include "RenderUtility.h"

Vec3f gDoorGlowColor[ NUM_DOOR_TYPE ] =
{
	Vec3f( 1.0, 0.1, 0.1 ) ,
	Vec3f( 0.1, 0.1, 1.0 ) ,
	Vec3f( 0.1, 1.0, 0.1 ) ,
};

class KeyPickupRenderer : public IRenderer
{
public:
	virtual void init()
	{
		TextureManager* texMgr = getGame()->getTextureMgr();
		mTex[ RP_DIFFUSE ] = texMgr->getTexture("KeyDiffuse.tga");
		mTex[ RP_NORMAL  ] = texMgr->getTexture("KeyNormal.tga");	
		mTex[ RP_GLOW    ] = texMgr->getTexture("KeyGlow.tga");
	}

	virtual void render( RenderPass pass , LevelObject* object )
	{
		KeyPickup* key = static_cast< KeyPickup* >( object );
		if ( pass == RP_GLOW )
		{
			glColor3fv( gDoorGlowColor[ key->mDoorId ] );
		}
		drawSprite(key->getRenderPos(),key->getSize(),key->mRotation, mTex[ pass ] );
		glColor3f(1.0, 1.0, 1.0);
	}

	Texture* mTex[ NUM_RENDER_PASS ];
};

DEFINE_RENDERER( KeyPickup , KeyPickupRenderer )

KeyPickup::KeyPickup( Vec2f const& pos , int id ) 
	:BaseClass( pos ),mDoorId( id )
{

}

void KeyPickup::init()
{
	ItemPickup::init();

	mSize.x=32;
	mSize.y=32;
	mRotation=0;
}

void KeyPickup::onSpawn()
{
	BaseClass::onSpawn();
	mLight = getLevel()->createLight( getPos() , 128 , false);
	switch( mDoorId )
	{
	case DOOR_RED:   mLight->setColorParam(Vec3f(1.0,0.1,0.1),4); break;
	case DOOR_BLUE:  mLight->setColorParam(Vec3f(0.1,0.25,1.0),4); break;
	case DOOR_GREEN: mLight->setColorParam(Vec3f(0.1,1.0,0.1),4); break;
	}
}

void KeyPickup::onDestroy()
{
	mLight->destroy();
	BaseClass::onDestroy();
}

void KeyPickup::tick()
{
	BaseClass::tick();
	mRotation += Math::toRad( 100*TICK_TIME );
	if(mRotation> 2 * PI )
		mRotation -= 2 * PI;
}

void KeyPickup::onPick( Player* player )
{
	getLevel()->playSound("pickup.wav");		

	TileMap& terrain = getLevel()->getTerrain();

	for(int x=0; x< terrain.getSizeX() ; ++x )
	for(int y=0; y< terrain.getSizeY() ; ++y )
	{
		Tile& tile = terrain.getData( x , y );

		if( tile.type == TID_DOOR && tile.meta == mDoorId )
		{
			tile.type = TID_FLAT;
			tile.meta = 0;

			Explosion* e=getLevel()->createExplosion( Vec2f(x*BLOCK_SIZE+BLOCK_SIZE/2, y*BLOCK_SIZE+BLOCK_SIZE/2), 128 );
			e->setParam(20,1000,50);
			e->setColor( gDoorGlowColor[ mDoorId ] );	
		}
	}

	destroy();
	
}
