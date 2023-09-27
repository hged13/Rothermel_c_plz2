
#pragma once

#include "CoreMinimal.h"
#include "FuelMap.generated.h"



// A Struct meant to be used with the 'Fuel Model' data from a Geotiff.
// The fuel model data contains only a number that corresponds fuel information
// This class consists of a struct, representing each parameter, and a map to store information for each number in the fuel model data (91-204)
USTRUCT(BlueprintType)
struct FFuelModel
{
    GENERATED_BODY()

        UPROPERTY(EditAnywhere, BlueprintReadWrite)
        double fuel_load_1hr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        double fuel_load_10hr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        double fuel_load_100hr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        double fuel_load_live_herb;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        double fuel_load_live_woody;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        FString fuel_model_type;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        double sav_ratio_dead_1hr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        double sav_ratio_live_herb;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        double sav_ratio_live_woody;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        double fuel_bed_depth;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        int dead_fuel_extinction_moisture;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        int heat_content;
};

/**
 *
 */
class ROTHERMEL_C_PLZ2_API FuelMap
{
public:
    FuelMap();
    ~FuelMap();

    UPROPERTY()
        TMap<int, FFuelModel> fuelModelTable;
};