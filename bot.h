#ifndef BOT_H
#define BOT_H

#include <unordered_map>

#include "dice.h"
#include "game.h"

typedef double ExpectedWorms;

class Bot : public Strategy {
  public:
    void prepareTurn(Game const &game) override;
    bool chooseWhetherToRoll(Game const &game, Dice const &taken) override;
    DieSide const *chooseSideToTake(Game const &game, Dice const &taken, Dice const &roll) override;

  private:
    std::unordered_map<Dice, ExpectedWorms> m_expectedWhenRolling;

    ExpectedWorms expectedWormsWhenTaking(Game const &game, Dice taken, Dice const &roll, DieSide const *side);
    ExpectedWorms expectedWormsWhenRolled(Game const &game, Dice taken, Dice const &roll);
    ExpectedWorms expectedWormsWhenRolling(Game const &game, Dice taken);
    ExpectedWorms expectedWormsWhenQuitting(Game const &game, Dice taken);
};

#endif
