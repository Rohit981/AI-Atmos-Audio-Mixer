// Fill out your copyright notice in the Description page of Project Settings.


#include "AudioManager.h"
#include "Components/AudioComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AI_Atmos_DolbyCharacter.h"


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

	ObjectComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("ObjectComponent"));
	ObjectComponent->SetupAttachment(RootComponent);
	ObjectComponent->bAutoActivate = false;

	FootStepComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("FootStepComponent"));
	FootStepComponent->SetupAttachment(RootComponent);
	FootStepComponent->bAutoActivate = false;

	CurrentMood = EAudioMood::Calm;

	MusicTrack = LoadObject<USoundBase>(nullptr, TEXT("/Script/Engine.SoundWave'/Game/Audio/Music/Desert_Storm_Music.Desert_Storm_Music'"));
	AmbientTrack = LoadObject<USoundBase>(nullptr, TEXT("/Script/Engine.SoundCue'/Game/Audio/Ambient/Birds_Ambient_Sound-2_Cue.Birds_Ambient_Sound-2_Cue'"));
	LoadObjectSound = LoadObject<USoundBase>(nullptr, TEXT("/Script/Engine.SoundWave'/Game/Audio/Object_Sound/Metal_Clang_Object_Sound.Metal_Clang_Object_Sound'"));
	FootStepTrack = LoadObject<USoundBase>(nullptr, TEXT("/Script/Engine.SoundCue'/Game/Audio/FootStepSound/FootStep_Sound.FootStep_Sound'"));
}



// Called when the game starts or when spawned
void AAudioManager::BeginPlay()
{
	Super::BeginPlay();

	SetupAudioComponents();

	FilePath = FPaths::ProjectDir() + "MLData.csv";
	FString Header = "PlayerVelocity,CurrentMood, Jumping, Sprinting\n";

	FFileHelper::SaveStringToFile(Header, *FilePath);
}

// Called every frame
void AAudioManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	ApplyMoodSetting();

	OutputMLData(DeltaTime);

}

void AAudioManager::ApplyMoodSetting()
{
	switch (CurrentMood)
	{
	case EAudioMood::Calm:
		MusicComponent->SetVolumeMultiplier(0.6f);
		AmbientComponent->SetVolumeMultiplier(1.0f);
		ObjectComponent->SetVolumeMultiplier(0.5f);
		FootStepComponent->SetVolumeMultiplier(0.5f);
		break;

	case EAudioMood::Tense:
		MusicComponent->SetVolumeMultiplier(0.8f);
		AmbientComponent->SetVolumeMultiplier(0.7f);
		ObjectComponent->SetVolumeMultiplier(1.5f);
		FootStepComponent->SetVolumeMultiplier(10.0f);

		break;

	case EAudioMood::Action:
		MusicComponent->SetVolumeMultiplier(1.0f);
		AmbientComponent->SetVolumeMultiplier(0.4f);
		ObjectComponent->SetVolumeMultiplier(1.0f);
		FootStepComponent->SetVolumeMultiplier(2.0f);

		break;
	default:
		break;
	}
}

void AAudioManager::LogMLData(float PlayerVelocity, bool isJumping, bool isSprinting)
{
	//if(!FPlatformFileManager::Get().GetPlatformFile().FileExists(*FilePath))
	//{
	//	
	//	//FFileHelper::SaveStringToFile(TEXT(""), *FilePath);

	//}

	FString Line = FString::Printf(TEXT("%.2f,%s, %i, %i\n"), PlayerVelocity,
								  *UEnum::GetValueAsString(CurrentMood), 
								  isJumping ? 1 : 0,
								  isSprinting ? 1 : 0);

	FFileHelper::SaveStringToFile(Line, *FilePath, FFileHelper::EEncodingOptions::AutoDetect, &IFileManager::Get(), FILEWRITE_Append);
}

void AAudioManager::OutputMLData(float DeltaTime)
{
	static float TimeSinceLastLog = 0.0f;
	TimeSinceLastLog += DeltaTime;

	if (TimeSinceLastLog >= 2.0f)
	{
		APawn* PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
		AAI_Atmos_DolbyCharacter* Character = Cast<AAI_Atmos_DolbyCharacter>(PlayerPawn);

		if (PlayerPawn)
		{
			float Speed = PlayerPawn->GetVelocity().Size();
			bool jump = PlayerPawn->GetMovementComponent()->IsFalling();
			bool sprint = Character->isSprinting;
			LogMLData(Speed, jump, sprint);
		}
		TimeSinceLastLog = 0.0f;
	}
}

void AAudioManager::SetupAudioComponents()
{
	ObjectSound.Add(LoadObjectSound);

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

	for (int i = 0; i < ObjectSound.Num(); i++)
	{
		if (ObjectComponent && ObjectSound[i])
		{
			ObjectComponent->SetSound(ObjectSound[i]);
		}

	}

	if (FootStepTrack && FootStepComponent)
	{
		FootStepComponent->SetSound(FootStepTrack);
	}
}

void AAudioManager::SetMood(EAudioMood NewMood)
{
	
	if (CurrentMood != NewMood)
	{
		CurrentMood = NewMood;
		
	}

	
}

