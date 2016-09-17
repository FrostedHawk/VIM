//copyright The Perfect Game Company 2016

#include "VIM.h"
#include "VCharacterMovementComponent.h"
#include "VBaseCharacter.h"



float UVCharacterMovementComponent::GetMaxSpeed() const
{
	float MaxSpeed = Super::GetMaxSpeed();

	const AVBaseCharacter* CharOwner = Cast<AVBaseCharacter>(PawnOwner);
	
	return MaxSpeed;
}