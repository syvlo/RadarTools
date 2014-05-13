RadarTools
==========

Tools to handle sar images.

Currently only have a imw2png converter.

### How-to install
This project uses CMake as a build system.

* First, you need to download and install the lib [SAR](https://github.com/syvlo/LibSAR).
* Make sure that CMake is installed on your system.
* In CMakeLists.txt, replace this line to the path to the include dir where lies libSAR.
```
include_directories(/Path/to/libSAR/include/)
```
* Go in the directory of the project and type:
```
cmake . && make
```
* You should have a binary named imw2png created in bin/

### Usage
Just run:

```
/Path/to/imw2png filename.imw n [out.png]
```

This will map the values in filename.imw to [0; mu + n * sigma] and will save it as out.png. If no output name is given, it will save it as filename.png.


