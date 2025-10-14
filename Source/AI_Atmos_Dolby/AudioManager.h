// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AudioManager.generated.h"

UENUM(BlueprintType)
enum class EAudioMood : uint8
{
	Calm UMETA(DisplayName = "Calm"),
	Tense UMETA(DisplayName = "Tense"),
	Action UMETA(DisplayName = "Action")
};

UCLASS()
class AI_ATMOS_DOLBY_API AAudioManager : public AActor
{
	GENERATED_BODY()
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Sets default values for this actor's properties
	AAudioManager();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio|State")
	EAudioMood CurrentMood;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio|Tracks")
	USoundBase* MusicTrack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio|Tracks")
	USoundBase* AmbientTrack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio|Tracks")
	TArray<USoundBase*> ObjectSound;

	void SetMood(EAudioMood NewMood);

private:

	UPROPERTY(EditAnywhere)
	UAudioComponent* MusicComponent;

	UPROPERTY(EditAnywhere)
	UAudioComponent* AmbientComponent;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* RootScene;

	//Volume Setting
	void ApplyMoodSetting();

};
