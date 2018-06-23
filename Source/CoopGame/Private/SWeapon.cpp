// Fill out your copyright notice in the Description page of Project Settings.

#include "SWeapon.h"
#include "DrawDebugHelpers.h"

// Sets default values
ASWeapon::ASWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Assign the pointer to a new "SkeletalMeshComponent" instance
	pSkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));

	// Set the "SkeletaMeshComponent" pointer to be the root component
	RootComponent = pSkeletalMeshComponent;
}

// Called when the game starts or when spawned
void ASWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Fires the weapon
void ASWeapon::Fire()
{
	// Check who owns the weapon
	AActor* MyOwner = GetOwner();

	if (MyOwner)
	{
		// Get the location of the actors eyes
		FVector EyeLocation;
		FRotator EyeRotation;
		MyOwner->GetActorEyesViewPoint(EyeLocation, EyeRotation);

		// Get the end of the trace using eye location + the rotation vector * distance of trace
		FVector TraceEnd = EyeLocation + (EyeRotation.Vector() * 10000);

		// Create variables to store the hit results
		FHitResult Hit;
		FCollisionQueryParams QueryParams;
		QueryParams.AddIgnoredActor(MyOwner); // Ignore the actor
		QueryParams.AddIgnoredActor(this); // Ignore the weapon
		QueryParams.bTraceComplex = true; // Detailed hit ie for head shots etc
		
		// Trace the world, from pawn eyes to cross hair location.
		// If we hit something...
		if (GetWorld()->LineTraceSingleByChannel(Hit, EyeLocation, TraceEnd, ECC_Visibility, QueryParams))
		{
			// Then do this...
		}

		// Draw debug trace
		DrawDebugLine(GetWorld(), EyeLocation, TraceEnd, FColor::Red, false, 5.0f, 0, 1.0f);
	}
}

// Called every frame
void ASWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

