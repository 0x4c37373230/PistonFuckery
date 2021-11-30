#include <iostream>
#include <string>
#include <vector>
#include "pch.h"
#include "mod.h"
#include "Minecraft.hpp"
#include "SymHook.hpp"
#include "termcolor/termcolor"
#include "gsl/gsl"

/*/////////////////////////////////////////////////////
						ISSUES
To finish the part which would allow for custom push
limit; I need the gsl::details struct which I haven't
been able to reconstruct from BDS. It should belong to
microsoft's GSL library; but it's not there in the 
newest version (however a 'details' namespace does 
exist inside the gsl namespace) nor in the newest 
release (there isn't even a 'details' namespace

*/////////////////////////////////////////////////////

const bool logArmUpdates{ log_arm_updates() };
const bool logUpdates{ log_updates() };
const bool deleteBlocks{ delete_blocks() };
const bool changePushLimit{ change_push_limit() };
const __int32 pushLimit{ push_limit() };

void mod_init() 
{
	std::cout << "Piston Fuckery successfully injected" << std::endl;
	std::cout << "Log Arm Updates: " << logArmUpdates << std::endl;
	std::cout << "Log Updates: " << logUpdates << std::endl;
	std::cout << "Block Deletion on Extension: " << deleteBlocks << std::endl;
}
void mod_exit() 
{

}

std::string getArmType(void* pistonThis)
{
	if (*((BYTE*)pistonThis + 208))
		return "Sticky";
	return "Regular";
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
		return '1'; /*
	else if (changePushLimit)
	{
		gsl::details *v15{ (gsl::details*)(*((unsigned __int64*)_this + 30) - *((unsigned __int64*)_this + 29)) };

		if ((unsigned __int64)((__int64)v15 / 12) > pushLimit)
			return 0;
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
		unsigned __int64* v5{ (unsigned __int64*)((char*)_this + 232) };
		__int64 v28{};

		if (!SYMCALL(char, mzGZCnpVKr, _this, a3))
		{
			v28 = *((unsigned __int64*)_this + 30);
			if (!v28 == *((unsigned __int64*)_this + 31))
			{
				v5[1] += 12i64;
			}
		}

		return (unsigned __int64)((v5[1] - *v5) / 12i64) <= pushLimit;
	}
}
*/