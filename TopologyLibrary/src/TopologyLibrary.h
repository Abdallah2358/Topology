#pragma once
#include <list>
#include <map>
#include <iterator>
#include <iostream>
#include <fstream> 
#include <json/json.h>
typedef std::string  string;
typedef Json::Value json_ob;
typedef std::map<string, string> NetList;
typedef std::map<string, double>DeviceValues;


namespace TopologyLibrary
{
    class Device {
    public:
        Device(string id, string type, string name, DeviceValues deviceValues, NetList netlist);
        string getId();
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

    class DeviceList {
    public:
        DeviceList();
        void addDevice(Device d);
        Device getDevice(string DeviceID);
        std::map< string , Device> getList();
    private:
        std::map< string, Device> deviceList;
    };


    class Topology {
    public:

        Topology();
        Topology(json_ob obj);
        string getId();
        void setId(string id);
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

   
   // 
    class TopologyList
    {
    public:
        TopologyList();
        void addTopology(Topology t);
        bool isTopologyExist(string TopologyID);
        bool removeTopology(string TopologyID);
        void printTopologies();
        std::map<string, Topology> getList();
        Topology getTopology(string TopologyID);
    private:
        std::map<string, Topology> topologyList;
    };


 
    Topology readJSON(string FileName);
    bool writeJSON(string FileName, Topology topology);
    TopologyList queryTopologies();
    bool deleteTopology(string TopologyID);
    DeviceList queryDevices(string TopologyID);
    bool isNetlistNodeConnected(NetList netList, string node);
    DeviceList queryDevicesWithNetlistNode(string TopologyID, string NetlistNodeID);
}
