# c-mda-engine
In this repository, we provide the source code of the C-MDA engine, which is a C++ proof-of-concept implementation of execution of MDA (Multi-Dimensional Acquisition) events. This implementation is inspired and closely follows the python implementation of [pymmcore-plus](https://github.com/pymmcore-plus/pymmcore-plus). This implementation works in conjunction with the [pymmcore](https://github.com/ashesh-0/pymmcore). In pymmcore, using SWIG wrappers, we expose the C++ classes and methods to python. The C-MDA engine is a C++ implementation of the MDA execution, which is called from python using the pymmcore library.

## Installation
1. Install [micro-manager](https://github.com/micro-manager/micro-manager/blob/57d3d9417d055fb805c8837e5b0182e67ac0242c/doc/how-to-build.md). It is needed to simulate the microscope environment.
2. Install python 3.7
3. Set LD_LIBRARY_PATH correctly to the location where .so files from micro-manager installation are stored. 
4. Run the [dev_build.sh](https://github.com/ashesh-0/pymmcore/blob/main/dev_build.sh)

After the setup is done, one can run [demo_run.py](https://github.com/ashesh-0/pymmcore/blob/main/scripts/demo_run.py) to see the C-MDA engine in action.