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
	arrayindex = 0;


	

}

// Called when the game starts or when spawned
void AGridManager::BeginPlay()
{
	Super::BeginPlay();
	// Determine the world grid size based on the maximum of mesh width and mesh length

	int32 DecimalPlaces = 2;

	// Round the floats to the specified number of decimal places
	

	//  The number of rows/columns
	GridSize = CalculationInstance->GridSize;
	WorldGridSize = CalculationInstance-> WorldGridSize;



	

	





	// The distance between midpoints

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


				// currently the grid is set to spawn above the mesh
				// In the future the zval won't matter because the fire will be mapped to the mesh
				// For now, the fire appears on the grid and just appears to be on the lanscape if the material is 'invisible' and the zval is low enough
				float zval = CenterLocation.Z + 25.0;
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


	

	UNiagaraComponent* NiagaraComponent = gridcellarray2[arrayindex]->GetNiagaraComponent();
	if(NiagaraComponent){
		NiagaraComponent->Activate();
		NiagaraComponent->SetPaused(false);
		}
	arrayindex++;
	// End the spread when all array elements have been accessed. 
	if (arrayindex > gc_arr_size-1) {
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red,"ENDED");

		endSpread();
	}


	
}



// Debug Logging function below:
//FString SizeString = FString::FromInt(gc_arr_size);
//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, SizeString);