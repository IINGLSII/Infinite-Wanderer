// Fill out your copyright notice in the Description page of Project Settings.


#include "ChunkGeneration/ChunkGenerator.h"

// temporary const ***MOVE TO EDIT_ANYWHERE/BP_RW***
const int8        AChunkGenerator::dim = 3;

AChunkGenerator::AChunkGenerator()
{
	grid_array.Init(nullptr, dim*dim);
	
}

void AChunkGenerator::BeginPlay() {
	for (int r = -dim / 2; r <= dim / 2; r++) {
		for (int c = -dim / 2; c <= dim / 2; c++) {
			spawn_chunk(r, c);
		}
	}
}

AChunk* AChunkGenerator::get_chunk(int8 r_offset, int8 c_offset, TArray<AChunk*> &arr)
{
	// check if row/column offsets fall within dimension of array (dim)
	verify(AChunkGenerator::validate_offset(r_offset, c_offset));
	
	// index and return contents of array at indexed position
	int8 pos = AChunkGenerator::convert_offset_to_idx(r_offset, c_offset);
	return arr[pos];
}

void AChunkGenerator::set_chunk(int8 r_offset, int8 c_offset, AChunk* chunk, TArray<AChunk*>& arr)
{
	// check if row/column fall within dimension of array (dim)
	verify(AChunkGenerator::validate_offset(r_offset, c_offset));

	// set contents of array at indexed position
	int8 pos = AChunkGenerator::convert_offset_to_idx(r_offset, c_offset);
	arr[pos] = chunk;
}

void AChunkGenerator::spawn_chunk(int8 r, int8 c)
{
	AChunk* center = AChunkGenerator::get_chunk(0, 0, grid_array);

	FVector offset = FVector(r * size, c * size, 0);
	FTransform spawn_transform;
	if (center != nullptr)
		spawn_transform.SetLocation(center->GetActorLocation() + offset);
	else
		spawn_transform.SetLocation(FVector(0, 0, 0) + offset);

	AChunk* chunk = GetWorld()->SpawnActorDeferred<AChunk>(ChunkBP, spawn_transform);
	chunk->set_size(size);
	chunk->FinishSpawning(spawn_transform);
	AChunkGenerator::set_chunk(r, c, chunk, grid_array);
}

bool AChunkGenerator::validate_offset(int8 r, int8 c)
{
	return (r >= -dim / 2 && r <= dim / 2) && (c >= -dim / 2 && c <= dim / 2);
}

int AChunkGenerator::convert_offset_to_idx(int8 r, int8 c)
{
	return (r + dim/2)* dim + (c + dim/2);
}


void AChunkGenerator::updateGrid(FVector location) {

	AChunk* center = AChunkGenerator::get_chunk(0,0, grid_array);
	
	verify(center != nullptr);

	int8 xoff = center->get_player_offset(location, 1);
	int8 yoff = center->get_player_offset(location, 0);
	GEngine->AddOnScreenDebugMessage(-1, 200, FColor::Green, FString::Printf(TEXT("offset %d %d"), xoff,yoff));

	// check if player has moved from center tile (0,0)
	if (abs(xoff) + abs(yoff) != 0) {

		// create empty grid array
		TArray<AChunk*> temp_arr;
		temp_arr.Init(nullptr, dim*dim);

		// iterate through every tile to shift to new pos
		for (int r = -dim / 2; r <= dim / 2; r++) {
			for (int c = -dim / 2; c <= dim / 2; c++) {
				// new offset of tile after shifting array
				int8 new_r = r - xoff;
				int8 new_c = c - yoff;
				
				// if tiles shifted location is within dim bounds, set shifted pos of temp array to unshifted pos in grid_array
				if (AChunkGenerator::validate_offset(new_r, new_c))
					AChunkGenerator::set_chunk(new_r, new_c, AChunkGenerator::get_chunk(r, c, grid_array), temp_arr);
				else
					get_chunk(r, c, grid_array)->Destroy();
			}
		}
		// set contents of grid array to temp array
		grid_array = temp_arr;

		//iterate again to spawn chunks for null positions of array (newly discovered chunks), and spawn new chunks
		for (int r = -dim / 2; r <= dim / 2; r++) {
			for (int c = -dim / 2; c <= dim / 2; c++) {
				if (AChunkGenerator::get_chunk(r, c, grid_array) == nullptr)
					AChunkGenerator::spawn_chunk(r, c);
			}
		}
	}
}

