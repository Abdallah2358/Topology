#include "TopologyLibrary.h"
using namespace std;
using namespace TopologyLibrary;
int main() {
	readJSON("./src/demo2.json");
	readJSON("./src/demo.json");
	queryTopologies().printTopologies();
	deleteTopology("top1");
	cout << "\nafter deleting top1 topology\n";
	queryTopologies().printTopologies();
	DeviceList dList = queryDevices("top2");

	return 0;
}