#pragma once

#include "SymHook.hpp"

template<typename T>
struct SharedPtr 
{
	auto get() 
	{
		return **reinterpret_cast<T***>(this);
	}
	auto operator->() 
	{
		return get();
	}
};

struct BlockLegacy 
{
	auto getFullName() const 
	{
		return  *(std::string*)((VA)this + 112);
	}

	auto getBlockItemId() const 
	{
		short v3 = *(short*)((VA)this + 268);
		if (v3 < 0x100) 
			return v3;
		return (short)(255 - v3);
	}

};

struct BlockPos 
{
	INT32* getPosition() const 
	{
		return reinterpret_cast<INT32*>(reinterpret_cast<VA>(this));
	}
};

struct Block {
	const BlockLegacy* getLegacyBlock() const 
	{
		return (BlockLegacy*)(**((VA**)this + 2));
	}
};

struct BlockActor 
{
	Block* getBlock() 
	{
		return *reinterpret_cast<Block**>(reinterpret_cast<VA>(this) + 16);
	}

	BlockPos* getPosition() 
	{
		return reinterpret_cast<BlockPos*>(reinterpret_cast<VA>(this) + 44);
	}
};

struct BlockSource 
{
	Block* getBlock(const BlockPos* blkpos) 
	{
		return SYMCALL(Block *, b_OVEWoaoj, this, blkpos);
	}
};

struct Vec3 
{
	float x;
	float y;
	float z;
};

struct Actor 
{
	BlockSource* getRegion() 
	{
		return *reinterpret_cast<BlockSource**>(reinterpret_cast<VA>(this) + 414*sizeof(void*));
	}

	int getDimension() 
	{
		return *reinterpret_cast<int*>(reinterpret_cast<VA>(this) + 204);
	}

	const std::string* getNameTag() const 
	{
		return SYMCALL(const std::string *, xyMjHVevKQ, this);
	}

	const byte isStand() 
	{
		return *reinterpret_cast<byte *>(reinterpret_cast<VA>(this) + 416);
	}

	Vec3* getPos() 
	{
		return SYMCALL(Vec3 *, eUAXxYCSqy, this);
	}
};
struct Mob
	:Actor 
{};
struct Player
	:Mob 
{};

struct GameMode 
{};

struct ContainerManagerModel 
{
	Player* getPlayer() 
	{
		return *reinterpret_cast<Player**>(reinterpret_cast<VA>(this) + 8);
	}
};
struct LevelContainerManagerModel
	:ContainerManagerModel 
{};

struct ItemStack 
{
	int getId() 
	{
		return SYMCALL(short,
			mgDiVqYgWO,
			this);
	}

	std::string getName() 
	{
		std::string str;
		SYMCALL(VA,
			bFRmLvs_hd,
			this, &str);
		return str;
	}

	int getCount() 
	{
		return *((char*)this + 34);
	}
};

struct LevelContainerModel 
{
	Player* getPlayer() 
	{
		return ((Player**)this)[26];
	}
};