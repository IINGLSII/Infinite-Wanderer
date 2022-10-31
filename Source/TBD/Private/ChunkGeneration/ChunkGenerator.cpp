// Fill out your copyright notice in the Description page of Project Settings.


#include "ChunkGeneration/ChunkGenerator.h"


AChunkGenerator::AChunkGenerator()
{
	
}

void AChunkGenerator::BeginPlay() {
	grid_array.Init(nullptr, dim * dim);
	// dimension must be odd (has a center tile)
	verify(dim % 2 != 0);
}



AChunk* AChunkGenerator::get_chunk(int8 row_offset, int8 col_offset, TArray<AChunk*> &arr) const
{
	// check if row/column offsets fall within dimension of array (dim)
	verify(AChunkGenerator::validate_offset(row_offset, col_offset));
	
	// index and return contents of array at indexed position
	int8 pos = AChunkGenerator::convert_offset_to_idx(row_offset, col_offset);
	return arr[pos];
}

void AChunkGenerator::set_chunk(int8 row_offset, int8 col_offset, AChunk* chunk, TArray<AChunk*>& arr)
{
	// check if row/column fall within dimension of array (dim)
	verify(AChunkGenerator::validate_offset(row_offset, col_offset));

	// set contents of array at indexed position
	int8 pos = AChunkGenerator::convert_offset_to_idx(row_offset, col_offset);
	arr[pos] = chunk;
}
// Spawns a chunk at a given r/c offset
void AChunkGenerator::spawn_chunk(int8 row, int8 col)
{
	// get reference to center
	AChunk* center = AChunkGenerator::get_chunk(0, 0, grid_array);
	FVector offset = FVector(row * chunk_size, col * chunk_size, 0);
	FTransform spawn_transform;
	// determine if center exists
	if (center != nullptr)
		spawn_transform.SetLocation(center->GetActorLocation() + offset);
	else
		spawn_transform.SetLocation(this->GetActorLocation() + offset);

	// spawn actor, adjust size variable, begin calling beginplay, and then set chunk reference in grid array
	AChunk* chunk = GetWorld()->SpawnActorDeferred<AChunk>(ChunkBP, spawn_transform);
	AChunkGenerator::generate_chunk(chunk);
	chunk->FinishSpawning(spawn_transform);
	AChunkGenerator::set_chunk(row, col, chunk, grid_array);
}

// returns True if given offsets result in a valid converted array index, False if not
bool AChunkGenerator::validate_offset(int8 row, int8 col) const
{
	return (row >= -dim / 2 && row <= dim / 2) && (col >= -dim / 2 && col <= dim / 2);
}

// converts row column offset from zero to array indices, where (0,0) offset is in the center of the 2D array
int AChunkGenerator::convert_offset_to_idx(int8 row, int8 col) const
{
	return (row + dim/2)* dim + (col + dim/2);
}


void AChunkGenerator::update_grid(FVector location) {

	AChunk* center_chunk = AChunkGenerator::get_chunk(0,0, grid_array);
	
	verify(center_chunk != nullptr);

	int8 x_offset = center_chunk->get_player_offset(location, 1);
	int8 y_offset = center_chunk->get_player_offset(location, 0);

	// check if player has moved from center tile (0,0)
	if (abs(x_offset) + abs(y_offset) != 0) {

		// create empty grid array
		TArray<AChunk*> temp_arr;
		temp_arr.Init(nullptr, dim*dim);

		// iterate through every tile to shift to new pos
		for (int8 row = -dim / 2; row <= dim / 2; row++) {
			for (int8 col = -dim / 2; col <= dim / 2; col++) {
				// new offset of tile after shifting array
				int8 new_row_offset = row - x_offset;
				int8 new_col_offset = col - y_offset;
				
				// if tiles shifted location is within dim bounds, set shifted pos of temp array to unshifted pos in grid_array
				if (AChunkGenerator::validate_offset(new_row_offset, new_col_offset))
					AChunkGenerator::set_chunk(new_row_offset, new_col_offset, AChunkGenerator::get_chunk(row, col, grid_array), temp_arr);
				else
					get_chunk(row, col , grid_array)->Destroy();
			}
		}
		// set contents of grid array to temp array
		grid_array = temp_arr;

		//spawn chunks for null positions of array (newly discovered chunks)
		AChunkGenerator::populate_grid(false);
	}
}

void AChunkGenerator::populate_grid(bool flush_array)
{
	for (int8 row = -dim / 2; row <= dim / 2; row++) {
		for (int8 col = -dim / 2; col <= dim / 2; col++) {
			if (AChunkGenerator::get_chunk(row, col, grid_array) == nullptr || flush_array)
				AChunkGenerator::spawn_chunk(row, col);
		}
	}
}

void AChunkGenerator::generate_chunk(AChunk* chunk)
{
	FChunkData chunk_data = FChunkData();
	chunk_data.chunk_size = chunk_size;
	chunk->load_chunk_data(chunk_data);
}