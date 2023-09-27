



// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Engine.h"
#include "WorldCalculations.h"
#include "GridCell.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "CoreMinimal.h"
#include "FuelMap.h"
#include "GeoReferencingSystem.h"
#include "GeoReferencingModule.h"
#include "RoundPlanetPawn.h"
#include "GameFramework/Actor.h"
#include "GridManager.generated.h"




USTRUCT(BlueprintType)
struct FireData
{
	GENERATED_BODY()


		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		double fuelload;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		double fueldepth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		double windspeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		double slope;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		double fuel_moisture;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		double fuel_sav;

};




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

	FuelMap* FuelMapRef;
	FFuelModel* FoundModel;
	FireData* FoundModel2;

	AGeoReferencingSystem* MyGeoRefSystem;

	TMap<FVector2D, FireData> FuelModelTable;

	void ParseData(FString filename);

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
