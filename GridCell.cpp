// Fill out your copyright notice in the Description page of Project Settings.

#include "GridCell.h"

// Sets default values
AGridCell::AGridCell()

{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Get the material and the mesh for this actor from the game engine
	static ConstructorHelpers::FObjectFinder<UMaterialInterface>MaterialAsset(TEXT( "/Game/StarterContent/Materials/M_Basic_Wall.M_Basic_Wall"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Game/StarterContent/Shapes/Shape_Cube"));


	// Check if the mesh  was loaded successfully
	if (MeshAsset.Succeeded())
	{
		Plane = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Plane"));
		Plane = Plane.Get();
		if (Plane != nullptr) {
			MyMesh = MeshAsset.Object;
			MyMaterial = MaterialAsset.Object;

			UMaterialInstanceDynamic* DynamicMaterial = UMaterialInstanceDynamic::Create(MyMaterial, nullptr);

			
			MyMesh->SetMaterial(0, DynamicMaterial);


			Plane->SetStaticMesh(MyMesh);

			CalculationInstance = new WorldCalculations();



	
			
			
			// World Units need to be divided by 100 to match units for an object
			float GridCellSize = CalculationInstance->WorldGridSize / 100 ;  // Calculate the size of each grid cell

			// Set the scale of the mesh component to match the grid cell size
			FVector NewScale = FVector(GridCellSize, GridCellSize, .01);
			Plane->SetRelativeScale3D(NewScale);
		}

		// Attach the static mesh component to the root component of the actor
		RootComponent = Plane;


		// Set up the niagara attachment. This is what allows the fire effect. 
		NiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraComponent"));
		NiagaraComponent->SetupAttachment(RootComponent);
		NiagaraComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 5.0f)); // Adjust the Z-coordinate to position the Niagara component above the actor
		NiagaraComponent->SetRelativeScale3D(FVector(0.01f, 0.01f, 0.01f)); // Adjust the Z-coordinate to position the Niagara component above the actor



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

