// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tile.generated.h"

UENUM()
enum class EWeather : uint8 {
	CLEAR = 0 UMETA(DisplayName = "CLEAR"),
	FOG = 1   UMETA(DisplayName = "FOG"),
	SNOW = 2  UMETA(DisplayName = "SNOW"),
	STORM = 3 UMETA(DisplayName = "STORM"),
};

UENUM()
enum class EStructure : uint8 {
	NONE = 0 UMETA(DisplayName = "NONE"),
	RUINS = 1   UMETA(DisplayName = "RUINS"),
	ALTAR = 2  UMETA(DisplayName = "ALTAR"),
	ROAD = 3 UMETA(DisplayName = "ROAD"),
};

UENUM()
enum class EEncounter : uint8 {
	NONE = 0 UMETA(DisplayName = "NONE"),
	WOLVES = 1 UMETA(DisplayName = "WOLVES"),
	SKELETONS = 2   UMETA(DisplayName = "SKELETONS"),
	WANDERER = 3  UMETA(DisplayName = "WANDERER"),
};


USTRUCT()
struct FTileData
{
	GENERATED_BODY()

	FTileData() {
		weather = EWeather::CLEAR;
		structure = EStructure::NONE;
		encounter = EEncounter::NONE;
		folliage_density = 0.5;
		tile_size = 400;
	}

	UPROPERTY()
		EWeather weather;

	UPROPERTY()
		EStructure structure;

	UPROPERTY()
		EEncounter encounter;

	UPROPERTY()
		float folliage_density;

	UPROPERTY()
		float tile_size;
};

USTRUCT()
struct FOffset
{
	GENERATED_BODY()

	FOffset() {
		row = 0;
		col = 0;
	}

	FOffset(int r, int c) {
		row = r;
		col = c;
	}

	UPROPERTY()
		int row;

	UPROPERTY()
		int col;

	friend bool operator==(FOffset OffsetA, FOffset OffsetB) {
		return ((OffsetA.col == OffsetB.col) && (OffsetA.row == OffsetB.row));
	}

	friend bool operator!=(FOffset OffsetA, FOffset OffsetB) {
		return !(OffsetA == OffsetB);
	}
};


UCLASS()
class ATile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATile();

	// returns int corresponding to player position in 3x3, 0-8 grid.
	UFUNCTION()
		FOffset get_player_offset(FVector loc) const;

	// placeholder mesh component
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UStaticMeshComponent* floor;

	// method called at spawn, before begin play, loads given tile data and appropriate structures.
	UFUNCTION()
		void load_tile_data(FTileData new_tile_data);

private:

	// structure containing tile state information.
	UPROPERTY()
		FTileData tile_data = FTileData();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
