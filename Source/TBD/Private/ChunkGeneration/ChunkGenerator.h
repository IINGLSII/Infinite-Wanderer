// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ChunkGeneration/Chunk.h"
#include "ChunkGenerator.generated.h"

/**
 * 
 */
USTRUCT()
struct FChunkGenerator
{
	GENERATED_BODY()
public:
	FChunkGenerator();
	~FChunkGenerator();

	void check_grid(FVector loc);

private:
	void destroy_chunks();
	void remap_chunks();
	void create_chunks();



	UPROPERTY()
	TArray<AChunk*> adjacency_grid;

};
