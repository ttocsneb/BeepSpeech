#ifndef __B_PHONETIC_RULES__
#define __B_PHONETIC_RULES__

#include <string>
#include <exception>
#include <regex>

namespace beepspeech {
namespace phonetics {
  /**
   * An exception that is thrown by IRule::match() when a match is not found
   */
  class MatchNotFoundException : public std::exception {
  private:
    const char* reason;
  public:
    MatchNotFoundException(const std::string& what) : reason(what.c_str()) {}
    MatchNotFoundException(const char* what) : reason(what) {}
    MatchNotFoundException() : reason("Could not find match") {}
    const char* what() const throw() { return reason; }
  };

  /**
   * The Match object that is returned by IRule::match()
   */
  typedef struct {
    size_t length;
    std::string result;
  } Match;

  /**
   * Interface Rule is used for Parser.
   */
  class IRule {
  public:
    /**
     * Does the given string make a match?
     *
     * @note a valid match starts at the beginning of str, and must have a
     * length of at least 1 character.
     *
     * @param str
     *
     * @return true if match is possible
     */
    virtual bool matches(const std::string& str) const = 0;
    /**
     * match the string and get the Match
     *
     * @note a valid match starts at the beginning of str, and must have a
     * length of at least 1 character.
     *
     * @param str
     *
     * @return Match object
     *
     * @throws MatchNotFoundException if no match is found
     */
    virtual Match match(const std::string& str) const = 0;

    /**
     * Get the priority of the rule.
     *
     * @note a higher value means a higher priority
     *
     * @return priority
     */
    virtual int priority() const = 0;

    virtual bool operator<(const IRule& rule) const {
      return priority() < rule.priority();
    }
    virtual bool operator>(const IRule& rule) const {
      return priority() > rule.priority();
    }

  };

  /**
   * Passthrough Rule will allow a matching string to pass through without
   * modification.
   */
  class PassthroughRule : public IRule {
  private:
    const std::string in;

    const int p;
  public:
    /**
     * Create a Passthrough Rule
     *
     * @param key
     * @param priority: 0
     */
    PassthroughRule(std::string key, int priority=0) : in(key), p(priority) {}

    bool matches(const std::string& str) const;
    Match match(const std::string& str) const;

    int priority() const { return p; }
  };

  /**
   * A simple rule that matches a string, and returns another.
   */
  class SimpleRule : public IRule {
  private:
    const std::string in;
    const std::string out;

    const int p;
  public:
    /**
     * Create a simple Rule
     *
     * @param key
     * @param value
     * @param priority: 0
     */
    SimpleRule(std::string key, std::string value, int priority=0) : in(key),
      out(value), p(priority) {}

    bool matches(const std::string& str) const;
    Match match(const std::string& str) const;

    int priority() const { return p; }
  };

  /**
   * Regex Passthrough will return the matched regex without any modification.
   */
  class RegexPassthroughRule : public IRule {
  private:
    const std::regex in;

    const int p;
  public:
    /**
     * Create a regex passthrough rule that returns the value if the key
     * matches.
     *
     * @param key regex string
     * @param priority: 0
     * @param options regex options: ECMAScript, case insensitive
     *
     * @warning the key must start with `^`
     */
    RegexPassthroughRule(std::string key, int priority=0,
        std::regex_constants::syntax_option_type options =
        std::regex_constants::ECMAScript | std::regex_constants::icase) :
      in(key, options), p(priority) {}

    bool matches(const std::string& str) const;
    Match match(const std::string& str) const;

    int priority() const { return p; }
  };

  /**
   * A regex based rule that returns a constant if it matches with the regex
   */
  class RegexRule : public IRule {
  private:
    const std::regex in;
    const std::string out;

    const int p;
  public:
    /**
     * Create a simple regex rule that returns the value if the key matches.
     *
     * @param key regex string
     * @param value output with key matches
     * @param priority: 0
     * @param options regex options: ECMAScript, case insensitive
     *
     * @warning the key must start with `^`
     */
    RegexRule(std::string key, std::string value, int priority=0,
        std::regex_constants::syntax_option_type options =
        std::regex_constants::ECMAScript | std::regex_constants::icase) :
      in(key, options), out(value), p(priority) {}

    bool matches(const std::string& str) const;
    Match match(const std::string& str) const;

    int priority() const { return p; }
  };

  /**
   * The Regex Replace Rule will replace the first group in the match with a
   * new value.
   */
  class RegexReplaceRule : public IRule {
  private:
    const std::regex in;
    const std::string out;

    const int p;
  public:
    /**
     * Create a regex based rule that replaces the first group of the regex
     * with the value matches.
     *
     * @param key regex string
     * @param value to replace the first group with
     * @param priority: 0
     * @param options regex options: ECMAScript, case insensitive
     *
     * @warning the key must start with `^`
     */
    RegexReplaceRule(std::string key, std::string value, int priority=0,
        std::regex_constants::syntax_option_type options =
        std::regex_constants::ECMAScript | std::regex_constants::icase) :
      in(key, options), out(value), p(priority) {}

    bool matches(const std::string& str) const;
    Match match(const std::string& str) const;

    int priority() const { return p; }
  };
}
}

#endif
