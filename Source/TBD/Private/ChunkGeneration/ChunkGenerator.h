// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Info.h"
#include "Chunk.h"
#include "Engine/Engine.h"
#include "ChunkGenerator.generated.h"


/**
 * 
 */
UCLASS()
class AChunkGenerator : public AInfo
{
	GENERATED_BODY()

public:

	AChunkGenerator();

	// cull/update/spawn chunks according to a new given position.
	UFUNCTION(BlueprintCallable)
		void update_grid(FVector location);

	// spawns chunks in all empty indicies of grid_array, if flush is true, it will reintialize the whole list with new chunks.
	UFUNCTION(BlueprintCallable)
		void populate_grid(bool flush_array);

	// class of chunks to be spawned
	UPROPERTY(EditAnywhere)
		TSubclassOf <class AChunk> ChunkBP;

private:

	// array of chunks of size (dim,dim) representing the players immediate surroundings
	UPROPERTY()
		TArray<AChunk*> grid_array;

	// gets chunk at r/c offset of a given array of chunks
	AChunk* get_chunk(int8 row_offset, int8 col_offset, TArray<AChunk*> &arr) const;

	// sets chunk at r/c offset of a given array of chunks
	void set_chunk(int8 row_offset, int8 col_offset, AChunk* chunk, TArray<AChunk*>& arr);

	// spawn chunk at r/c offset
	void spawn_chunk(int8 row_offset, int8 col_offset);

	// returns True if given offsets fall within the grid
	bool validate_offset(int8 row_offset, int8 col_offset) const;

	// converts row/center offset from center to array indices
	int convert_offset_to_idx(int8 row_offset, int8 col_offset) const;

	// calculate new random chunk information and load it into given chunk. Calls chunk update method.
	void generate_chunk(AChunk* chunk);

protected:
	// dimension of the chunk 2D array
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int dim = 3;

	// chunk size (end to end)
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float chunk_size = 400;

	virtual void BeginPlay() override;
};
