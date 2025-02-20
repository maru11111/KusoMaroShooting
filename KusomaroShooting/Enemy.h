﻿#pragma once
#include "TwoQuads.h"

struct Objects;

class BaseEnemy {
public:

	BaseEnemy(Objects& objects_, Vec2 pos_);

	void update();

	virtual void attack();

	virtual void move()=0;

	//ダメージを受ける関数。無敵時間ならfalse, そうでなければtrueを返す
	bool damage(int damageAmount, bool isExistInv);

	bool isDestroy();

	bool isInvincibility();

	virtual TwoQuads collision()const=0;

	int getDamageAmount();

	Vec2 getPos();

	int getId();

	virtual void draw()=0;

protected:
	Objects& objects;
	int id;
	static int prevId;
	int maxHp;
	int hp;
	Vec2 pos;
	Vec2 vec;
	double speed;
	int damageAmount;
	double timer = 0;
	double remainingInvincibilityTime = 0;
	double invincibilityTime = 0.5;
};

class GarbageBagNormal : public BaseEnemy {
public:

	GarbageBagNormal(Objects& objects_, Vec2 pos_);

	void move()override;

	TwoQuads collision()const override;

	void draw()override;
};

class GarbageBagFast : public BaseEnemy {
public:
	GarbageBagFast(Objects& objects_, Vec2 pos_);
	void move()override;

	TwoQuads collision()const override;

	void draw()override;
};

class GarbageBagWithCan : public BaseEnemy {
public:
	GarbageBagWithCan(Objects& objects_, Vec2 pos_);
	void move()override;
	void attack()override;
	TwoQuads collision()const override;
	void draw()override;
private:
	double attackInterval=3;
};

class Can : public BaseEnemy {
public:
	enum class CanType {
		Red,
		Grape,
		Orange,
		White,
		Size
	};
	CanType canType;
	Texture texture;
	Can(Objects& objects_, Vec2 pos_, Vec2 vec_);
	void move()override;
	TwoQuads collision()const;
	void draw()override;
private:
};

class Fish : public BaseEnemy {
public:
	Fish(Objects& objects_, Vec2 pos_);
	void move()override;
	TwoQuads collision()const;
	void draw()override;
private:
	double moveInterval=3;
	double isMoving=false;
};

class Umbrella : public BaseEnemy {
public:
	Umbrella(Objects& objects_, Vec2 pos_);
	void move()override;
	TwoQuads collision()const;
	void draw()override;
private:
	double gravity=30;
	double maxVelX = 200;
	double currentVelX=0;
	double angle=0;
};

class GarbageBox : public BaseEnemy {
public:
	enum class State {
		Idle,
		ThrowCan,
		RollingAttack,
		DashAttack,
		StateNum
	};
	struct TimerVar {
		double timer;
		double time;
		TimerVar(double time_) {
			timer = 0;
			time = time_;
		}
	};
	GarbageBox(Objects& objects_, Vec2 pos_);
	void move()override;
	TwoQuads collision()const;
	void updateAttackStateTimer();
	void draw()override;

private:
	State state = State::Idle;
	State nextState = State::ThrowCan;

	TimerVar timers[(int)State::StateNum] =
	{
		//待機
		TimerVar(2.0),
		//缶投げ
		TimerVar(100.0),
		//ローリング体当たり
		TimerVar(3.0),
		//ダッシュアタック
		TimerVar(3.0)
	};
	bool isLidOpen=false;

	bool isEndAttack=false;
};
