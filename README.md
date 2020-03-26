# BeepSpeech

BeepSpeech is intended to be able to create sounds for scrolling text. It has
the capability to create beep-speech similar to that of animal crossing's
animalese.

To do this, there are several provided classes:

* beepspeech::ISound audio file interface.
* beepspeech::Sounds beepspeech::ISound container
* beepspeech::Voice Sound Player
* beepspeech::phonetics::Parser Converter from text to phonetic alphabet

There are several possibilities available with BeepSpeech:

## Simple beeps

By providing one sound object, you can make simple speech. Assigning this beep
with a letter such as `b`. And creating a
beepspeech::phonetics::RegexRule('\\w', 'b'). All text provided can make beep
sounds.

## Scripted sounds

You could go one step further, and add multiple sounds, each assigned to a
different letter. These sounds can be used to make listening a bit more bearable.

## Animalese like speech

Creating a speech like beep is the most advanced use for this library. You could
use the phonetics::Parser to convert text to the used sounds, the resulting list
can be fed into a Voice to play that speech.

> Do note that if many rules are made in beepspeech::phonetics::Parser, it can
> make parsing slow, especially for long text as finding the correct rule will
> be `O log(n^2)`
