//// Fill out your copyright notice in the Description page of Project Settings.
//
//
//#include "MoodPredictor.h"
//
////THIRD_PARTY_INCLUDES_START
////PRAGMA_PUSH_PLATFORM_DEFAULT_PACKING
////#include <torch/script.h>
////PRAGMA_POP_PLATFORM_DEFAULT_PACKING
////THIRD_PARTY_INCLUDES_END
//
//
////torch::jit::script::Module MoodModel;
//
//// Sets default values
//AMoodPredictor::AMoodPredictor()
//{
// 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
//	PrimaryActorTick.bCanEverTick = true;
//
//}
//
//// Called when the game starts or when spawned
//void AMoodPredictor::BeginPlay()
//{
//	Super::BeginPlay();
//
//	/*try
//	{
//		FString ModelPath = FPaths::ProjectDir() + TEXT("MoodNetModel.pt");
//		std::string ModelPathSTD = TCHAR_TO_UTF8(*ModelPath);
//		MoodModel = torch::jit::load(ModelPathSTD);
//
//		UE_LOG(LogTemp, Warning, TEXT("Mood model loaded successfully from %s"), *ModelPath);
//	}
//	catch (const c10::Error& e)
//	{
//		UE_LOG(LogTemp, Error, TEXT("Error loading the mood model: %s"), *FString(e.what()));
//	}*/
//
//	string ModelPath = TCHAR_TO_UTF8(*(FPaths::ProjectDir() + TEXT("MoodNetModel_TorchScript.pt")));
//	TorchModel = new TorchWrapper(ModelPath);
//
//	UE_LOG(LogTemp, Warning, TEXT("Mood model wrapper initialized successfully from %s"), *(FPaths::ProjectDir() + TEXT("MoodNetModel_TorchScript.pt")));
//	
//}
//
//// Called every frame
//void AMoodPredictor::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//
//}
//
