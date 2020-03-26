#ifndef __B_PHONETICS__
#define __B_PHONETICS__

#include <functional>
#include <set>
#include <vector>

#include "phonetic_rules.hpp"

namespace beepspeech {

/**
 * All phonetics related code
 */
namespace phonetics {

  typedef std::multiset<IRule*, std::greater<IRule*> > RuleSet;

  /**
   * Parse a piece of text into a phonetic sentence.
   *
   * To do this, a set of IRules are provided
   */
  class Parser : public RuleSet {
  public:
    Parser(RuleSet rules) : RuleSet(rules) {}
    template<typename Iterable> Parser(Iterable rules) :
      RuleSet(rules.begin(), rules.end()) {}
    Parser() {}

    std::vector<std::string> parse(const std::string& str) const;
    std::string parseToString(const std::string& str) const;
  };
}
}

#endif
