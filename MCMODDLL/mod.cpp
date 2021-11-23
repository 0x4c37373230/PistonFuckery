#include <iostream>
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

THook(char, fFEJoOUAfG, void* _this, BlockSource* a2)
{
	return '1';
}