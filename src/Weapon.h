#ifndef Weapon_h__
#define Weapon_h__

#include "Object.h"

class Level;
class Bullet;
class Player;
class Weapon;

class FireHelper
{
public:
	void fire( Bullet* bullet , Vec2f const& offset = Vec2f(0,0) );
	Vec2f pos;
	Vec2f dir;
	int   team;
	Weapon* weapon;
};

class Weapon : public Object
{
public:
	virtual void init( Player* player );
	virtual void update(float deltaT);

	virtual IRenderer* getRenderer(){ return NULL; }

	virtual void render( RenderPass pass );
	
	virtual void onFireBullet(Bullet* p);

	void fire( Vec2f const& pos , Vec2f const& dir, int team );

	Player* getOwner(){ return mOwner; }
	float   getEnergyCast(){  return mEnergyCast;  }

protected:
	virtual void doFire( FireHelper& helper ){}

	friend class WeaponRenderer;
	Texture* mTextues[ NUM_RENDER_PASS ];

	float   mCDTime, mFireTimer;
	float   mCDSpeed;
	float   mEnergyCast;
	Player* mOwner;
};


#endif // Weapon_h__