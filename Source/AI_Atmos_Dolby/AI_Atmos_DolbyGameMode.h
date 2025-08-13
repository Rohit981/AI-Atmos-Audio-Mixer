// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "AI_Atmos_DolbyGameMode.generated.h"

UCLASS(minimalapi)
class AAI_Atmos_DolbyGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AAI_Atmos_DolbyGameMode();

protected:
	virtual void BeginPlay();
};



