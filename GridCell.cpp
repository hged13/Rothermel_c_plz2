// Fill out your copyright notice in the Description page of Project Settings.

#include "GridCell.h"

// Sets default values
AGridCell::AGridCell()

{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Game/StarterContent/Shapes/Shape_Sphere"));


	// Check if the material was loaded successfully
	if (MeshAsset.Succeeded())
	{
		Sphere = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Sphere"));
		Sphere = Sphere.Get();
		if (Sphere != nullptr) {
			MyMesh = MeshAsset.Object;

			Sphere->SetStaticMesh(MyMesh);

			// Assuming you have a UStaticMeshComponent named MeshComponent

			float WorldGridSize = 100.0f; // Total size of the world grid
			int32 GridSize = 10; // Number of cells per row

			float GridCellSize = WorldGridSize / GridSize; // Calculate the size of each grid cell

			// Set the scale of the mesh component to match the grid cell size
			FVector NewScale = FVector(GridCellSize, GridCellSize, GridCellSize);
			Sphere->SetRelativeScale3D(NewScale);
		}

		// Attach the static mesh component to the root component of the actor
		RootComponent = Sphere;

		NiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraComponent"));
		NiagaraComponent->SetupAttachment(RootComponent);
		NiagaraComponent->bAutoActivate = false; // Disable auto-activation of the Niagara component
		auto NiagaraSystemAssetPtr = LoadObject<UNiagaraSystem>(nullptr, TEXT("/Game/Fire.Fire"));
		if (NiagaraSystemAssetPtr)
		{
			NiagaraComponent->SetAsset(NiagaraSystemAssetPtr);
			NiagaraComponent->Deactivate(); // Deactivate the Niagara component initially


		}





	}


}


// Called every frame
void AGridCell::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

