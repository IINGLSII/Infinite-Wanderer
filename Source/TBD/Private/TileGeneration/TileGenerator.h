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

	// class of tiles to be spawned
	UPROPERTY(EditAnywhere)
		TSubclassOf <class ATile> TileBP;

protected:
// OVERRIDES
	virtual void BeginPlay() override;

// PARAMETERS
	// the dimension of the tile 2D array
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int dim = 3;

	// tile size (end to end)
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float tile_size = 400;
	// 4x4 transition matrices for markov chain process
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TArray<FMatrix> ProbabilityMatricies;

// MEMBER VARIABLES
private:
	// array of tiles of size (dim,dim) representing the players immediate surroundings
	UPROPERTY()
		TArray<ATile*> grid_array;
		

public:
// INTERFACE FUNCTIONS
	// returns the dimension of the grid
	UFUNCTION()
		int get_dim() const;

	// returns the tile size of the tiles within the grid
	UFUNCTION()
		float get_tile_size() const;

	// returns tile at a given row/columb offset from grid_array
	UFUNCTION()
		ATile* get_tile(FOffset offset) const;

	// returns tile at specific index of the grid_array
	UFUNCTION()
		ATile* get_tile_by_index(int32 index) const;

	// cull/update/spawn tiles according to a new given position.
	UFUNCTION(BlueprintCallable)
		void update_grid(FVector location);

	// spawns tiles in all empty indicies of grid_array, if flush is true, it will reintialize the whole list with new chunks.
	UFUNCTION(BlueprintCallable)
		void populate_grid(bool flush_array);


// PURE FUNCTIONS
	// returns True if given offsets fall within the grid
	bool validate_offset(FOffset offset) const;

	// converts row/center offset from center to array indices
	int convert_offset_to_idx(FOffset offset) const;

	// converts array_grid index to row/column offset
	FOffset convert_idx_to_offset(int index) const;


private:
// INTERNAL FUNCTIONS
	// gets tiles at r/c offset of a given array of tiles
	ATile* get_tile(FOffset offset, const TArray<ATile*> &arr) const;

	// sets tiles at r/c offset of a given array of tiles
	void set_tile(FOffset offset, ATile* tile, TArray<ATile*>& arr);

	// spawn tile at r/c offset at grid_array
	void spawn_tile(FOffset offset);

	// calculate new random tile information and load it into given tile. Calls tile update method.
	void generate_tile(ATile* tile);
};


