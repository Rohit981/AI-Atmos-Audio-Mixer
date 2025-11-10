// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionMoodTrigger.h"
#include "AudioManager.h"
#include "Kismet/GameplayStatics.h"
#include "AI_Atmos_DolbyCharacter.h"

// Sets default values
AActionMoodTrigger::AActionMoodTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TriggerVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerVolume"));
	RootComponent = TriggerVolume;
	TriggerVolume->SetCollisionProfileName(TEXT("Overlap"));
	TriggerVolume->SetGenerateOverlapEvents(true);

	TriggerVolume->OnComponentBeginOverlap.AddDynamic(this, &AActionMoodTrigger::OnOverlapBegin);
	TriggerVolume->OnComponentEndOverlap.AddDynamic(this, &AActionMoodTrigger::OnOverlapEnd);

}

// Called when the game starts or when spawned
void AActionMoodTrigger::BeginPlay()
{
	Super::BeginPlay();
	
	DrawDebugBox(GetWorld(), TriggerVolume->GetComponentLocation(), TriggerVolume->GetScaledBoxExtent(), FColor::Red, true);

	
	
}

// Called every frame
void AActionMoodTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AActionMoodTrigger::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor && OtherActor != this)
	{
		AAudioManager* AudioManager = Cast<AAudioManager>(UGameplayStatics::GetActorOfClass(GetWorld(), AAudioManager::StaticClass()));

		if(AudioManager)
		{
			AudioManager->IsActionTrigger = true;
			AudioManager->SetMood(EAudioMood::Action);

		}
	}
}

void AActionMoodTrigger::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if(OtherActor && OtherActor != this)
	{

		AAI_Atmos_DolbyCharacter* Character = Cast<AAI_Atmos_DolbyCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());

		AAudioManager* AudioManager = Cast<AAudioManager>(UGameplayStatics::GetActorOfClass(GetWorld(), AAudioManager::StaticClass()));


		if(AudioManager)
		{
			AudioManager->IsActionTrigger = false;

			if(Character->isSprinting !=true)
			AudioManager->SetMood(EAudioMood::Calm);
			else
			AudioManager->SetMood(EAudioMood::Tense);
		}
	}
}

