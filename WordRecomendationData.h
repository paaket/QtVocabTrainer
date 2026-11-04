#pragma once
#include "Word.h"

struct WordRecomendationData {
	Word word;
	int attempts = 0;
	int errors = 0;
};