// Fill out your copyright notice in the Description page of Project Settings.


#include "AmbientActor.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundBase.h"

// Sets default values
AAmbientActor::AAmbientActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
	RootComponent = AudioComponent;
	AudioComponent->bAutoActivate = true;


}

// Called when the game starts or when spawned
void AAmbientActor::BeginPlay()
{
	Super::BeginPlay();

	
	
}

// Called every frame
void AAmbientActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

