// Fill out your copyright notice in the Description page of Project Settings.


#include "AudioManager.h"
#include "Components/AudioComponent.h"

// Sets default values
AAudioManager::AAudioManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));
	RootComponent = RootScene;

	MusicComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("MusicComponent"));
	MusicComponent->SetupAttachment(RootComponent);
	MusicComponent->bAutoActivate = false;

	AmbientComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AmbientComponent"));
	AmbientComponent->SetupAttachment(RootComponent);
	AmbientComponent->bAutoActivate = false;

	CurrentMood = EAudioMood::Calm;

	MusicTrack = LoadObject<USoundBase>(nullptr, TEXT("/Script/Engine.SoundWave'/Game/Audio/Music/Desert_Storm_Music.Desert_Storm_Music'"));
	AmbientTrack = LoadObject<USoundBase>(nullptr, TEXT("/Script/Engine.SoundCue'/Game/Audio/Ambient/Birds_Ambient_Sound-2_Cue.Birds_Ambient_Sound-2_Cue'"));

}



// Called when the game starts or when spawned
void AAudioManager::BeginPlay()
{
	Super::BeginPlay();

	if (MusicTrack && MusicComponent)
	{
		MusicComponent->SetSound(MusicTrack);
		MusicComponent->Play();
	}

	if (AmbientTrack && AmbientComponent)
	{
		AmbientComponent->SetSound(AmbientTrack);
		AmbientComponent->Play();
	}
	
}

// Called every frame
void AAudioManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	ApplyMoodSetting();

}

void AAudioManager::ApplyMoodSetting()
{
	/*if (!MusicComponent || !AmbientComponent) return;

	if (!MusicComponent->IsPlaying())
		MusicComponent->Play();

	if (!AmbientComponent->IsPlaying())
		AmbientComponent->Play();*/

	switch (CurrentMood)
	{
	case EAudioMood::Calm:
		MusicComponent->SetVolumeMultiplier(0.6f);
		AmbientComponent->SetVolumeMultiplier(1.0f);
		break;
	case EAudioMood::Tense:
		MusicComponent->SetVolumeMultiplier(0.8f);
		AmbientComponent->SetVolumeMultiplier(0.7f);
		break;
	case EAudioMood::Action:
		MusicComponent->SetVolumeMultiplier(1.0f);
		AmbientComponent->SetVolumeMultiplier(0.4f);
		break;
	default:
		break;
	}
}

void AAudioManager::SetMood(EAudioMood NewMood)
{
	
	if (CurrentMood != NewMood)
	{
		CurrentMood = NewMood;
		//ApplyMoodSetting();
	}

	
}

