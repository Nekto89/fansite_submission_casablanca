#pragma once

#include "FansiteConfig.h"

class FansiteKernel
  {
  private:
    FansiteConfig m_config;

  public:
    FansiteKernel(int i_argument_count, wchar_t* i_arguments[]);
  };