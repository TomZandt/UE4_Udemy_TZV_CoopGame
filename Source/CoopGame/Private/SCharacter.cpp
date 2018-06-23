// Fill out your copyright notice in the Description page of Project Settings.

#include "SCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/PawnMovementComponent.h"

// ********************************************************************************************************
// Sets default values
ASCharacter::ASCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Assign the pointer to a new "SpringArmComponent" instance
	pSpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));

	// Use the pawns rotation to rotate the spring arm
	pSpringArmComponent->bUsePawnControlRotation = true;

	// Make the "SpringArmComponent" a child of the characters root component
	pSpringArmComponent->SetupAttachment(RootComponent);

	// Add default "SpringArmComponent" offset
	SpringArmComponentOffset = { 0.0f, 0.0f, 50.0f };

	// Offset the "SpringArmComponent" to be head height
	pSpringArmComponent->AddLocalOffset(SpringArmComponentOffset);

	// Assign the pointer to a new "UCameraComponent" instance
	pCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));

	// Make the "CameraComponent" a child of the "SpringArmComponent"
	pCameraComponent->SetupAttachment(pSpringArmComponent);

	// Tell UE4 that the character is allowed to crouch
	GetMovementComponent()->GetNavAgentPropertiesRef().bCanCrouch = true;
}

// ********************************************************************************************************
// Called when the game starts or when spawned
void ASCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// ********************************************************************************************************
// Call to move the player in the forward axis by the incoming value
void ASCharacter::MoveForward(float Value)
{
	// Get the forward vector of the character and move by the "value" amount
	AddMovementInput(GetActorForwardVector() * Value);
}

// ********************************************************************************************************
// Call to move the player in the right axis by the incoming value
void ASCharacter::MoveRight(float Value)
{
	// Get the right vector of the character and move by the "value" amount
	AddMovementInput(GetActorRightVector() * Value);
}

// ********************************************************************************************************
// Call to begin crouch
void ASCharacter::BeginCrouch()
{
	// Call inherited crouch function
	Crouch();
}

// ********************************************************************************************************
// Call to end crouch
void ASCharacter::EndCrouch()
{
	// Call inherited un crouch function
	UnCrouch();
}

// ********************************************************************************************************
// Called every frame
void ASCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// ********************************************************************************************************
// Called to bind functionality to input
void ASCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Bind the "MoveForward" axis to this and call MoveForward function
	PlayerInputComponent->BindAxis("MoveForward", this, &ASCharacter::MoveForward);

	// Bind the "MoveRight" axis to this and call MoveRight function
	PlayerInputComponent->BindAxis("MoveRight", this, &ASCharacter::MoveRight);

	// Bind the "LookUp" axis to this and call the inherited AddControllerPitchInput
	PlayerInputComponent->BindAxis("LookUp", this, &ASCharacter::AddControllerPitchInput);

	// Bind the "Turn" axis to this and call the inherited AddControllerYawInput
	PlayerInputComponent->BindAxis("Turn", this, &ASCharacter::AddControllerYawInput);

	// Bind the "Crouch" input to this and call "BeginCrouch" when pressed
	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &ASCharacter::BeginCrouch);

	// Bind the "Crouch" input to this and call "EndCrouch" when released
	PlayerInputComponent->BindAction("Crouch", IE_Released, this, &ASCharacter::EndCrouch);

	// Bind the "Jump" input to this and call "Jump"
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
}

// ********************************************************************************************************
// Override "GetPawnViewLocation" to return the position of the camera
FVector ASCharacter::GetPawnViewLocation() const
{
	// If there is a camera component...
	if (pCameraComponent)
	{
		// Return the location of it
		return pCameraComponent->GetComponentLocation();
	}

	// else return default
	return Super::GetPawnViewLocation();
}

