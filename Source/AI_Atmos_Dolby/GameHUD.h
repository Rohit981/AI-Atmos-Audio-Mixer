// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Blueprint/UserWidget.h"
#include "GameHUD.generated.h"

/**
 * 
 */
UCLASS()
class AI_ATMOS_DOLBY_API AGameHUD : public AHUD
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD")
	TSubclassOf<class UUserWidget> PlayerHUDClass;

	virtual void BeginPlay() override;

private:
	UPROPERTY()
	UUserWidget* PlayerHealth_Ref;


	
};
