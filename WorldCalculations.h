// Fill out your copyright notice in the Description page of Project Settings.
// This is a class to keep track of world dimensions in order to spawn appropriately sized grid and cells
#pragma once
#include "Engine/World.h"
#include <math.h>       

#include "CoreMinimal.h"

/**
 * 
 */
class ROTHERMEL_C_PLZ2_API WorldCalculations
{
public:
	WorldCalculations();
	~WorldCalculations();

	float GridWidth;
	int GridLength;

	float WorldGridSize;
	float GridSize;
	float finalgrid;


};
