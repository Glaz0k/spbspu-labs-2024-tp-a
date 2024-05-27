﻿#include <functional>
#include <iostream>
#include <map>
#include <exception>

#include "commands.hpp"

int main()
{
  using namespace belokurskaya;
  std::vector< belokurskaya::EngRusDict > EngRusDicts;
  std::map< std::string, std::function< void(std::istream&, std::ostream&) > > commands;
  {
    using namespace std::placeholders;
    commands["createDict"] = std::bind(cmd::createDict, std::ref(EngRusDicts), _1);
  }
  commands["help"](std::cin, std::cout);
  while (true)
  {
    std::string command;
    std::cin >> command;
    if (std::cin.eof())
    {
      break;
    }
    try
    {
      commands.at(command)(std::cin, std::cout);
    }
    catch (const std::exception&)
    {
      std::cout << "<INVALID COMMAND>\n";
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
  return 0;
}
