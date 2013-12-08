#pragma once

class FansiteConfig
  {
  private:
    std::string m_token;
    std::string m_simulator;
    unsigned m_simulations_per_deck;
    unsigned short m_threads;
    bool m_run_forever;

  public:
    FansiteConfig();

    const std::string& GetToken() const;
    const std::string& GetSimulator() const;
    unsigned GetSimulationsPerDeck() const;
    unsigned short GetThreads() const;
    bool GetRunForever() const;

    void SetToken(std::string&& i_token);
    void SetSimulator(std::string&& i_simulator);
    void SetSimulationsPerDeck(unsigned i_simulations_per_deck);
    void SetThreads(unsigned short i_threads);
    void SetRunForever(bool i_run_forever);
  };