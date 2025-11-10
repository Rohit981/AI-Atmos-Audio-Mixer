// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AudioMLData.generated.h"


USTRUCT(BlueprintType)
struct FAudioMLData
{
	GENERATED_BODY()

	UPROPERTY()
	float PlayerVelocity;

	UPROPERTY()
	int32 CurrentMood;

	bool isJumping;
	bool isSprinting;

	float Health;

	float PlayerLocationX;
	float PlayerLocationY;

	//float DistanceFromAudioSource;

	FAudioMLData() : PlayerVelocity(0.0f), CurrentMood(0), isJumping(0), isSprinting(0), Health(0), PlayerLocationX(0.0f), PlayerLocationY(0.0f){}


};

