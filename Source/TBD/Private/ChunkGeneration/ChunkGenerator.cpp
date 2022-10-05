// Fill out your copyright notice in the Description page of Project Settings.


#include "ChunkGeneration/ChunkGenerator.h"

const int        AChunkGenerator::dim = 3;

AChunkGenerator::AChunkGenerator()
{
	grid_array.Init(nullptr, 9);
	
}

void AChunkGenerator::BeginPlay() {
	
}

AChunk* AChunkGenerator::get_chunk(uint8 r_offset, uint8 c_offset, TArray<AChunk*> &arr)
{
	verify(r_offset < dim&& c_offset < dim);
	verify(r_offset >= 0 && c_offset >= 0);
	
	uint8 pos = (c_offset +1) * dim + (r_offset +1);
	return arr[pos];
}

void AChunkGenerator::set_chunk(uint8 r_offset, uint8 c_offset, AChunk* chunk)
{
	verify(r_offset < dim && c_offset < dim);
	verify(r_offset >= 0 && c_offset >= 0);

	uint8 pos = (c_offset + 1) * dim + (r_offset + 1);
	grid_array[pos] = chunk;
}


void AChunkGenerator::updateGrid(FVector location) {

	AChunk* center = AChunkGenerator::get_chunk(0,0, grid_array);
	uint8 xoff = center->get_player_offset(location);
	uint8 yoff = center->get_player_offset(location, 0);

	if (abs(xoff) + abs(yoff) != 0) {

		TArray<AChunk*> temp_arr = TArray<AChunk*> (grid_array);

		for (int r = 0; r < dim; r++) {
			for (int c = 0; c < dim; c++) {
				uint8 new_r = r - xoff;
				uint8 new_c = c - yoff;

				if ((new_r < 0 || new_r >= dim) || (new_c < 0 || new_c >= dim)) {
					if (get_chunk(r, c, temp_arr) == get_chunk(r, c, grid_array))
						AChunkGenerator::set_chunk(r, c, nullptr);
				}
				else
					AChunkGenerator::set_chunk(new_r, new_c, AChunkGenerator::get_chunk(r, c, temp_arr));
			}
		}
	}

	//if(GEngine)
	//	GEngine->AddOnScreenDebugMessage(-1, 100, FColor::Yellow, FString::Printf(TEXT("AT %i"), loc));

}