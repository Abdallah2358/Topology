#include "TopologyLibrary.h"


namespace TopologyLibrary
{
    Device::Device(string id, string type, string name, DeviceValues deviceValues, NetList netlist) {
        this->id = id;
        this->type = type;
        this->name = name;
        this->deviceValues = deviceValues;
        this->netlist = netlist;
    };
    NetList Device::getNetList() {
        return this->netlist;
    };



    Topology::Topology() {

    };
    Topology::Topology(json_ob obj) {
        this->rawJson = obj;
        this->id = obj["id"].asString();
        for (auto itr : obj["components"])
        {
            string deviceName;
            if (itr.isMember("resistance"))
                deviceName = "resistance";
            else if (itr.isMember("m(l)"))
                deviceName = "m(l)";
            DeviceValues deviceValues;
            for (string key : obj[deviceName].getMemberNames())
                deviceValues.insert({ key , obj[deviceName][key].asDouble() });

            NetList netlist;
            for (string key : obj["netlist"].getMemberNames())
                netlist.insert({ key , obj["netlist"][key].asString() });

            Device device(itr["id"].asString(), itr["type"].asString(), deviceName, deviceValues, netlist);
            this->deviceList.push_back(device);
        }
    };
    void Topology::printTopology() {
        std::cout << rawJson;
    };
    json_ob Topology::getRawJson() {
        return this->rawJson;
    };
    string Topology::getId() {
        return this->id;
    }
    DeviceList Topology::getDeviceList() {
        return this->deviceList;
    };



    Topology readJSON(string FileName) {
        json_ob root;
        std::ifstream  file(FileName);
        if (!file.good())
        {
            std::cout << FileName << " is either empty or doesn`t exist" << std::endl;
            return  Topology();
        }
        file >> root;
        Topology t(root);
        tList.insert({ t.getId(), t });
        return t;
    }
    bool writeJSON(string FileName, Topology topology) {
        std::ifstream file(FileName);
        if (file.good()) {
            file.close();
            char ans = 'a';
            std::cout << "this file already exist do you wish to overwrite it ? y/n" << std::endl;
            while (ans != 'y' || ans != 'n')
            {
                std::cin >> ans;
                if (ans == 'n') {

                    return false;
                }
                else  if (ans == 'y') {}
                else { std::cout << "invalid input" << std::endl; }
            }
        }

        std::ofstream ofile(FileName);
        ofile << topology.getRawJson();
        ofile.close();
        return true;
    }
    TopologyList queryTopologies() {
        return tList;
    }
    bool deleteTopology(string TopologyID) {
        TopologyList::iterator it;
        it = tList.find(TopologyID);
        if (it != tList.end())
        {
            tList.erase(it);
            return true;
        }

        return false;
    }
    DeviceList queryDevices(string TopologyID) {
        TopologyList::iterator it;
        it = tList.find(TopologyID);
        if (it != tList.end())
        {
            return it->second.getDeviceList();
        }
        return DeviceList();
    }
    bool isNetlistNodeConnected(NetList netList, string node) {
        NetList::iterator itr;
        for (itr = netList.begin(); itr != netList.end(); ++itr) {
            if (itr->second == node)
            {
                return true;
            }
        }
        return false;
    }
    DeviceList queryDevicesWithNetlistNode(string TopologyID, string NetlistNodeID) {
        DeviceList dList;
        TopologyList::iterator it;
        it = tList.find(TopologyID);
        if (it != tList.end())
        {
            for (Device device : it->second.getDeviceList()) {
                if (isNetlistNodeConnected(device.getNetList(), NetlistNodeID))
                    dList.push_back(device);
            }
        }
        return dList;
    }

}