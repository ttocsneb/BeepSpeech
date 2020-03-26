#include "voice.hpp"

/**
 * All code available in BeepSpeech
 */
using namespace beepspeech;
using std::string;

bool Voice::valid() const {
  for (string sound : sequence) {
    if (!sounds.count(sound)) {
      return false;
    }
  }
  return true;
}

bool Voice::next() {
  ISound* sound = sounds[sequence.at(i)];
  i++;
  return sound->play(speed, pitch);
}

bool Voice::playAll(bool stopFast) {
  bool ret = true;
  for (auto sound=sequence.begin() + i;sound!=sequence.end();++sound) {
    ++i;
    bool result = sounds[*sound]->play(speed, pitch);
    if (!result) {
      if(stopFast) {
        return false;
      }
      ret = false;
    }
  }
  return ret;
}
