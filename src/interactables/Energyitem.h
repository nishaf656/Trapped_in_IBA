#pragma once
#include "Interactable.h"

// A consumable food or drink item that restores player energy.
// Can only be used once; subsequent interactions return a "nothing left" message.
//
// NOTE: EnergyItem does NOT hold a pointer to player energy.
// Instead, GameManager checks wasConsumed() after calling interact() and
// calls player->restoreEnergy(getRestoreAmount()) itself.
// This avoids storing a raw pointer to a potentially-deleted Player object.
class EnergyItem : public Interactable {
private:
    float energyRestore;   // How much energy to give back (must be > 0)

public:
    // Throws InvalidDataError if energyRestore <= 0.
    EnergyItem(const std::string& name,
               const std::string& description,
               float energyRestore);

    std::string interact() override;

    // Amount to restore - GameManager reads this and calls player->restoreEnergy()
    float getRestoreAmount() const;

    // True if the item has just been (or was previously) consumed.
    // GameManager uses this to know when to apply the energy restore.
    bool wasConsumed() const { return hasBeenUsed; }
};