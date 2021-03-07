#ifndef CARTRIDGE_INTERFACE_H
#define CARTRIDGE_INTERFACE_H

#include <string>


/// make a Cartridge interface to decouple client that uses a concrete type of a cartridge.
class CartridgeInterface
{
};

/// concreate type Cartridge of CartridgeInterface, if constructor changes, change the below faatory without affecting the client.
class Cartridge : public CartridgeInterface
{
public:
    Cartridge(std::string model_no){}
};

/// make a factory for client to specify which concrete type of cartridge wanted to prepare.
CartridgeInterface* make_cartridge(std::string model)
{
    if (model == "X543-44")
    {
        return new Cartridge(model);
    }

    return nullptr;
}

#endif // CARTRIDGE_INTERFACE_H
