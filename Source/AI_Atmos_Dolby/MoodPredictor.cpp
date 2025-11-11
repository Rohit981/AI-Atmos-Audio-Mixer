// Fill out your copyright notice in the Description page of Project Settings.


#include "MoodPredictor.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "HAL/PlatformFilemanager.h"
#include "GenericPlatform/GenericPlatformProcess.h"
#include "Json.h"

// Sets default values
AMoodPredictor::AMoodPredictor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMoodPredictor::BeginPlay()
{
	Super::BeginPlay();
	
	StartPythonBridge();
}

// Called every frame
void AMoodPredictor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMoodPredictor::StartPythonBridge()
{
	PythonPath = TEXT("C:/Users/Rohit/AppData/Local/Programs/Python/Python313/python.exe");
	ScriptPath = FPaths::ProjectDir() + TEXT("MLBridge/Mood_Infer.py");
	
	FString Command = FString::Printf(TEXT("\"%s\" \"%s\""), *PythonPath, *ScriptPath);
	PythonProcessHandle = FPlatformProcess::CreateProc(*PythonPath, *Command, true, false, false, nullptr, 0, nullptr, nullptr);

	if(PythonProcessHandle.IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("Python Bridge started successfully."));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to start Python process."));
	}
}

void AMoodPredictor::SendDataToPython(float Velocity, bool IsJumping, bool IsSprinting, float Health, float PlayerLocationX, float PlayerLocationY)
{

	// Scaler Constants from Training Data
	const float meanVelocity = 874.238887f;
	const float meanJumping = 0.445312500f;
	const float meanSprinting = 0.520182292f;
	const float meanHealth = 69.1145833f;
	const float meanPlayerLocationX = 2397.80192f;
	const float meanPlayerLocationY = 1764.17562f;

	const float scaleVelocity = 356.771662f;
	const float scaleJumping = 0.497000279f;
	const float scaleSprinting = 0.499592509f;
	const float scaleHealth = 26.1057025f;
	const float scalePlayerLocationX = 1630.00791f;
	const float scalePlayerLocationY = 872.415692f;

	// Convert bools to float for scaling
	float fJumping = IsJumping ? 1.0f : 0.0f;
	float fSprinting = IsSprinting ? 1.0f : 0.0f;

	// Apply scaling
	float scaledVelocity = (Velocity - meanVelocity) / scaleVelocity;
	float scaledJumping = (fJumping - meanJumping) / scaleJumping;
	float scaledSprinting = (fSprinting - meanSprinting) / scaleSprinting;
	float scaledHealth = (Health - meanHealth) / scaleHealth;
	float scaledPlayerLocationX = (PlayerLocationX - meanPlayerLocationX) / scalePlayerLocationX;
	float scaledPlayerLocationY = (PlayerLocationY - meanPlayerLocationY) / scalePlayerLocationY;

	FString JsonData;

	JsonData = FString::Printf(TEXT("{\"PlayerVelocity\": %.6f, \"Jumping\": %.6f, \"Sprinting\": %.6f, \"Health\": %.6f, \"PlayerLocationX\": %.6f, \"PlayerLocationY\": %.6f}"),
							 scaledVelocity,scaledJumping,scaledSprinting,scaledHealth, scaledPlayerLocationX, scaledPlayerLocationY);

	FString InputFilePath = FPaths::ProjectDir() + TEXT("MLBridge/input.json");
	FFileHelper::SaveStringToFile(JsonData, *InputFilePath);

	UE_LOG(LogTemp, Warning, TEXT("Wrote scaled input -> V: %.4f J: %.4f S: %.4f H: %.4f LX: %.4f LY: %.4f"),
								scaledVelocity, scaledJumping, scaledSprinting, scaledHealth, scaledPlayerLocationX, scaledPlayerLocationY);
}

int32 AMoodPredictor::ReadPredictionFromPython()
{
	FString OutputFilePath = FPaths::ProjectDir() + TEXT("MLBridge/output.json");
	FString JsonContent;

	if(!FPlatformFileManager::Get().GetPlatformFile().FileExists(*OutputFilePath))
	{
		UE_LOG(LogTemp, Warning, TEXT("Output file does not exist yet."));
		return -1;
	}

	if(FFileHelper::LoadFileToString(JsonContent, *OutputFilePath))
	{
		TSharedPtr<FJsonObject> JsonObject;
		TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(JsonContent);
		if(FJsonSerializer::Deserialize(Reader, JsonObject) && JsonObject.IsValid())
		{
			int32 MoodPrediction = JsonObject->GetIntegerField("Mood");
			return MoodPrediction;
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to parse JSON from output file."));
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to read output file."));
	}

	return -1;
	
}

