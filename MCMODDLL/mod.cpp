#include <iostream>
#include <string>
#include <vector>
#include "pch.h"
#include "mod.h"
#include "Minecraft.hpp"
#include "SymHook.hpp"
#include "termcolor/termcolor"

const bool logArmUpdates{ log_arm_updates() };
const bool logUpdates{ log_updates() };
const bool deleteBlocks{ delete_blocks() };
//const bool changePushLimit{ change_push_limit() };

void mod_init() 
{
	std::cout << "Piston Fuckery successfully injected" << std::endl;
	std::cout << "Log Arm Updates: " << logArmUpdates << std::endl;
	std::cout << "Log Updates: " << logUpdates << std::endl;
	std::cout << "Block Deletion on Extension: " << deleteBlocks << std::endl;
	//std::cout << "Custom Push Limit: " << changePushLimit << std::endl;
	//std::cout << "New Push Limit: " << 18 << std::endl;
}
void mod_exit() 
{

}

std::string getArmType(void* pistonThis)
{
	if (*((BYTE*)pistonThis + 200))
		return "Sticky";
	return "Regular";
}

unsigned __int64 __fastcall size(void* _this)
{
	return *((unsigned __int64*)_this + 4);
}

void pistonArmState(void* _pistonThis, char state)
{
	switch (state)
	{
	case 'e':
		std::cout 
			<< "Piston Action\n" << termcolor::bright_green
			<< "\tPiston Type: " << termcolor::bright_magenta << getArmType(_pistonThis) << termcolor::bright_green << std::endl
			<< "\tPiston Action: " << termcolor::bright_magenta << "Extending" << termcolor::reset << std::endl;
		break;
	case 'r':
		std::cout
			<< "Piston Action\n" << termcolor::bright_green
			<< "\tPiston Type: " << termcolor::bright_magenta << getArmType(_pistonThis) << termcolor::bright_green << std::endl
			<< "\tPiston Action: " << termcolor::bright_magenta << "Retracting" << termcolor::reset << std::endl;
		break;
	}
}

//PistonBlockActor::_checkAttachedBlocks
THook(char, fFEJoOUAfG, void* _this, BlockSource* a2)
{
	if (deleteBlocks)
		return '1';/*
	else if (changePushLimit)
	{
		unsigned __int64 v15{ size(a2) };
		__int64 v16{ (*(__int64(__fastcall**)(unsigned __int64))(*(unsigned __int64*)v15 + 1448i64))(v15) };
		char v23[8];
		bool v17{ (unsigned int)SYMCALL(unsigned __int64, VekUuoPYdu, v16, v23) != 0 };

		if ((unsigned __int64)((*((unsigned __int64*)_this + 29) - *((unsigned __int64*)_this + 28)) / 12i64) > 18)
		{
			return 0;
		}
		return v17;
	} */
	return original(_this, a2);
}

//PistonBlockActor::isExpanded
THook(bool, D_LHvgIEZR, void* _this)
{
	if (logUpdates)
	{
		std::cout
			<< termcolor::bright_yellow << getArmType(_this)
			<< " piston updated" << termcolor::reset << std::endl;
	}
	return original(_this);
}

//PistonBlockActor::isRetracting
THook(bool, Xq_Bdi_TjC, void* _this)
{
	bool ogFunc{ original(_this) };

	if (logArmUpdates)
	{
		if (ogFunc)
			pistonArmState(_this, 'r');
	}
	return ogFunc;
}

//PistonBlock::canSurvive
THook(bool, WfEASBMNQp, void* _this, BlockSource* a2, BlockPos* a3)
{
	if (SYMCALL(bool, eDWwWumtrL, SYMCALL(BlockActor*, WcoDPEQrUn, a2, a3)))
		pistonArmState(SYMCALL(BlockActor*, WcoDPEQrUn, a2, a3), 'e');
	return original(_this, a2, a3);
}
/*
//PistonBlockActor::_attachedBlockWalker
THook(bool, DRHTpLpIcu, void* _this, BlockSource* a2, BlockPos* a3, unsigned __int8 a4, char a5)
{
	if (changePushLimit)
	{
		unsigned __int64* v5{ (unsigned __int64*)((char*)_this + 224) };
		__int64 v28 = *((unsigned __int64*)_this + 29);

		if (!SYMCALL(char, mzGZCnpVKr, _this, a3))
		{
			if (!v28 == *((unsigned __int64*)_this + 30))
			{
				v5[1] += 12i64;
			}
		}
		return (unsigned __int64)((v5[1] - *v5) / 12i64) <= 18;
	}
	return original(_this, a2, a3, a4, a5);
} */