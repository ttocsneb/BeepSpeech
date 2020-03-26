#include "phonetics.hpp"
#include <set>
#include <list>
#include <sstream>

using namespace beepspeech::phonetics;
using std::vector;
using std::list;
using std::string;
using std::ostringstream;



vector<string> Parser::parse(const string& str) const {
  list<string> result;

  size_t i = 0;
  size_t len = str.size();
  while (i < len) {
    for (IRule* rule : *this) {
      try {
        Match m = rule->match(str.substr(i));
        result.push_back(m.result);
        i += m.length;
        break;
      } catch (MatchNotFoundException& e) {}
    }
  }

  return vector<string>(result.begin(), result.end());
}

string Parser::parseToString(const string& str) const {
  ostringstream oss;

  size_t i = 0;
  size_t len = str.size();
  while (i < len) {
    for (IRule* rule : *this) {
      try {
        Match m = rule->match(str.substr(i));
        oss << m.result;
        i += m.length;
        break;
      } catch (MatchNotFoundException& e) {}
    }
  }

  return oss.str();
}
