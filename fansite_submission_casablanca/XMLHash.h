#pragma once

class XMLHash
  {
  private:
    std::string m_achievements;
    std::string m_cards;
    std::string m_missions;
    std::string m_quests;
    std::string m_raids;

    std::string _MD5(const std::string& i_input) const;

  public:
    XMLHash(std::istream& i_achievements, std::istream& i_cards, std::istream& i_missions, std::istream& i_quests, std::istream& i_raids);
    const std::string& GetAchievementsHash() const;
    const std::string& GetCardsHash() const;
    const std::string& GetMissionsHash() const;
    const std::string& GetQuestsHash() const;
    const std::string& GetRaidsHash() const;
  };