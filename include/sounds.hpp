#ifndef __B_SOUNDS__
#define __B_SOUNDS__

#include <string>
#include <map>

namespace beepspeech {

/**
 * ISound is a virtual object whose children should implement the
 * loading/playing of sound files.
 */
class ISound {
private:
  std::string name;
public:
  /**
   * Create a new virtual sound object.
   *
   * @param name sound name
   */
  ISound(std::string name) : name(name) {}
  virtual ~ISound() {}

  /**
   * Get the name of the object
   *
   * @return sound name
   */
  virtual const std::string& getName() const { return name; }

  /**
   * Play the sound.
   *
   * @param speed
   * @param pitch
   *
   * @return true on success
   */
  virtual bool play(float speed=1.0, float pitch=1.0) const = 0;
  /**
   * Load the sound data
   *
   * @return true on success, or if the object is already loaded.
   */
  virtual bool load() = 0;
  /**
   * Check if the sound data is loaded
   *
   * @return true on success
   */
  virtual bool isLoaded() = 0;
};

/**
 * Sounds is a map of Sound objects.
 */
class Sounds : public std::map<std::string, ISound*> {
public:
  /**
   * Put a sound object in the object, using the sounds name as a key.
   *
   * @param sound
   *
   * @return true if the sound was placed without errors
   */
  bool put(ISound* sound);

  /**
   * Load all the sounds contained.
   *
   * @note This is the preferend method for adding sound objects.
   *
   * @param stopFast stop loading on the first unsuccessful load
   *
   * @return true if all sounds were successfully loaded
   */
  bool load(bool stopFast=false);
  /**
   * Check if all the sounds contained are loaded.
   *
   * @return true if all sounds are loaded
   */
  bool isLoaded() const;
};
}

#endif
