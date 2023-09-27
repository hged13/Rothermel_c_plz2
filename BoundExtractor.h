// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../GridManager.h"
#include "GameFramework/Actor.h"
#include "BoundExtractor.generated.h"

UCLASS()
class ROTHERMEL_C_PLZ2_API ABoundExtractor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABoundExtractor();
	AGridManager* GridManager;
	bool isticking;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
