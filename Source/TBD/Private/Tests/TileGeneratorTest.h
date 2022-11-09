// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FunctionalTest.h"
#include "TBD\Private\TileGeneration\TileGenerator.h"
#include "TileGeneratorTest.generated.h"

/**
 * 
 */
UCLASS()
class ATileGeneratorTest : public AFunctionalTest
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	ATileGenerator* generator;

private:
	// ensure all tiles maintain TILE_SIZE minimum distance.
	void minimum_distance_TEST();

	void unit_TEST();

	virtual void StartTest() override;
};
