# PistonFuckery
A MCBE dll mod (mainly for testing) which modifies some piston functions. The current version modifies `PistonBlockActor::_checkAttachedBlocks` to return true. The results are the same as in [this](https://www.youtube.com/watch?v=11b7JH2Pw0c) video. Credits to Pixel for (you could say) discovering this and to [Player] for the BDS mod solution template

## How to update
Get and update the RVAs (Relative Virtual Addresses) and update them in the `SymHook.hpp` file. You can do this with [my own pdb dumper](https://github.com/0x4c37373230/BDumper)  Check if the functions being hooked's formal parameters (which arguments they take) are still the same; if they're not, update them.
