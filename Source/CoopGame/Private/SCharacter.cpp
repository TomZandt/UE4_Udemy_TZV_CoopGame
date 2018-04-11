// Fill out your copyright notice in the Description page of Project Settings.

#include "SCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

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
}

