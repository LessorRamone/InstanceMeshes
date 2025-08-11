// Fill out your copyright notice in the Description page of Project Settings.


#include "InstanceMeshActor.h"
#include "Components/InstancedStaticMeshComponent.h"

// Sets default values
AInstanceMeshActor::AInstanceMeshActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	InstanceComp = Cast<UInstancedStaticMeshComponent>(CreateDefaultSubobject<UInstancedStaticMeshComponent>("InstanceComp"));
	RootComponent = InstanceComp;
	InstanceComp->NumCustomDataFloats = 3;
}

// Called when the game starts or when spawned
void AInstanceMeshActor::BeginPlay()
{
	Super::BeginPlay();
	TArray<int> Ids = InstanceComp->AddInstances(RandomTransformsOnSphere(InstanceCount, Radius), true, false, false);
	//NumCusomte
	for (int id : Ids)
	{
		InstanceComp->SetCustomData(id, { FMath::FRand(), FMath::FRand(), FMath::FRand() }, false);
	}
}

// Called every frame
void AInstanceMeshActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (Rotate)
	{
		const float RotationSpeed = 20.0f; // degrees per second
		FRotator DeltaRotation(0.f, RotationSpeed * DeltaTime, 0.f);
		AddActorLocalRotation(DeltaRotation);
	}
}

TArray<FTransform> AInstanceMeshActor::RandomTransformsOnSphere(int Count, float Radius)
{
	TArray<FTransform> Results;
	for (int i = 0; i < Count; ++i)
	{
		const float Theta = FMath::FRandRange(0.f, 2.f * PI); // Azimuth 
		const float Phi = FMath::Acos(1.f - 2.f * FMath::FRand()); // El

		// Convert spherical coordinates to Cartesian
		const float X = Radius * FMath::Sin(Phi) * FMath::Cos(Theta);
		const float Y = Radius * FMath::Sin(Phi) * FMath::Sin(Theta);
		const float Z = Radius * FMath::Cos(Phi);

		Results.Add(FTransform(FRotator::ZeroRotator, FVector(X, Y, Z), FVector(0.1f)));
	}
	return Results;
}

