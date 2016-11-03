// copyright The Perfect Game Company 2016

#pragma once

#include "GameFramework/GameMode.h"
#include "VMutator.h"
#include "VGameMode.generated.h"

/**
 * 
 */
UCLASS()
class VIM_API AVGameMode : public AGameMode
{
	GENERATED_BODY()

protected:

	AVGameMode(const FObjectInitializer& ObjectInitializer);

	virtual void PreInitializeComponents() override;

	virtual void InitGameState();

	virtual void DefaultTimer();
	
	virtual void StartMatch();

	virtual void OnNightEnded();

	virtual void SpawnDefaultInventory(APawn* PlayerPawn);
	
	/**
	* Make sure pawn properties are back to default
	* Also a good place to modify them on spawn
	*/
	virtual void SetPlayerDefaults(APawn* PlayerPawn) override;

	/* Handle for efficient management of DefaultTimer timer */
	FTimerHandle TimerHandle_DefaultTimer;

	/* Can we deal damage to players in the same team */
	UPROPERTY(EditDefaultsOnly, Category = "Rules")
	bool bAllowFriendlyFireDamage;

	/* Allow Enemy spawns to be disabled (for debugging) */
	UPROPERTY(EditDefaultsOnly, Category = "Debug")
	bool bSpawnEnemiesAtNight;

	float BotSpawnInterval;

	/* Called once on every new player that enters the gamemode */
	//QT  changed the InitNewPlayer() to second version as the first version seems to not be called by the UE engine anymore 2016/11/02
	//To fix bug of Player and AI being on same team at start of game and not being able to damage each other
	virtual FString InitNewPlayer(class APlayerController* NewPlayerController, const FUniqueNetIdRepl& UniqueId, const FString& Options, const FString& Portal = TEXT(""));
	/* The teamnumber assigned to Players */
	int32 PlayerTeamNum;

	/* Keep reference to the night state of the previous frame */
	bool LastIsNight;

	/* The start time for the gamemode */
	int32 TimeOfDayStart;

	/* The enemy pawn class */
	UPROPERTY(EditDefaultsOnly, Category = "AI")
	TSubclassOf<class APawn> BotPawnClass;

	/* Handle for nightly bot spawning */
	FTimerHandle TimerHandle_BotSpawns;

	/* Handles bot spawning (during nighttime) */
	void SpawnBotHandler();

	/************************************************************************/
	/* Player Spawning                                                      */
	/************************************************************************/

	/* Don't allow spectating of bots */
	virtual bool CanSpectate_Implementation(APlayerController* Viewer, APlayerState* ViewTarget) override;

	virtual AActor* ChoosePlayerStart_Implementation(AController* Player) override;

	/* Always pick a random location */
	virtual bool ShouldSpawnAtStartSpot(AController* Player) override;

	virtual bool IsSpawnpointAllowed(APlayerStart* SpawnPoint, AController* Controller);

	virtual bool IsSpawnpointPreferred(APlayerStart* SpawnPoint, AController* Controller);

	/** returns default pawn class for given controller */
	virtual UClass* GetDefaultPawnClassForController_Implementation(AController* InController) override;

	/************************************************************************/
	/* Damage & Killing                                                     */
	/************************************************************************/

public: 

	virtual void Killed(AController* Killer, AController* VictimPlayer, APawn* VictimPawn, const UDamageType* DamageType);

	/* Can the player deal damage according to gamemode rules (eg. friendly-fire disabled) */
	virtual bool CanDealDamage(class AVPlayerState* DamageCauser, class AVPlayerState* DamagedPlayer) const;

	virtual float ModifyDamage(float Damage, AActor* DamagedActor, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) const;

	/************************************************************************/
	/* Bots                                                                 */
	/************************************************************************/

protected:

	void SpawnNewBot();

	/* Set all bots back to idle mode */
	void PassifyAllBots();

	/* Set all bots to active patroling state */
	void WakeAllBots();

public:

	/* Primary sun of the level. Assigned in Blueprint during BeginPlay (BlueprintReadWrite is required as tag instead of EditDefaultsOnly) */
	UPROPERTY(BlueprintReadWrite, Category = "DayNight")
	ADirectionalLight* PrimarySunLight;

	/* The default weapons to spawn with */
	UPROPERTY(EditDefaultsOnly, Category = "Player")
	TArray<TSubclassOf<class AVWeapon>> DefaultInventoryClasses;

	/************************************************************************/
	/* Modding & Mutators                                                   */
	/************************************************************************/

protected:

	/* Mutators to create when game starts */
 	UPROPERTY(EditAnywhere, Category = "Mutators")
 	TArray<TSubclassOf<class AVMutator>> MutatorClasses;

	/* First mutator in the execution chain */
	AVMutator* BaseMutator;

	void AddMutator(TSubclassOf<AVMutator> MutClass);

	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;

	/** From UT Source: Used to modify, remove, and replace Actors. Return false to destroy the passed in Actor. Default implementation queries mutators.
	* note that certain critical Actors such as PlayerControllers can't be destroyed, but we'll still call this code path to allow mutators
	* to change properties on them
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintAuthorityOnly)
	bool CheckRelevance(AActor* Other);

	/* Note: Functions flagged with BlueprintNativeEvent like above require _Implementation for a C++ implementation */
	virtual bool CheckRelevance_Implementation(AActor* Other);

	/* Hacked into ReceiveBeginPlay() so we can do mutator replacement of Actors and such */
	void BeginPlayMutatorHack(FFrame& Stack, RESULT_DECL);

};
