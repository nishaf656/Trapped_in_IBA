#include "EnergyItem.h"
#include "../core/GameError.h"
#include <sstream>

EnergyItem::EnergyItem(const std::string& name, const std::string& description, float energyRestore) : Interactable(name, description, nullptr),
energyRestore(energyRestore)
{
    if (energyRestore <= 0.0f) {
        throw InvalidDataError( "EnergyItem '" + name + "': restore amount must be > 0. Got: " + std::to_string(energyRestore)); }
}

std::string EnergyItem::interact() {
    if (hasBeenUsed) { return "You already had the " + name + ". Nothing left.";
    }
    hasBeenUsed=true;

    std::ostringstream ss;
    ss << "You eat/drink the " << name << ".\n"
       << "Not bad for a midnight snack! Energy +" << (int)energyRestore << ".";
    return ss.str();
    //actual energy restore is applied by GameManager after this returns,
    // because EnergyItem has no reference to the Player object (safer design).
}

float EnergyItem::getRestoreAmount() const 
{
    return energyRestore;
}