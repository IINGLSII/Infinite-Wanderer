// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FunctionalTest.h"
#include "TBD\Private\TileGeneration\TileGenerator.h"
#include "TileGeneration_Test.generated.h"

/**
 * 
 */
UCLASS()
class ATileGeneration_Test : public AFunctionalTest
{
	GENERATED_BODY()
	
public:
	ATileGeneration_Test();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		ATileGenerator* generator;

	virtual void StartTest() override;
	
};
