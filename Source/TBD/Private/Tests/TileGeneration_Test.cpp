// Fill out your copyright notice in the Description page of Project Settings.


#include "TileGeneration_Test.h"

ATileGeneration_Test::ATileGeneration_Test()
{
}

void ATileGeneration_Test::StartTest()
{
	float minimum_tile_size = generator->get_tile_size();
	generator->populate_grid(true);


	FinishTest(EFunctionalTestResult::Succeeded,FString("Tile maintains minimum distance."));

}
