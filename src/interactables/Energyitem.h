#pragma once
#include "Interactable.h"

//a consumable food or drink item that restores player energy. can only be used once and subsequent interactions return a "nothing left" message.
//does NOT hold a pointer to player energy.
//instead, GameManager checks wasConsumed() after calling interact() and
//calls player->restoreEnergy(getRestoreAmount()) itself.
//this avoids storing a raw pointer to a potentially-deleted Player object.
class EnergyItem : public Interactable {
private:
    float energyRestore;   //how much energy to give back (must be >0)

public:
    //throws InvalidDataError if energyRestore<=0.
    EnergyItem(const std::string& name,
               const std::string& description,
               float energyRestore);

    std::string interact() override;

    //amount to restore - GameManager reads this and calls player->restoreEnergy()
    float getRestoreAmount() const;

    //true if the item has just been (or was previously) consumed.
    //gameManager uses this to know when to apply the energy restore.
    bool wasConsumed() const { return hasBeenUsed; }
};