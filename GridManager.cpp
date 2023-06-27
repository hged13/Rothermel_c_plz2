// Fill out your copyright notice in the Description page of Project Settings.
#include "GridManager.h"
#include "TimerManager.h"
#include "Engine/World.h"
#include <math.h>
#include "WorldCalculations.h"
#include "CoreMinimal.h"




// Sets default values
AGridManager::AGridManager()

{	// instance of WorldCalculations in order to access variables
	CalculationInstance = new WorldCalculations();
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//initialize arrayindex variable to be zero. To be used in MakeFire later.
	arrayindex = 0;

// Create a pointer to the mesh landscape so we can access it later
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Game/StarterContent/Maps/mesh_out.mesh_out"));
	if (MeshAsset.Succeeded())
	{
		UStaticMesh* StaticMesh = MeshAsset.Object;

		MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent")); // Create a default subobject of UStaticMeshComponent
		MeshComponent->SetStaticMesh(StaticMesh);

		// Use the MeshComponent as needed
	}
	// Access the niagara system from the game engine and save as a var
	ConstructorHelpers::FObjectFinder<UNiagaraSystem> NiagaraSystemAsset(TEXT("/Game/Fire.Fire"));
	if (NiagaraSystemAsset.Succeeded())
	{
		NiagaraSystem = NiagaraSystemAsset.Object;
	}
}



// Called when the game starts or when spawned
void AGridManager::BeginPlay()
{
	Super::BeginPlay();
	// Determine the world grid size based on the maximum of mesh width and mesh length
	//  The number of rows/columns
	GridSize = CalculationInstance->GridSize;
	// The distance between midpoints
	WorldGridSize = CalculationInstance-> WorldGridSize;

	InitializeGrid();
	isSpreading = false;
	





	
}




// Called every frame
void AGridManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// On the first tick, the fire spread is initiated. 
	if (isSpreading == false) {
		



		// Timer that calls TimerCallbackSpread every 0.5 seconds
		// Eventually this float value will be updated incrementally with the output of the Rothermel equation
		GetWorld()->GetTimerManager().SetTimer(spreadTimer, this, &AGridManager::TimerCallbackSpread, 0.5f, true);

		

	}

	//nothing will happen for other ticks  (other than the boolean if statement)
	isSpreading = true;
	

	
	


}


// The grid of actors is spawned
void AGridManager::InitializeGrid()
{

	UWorld* World = GetWorld();
	if (IsValid(World)) {
		


		FBoxSphereBounds MeshBounds = MeshComponent->CalcBounds(MeshComponent->GetComponentTransform());

		// We use the center of the mesh for reference to determine where the center of the grid will be 
		FVector CenterLocation = MeshBounds.GetBox().GetCenter();

		FActorSpawnParameters SpawnInfo;

		//  Because we want the center of the grid to line up with the center of the mesh we have to offset it 
		// Otherwise, spawning would start at the middle of the grid (making this point a corner)
		float world = WorldGridSize * .5;
		float both = (WorldGridSize * GridSize) * .5;
		float world_offset = both - world;

		for (int i = 0; i < GridSize - 1; i++)
		{
			int index_y = i * WorldGridSize;
			float yval = index_y - world_offset + CenterLocation.Y;
			for (int j = 0; j < GridSize - 1; j++) {
				int index_x = j * WorldGridSize;
				float xval = index_x - world_offset+CenterLocation.X;


				// The zval can be arbitrarily large or small. as long as it is higher than the highest z value of the mesh.


				float zval = CenterLocation.Z + 1000.0;
				// Set the spawn parameters
				FActorSpawnParameters SpawnParams;
				SpawnParams.Owner = this;

				// Set the location and rotation of the new actor
				FVector SpawnLocation = FVector(xval, yval, zval);
				FRotator SpawnRotation = FRotator(0.f, 0.f, 0.f);

				// Spawn the actor
				AGridCell* NewActor = World->SpawnActor<AGridCell>(AGridCell::StaticClass(), SpawnLocation, SpawnRotation, SpawnParams);

				GridCellArray.Add(NewActor);
				//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Grid Cell Created");





			}
		}
	}
}
	







// Everytime the timer runs out, MakeFire is called
void AGridManager::TimerCallbackSpread()
{
	MakeFire(GridCellArray);
}

// Turns the timer off
void AGridManager::endSpread() {
	GetWorld()->GetTimerManager().ClearTimer(spreadTimer);
	
}






// Increments the variable arrayindex and turns the Niagara Component of the current grid cell on.

void AGridManager::MakeFire(TArray<AGridCell*> gridcellarray2) {



	int gc_arr_size = gridcellarray2.Num();


	FVector ActorLocation = gridcellarray2[arrayindex]->GetActorLocation();
	float XCoordinate = ActorLocation.X;
	float YCoordinate = ActorLocation.Y;
	float ZCoordinate = ActorLocation.Z;

	FHitResult HitResult;
	FVector StartLocation = FVector(XCoordinate, YCoordinate, ZCoordinate);  // Starting location above the landscape
	FVector EndLocation = FVector(XCoordinate, YCoordinate, ZCoordinate-3000);  // End location below the landscape

	FCollisionQueryParams TraceParams(FName(TEXT("LineTrace")), true, nullptr);
	TraceParams.bTraceComplex = true;  // Enable complex collision tracing if needed


	// ...

	// In the constructor or initialization function
	arrayindex++;
	// Perform the line trace
	if (GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_WorldStatic, TraceParams))
	{
		// Check if the hit component is of type UStaticMeshComponent
		if (HitResult.Component.IsValid() && HitResult.Component->IsA<UStaticMeshComponent>())
		{
			UStaticMeshComponent* HitMeshComponent = Cast<UStaticMeshComponent>(HitResult.Component.Get());

			// Retrieve the hit location on the mesh
			FVector HitLocation = HitResult.Location;

			// Place the Niagara component at the hit location on the mesh
			UNiagaraComponent* NiagaraComponen2 = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), NiagaraSystem, HitLocation, FRotator::ZeroRotator);
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "ACtivating");
			NiagaraComponen2->Activate();

			// Set additional properties or parameters for the Niagara component if needed
			// NiagaraComponent->Set...
		}
	}

	// End the spread when all array elements have been accessed. 
	if (arrayindex > gc_arr_size-1) {
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red,"ENDED");

		endSpread();
	}


	
}



// Debug Logging function below:
//FString SizeString = FString::FromInt(gc_arr_size);
//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, SizeString);