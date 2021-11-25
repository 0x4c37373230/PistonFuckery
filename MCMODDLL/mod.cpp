#include <iostream>
#include <string>
#include "pch.h"
#include "mod.h"
#include "Minecraft.hpp"
#include "SymHook.hpp"
#include "deps/termcolor"

/*///////////////////////////////////////////////////////////////
							ISSUES
1-	You can't use PistonBlockActor::isExpanding to know if a 
	piston is extending as it's called in a different 
	function than PistonBlockActor::isRetracting and that 
	function gets called inside the function in which 
	isRetracting is called. Adding a check for expansion in
	the function where retraction is checked and checking if 
	the piston is not retracting don't work either.
///////////////////////////////////////////////////////////////*/

void mod_init() 
{
	std::cout << "Piston Fuckery successfully injected" << std::endl;
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
	default:
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
	return '1';
}

//PistonBlockActor::isExpanded
THook(bool, D_LHvgIEZR, void* _this)
{
	std::cout 
		<< termcolor::bright_yellow << getArmType(_this) 
		<< " piston updated" << termcolor::reset << std::endl;
	return original(_this);
}

//PistonBlockActor::isRetracting
THook(bool, Xq_Bdi_TjC, void* _this)
{
	bool ogFunc{ original(_this) };

	if (ogFunc)
		pistonArmState(_this, 'r');
	return ogFunc;
}
/*
//PistonBlockActor::isExpanding
THook(bool, eDWwWumtrL, void* _this)
{}

//PistonBlock::canSurvive
THook(bool, WfEASBMNQp, void* _this, BlockSource* a2, BlockPos* a3)
{}
*/