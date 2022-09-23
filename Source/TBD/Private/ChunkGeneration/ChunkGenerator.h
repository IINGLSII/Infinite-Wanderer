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

	UPROPERTY()
	TArray<AChunk*> adjacency_grid;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float size;

	UFUNCTION(BlueprintCallable)
	void updateGrid(FVector location);

	UPROPERTY(EditAnywhere)
	TSubclassOf <class AChunk> ChunkBP;

private:

	void cullChunks(TArray<uint8>);

	void remapChunks(TArray<uint8>, TArray<uint8>);

	void generateChunks(TArray<uint8>);

protected:

	virtual void BeginPlay() override;
};
