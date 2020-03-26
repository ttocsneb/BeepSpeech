#ifndef __B_VOICE__
#define __B_VOICE__

#include "sounds.hpp"
#include <string>
#include <vector>

/**
 * All BeepSpeech code
 */
namespace beepspeech {

/**
 * Voice is the main class that plays audio clips.
 *
 * To play sounds, the Voice Object should be provided with all available
 * sounds, then call play() to start a sequence of sounds. If you are
 * converting text to sound, use phonetics::Parser
 */
class Voice {
private:
  Sounds sounds;
  std::vector<std::string> sequence;

  float speed;
  float pitch;

  size_t i;

  bool r;
public:
  /**
   * Create a Voice Object using an iterable list of Sound objects
   *
   * @param sounds iterable
   */
  template<typename Iterable> Voice(Iterable sounds) : sounds(sounds.begin(),
    sounds.end()), r(false) {}
  /**
   * Create a Voice Object
   *
   * @param sounds Sounds
   */
  Voice(Sounds sounds) : sounds(sounds), r(false) {}
  /**
   * Create an empty Voice Object
   */
  Voice() : r(false) {}

  /**
   * Load a sequence of sounds to play
   *
   * @param sequence an object that contains a begin and end function.
   * @param speed
   * @param pitch
   *
   * @note sequence should be a list of Sound names, you can use
   * phonetics::Parser to convert text into the list
   *
   * @return true if all elements are valid sounds
   */
  template<typename Iterable> bool play(const Iterable& sequence,
      float speed=1, float pitch=1) {
    this->speed = speed;
    this->pitch = pitch;
    this->sequence = std::vector<std::string>(sequence.begin(),
      sequence.end());
    i = 0;
    r = true;
    return valid();
  }

  /**
   * Check if all the sounds in the sound sequence is valid.
   *
   * @return true if all sounds in sequence is valid.
   */
  bool valid() const;

  /**
   * Play the next sound in the sequence.
   *
   * @return true if successful
   */
  bool next();
  /**
   * Play all of the sounds in the sequence from the current position.
   *
   * @param stopFast should the playback stop if one of the sounds fail
   *
   * @return true if all of the sounds were played successfully
   */
  bool playAll(bool stopFast=false);
  /**
   * Check if the sound sequence is complete
   *
   * @return true if complete
   */
  bool complete() const { return i >= sequence.size(); }
  /**
   * Check if the voice is ready to play.
   *
   * It is ready to play after play() is called populating sequence with
   * sounds to play.
   *
   * @return true if ready to play sounds
   */
  bool ready() const { return r; }

};
}

#endif
