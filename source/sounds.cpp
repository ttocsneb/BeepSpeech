#include "sounds.hpp"

using namespace beepspeech;
using std::string;

bool Sounds::put(ISound *sound) {
  string name = sound->getName();
  if (this->count(name) == 0) {
    (*this)[name] = sound;
    return true;
  }
  return false;
}

bool Sounds::load(bool stopFast) {
  bool ret = true;
  for (auto i : *this) {
    bool succ = i.second->load();
    if (stopFast) {
      if (!succ)
        return false;
    } else {
      ret = ret && succ;
    }
  }
  return ret;
}

bool Sounds::isLoaded() const {
  for (auto i : *this) {
    if (!i.second->isLoaded()) {
      return false;
    }
  }
  return true;
}
