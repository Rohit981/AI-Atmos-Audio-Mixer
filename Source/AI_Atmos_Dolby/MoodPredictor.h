// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MoodPredictor.generated.h"

UCLASS()
class AI_ATMOS_DOLBY_API AMoodPredictor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMoodPredictor();

	void StartPythonBridge();
	void SendDataToPython(float Velocity, bool IsJumping, bool IsSprinting, float Health);
	int32 ReadPredictionFromPython();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:	
	FString PythonPath;
	FString ScriptPath;
	FProcHandle PythonProcessHandle;


};
