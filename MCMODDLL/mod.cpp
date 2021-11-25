#include <iostream>
#include <string>
#include "pch.h"
#include "mod.h"
#include "Minecraft.hpp"
#include "SymHook.hpp"

void mod_init() 
{
	std::cout << "Piston Fuckery successfully injected" << std::endl;
}
void mod_exit() 
{

}

std::string getArmType(void* pistonThis)
{
	std::string result{ "Regular" };

	if (*((BYTE*)pistonThis + 208))
		result = "Sticky";
	return result;
}

void pistonArmState(void* _pistonThis, char state)
{
	std::string getArm{ getArmType(_pistonThis) };

	if (state == 'e')
	{
		std::cout << getArm << " piston is expanding" << std::endl;
	}
	else
	{
		std::cout << getArm << " piston is retracting" << std::endl;
	}
}

//PistonBlockActor::_checkAttachedBlocks
THook(char, fFEJoOUAfG, void* _this, BlockSource* a2)
{
	return '1';
}

//PistonBlockActor::isExpanded
THook(bool, D_LHvgIEZR, void* _this) 
{
	std::string getArm{ getArmType(_this) };

	std::cout << getArm << " piston was updated" << std::endl;
	return original(_this);
}

//PistonBlockActor::isExpanding
THook(bool, eDWwWumtrL, void* _this)
{
	pistonArmState(_this, 'e');
	return original(_this);
}

//PistonBlockActor::isRetracting
THook(bool, Xq_Bdi_TjC, void* _this)
{
	pistonArmState(_this, 'r');
	return original(_this);
}