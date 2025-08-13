// Fill out your copyright notice in the Description page of Project Settings.


#include "SoundTriggerComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
USoundTriggerComponent::USoundTriggerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void USoundTriggerComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void USoundTriggerComponent::PlaySound()
{
	if (bAttachToOwner)
	{
		if (SoundToPlay)
		{
			UGameplayStatics::SpawnSoundAttached(SoundToPlay, GetOwner()->GetRootComponent());

		}
		else
		{
			UGameplayStatics::PlaySoundAtLocation(this, SoundToPlay, GetOwner()->GetActorLocation());
		}
	}

}




