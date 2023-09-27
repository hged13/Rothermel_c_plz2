// Fill out your copyright notice in the Description page of Project Settings.


#include "BoundExtractor.h"

// Sets default values
ABoundExtractor::ABoundExtractor()
{

	

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	isticking = true;

}

// Called when the game starts or when spawned
void ABoundExtractor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABoundExtractor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(isticking==true){

	for (TActorIterator<AGridManager> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		GridManager = *ActorItr;
		break;  // Exit the loop as soon as we've found the actor
	}

	if (GridManager)
	{
		UStaticMeshComponent* MeshComponent = GridManager->FindComponentByClass<UStaticMeshComponent>();

		if (MeshComponent)
		{
			UStaticMesh* Mesh = MeshComponent->GetStaticMesh();

			//Get the bounding box of mesh
			FBoxSphereBounds Bounds = Mesh->GetBoundingBox();

			FVector minextent = Bounds.GetBox().Min;
			FVector maxextent = Bounds.GetBox().Max;
			minextent *= 100;
			maxextent *= 100;

			// Convert them to FString
			


			FCartesianCoordinates MyECEFCoordsMin;
			FCartesianCoordinates MyGEOCoordsMin;
			FCartesianCoordinates MyECEFCoordsMax;
			FCartesianCoordinates MyGEOCoordsMax;
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::Printf(TEXT("Engine MIN: X=%f, Y=%f"), minextent.X, minextent.Y));
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::Printf(TEXT("Engine MAX: X=%f, Y=%f"), maxextent.X, maxextent.Y));





			TArray<AActor*> FoundActors;
			UGameplayStatics::GetAllActorsOfClass(GetWorld(), AGeoReferencingSystem::StaticClass(), FoundActors);

			// Ensure that at least one instance was found
			if (FoundActors.Num() > 0)
			{
				AGeoReferencingSystem* MyGeoRefSystem = Cast<AGeoReferencingSystem>(FoundActors[0]);
				MyGeoRefSystem->EngineToECEF(minextent, MyECEFCoordsMin);
				MyGeoRefSystem->ECEFToProjected(MyECEFCoordsMin, MyGEOCoordsMin);
				MyGeoRefSystem->EngineToECEF(maxextent, MyECEFCoordsMax);
				MyGeoRefSystem->ECEFToProjected(MyECEFCoordsMax, MyGEOCoordsMax);

				// Print to screen
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("MAX, Latitude: %f, Longitude: %f"), MyGEOCoordsMax.X, MyGEOCoordsMax.Y));
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("MIN, Latitude: %f, Longitude: %f"), MyGEOCoordsMin.X, MyGEOCoordsMin.Y));

					//}



			}
			isticking = false;

		}
			// Do something with FoundActor
		}
		
	}
}

