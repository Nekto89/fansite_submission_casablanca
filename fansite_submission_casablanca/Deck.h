#pragma once

class Deck
  {
  public:
    enum EDeckType { ERaid, EAchievement, EMission, EQuest, ECustom };
  private:
    unsigned short m_achievement_id;
    std::string m_attacking_deck;
    std::vector<std::string> m_attacking_deck_cards;
    unsigned short m_battleground_id;
    std::string m_defending_deck;
    std::vector<std::string> m_defending_deck_cards;
    bool m_is_delayed;
    bool m_is_ordered;
    bool m_is_surge;
    unsigned short m_mission_id;
    unsigned short m_quest_id;
    unsigned short m_raid_id;
    EDeckType m_type;
    std::string m_deck_id;
  public:
    Deck(std::string&& i_attacking_deck, std::vector<std::string>&& i_attacking_deck_cards, bool i_is_delayed, bool i_is_ordered, bool i_is_surge, EDeckType i_type, std::string&& i_deck_id);
    void SetAchievementId(unsigned short i_achievement_id);
    void SetMissionId(unsigned short i_mission_id);
    void SetQuestId(unsigned short i_quest_id);
    void SetRaidId(unsigned short i_raid_id);
  };