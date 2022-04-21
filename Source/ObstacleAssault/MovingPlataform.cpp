// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlataform.h"

// Sets default values
AMovingPlataform::AMovingPlataform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMovingPlataform::BeginPlay()
{
	Super::BeginPlay();

	StartLocation = GetActorLocation();
	
}

// Called every frame
void AMovingPlataform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MovePlatform(DeltaTime);

	RotatePlatform(DeltaTime);
}

void AMovingPlataform:: MovePlatform(float DeltaTime)
{
	if (ShouldPlatformReturn()) {
		FVector MoveDirection = PlataformVelocity.GetSafeNormal();
		StartLocation = StartLocation + MoveDirection * MoveDistanceLimit;
		SetActorLocation(StartLocation);
		PlataformVelocity = -PlataformVelocity;
	}
	else {
		FVector CurrentLocation = GetActorLocation();
		CurrentLocation += PlataformVelocity * DeltaTime;
		SetActorLocation(CurrentLocation);
	}
}

void AMovingPlataform::RotatePlatform(float DeltaTime)
{
	//UE_LOG(LogTemp, Display, TEXT("Begin play: %s"), *Name);
	FRotator CurrentRotation = GetActorRotation();

	CurrentRotation += RotationVelocity * DeltaTime;
	SetActorRotation(CurrentRotation);
	
}

bool AMovingPlataform::ShouldPlatformReturn() const
{
	return GetDistanceMoved() > MoveDistanceLimit;
}

float AMovingPlataform::GetDistanceMoved() const
{
	return FVector::Dist(StartLocation, GetActorLocation());
}
