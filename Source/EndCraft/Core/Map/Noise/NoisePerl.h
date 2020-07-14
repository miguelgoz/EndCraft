// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"

/**
 * 
 */
class ENDCRAFT_API NoisePerl
{
public:
	NoisePerl();
	~NoisePerl();

	static TArray<TArray<float>*> GenerateNoiseMap(int MapWidth, int MapHeight, float Scale);
};
