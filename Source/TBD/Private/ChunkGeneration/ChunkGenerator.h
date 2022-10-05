// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Info.h"
#include "Chunk.h"
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

	const static int dim;

	UPROPERTY()
	TArray<AChunk*> grid_array;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float size;

	UFUNCTION(BlueprintCallable)
	void updateGrid(FVector location);

	UPROPERTY(EditAnywhere)
	TSubclassOf <class AChunk> ChunkBP;

private:

	AChunk* get_chunk(uint8 r, uint8 c, TArray<AChunk*> &arr);

	void set_chunk(uint8 r, uint8 c, AChunk* chunk);

	AChunk* spawnChunk(uint8 r, uint8 c);

protected:

	virtual void BeginPlay() override;
};
