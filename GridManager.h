



// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "WorldCalculations.h"
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


	bool isSpreading;

    float WorldGridSize;

    float GridSize;

	float Delay;

	WorldCalculations* CalculationInstance;


	UFUNCTION(BlueprintCallable, Category = "MyCategory")
		void InitializeGrid();

	UFUNCTION(BlueprintCallable,Category = "MyCategory")
		void MakeFire(TArray<AGridCell*> GridCellArray2);

	





	UFUNCTION(BlueprintCallable, Category = "MyCategory")
		void TimerCallbackSpread();

protected:
	FTimerHandle Timer;
	float GridWidth;
	int GridLength;
	FTimerHandle spreadTimer;
	UStaticMeshComponent* MeshComponent;
	void endSpread();
	UNiagaraSystem* NiagaraSystem;
	void PerformLineTracing(AActor* Actor);


};
