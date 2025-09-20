// game_end.hpp
#pragma once
#include <vector>
#include "structs.hpp"
namespace GameEnd
{;
Winner calculateEndGame(ChessGame, std::vector<Move>);
bool insufficientMaterials(const ChessGame&, Color);
}