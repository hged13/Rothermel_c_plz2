// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldCalculations.h"

WorldCalculations::WorldCalculations()
{
	
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Game/StarterContent/Levels/mesh_out.mesh_out"));
	if (MeshAsset.Succeeded())
	{

		UStaticMesh* Mesh = MeshAsset.Object;
		
		//Get the bounding box of mesh
		//FBoxSphereBounds Bounds = Mesh->GetBoundingBox();
	
		//MinExtent = Bounds.GetBox().Min;
		//MaxExtent = Bounds.GetBox().Max;

		// Convert them to FString
	

		// Print to screen
		


		// Calculate grid dimensions based on bounding box of mesh
		GridWidth = ceil(MaxExtent.X - MinExtent.X);
		GridLength = ceil(MaxExtent.Y - MinExtent.Y);
		if (GridWidth > GridLength) {
			finalgrid = GridWidth;
		}
		else {
			finalgrid = GridLength;
		}


		float GridHeight = MaxExtent.Z - MinExtent.Z;

		//This value will eventually be dynamic somehow. (set by the user to change graph resolution)
		// the higher the value, the MORE grid cells. 
		GridSize = 30;

		WorldGridSize = finalgrid/GridSize;

	}




	

}

WorldCalculations::~WorldCalculations()
{
}
