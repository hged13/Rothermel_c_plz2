



// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "GridCell.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GridManager.generated.h"


UCLASS()
class ROTHERMEL_C_PLZ2_API AGridManager : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AGridManager();

	




protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(EditAnywhere)
		TArray<AGridCell*> GridCellArray;

	UPROPERTY(EditAnywhere)
		int32 arrayindex;

	UFUNCTION(BlueprintCallable, Category = "MyCategory")
		void InitializeGrid(int32 GridSize, int32 WorldGridSize);

	UFUNCTION(BlueprintCallable,Category = "MyCategory")
		int32 MakeFire(TArray<AGridCell*> GridCellArray2, int32 ind);

	UFUNCTION(BlueprintCallable, Category = "MyCategory")
		void SpreadFire();

	FTimerHandle Timer;


	UPROPERTY(EditAnywhere)
		float Delay;

	UFUNCTION(BlueprintCallable, Category = "MyCategory")
		void StartTimer();

	UFUNCTION(BlueprintCallable, Category = "MyCategory")
		void StopTimer();

	UFUNCTION(BlueprintCallable, Category = "MyCategory")
		void TimerCallback();


};
