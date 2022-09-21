// Fill out your copyright notice in the Description page of Project Settings.


#include "ChunkGeneration/ChunkGenerator.h"

UChunkGenerator::UChunkGenerator()
{
	adjacency_grid.Init(nullptr, 9);
}

void UChunkGenerator::cullChunks() {

}

void UChunkGenerator::remapChunks() {

}

void UChunkGenerator::generateChunks() {

}

void UChunkGenerator::updateGrid(FVector location) {
	uint8 loc = adjacency_grid[3]->check_player_adjacency(location);
	if (loc != 4){
		AChunk* focus = adjacency_grid[3];
	}

}