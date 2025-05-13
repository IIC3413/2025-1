#pragma once

#include <ostream>

class QueryAction {
public:
  virtual ~QueryAction() = default;

  virtual void execute() = 0;

  virtual std::ostream& print_to_ostream(std::ostream& os, int indent = 0) const = 0;

  friend std::ostream& operator<<(std::ostream& os, const QueryAction& iter) {
    return iter.print_to_ostream(os);
  }
};
