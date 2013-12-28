#include "stdafx.h"
#include "Deck.h"

Deck::Deck(std::string&& i_attacking_deck, std::vector<std::string>&& i_attacking_deck_cards, bool i_is_delayed, bool i_is_ordered, bool i_is_surge, EDeckType i_type, std::string&& i_deck_id)
  : m_attacking_deck(i_attacking_deck)
  , m_attacking_deck_cards(i_attacking_deck_cards)
  , m_is_delayed(i_is_delayed)
  , m_is_ordered(i_is_ordered)
  , m_is_surge(i_is_surge)
  , m_type(i_type)
  , m_deck_id(i_deck_id)
  {
  }

void Deck::SetAchievementId(unsigned short i_achievement_id)
  {
  m_achievement_id = i_achievement_id;
  }

void Deck::SetBattlegroundId(unsigned short i_battleground_id)
  {
  m_battleground_id = i_battleground_id;
  }

void Deck::SetDefendingDeck(std::string&& i_defending_deck)
  {
  m_defending_deck = std::move(i_defending_deck);
  }

void Deck::SetDefendingDeckCards(std::vector<std::string>&& i_defending_deck_cards)
  {
  m_defending_deck_cards = std::move(i_defending_deck_cards);
  }

void Deck::SetMissionId(unsigned short i_mission_id)
  {
  m_mission_id = i_mission_id;
  }

void Deck::SetQuestId(unsigned short i_quest_id)
  {
  m_quest_id = i_quest_id;
  }

void Deck::SetRaidId(unsigned short i_raid_id)
  {
  m_raid_id = i_raid_id;
  }