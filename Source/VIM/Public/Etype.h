// Copyright The Perfect Game  2016 

#pragma once

/*
 Storage for all Enums used in Game
 */
 //"BlueprintType" is essential to include if we want to access this from a blueprint
UENUM(BlueprintType)		
enum class EDifficultyLevel : uint8
{
	ED_Easy 	UMETA(DisplayName = "Easy"),
	ED_Medium 	UMETA(DisplayName = "Medium"),
	ED_Normal	UMETA(DisplayName = "Normal"),
	ED_Hard 	UMETA(DisplayName = "Hard"),
	ED_Insane	UMETA(DisplayName = "Insane")
};




class VIM_API Etype
{
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Enum)
	EDifficultyLevel DifficultyLevel;



	Etype();
	~Etype();

	

};
