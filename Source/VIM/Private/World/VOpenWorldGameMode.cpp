// copyright The Perfect Game Company 2016

#include "VIM.h"
#include "VOpenWorldGameMode.h"





AVOpenWorldGameMode::AVOpenWorldGameMode(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	/* Open world content is free-for-all */
	bAllowFriendlyFireDamage = true;
}


bool AVOpenWorldGameMode::CanSpectate_Implementation(APlayerController* Viewer, APlayerState* ViewTarget)
{
	return false;
}
