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

	FAudioMLData() : PlayerVelocity(0.0f), CurrentMood(0) {}


};

