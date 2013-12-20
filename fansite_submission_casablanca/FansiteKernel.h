#pragma once

#include "FansiteConfig.h"
#include "HTTPClient.h"

class FansiteKernel
  {
  private:
    FansiteConfig m_config;
    HTTPClient m_client;

  public:
    FansiteKernel(int i_argument_count, wchar_t* i_arguments[]);
  };