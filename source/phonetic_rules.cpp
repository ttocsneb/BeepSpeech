#include "phonetic_rules.hpp"

#include <regex>
#include <stdexcept>

using namespace beepspeech::phonetics;
using std::string;
using std::regex_search;
using std::smatch;
using std::ssub_match;
using namespace std::regex_constants;
using std::out_of_range;

bool PassthroughRule::matches(const string &str) const {
  return str.rfind(in, 0) != string::npos;
}

Match PassthroughRule::match(const string &str) const {
  if (matches(str)) {
    return {
      str.size(),
      str
    };
  }
  throw MatchNotFoundException("Could not find match '" + in + "'");
}

bool SimpleRule::matches(const string &str) const {
  return str.rfind(in, 0) != string::npos;
}

Match SimpleRule::match(const string &str) const {
  if (matches(str)) {
    return {
      in.size(),
      out
    };
  }
  throw MatchNotFoundException("Could not find '" + in + "' in '" + str + "'");
}

bool RegexPassthroughRule::matches(const string &str) const {
  return regex_search(str, in, match_not_null);
}

Match RegexPassthroughRule::match(const string &str) const {
  smatch r_match;

  if (regex_search(str, r_match, in, match_not_null)) {
    return {
      static_cast<size_t>(r_match.length()),
      r_match.str()
    };
  }
  throw MatchNotFoundException();
}

bool RegexRule::matches(const string &str) const {
  return regex_search(str, in, match_not_null);
}

Match RegexRule::match(const string &str) const {

  smatch r_match;

  if (regex_search(str, r_match, in, match_not_null)) {
    return {
      static_cast<size_t>(r_match.length()),
      out
    };
  }
  throw MatchNotFoundException();
}

bool RegexReplaceRule::matches(const string &str) const {
  return regex_search(str, in, match_not_null);
}

Match RegexReplaceRule::match(const string &str) const {
  smatch r_match;

  if (regex_search(str, r_match, in, match_not_null)) {
    string found = r_match.str();
    ssub_match sub = r_match[1];
    try {
      found.replace(found.find(sub.str()), sub.length(), sub.str());
      return {
        static_cast<size_t>(r_match.length()),
        found
      };
    } catch (const out_of_range &e) {}
  }

  throw MatchNotFoundException();
}
