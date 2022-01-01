#pragma once
#include <list>
#include <map>
#include <iterator>
#include <iostream>
#include <fstream> 
#include <json/json.h>

typedef std::string string;
typedef Json::Value json_ob;
typedef std::map<string, string> NetList;
typedef std::map<string, double>DeviceValues;

namespace TopologyLibrary
{
    class Device {
    public:
        Device(string id, string type, string name, DeviceValues deviceValues, NetList netlist);

        bool operator == (const Device& d) const { return this->id == d.id; }
        bool operator != (const Device& d) const { return !operator==(d); }
        NetList getNetList();
    private:
        string id;
        string type;
        string name;
        NetList netlist;
        DeviceValues deviceValues;
    };
    typedef std::list<Device> DeviceList;

    class Topology {
    public:

        Topology();
        Topology(json_ob obj);
        string getId();
        //void setId(string id);
        void printTopology();
        json_ob getRawJson();
        DeviceList getDeviceList();

        bool operator == (const Topology& t) const { return this->id == t.id; }
        bool operator != (const Topology& t) const { return !operator==(t); }
    private:
        json_ob rawJson;
        string id;
        DeviceList deviceList;
    };
    typedef std::map<string, Topology> TopologyList;

    TopologyList tList;
    Topology readJSON(string FileName);
    bool writeJSON(string FileName, Topology topology);
    bool deleteTopology(string TopologyID);
    DeviceList queryDevices(string TopologyID);
    bool isNetlistNodeConnected(NetList netList, string node);
    DeviceList queryDevicesWithNetlistNode(string TopologyID, string NetlistNodeID);
}
