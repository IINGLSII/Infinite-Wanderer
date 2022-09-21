// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Chunk.h"
#include "ChunkGenerator.generated.h"

/**
 * 
 */
UCLASS()
class UChunkGenerator : public UObject
{
	GENERATED_BODY()

public:

	UChunkGenerator();

	UPROPERTY()
	TArray<AChunk*> adjacency_grid;

private:
	void updateGrid(FVector location);

	void cullChunks();

	void remapChunks();

	void generateChunks();
};
