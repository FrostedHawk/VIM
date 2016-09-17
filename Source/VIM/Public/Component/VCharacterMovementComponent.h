// copyright The Perfect Game Company 2016

#pragma once

#include "GameFramework/CharacterMovementComponent.h"
#include "VCharacterMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class VIM_API UVCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()

	virtual float GetMaxSpeed() const override;

};