// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InstanceMeshActor.generated.h"

UCLASS(Blueprintable, BlueprintType)
class THIRDPERSONFIVEFIVE_API AInstanceMeshActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInstanceMeshActor();

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UInstancedStaticMeshComponent* InstanceComp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int InstanceCount = 10000;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Radius = 500.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool Rotate = false;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	static TArray<FTransform> RandomTransformsOnSphere(int Count, float Radius);

};
