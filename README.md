# BlenderCompat
Windows 7 support for Blender 3.0

## Description

This repository contains a compatibility DLL for running Blender 3.0 on Windows 7 and a patch to modify the Blender source to use it. It does this by prepending `bcompat7` to the list of libraries so it uses the entry points in it instead of those in the system libraries.

## Binaries

You can get a build of Blender 3.0 that should work on Windows 7 from https://1drv.ms/u/s!AhpnXywMA4U1mQV-F-k19I17fE51?e=K8kgKw

## Building Blender for Windows 7

Build Blender following these instructions: https://wiki.blender.org/wiki/Building_Blender/Windows with a small change.
Before running `make update`, copy `bcompat7.patch` into the blender source tree and run `git apply bcompat7.patch` (there will be some warnings about whitespace, they can be ignored) then continue with the guide.

To use the your own build of this compatibility DLL, overwrite the files in the `lib/win64_vc15/bcompat7` directory created after running `make update`.

## api-ms-win-core-path-l1-1-0.dll

In addition to this DLL, `api-ms-win-core-path-l1-1-0.dll` is required to run Blender because of Python. A version of this library for Windows 7 can be found here: https://github.com/nalexandru/api-ms-win-core-path-HACK
