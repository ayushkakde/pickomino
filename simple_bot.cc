#include "simple_bot.h"
#include "roll.h"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <limits>

using namespace std;

void SimpleBot::prepareTurn(Game const &) {
}

bool SimpleBot::chooseWhetherToRoll(Game const &game, Dice const &taken) {
  Score score = taken.sum();
  Tile stealable = game.stealableTile(this, score);
  Tile remaining = game.bestRemainingTile(score);
  return !stealable.valid() && !remaining.valid();
}

DieSide const *SimpleBot::chooseSideToTake(Game const &, Dice const &taken, Dice const &roll) {
  Score maxScore = 0;
  DieSide const *maxSide = nullptr;
  for (DieSide const *side : {DieSide::WORM, DieSide::FIVE, DieSide::FOUR, DieSide::THREE, DieSide::TWO, DieSide::ONE}) {
    if (roll.contains(side) && !taken.contains(side)) {
      if (side == DieSide::WORM && taken.count() > 0) {
        return side;
      }
      Score score = side->score() * roll[side];
      if (score > maxScore) {
        maxScore = score;
        maxSide = side;
      }
    }
  }
  assert(maxSide);
  return maxSide;
}