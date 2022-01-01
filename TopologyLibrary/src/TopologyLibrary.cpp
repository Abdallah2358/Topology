#include "TopologyLibrary.h"


namespace TopologyLibrary
{
    TopologyList tList;

    Device::Device(string id, string type, string name, DeviceValues deviceValues, NetList netlist) {
        this->id = id;
        this->type = type;
        this->name = name;
        this->deviceValues = deviceValues;
        this->netlist = netlist;
    };
   string Device::getId() {
        return this->id;
    }
    DeviceList::DeviceList(){};
    void  DeviceList::addDevice(Device d){
        this->deviceList.insert({d.getId(), d});
    };
    std::map< string, Device>  DeviceList::getList() {
        return this->deviceList;
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
            this->deviceList.addDevice(device);
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

    TopologyList::TopologyList(){}
    void TopologyList::addTopology(Topology t) {
        this->topologyList.insert({ t.getId(),t });
    };
    bool   TopologyList::isTopologyExist(string TopologyID) {
        std::map<string, Topology>::iterator it;
        it = this->topologyList.find(TopologyID);
        return it != this->topologyList.end();
    };
    bool TopologyList::removeTopology(string TopologyID) {
         if (isTopologyExist(TopologyID))
         {
             this->topologyList.erase(TopologyID);
             return true;
         }
         return false;
    };
    void TopologyList::printTopologies() {
        for (auto itr = this->topologyList.begin(); itr != this->topologyList.end(); itr++)
            std::cout << "id :" << itr->first << std::endl << ", json :" << itr->second.getRawJson() << std::endl;
    };
    std::map<string, Topology> TopologyList::getList()
    {
        return this->topologyList;
    };
    Topology TopologyList::getTopology(string TopologyID) {
        return this->topologyList.find(TopologyID)->second;
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
        tList.addTopology(t);
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
        return tList.removeTopology(TopologyID);
    }
    DeviceList queryDevices(string TopologyID) {
   
        if (tList.isTopologyExist(TopologyID))      
            return tList.getTopology(TopologyID).getDeviceList();
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
        if (tList.isTopologyExist(TopologyID))
        {   
            DeviceList temp = tList.getTopology(TopologyID).getDeviceList();
            for (auto itr = temp.getList().begin(); itr != temp.getList().end(); itr++) {
                if (isNetlistNodeConnected(itr->second.getNetList(), NetlistNodeID))
                    dList.addDevice(itr->second);
            }
        }
        return dList;
    }

}