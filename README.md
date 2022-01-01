- ## [**Table of content**](#table-of-content)
- [Description](#description)
- [Getting started:](#getting-started)
  - [Requirements and pre-requisites](#requirements-and-pre-requisites)
  - [API Usage :](#api-usage-)
    - [Includes](#includes)
    - [Code Examples :](#code-examples-)
- [Development note](development-note)
## Description

 A Static API library which does the following:
  1. Read a topology from a given JSON file and store it in the memory.
  2. Write a given topology from the memory to a JSON file.
  3. Query about which topologies are currently in the memory.
  4. Delete a given topology from memory.
  5. Query about which devices are in a given topology.
  6. Query about which devices are connected to a given netlist node in
  a given topology.

## Getting started:

### Requirements and pre-requisites

This API  depends on [jsoncpp](https://github.com/open-source-parsers/jsoncpp) package to easily install this package you can use [vcpkg](https://vcpkg.io/en/index.html) using the following commands 

> #### Windows setup of jsoncpp :
```powershell
    git clone https://github.com/Microsoft/vcpkg.git
    .\vcpkg\bootstrap-vcpkg.bat
    .\vcpkg\vcpkg integrate install
    .\vcpkg\vcpkg installjsoncpp
```
> #### linux setup of jsoncpp:
```bash
    git clone https://github.com/Microsoft/vcpkg.git
    cd vcpkg
    ./bootstrap-vcpkg.sh
    ./vcpkg integrate install   # used to 
    ./vcpkg install jsoncpp
```

### API Usage :

#### Includes
```c++
// your main.cpp

#include "TopologyLibrary.h"


//optional makes you life a little easier
using namespace TopologyLibrary;
```

#### Code Examples :
```c++
    // reads a json file ,returns a topology object 
    // and adds the topology to topology list
    Topology readJSON(string FileName);
    
    // stores the received topology in file
    bool writeJSON(string FileName, Topology topology);
    
    // returns the stored topologies in the memory in form 
    // of topology list
    TopologyList queryTopologies();
    
    // deletes a topology from the memory based on topology id
    bool deleteTopology(string TopologyID);
    
    // returns a list of devices in a given topology 
    DeviceList queryDevices(string TopologyID);
    
    // returns the devices are connected to a given netlist node in
    // a given topology.
    DeviceList queryDevicesWithNetlistNode(string TopologyID, string NetlistNodeID);
```
> A demo file can be found [here](./Demo/src/demo.cpp)
> Demo Json files can be found here [src](./Demo/src)

## Development note 
To start this project using [Visual studio community 2022](https://visualstudio.microsoft.com/) simply open this file [Topology.sln](Topology.sln)

_But make sure to have the required tools downloaded_


