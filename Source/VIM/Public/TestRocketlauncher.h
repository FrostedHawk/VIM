// copyright The Perfect Game Company 2016

#pragma once

#include "Items/VWeapon.h"
#include "TestRocketlauncher.generated.h"

/**
 * 
 */
UCLASS()
class VIM_API ATestRocketlauncher : public AVWeapon
{
	GENERATED_BODY()
	
		virtual void FireWeapon() override;

private:
	UPROPERTY(EditDefaultsOnly)
		float ImpulseStrength;
	
	
};
