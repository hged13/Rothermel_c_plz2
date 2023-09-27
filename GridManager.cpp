// Fill out your copyright notice in the Description page of Project Settings.
#include "GridManager.h"
#include "TimerManager.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
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
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Game/StarterContent/Levels/mesh_out.mesh_out")); 
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
	//FVector minextent = CalculationInstance->MinExtent;
	//FVector maxextent = CalculationInstance->MaxExtent;
	//FCartesianCoordinates MyECEFCoordsMin;
	//FCartesianCoordinates MyGEOCoordsMin;
	//FCartesianCoordinates MyECEFCoordsMax;
	//FCartesianCoordinates MyGEOCoordsMax;
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::Printf(TEXT("Engine MIN: X=%f, Y=%f"), minextent.X, minextent.Y));
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::Printf(TEXT("Engine MAX: X=%f, Y=%f"), maxextent.X, maxextent.Y));


	// The distance between midpoints
	WorldGridSize = CalculationInstance-> WorldGridSize;

	InitializeGrid();
	FString CSVFilePath = FPaths::ProjectDir() / TEXT("Source/Rothermel_c_plz2/data.csv");
	//ParseData(CSVFilePath);

	isSpreading = true;

	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AGeoReferencingSystem::StaticClass(), FoundActors);

	// Ensure that at least one instance was found
	//if (FoundActors.Num() > 0)
	//{
		//MyGeoRefSystem = Cast<AGeoReferencingSystem>(FoundActors[0]);
	  //  MyGeoRefSystem->EngineToECEF(minextent, MyECEFCoordsMin);
		//MyGeoRefSystem->ECEFToProjected(MyECEFCoordsMin, MyGEOCoordsMin);
		//MyGeoRefSystem->EngineToECEF(maxextent, MyECEFCoordsMax);
		//MyGeoRefSystem->ECEFToProjected(MyECEFCoordsMax, MyGEOCoordsMax);

		// Print to screen
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("GeographicCRS: " + GeographicCRS));
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("MAX, Latitude: %f, Longitude: %f"), MyGEOCoordsMax.X, MyGEOCoordsMax.Y));
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("MIN, Latitude: %f, Longitude: %f"), MyGEOCoordsMin.X, MyGEOCoordsMin.Y));


	//}


	




	
}




// Called every frame
void AGridManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// On the first tick, the fire spread is initiated. 
	if (isSpreading == true) {
		


		
		// Timer that calls TimerCallbackSpread every 0.5 seconds
		// Eventually this float value will be updated incrementally with the output of the Rothermel equation
		GetWorld()->GetTimerManager().SetTimer(spreadTimer, this, &AGridManager::TimerCallbackSpread, 0.5f, true);

		

	}

	//nothing will happen for other ticks  (other than the boolean if statement)
	isSpreading = false;
	

	
	


}


// The grid of actors is spawned
void AGridManager::InitializeGrid()
{

	UWorld* World = GetWorld();
	if (IsValid(World)) {

		//TEst to check if map can be accessed
		// in the future we will set up data here to be used in future. 
	
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





			}
		}
	}
}
	


void AGridManager::ParseData(FString CSVFilePath) {
		FuelMapRef = new FuelMap();


		// Array to hold the lines of the CSV file
		TArray<FString> CSVLines;

		// Read the lines of the CSV file into the array
		if (FFileHelper::LoadFileToStringArray(CSVLines, *CSVFilePath))
		{
			// Iterate over the lines of the CSV file
			for (int32 i = 1; i < CSVLines.Num(); i++)
			{
				// Split the line into fields using the comma as a delimiter
				TArray<FString> CSVFields;
				CSVLines[i].ParseIntoArray(CSVFields, TEXT(","));
				int fuelmodel = FCString::Atoi(*CSVFields[5]);
			
				FireData TempData;

				if (fuelmodel == -9999) {
					TempData.fuelload = 2.0;
					TempData.fueldepth = 1.0;
					TempData.fuel_moisture = 1.0;
					TempData.fuel_sav = 3.0;
					TempData.slope = FCString::Atof(*CSVFields[3]);
					TempData.windspeed = 5.0;

				}
				else {
					
					

					FoundModel = FuelMapRef->fuelModelTable.Find(fuelmodel);
					// Create a new FireData instance

					double load = static_cast<float>(FoundModel->fuel_load_1hr);
					FString type = FoundModel->fuel_model_type;

					TempData.fuelload = static_cast<float>(FoundModel->fuel_load_1hr);
					TempData.fueldepth = static_cast<float>(FoundModel->fuel_bed_depth);
					TempData.fuel_moisture = 1.0;
					TempData.fuel_sav = static_cast<float>(FoundModel->sav_ratio_dead_1hr);
					TempData.slope = FCString::Atof(*CSVFields[3]);
					TempData.windspeed = 5.0;
				}
				// Set the properties of the FireData instance using the fields from the CSV line
				// Note: You may need to convert the fields from FString to the appropriate type

				// ... set the rest of TempData's properties ...

				// Add TempData to FuelModelTable with appropriate key
				FuelModelTable.Add(FVector2D(FCString::Atod(*CSVFields[0]), FCString::Atod(*CSVFields[1])), TempData);  // Assuming FVector2D's X and Y components are the ninth and tenth fields
				

				
			}
		}
		else {
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Purple, "File Not Accessed.");


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
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red,"Fire");





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
			
			FVector NewScale = FVector(.001f, .001f, .001f);  // Use the scale you need
			NiagaraComponen2->SetRelativeScale3D(NewScale);
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