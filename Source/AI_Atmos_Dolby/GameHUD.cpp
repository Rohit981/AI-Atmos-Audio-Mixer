// Fill out your copyright notice in the Description page of Project Settings.


#include "GameHUD.h"


void AGameHUD::BeginPlay()
{
	Super::BeginPlay();

	if (PlayerHUDClass)
	{
		PlayerHealth_Ref = CreateWidget<UUserWidget>(GetWorld(), PlayerHUDClass);

		if (PlayerHealth_Ref)
		{
			PlayerHealth_Ref->AddToViewport();

			
		}
	}
}
