// Fill out your copyright notice in the Description page of Project Settings.

#include "GridCell.h"

// Sets default values
AGridCell::AGridCell()

{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	// load mesh from game engine
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Game/StarterContent/Shapes/Shape_Sphere"));


	// Check if the mesh was loaded successfully
	if (MeshAsset.Succeeded())
	{	// The shape was actually changed to a plane, not a shape, but 
		Plane = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Plane"));
		Plane = Plane.Get();
		if (Plane != nullptr) {
			MyMesh = MeshAsset.Object;

			Plane->SetStaticMesh(MyMesh);
			
			// Currently hardcoded values but will be updated to be dynamic (based on grid size in GridManager)
			float WorldGridSize = 100.0f; // Total size of the world grid
			int32 GridSize = 10; // Number of cells per row

			float GridCellSize = WorldGridSize / GridSize; // Calculate the size of each grid cell

			// Set the scale of the mesh component to match the grid cell size
			FVector NewScale = FVector(GridCellSize, GridCellSize, GridCellSize);
			Plane->SetRelativeScale3D(NewScale);
		}

		// Attach the static mesh component to the root component of the actor
		RootComponent = Plane;
		
		// The fire capability is added to the GridCell through a niagara component
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

