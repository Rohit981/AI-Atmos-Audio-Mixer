// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractbleAudioObject.h"
#include "Components/SceneComponent.h"


// Sets default values
AInteractbleAudioObject::AInteractbleAudioObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollider"));
	RootComponent = BoxComponent;

	BoxComponent->SetCollisionProfileName(TEXT("Overlap"));
	BoxComponent->SetGenerateOverlapEvents(true);

	SoundTrigger = CreateDefaultSubobject<USoundTriggerComponent>(TEXT("SoundTriggerComp"));



}

// Called when the game starts or when spawned
void AInteractbleAudioObject::BeginPlay()
{
	Super::BeginPlay();

	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AInteractbleAudioObject::OnOverlapBegin);

	DrawDebugSphere(GetWorld(), GetActorLocation(), 200.f, 12, FColor::Green, true);
	
}

// Called every frame
void AInteractbleAudioObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AInteractbleAudioObject::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	SoundTrigger = FindComponentByClass<USoundTriggerComponent>();
	if (OtherActor && OtherActor != this)
	{
		if (SoundTrigger)
		{
			SoundTrigger->PlaySound();

		}
	}
}

