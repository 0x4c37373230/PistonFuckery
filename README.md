# PistonFuckery
A MCBE dll mod (mainly for testing) which modifies some piston functions. The current version modifies `PistonBlockActor::_checkAttachedBlocks` to return true. The results are the same as in [this](https://www.youtube.com/watch?v=11b7JH2Pw0c) video. Credits to Pixel for (you could say) discovering this and to [Player] for the BDS mod solution template

## Injecting
Download and run the [Xenos](https://github.com/DarthTon/Xenos) dll injector. In the **Process selection** section; select **nNew** and open the bedrock_server.exe file. Then on the **Images** section, click on the **Add** button and select the dll file; then click on the **Inject** button

<p align="center">
  <img src="https://user-images.githubusercontent.com/81709312/143133453-861be19d-86f5-4277-be48-488f8263e6cd.png" />
</p>

## How to update
Get and update the RVAs (Relative Virtual Addresses) and update them in the `SymHook.hpp` file. You can do this with [my own pdb dumper](https://github.com/0x4c37373230/BDumper)  Check if the functions being hooked's formal parameters (which arguments they take) are still the same; if they're not, update them.
