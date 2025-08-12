// Copyright Epic Games, Inc. All Rights Reserved.

#include "AI_Atmos_DolbyGameMode.h"
#include "AI_Atmos_DolbyCharacter.h"
#include "UObject/ConstructorHelpers.h"

AAI_Atmos_DolbyGameMode::AAI_Atmos_DolbyGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
