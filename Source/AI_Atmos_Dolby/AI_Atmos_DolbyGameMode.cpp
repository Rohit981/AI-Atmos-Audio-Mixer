// Copyright Epic Games, Inc. All Rights Reserved.

#include "AI_Atmos_DolbyGameMode.h"
#include "AI_Atmos_DolbyCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundBase.h"

AAI_Atmos_DolbyGameMode::AAI_Atmos_DolbyGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}

void AAI_Atmos_DolbyGameMode::BeginPlay()
{
	Super::BeginPlay();

	USoundBase* BackgroundMusic = LoadObject<USoundBase>(nullptr, TEXT("/Script/Engine.SoundWave'/Game/Audio/Music/Desert_Storm_Music.Desert_Storm_Music'"));

	if (BackgroundMusic)
	{
		UGameplayStatics::PlaySound2D(GetWorld(), BackgroundMusic);
	}
}
