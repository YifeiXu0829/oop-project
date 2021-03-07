#include "Printer.h"
#include "CartridgeInterface.h"


/// client (Printer) used to tightly coupled with concrete type of Cartridge.
/// now client only interact with the cartridge-interface, any change to concreate type of a cartridge-interface implementation won't affact client complilation any more.
void Printer::prepare()
{
	cout << "Printer is preparing to print\n";
    string name = "X543-44";
    CartridgeInterface* c = make_cartridge(name);

    if(c) delete c;
}
void Printer::print()
{
	cout << "Printer is printing\n";
}


