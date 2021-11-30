#include <cstdarg>
#include <cstdint>
#include <cstdlib>
#include <ostream>
#include <new>
#include "pch.h"

extern "C" {

bool delete_blocks();

bool log_updates();

bool log_arm_updates();

bool change_push_limit();

__int32 push_limit();

} // extern "C"
