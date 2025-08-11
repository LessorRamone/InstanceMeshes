// Fill out your copyright notice in the Description page of Project Settings.


#include "DynamicActorMgrBase.h"

// Sets default values for this component's properties
UDynamicActorMgrBase::UDynamicActorMgrBase()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	//PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UDynamicActorMgrBase::BeginPlay()
{
	Super::BeginPlay();
	SpawnItAll();
	// ...
	
}

void UDynamicActorMgrBase::SpawnItAll()
{
	TArray<UClass*> HardClasses;
	for (auto& ptr : ClassesToSpawn)
	{
		//ptr.Get()
		HardClasses.Add(ptr.LoadSynchronous());
	}

	int HardClassCount = HardClasses.Num();
	int HardClassIndex = 0;

	for (int i = 0; i < SpawnCount; i++)
	{
		UClass* ClassToSpawn = HardClasses[HardClassIndex];
		HardClassIndex++;
		HardClassIndex = HardClassIndex % HardClassCount;
		if (ClassToSpawn)
		{
			FVector SpawnLocation = FVector(0, 0, 2000);
			FActorSpawnParameters SpawnParams;
			SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

			AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(ClassToSpawn, SpawnLocation, FRotator::ZeroRotator);
			if (SpawnedActor)
			{
				SpawnedActor->SetActorHiddenInGame(false);
				AllSpawns.Add(SpawnedActor);
			}
		}
	}
}


