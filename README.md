# coverage_benchmark
This repository contains a set of 16 static and 16 dynamic test scenes for dynamic multi-target coverage maximization.

## Overview

Each scene (see folder scenes) is a *.json files with the following components:

* boundary: simple time-invariant polygon which contains all targets, obstacles, and cameras at all times
* targets: array of targets, each containing:
  * shape: simple time-invariant polygon
  * path: simple polygon describing the path the target is moving on; can consist of a single point if the target is static
  * velocity: (optional) Speed the target is moving on the given path, in meters per second
* obstacles: array of obstacles with the same properties as a target
* cameraFoV: field of view of all cameras (half-angle), in degrees
* cameras: array of cameras, each containing:
  * pos: initial position of the camera
  * angle: initial yaw of the camera, in degrees
  * maxVelocity: maximum translational speed, in m/s
  * maxAngularVelocity: maximum rotational speed, in rad/s

The polygons and points are in WKT format.

## Building

You need `cmake` and `boost`.

Use the following steps to build:
```
mkdir build
cd build
cmake ..
make
```

It should create a sample application which converts the json files to svg images.

## Usage

The resulting binary `json2svg` can be used on a single file:
```
json2svg --scene static1.json --output static1.svg
```

For convenience, there is also a bash script (`all.sh`) running the program on all scenes.

## Scenes

### Static

<img src="https://cdn.rawgit.com/USC-ACTLab/coverage_scenes/master/svg/static1.svg" width="100">
<img src="https://cdn.rawgit.com/USC-ACTLab/coverage_scenes/master/svg/static2.svg" width="100">
<img src="https://cdn.rawgit.com/USC-ACTLab/coverage_scenes/master/svg/static3.svg" width="100">
<img src="https://cdn.rawgit.com/USC-ACTLab/coverage_scenes/master/svg/static4.svg" width="100">
<img src="https://cdn.rawgit.com/USC-ACTLab/coverage_scenes/master/svg/static5.svg" width="100">
<img src="https://cdn.rawgit.com/USC-ACTLab/coverage_scenes/master/svg/static6.svg" width="100">
<img src="https://cdn.rawgit.com/USC-ACTLab/coverage_scenes/master/svg/static7.svg" width="100">
<img src="https://cdn.rawgit.com/USC-ACTLab/coverage_scenes/master/svg/static8.svg" width="100">
<img src="https://cdn.rawgit.com/USC-ACTLab/coverage_scenes/master/svg/static9.svg" width="100">
<img src="https://cdn.rawgit.com/USC-ACTLab/coverage_scenes/master/svg/static10.svg" width="100">
<img src="https://cdn.rawgit.com/USC-ACTLab/coverage_scenes/master/svg/static11.svg" width="100">
<img src="https://cdn.rawgit.com/USC-ACTLab/coverage_scenes/master/svg/static12.svg" width="100">
<img src="https://cdn.rawgit.com/USC-ACTLab/coverage_scenes/master/svg/static13.svg" width="100">
<img src="https://cdn.rawgit.com/USC-ACTLab/coverage_scenes/master/svg/static14.svg" width="100">
<img src="https://cdn.rawgit.com/USC-ACTLab/coverage_scenes/master/svg/static15.svg" width="100">
<img src="https://cdn.rawgit.com/USC-ACTLab/coverage_scenes/master/svg/static16.svg" width="100">

### Dynamic

<img src="https://cdn.rawgit.com/USC-ACTLab/coverage_scenes/master/svg/dynamic1.svg" width="100">
<img src="https://cdn.rawgit.com/USC-ACTLab/coverage_scenes/master/svg/dynamic2.svg" width="100">
<img src="https://cdn.rawgit.com/USC-ACTLab/coverage_scenes/master/svg/dynamic3.svg" width="100">
<img src="https://cdn.rawgit.com/USC-ACTLab/coverage_scenes/master/svg/dynamic4.svg" width="100">
<img src="https://cdn.rawgit.com/USC-ACTLab/coverage_scenes/master/svg/dynamic5.svg" width="100">
<img src="https://cdn.rawgit.com/USC-ACTLab/coverage_scenes/master/svg/dynamic6.svg" width="100">
<img src="https://cdn.rawgit.com/USC-ACTLab/coverage_scenes/master/svg/dynamic7.svg" width="100">
<img src="https://cdn.rawgit.com/USC-ACTLab/coverage_scenes/master/svg/dynamic8.svg" width="100">
<img src="https://cdn.rawgit.com/USC-ACTLab/coverage_scenes/master/svg/dynamic9.svg" width="100">
<img src="https://cdn.rawgit.com/USC-ACTLab/coverage_scenes/master/svg/dynamic10.svg" width="100">
<img src="https://cdn.rawgit.com/USC-ACTLab/coverage_scenes/master/svg/dynamic11.svg" width="100">
<img src="https://cdn.rawgit.com/USC-ACTLab/coverage_scenes/master/svg/dynamic12.svg" width="100">
<img src="https://cdn.rawgit.com/USC-ACTLab/coverage_scenes/master/svg/dynamic13.svg" width="100">
<img src="https://cdn.rawgit.com/USC-ACTLab/coverage_scenes/master/svg/dynamic14.svg" width="100">
<img src="https://cdn.rawgit.com/USC-ACTLab/coverage_scenes/master/svg/dynamic15.svg" width="100">
<img src="https://cdn.rawgit.com/USC-ACTLab/coverage_scenes/master/svg/dynamic16.svg" width="100">
