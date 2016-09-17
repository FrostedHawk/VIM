// copyright The Perfect Game Company 2016

#pragma once

#include "VUsableActor.h"
#include "VPickupActor.generated.h"

/**
 * 
 */
UCLASS(ABSTRACT)
class VIM_API AVPickupActor : public AVUsableActor
{
	GENERATED_BODY()

	void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	USoundCue* PickupSound;

	UFUNCTION()
	void OnRep_IsActive();

protected:

	AVPickupActor(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(Transient, ReplicatedUsing = OnRep_IsActive)
	bool bIsActive;

	virtual void RespawnPickup();

	virtual void OnPickedUp();

	virtual void OnRespawned();

public:

	virtual void OnUsed(APawn* InstigatorPawn) override;

	/* Immediately spawn on begin play */
	UPROPERTY(EditDefaultsOnly, Category = "Pickup")
	bool bStartActive;

	/* Will this item ever respawn */
	UPROPERTY(EditDefaultsOnly, Category = "Pickup")
	bool bAllowRespawn;

	UPROPERTY(EditDefaultsOnly, Category = "Pickup")
	float RespawnDelay;

	/* Extra delay randomly applied on the respawn timer */
	UPROPERTY(EditDefaultsOnly, Category = "Pickup")
	float RespawnDelayRange;
};
