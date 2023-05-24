

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NiagaraComponent.h"
#include "GridCell.generated.h"


UCLASS()
class ROTHERMEL_C_PLZ2_API AGridCell : public AActor
{
	GENERATED_BODY()

public:

	/** Please add a variable description */
	UPROPERTY(EditAnywhere, Category = "Default")
		TObjectPtr<UStaticMeshComponent> Sphere;

	UPROPERTY(EditAnywhere, Category = "Materialr")
		UMaterialInterface* MyMaterial;

	UPROPERTY(EditAnywhere)
		UStaticMesh* MyMesh;

	/** Please add a variable description */
	UPROPERTY(EditAnywhere, Category = "Default")
		TObjectPtr<USceneComponent> DefaultSceneRoot;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Niagara")
		UNiagaraSystem* NiagaraSystemAsset;

	UPROPERTY(VisibleAnywhere, BlueprintReadONly, Category = "Niagara")
		UNiagaraComponent* NiagaraComponent;


	UFUNCTION(BlueprintCallable,Category="MyActor")
		UNiagaraComponent* GetNiagaraComponent() const { return NiagaraComponent; }
		


	// Sets default values for this actor's properties
	AGridCell();

protected:



public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;



};

