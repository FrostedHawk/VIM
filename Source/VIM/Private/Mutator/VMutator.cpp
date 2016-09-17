// copyright The Perfect Game Company 2016

#include "VIM.h"
#include "VMutator.h"





bool AVMutator::CheckRelevance_Implementation(AActor* Other)
{
	if (NextMutator)
	{
		return NextMutator->CheckRelevance(Other);
	}

	return true;
}


void AVMutator::InitGame_Implementation(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	if (NextMutator)
	{
		NextMutator->InitGame(MapName, Options, ErrorMessage);
	}
}
