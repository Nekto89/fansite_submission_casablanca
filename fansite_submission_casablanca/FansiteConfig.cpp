#include "stdafx.h"
#include "FansiteConfig.h"

FansiteConfig::FansiteConfig()
  : m_token("00000000000000000000000000000000")
  , m_simulator("Tyrant Optimizer")
  , m_simulations_per_deck(1000000)
  , m_threads(std::thread::hardware_concurrency())
  , m_run_forever(false)
  {
  if (m_threads == 0)
    m_threads = 1;
  }

const std::string& FansiteConfig::GetToken() const
  {
  return m_token;
  }

const std::string& FansiteConfig::GetSimulator() const
  {
  return m_simulator;
  }

unsigned FansiteConfig::GetSimulationsPerDeck() const
  {
  return m_simulations_per_deck;
  }

unsigned short FansiteConfig::GetThreads() const
  {
  return m_threads;
  }

bool FansiteConfig::GetRunForever() const
  {
  return m_run_forever;
  }

void FansiteConfig::SetToken(std::string&& i_token)
  {
  m_token = std::move(i_token);
  }

void FansiteConfig::SetSimulator(std::string&& i_simulator)
  {
  m_simulator = std::move(i_simulator);
  }

void FansiteConfig::SetSimulationsPerDeck(unsigned i_simulations_per_deck)
  {
  m_simulations_per_deck = i_simulations_per_deck;
  }

void FansiteConfig::SetThreads(unsigned short i_threads)
  {
  m_threads = i_threads;
  }

void FansiteConfig::SetRunForever(bool i_run_forever)
  {
  m_run_forever = i_run_forever;
  }