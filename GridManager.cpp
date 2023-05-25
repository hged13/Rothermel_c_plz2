// Fill out your copyright notice in the Description page of Project Settings.
#include "GridManager.h"
#include "TimerManager.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "CoreMinimal.h"




// Sets default values
AGridManager::AGridManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	arrayindex = 0;

	

}

// Called when the game starts or when spawned
void AGridManager::BeginPlay()
{
	Super::BeginPlay();
	InitializeGrid(100, 1000);
	isSpreading = false;


	
}




// Called every frame
void AGridManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (isSpreading == false) {

		GetWorld()->GetTimerManager().SetTimer(spreadTimer, this, &AGridManager::TimerCallbackSpread, 1.0f, true);

		

	}
	isSpreading = true;
	

	
	


}

void AGridManager::InitializeGrid(int32 GridSize, int32 WorldGridSize)
{

	UWorld* World = GetWorld();
	if (IsValid(World)) {

		FActorSpawnParameters SpawnInfo;
		float world = WorldGridSize * .5;
		float both = (WorldGridSize * GridSize) * .5;
		float world_offset = both - world;

		for (int i = 0; i < GridSize - 1; i++)
		{
			int index_y = i * WorldGridSize;
			float yval = index_y - world_offset;
			for (int j = 0; j < GridSize - 1; j++) {
				int index_x = j * WorldGridSize;
				float xval = index_x - world_offset;

				// Get a reference to the current world



				// Set the spawn parameters
				FActorSpawnParameters SpawnParams;
				SpawnParams.Owner = this;

				// Set the location and rotation of the new actor
				FVector SpawnLocation = FVector(xval, yval, 0.f);
				FRotator SpawnRotation = FRotator(0.f, 0.f, 0.f);

				// Spawn the actor
				AGridCell* NewActor = World->SpawnActor<AGridCell>(AGridCell::StaticClass(), SpawnLocation, SpawnRotation, SpawnParams);

				// Do something with the new actor
				GridCellArray.Add(NewActor);




			}
		}
	}
}
	








void AGridManager::TimerCallbackSpread()
{
	MakeFire(GridCellArray);
}

void AGridManager::endSpread() {
	GetWorld()->GetTimerManager().ClearTimer(spreadTimer);
	
}





void AGridManager::MakeFire(TArray<AGridCell*> gridcellarray2) {



	int gc_arr_size = gridcellarray2.Num();

	FString SizeString = FString::FromInt(gc_arr_size);
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, SizeString);

	

	UNiagaraComponent* NiagaraComponent = gridcellarray2[arrayindex]->GetNiagaraComponent();
	if(NiagaraComponent){
		NiagaraComponent->Activate();
		NiagaraComponent->SetPaused(false);
		}
	arrayindex++;
	if (arrayindex > gc_arr_size) {
		endSpread();
	}


	
}



// Debug Logging function below:
//FString SizeString = FString::FromInt(gc_arr_size);
//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, SizeString);