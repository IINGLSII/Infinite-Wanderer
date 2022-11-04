// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Info.h"
#include "Tile.h"
#include "Engine/Engine.h"
#include "TileGenerator.generated.h"


/**
 * 
 */
UCLASS()
class ATileGenerator : public AInfo
{
	GENERATED_BODY()

public:

	ATileGenerator();

	// cull/update/spawn tiles according to a new given position.
	UFUNCTION(BlueprintCallable)
		void update_grid(FVector location);

	// spawns tiles in all empty indicies of grid_array, if flush is true, it will reintialize the whole list with new chunks.
	UFUNCTION(BlueprintCallable)
		void populate_grid(bool flush_array);

	// class of tiles to be spawned
	UPROPERTY(EditAnywhere)
		TSubclassOf <class ATile> TileBP;

	UFUNCTION()
		ATile* get_tile(int row_offset, int col_offset) const;

	UFUNCTION()
		int get_dim();

	UFUNCTION()
		float get_tile_size();
private:

	// array of tiles of size (dim,dim) representing the players immediate surroundings
	UPROPERTY()
		TArray<ATile*> grid_array;

	// gets tiles at r/c offset of a given array of tiles
	ATile* get_tile(int8 row_offset, int8 col_offset, const TArray<ATile*> &arr) const;

	// sets tiles at r/c offset of a given array of tiles
	void set_tile(int8 row_offset, int8 col_offset, ATile* tile, TArray<ATile*>& arr);

	// spawn tile at r/c offset
	void spawn_tile(int8 row_offset, int8 col_offset);

	// returns True if given offsets fall within the grid
	bool validate_offset(int8 row_offset, int8 col_offset) const;

	// converts row/center offset from center to array indices
	int convert_offset_to_idx(int8 row_offset, int8 col_offset) const;

	// calculate new random tile information and load it into given tile. Calls tile update method.
	void generate_tile(ATile* tile);

protected:
	// dimension of the tile 2D array
	UPROPERTY(BlueprintReadWrite)
		int dim = 3;

	// tile size (end to end)
	UPROPERTY(BlueprintReadWrite)
		float tile_size = 400;

	virtual void BeginPlay() override;
};
