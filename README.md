# PistonFuckery
A MCBE dll mod (mainly for testing) which modifies some piston functions. The current version modifies `PistonBlockActor::_checkAttachedBlocks` to return true. The results are the same as in [this](https://www.youtube.com/watch?v=11b7JH2Pw0c) video. It also adds logging for piston updates (extension, retraction and updates; (`PistonBlockActor::isExtending` and `PistonBlock::canSurvive`, `PistonBlockActor:isRetracting` and `PistonBlockActor::isExtended`) and a way to get the piston type (a recreation of `PistonBlockActor::getCorrectArmBlock`). Credits to Pixel for (you could say) discovering this and to [Player] for the BDS mod solution template

## Usage
Download the latest release on the releases section. The zip file will contain 2 dlls (p_utilities and MCMODDLL) and file named config.cfg. Move all the files to the main BDS folder and inject MCMODDLL with the steps below

## Injecting
Download and run the [Xenos](https://github.com/DarthTon/Xenos) dll injector. In the **Process selection** section; select **nNew** and open the bedrock_server.exe file. Then on the **Images** section, click on the **Add** button and select the MCMODDLL dll file; then click on the **Inject** button

<p align="center">
  <img src="https://user-images.githubusercontent.com/81709312/143133453-861be19d-86f5-4277-be48-488f8263e6cd.png" />
</p>

## config.cfg
This file can be modified to control which modifications should be active. The file structure is as follows:
```ini
armLogging = 1
updateLogging = 1
deleteBlocksOnExtension = 0
customPushLimit = 1
newPushLimit = 16
```
`armLogging` determines if the mod should log piston extension and retraction, `updateLogging` determines if the mod should log piston updates, and `deleteBlocksOnExtension` determines whether pistons should delete the block facing them on extension or just extend normally. All of these values can be set to 1 to enable them or 0 to disable them. `customPushLimit` and `newPushLimit` are not yet usable

## How to update
Get and update the RVAs (Relative Virtual Addresses) and update them in the `SymHook.hpp` file. You can do this with [my own pdb dumper](https://github.com/0x4c37373230/BDumper)  Check if the functions being hooked's formal parameters (which arguments they take) are still the same; if they're not, update them.

### TODO
- Logging through chat messages as opposed to the console
- Get which direction the piston is facing
- Get the piston coordinates
- Customizable push limit [Partially done. See 'Issues' section in `mod.cpp`]
- Check if the piston has blocks attached
