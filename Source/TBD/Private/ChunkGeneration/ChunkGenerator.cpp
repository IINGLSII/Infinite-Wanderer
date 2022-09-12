// Fill out your copyright notice in the Description page of Project Settings.


#include "ChunkGeneration/ChunkGenerator.h"

FChunkGenerator::FChunkGenerator()
{
	adjacency_grid.Init(nullptr, 9);
}

FChunkGenerator::~FChunkGenerator()
{
	delete& adjacency_grid;
}

void FChunkGenerator::check_grid(FVector loc) {
	uint8 region = adjacency_grid[4]->check_player_adjacency(loc);
	if (region != 4) 
	{
		AChunk* focus = adjacency_grid[region];
		switch (region) {
			case 0:
				destroy_chunks();
				remap_chunks();
				create_chunks();
			case 1:
				destroy_chunks();
				remap_chunks();
				create_chunks();
			case 2:

			case 3:

			case 5:

			case 6:

			case 7:

			case 8:
			}
	}
	
}

void FChunkGenerator::destroy_chunks(TArray<uint8>& indices)
{
}

void FChunkGenerator::remap_chunks(TArray<uint8>& mapping)
{
}

void FChunkGenerator::create_chunks(TArray<uint8>& indicies)
{
}
