// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AudioMLData.h"
#include "Misc/FileHelper.h"
#include "HAL/PlatformFilemanager.h"
#include "MoodPredictor.h"
#include "GameFramework/Actor.h"
#include "AudioManager.generated.h"

UENUM(BlueprintType)
enum class EAudioMood : uint8
{
	Action UMETA(DisplayName = "Action"),
	Calm UMETA(DisplayName = "Calm"),
	Tense UMETA(DisplayName = "Tense")
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio|State")
	EAudioMood PredictedMood;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio|Tracks")
	USoundBase* MusicTrack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio|Tracks")
	USoundBase* AmbientTrack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio|Tracks")
	TArray<USoundBase*> ObjectSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio|Tracks")
	USoundBase* FootStepTrack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio|Tracks")
	USoundBase* LandingSound;

	UPROPERTY(EditAnywhere)
	UAudioComponent* FootStepComponent;

	UPROPERTY(EditAnywhere)
	UAudioComponent* ObjectComponent;

	bool IsActionTrigger = false;

	void SetMood(EAudioMood NewMood);

private:

	UPROPERTY(EditAnywhere)
	UAudioComponent* MusicComponent;

	UPROPERTY(EditAnywhere)
	UAudioComponent* AmbientComponent;

	UPROPERTY(EditAnywhere, Category = "ML")
	AMoodPredictor* MoodPredictorInstance;

	USoundBase* LoadObjectSound;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* RootScene;

	//Volume Setting
	void ApplyMoodSetting();

	void LogMLData(float PlayerVelocity, bool isJumping, bool isSprinting, float Health, float PlayerLocationX, float PlayerLocationY);

	void OutputMLData(float DeltaTime);

	void SetupAudioComponents();

	void FootStepComponentVolumeSetup();

	void SetPlayerMovementValues();

	void SendDataAndReadPrediction(float DeltaTime);

	FString FilePath;

	float Speed;
	bool jump;
	bool sprint;
	float PlayerHealth;
	float PlayerLocationX;
	float PlayerLocationY;
	

};
