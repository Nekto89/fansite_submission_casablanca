#include "stdafx.h"
#include "FansiteKernel.h"
#include "ArgumentParser.h"
#include "XMLHash.h"
#include <iostream>
#include <fstream>
#include <Windows.h>

FansiteKernel::FansiteKernel(int i_argument_count, wchar_t* i_arguments[])
  {
  if (i_argument_count > 1)
    ArgumentParser(i_argument_count, i_arguments, m_config);

  TCHAR buffer[MAX_PATH + 1];
  GetCurrentDirectory(MAX_PATH, buffer);
  std::wcout << buffer << std::endl;

  bool error;
  std::string error_message;
  std::string result = m_client.GetSessionId
    ( ""
    , "1.1.6"
    , XMLHash
      ( std::ifstream("achievements.xml", std::ios::binary)
      , std::ifstream("cards.xml", std::ios::binary)
      , std::ifstream("missions.xml", std::ios::binary)
      , std::ifstream("quests.xml", std::ios::binary)
      , std::ifstream("raids.xml", std::ios::binary)
      )
    , error
    , error_message
    );
  if (error)
    std::cout << error_message;
  else
    std::cout << result;
  }