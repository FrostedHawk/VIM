// copyright The Perfect Game Company 2016
#pragma once

#include "GameFramework/SaveGame.h"
#include "VSaveGame.generated.h"

/**
 * Basic Save Game Class Functionality needs to be wired in
 */
UCLASS()
class VIM_API UVSaveGame : public USaveGame
{
	GENERATED_BODY()
	
	
public:

	UPROPERTY(VisibleAnywhere, Category = Basic)
		FString PlayerName;

	UPROPERTY(VisibleAnywhere, Category = Basic)
		FString SaveSlotName;

	UPROPERTY(VisibleAnywhere, Category = Basic)
		uint32 UserIndex;
	/*to add functionality use the following
	UPROPERTY(VisibleAnywhere, Category = Basic)
	Variable type, Variable name eg.
    FString PlayerName;*/

	UVSaveGame();
	
};
