#pragma once

class XMLHash;
class Deck;

class HTTPClient
  {
  public:
    //gets session id, in case of error o_error becomes true
    std::string GetSessionId(const std::string& i_access_token, const std::string& i_version, const XMLHash& i_check, bool& o_error, std::string& o_error_message) const;
    std::vector<Deck> GetDecks(unsigned short i_limit, const std::string& i_session_id, bool& o_error, std::string& o_error_message) const;
    bool SubmitSimulation(const std::string& i_deck_id, const std::string& i_session_id, double i_ard, unsigned i_battles_total, unsigned i_battles_won, unsigned i_time_taken, std::string& o_error_message) const;
  };