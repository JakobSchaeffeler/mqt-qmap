//
// This file is part of the MQT QMAP library released under the MIT license.
// See README.md or go to https://github.com/cda-tum/qmap for more information.
//

#pragma once

#include <iostream>

enum class CommanderGrouping { Halves, Fixed2, Fixed3, Logarithm };

static std::string toString(const CommanderGrouping grouping) {
  switch (grouping) {
  case CommanderGrouping::Fixed2:
    return "fixed2";
  case CommanderGrouping::Fixed3:
    return "fixed3";
  case CommanderGrouping::Logarithm:
    return "logarithm";
  case CommanderGrouping::Halves:
    return "halves";
  }
  return " ";
}

[[maybe_unused]] static CommanderGrouping
groupingFromString(const std::string& grouping) {
  if (grouping == "halves" || grouping == "0") {
    return CommanderGrouping::Halves;
  } else if (grouping == "fixed2" || grouping == "1") {
    return CommanderGrouping::Fixed2;
  } else if (grouping == "fixed3" || grouping == "2") {
    return CommanderGrouping::Fixed3;
  } else if (grouping == "logarithm" || grouping == "3") {
    return CommanderGrouping::Logarithm;
  } else {
    throw std::invalid_argument("Invalid grouping value: " + grouping);
  }
}
