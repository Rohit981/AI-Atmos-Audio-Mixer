// Copyright Epic Games, Inc. All Rights Reserved.

#include "AI_Atmos_DolbyCharacter.h"
#include "AI_Atmos_DolbyProjectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/AudioComponent.h"


//////////////////////////////////////////////////////////////////////////
// AAI_Atmos_DolbyCharacter

AAI_Atmos_DolbyCharacter::AAI_Atmos_DolbyCharacter()
{
	// Character doesnt have a rifle at start
	bHasRifle = false;
	
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
		
	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	//Mesh1P->SetRelativeRotation(FRotator(0.9f, -19.19f, 5.2f));
	Mesh1P->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));

	

}

void AAI_Atmos_DolbyCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	AudioManager = Cast<AAudioManager>(UGameplayStatics::GetActorOfClass(GetWorld(), AAudioManager::StaticClass()));

	CurrentHealth = MaxHealth;

}

void AAI_Atmos_DolbyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CheckMovementState();

	if(CurrentHealth <= 40.0f)
	{
		if(AudioManager != NULL)
		AudioManager->SetMood(EAudioMood::Action);
	}
}

//////////////////////////////////////////////////////////////////////////// Input

void AAI_Atmos_DolbyCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		//Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAI_Atmos_DolbyCharacter::Move);

		//Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AAI_Atmos_DolbyCharacter::Look);

		
		//Sprinting
		EnhancedInputComponent->BindAction(Sprint, ETriggerEvent::Started, this, &AAI_Atmos_DolbyCharacter::StartSprinting);
		EnhancedInputComponent->BindAction(Sprint, ETriggerEvent::Completed, this, &AAI_Atmos_DolbyCharacter::StopSprinting);
	}
}



void AAI_Atmos_DolbyCharacter::StartSprinting()
{
	isSprinting = true;
	GetCharacterMovement()->MaxWalkSpeed = 1200.0f;

	if (AudioManager != NULL && AudioManager->IsActionTrigger != true)
	AudioManager->SetMood(EAudioMood::Tense);
}

void AAI_Atmos_DolbyCharacter::StopSprinting()
{
	isSprinting = false;
	GetCharacterMovement()->MaxWalkSpeed = 600.0f;

	if (AudioManager != NULL && AudioManager->IsActionTrigger != true)
	AudioManager->SetMood(EAudioMood::Calm);
}



void AAI_Atmos_DolbyCharacter::PlayFootstepSound()
{
	AudioManager->FootStepComponent->SetSound(AudioManager->FootStepTrack);

	USoundBase* FootstepSound = isSprinting ? AudioManager->FootStepComponent->Sound : AudioManager->FootStepComponent->Sound;

	if (FootstepSound)
	{
		AudioManager->FootStepComponent->Play();
	}
}

void AAI_Atmos_DolbyCharacter::CheckMovementState()
{
	FVector velocity = GetVelocity();
	float speed = velocity.Size();

	bool isMoving = speed > 10.0f && GetMovementComponent()->IsMovingOnGround();

	if (isMoving && !GetWorldTimerManager().IsTimerActive(FootstepTimerHandle))
	{
		/*if (AudioManager != NULL)
		{
			AudioManager->PlayFootstepSound();
		}*/

		AudioManager->FootStepComponent->SetPitchMultiplier(FMath::FRandRange(0.95f, 1.05f));

		float footstepInterval = isSprinting ? 0.25f : 0.45f;
		GetWorldTimerManager().SetTimer(FootstepTimerHandle, this, &AAI_Atmos_DolbyCharacter::PlayFootstepSound, footstepInterval, false);
	}
	else if (!isMoving)
	{
		GetWorldTimerManager().ClearTimer(FootstepTimerHandle);
	}
}

void AAI_Atmos_DolbyCharacter::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);
	if (AudioManager->FootStepComponent->Sound)
	{
		AudioManager->FootStepComponent->SetSound(AudioManager->LandingSound);
		AudioManager->FootStepComponent->Play();

	}
}


void AAI_Atmos_DolbyCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add movement 
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void AAI_Atmos_DolbyCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AAI_Atmos_DolbyCharacter::SetHasRifle(bool bNewHasRifle)
{
	bHasRifle = bNewHasRifle;
}

bool AAI_Atmos_DolbyCharacter::GetHasRifle()
{
	return bHasRifle;
}

void AAI_Atmos_DolbyCharacter::ReduceHealth()
{
	// Implement health reduction logic here
	CurrentHealth -= 20.0f;

	MaxHealth = CurrentHealth;
	
}
