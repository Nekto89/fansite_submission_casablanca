#include "stdafx.h"
#include "FansiteKernel.h"
#include "ArgumentParser.h"

FansiteKernel::FansiteKernel(int i_argument_count, wchar_t* i_arguments[])
  {
  if (i_argument_count > 1)
    ArgumentParser(i_argument_count, i_arguments, m_config);
  }