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

	// temporary const ***MOVE TO EDIT_ANYWHERE/BP_RW***
	const static int8 dim;

	// chunk size (end to end)
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float size;

	// array of chunks that represent player's loaded surrounding chunks
	UPROPERTY()
	TArray<AChunk*> grid_array;

	// cull/update/spawn chunks according to given player position.
	UFUNCTION(BlueprintCallable)
	void updateGrid(FVector location);

	// class of chunks to be spawned
	UPROPERTY(EditAnywhere)
	TSubclassOf <class AChunk> ChunkBP;

private:
	// gets chunk at r/c offset of a given array of chunks
	AChunk* get_chunk(int8 r, int8 c, TArray<AChunk*> &arr);

	// sets chunk at r/c offset of a given array of chunks
	void set_chunk(int8 r, int8 c, AChunk* chunk, TArray<AChunk*>& arr);

	// spawn chunk at r/c offset
	void spawn_chunk(int8 r, int8 c);

	// returns True if given offsets fall within the grid
	bool validate_offset(int8 r, int8 c);

	// converts row/center offset from center to array indices
	int convert_offset_to_idx(int8 r, int8 c);

protected:

	virtual void BeginPlay() override;
};
