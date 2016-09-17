// copyright The Perfect Game Company 2016

#include "VIM.h"
#include "VIMGameMode.h"
#include "VIMPlayerController.h"
#include "VIMCharacter.h"

AVIMGameMode::AVIMGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = AVIMPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/VIM/Blueprints/PlayerCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}