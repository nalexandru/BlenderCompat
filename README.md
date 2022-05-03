# BlenderCompat
Windows 7 support for Blender 3.x

## Description

This repository contains a compatibility DLL for running Blender 3.x on Windows 7 and a patch to modify the Blender source to use it. It does this by prepending `bcompat7` to the list of libraries so it uses the entry points in it instead of those in the system libraries.

## Binaries

Stable releases, compiled from the same commit as the official releases, are available on the [Releases](https://github.com/nalexandru/BlenderCompat/releases) page.

More recent builds, including pre-release versions, are provided by Loriem: https://www.dropbox.com/sh/eufffe60fvtr9mz/AAA0YtogOoJTKggWtgAXRyXJa?dl=0

## Building Blender for Windows 7

Build Blender following these instructions: https://wiki.blender.org/wiki/Building_Blender/Windows with a small change.
Before running `make update`, copy `bcompat7.patch` into the blender source tree and run `git apply bcompat7.patch` (there will be some warnings about whitespace, they can be ignored) then continue with the guide.

To use the your own build of this compatibility DLL, overwrite the files in the `lib/win64_vc15/bcompat7` directory created after running `make update`.

## api-ms-win-core-path-l1-1-0.dll

In addition to this DLL, `api-ms-win-core-path-l1-1-0.dll` is required to run Blender because of Python. A version of this library for Windows 7 can be found here: https://github.com/nalexandru/api-ms-win-core-path-HACK
