// copyright The Perfect Game Company 2016

#pragma once

#include "VPickupActor.h"
#include "VConsumableActor.generated.h"

/**
 * Base class for consumable (food) items. Consumable by players to restore energy
 */
UCLASS(ABSTRACT)
class VIM_API AVConsumableActor : public AVPickupActor
{
	GENERATED_BODY()

	AVConsumableActor(const FObjectInitializer& ObjectInitializer);

protected:

	/* Consume item, restoring energy to player */
	virtual void OnUsed(APawn* InstigatorPawn) override;

	/* Amount of hitpoints restored and hunger reduced when consumed. */
	UPROPERTY(EditDefaultsOnly, Category = "Consumable")
	float Nutrition;
};
