#include "pch.h"
#include "Sound.h"

Audio::Sound::Sound(FMOD::System* system, FMOD::ChannelGroup* group, const char* path, bool isLoop)
    : _system(system), _channel(nullptr), _group(group)
{
    _system->createSound(path, isLoop ? FMOD_LOOP_NORMAL : FMOD_DEFAULT, nullptr, &_sound);
    _system->getSoftwareFormat(&_rate, nullptr, nullptr);
}

Audio::Sound::~Sound()
{
    Sound::Stop();
    _sound->release();
    _sound = nullptr;
}

void Audio::Sound::Play()
{
    _system->playSound(_sound, _group, false, &_channel);
}

void Audio::Sound::Stop()
{
    if (_channel == nullptr) return;
    _channel->removeFadePoints(0, _rate);
    _channel->stop();
    _channel = nullptr;
}

bool Audio::Sound::IsPlaying() const
{
    if (_channel == nullptr) return false;
    bool isPlaying;
    _channel->isPlaying(&isPlaying);
    return isPlaying;
}

void Audio::Sound::Pause()
{
    if (_channel == nullptr) return;
    if (IsPaused()) return;
    _channel->setPaused(true);
}

void Audio::Sound::Resume()
{
    if (_channel == nullptr) return;
    if (!IsPaused()) return;
    _channel->setPaused(false);
}

bool Audio::Sound::IsPaused() const
{
    if (_channel == nullptr) return false;
    bool isPaused;
    _channel->getPaused(&isPaused);
    return isPaused;
}

void Audio::Sound::SetVolume(const float volume)
{
    if (_channel == nullptr) return;
    _channel->setVolume(volume);
}

float Audio::Sound::GetVolume() const
{
    if (_channel == nullptr) return 0.f;
    float volume;
    _channel->getVolume(&volume);
    return volume;
}

void Audio::Sound::Mute()
{
    if (_channel == nullptr) return;
    if (IsMuted()) return;
    _channel->setMute(true);
}

void Audio::Sound::Unmute()
{
    if (_channel == nullptr) return;
    if (!IsMuted()) return;
    _channel->setMute(false);
}

bool Audio::Sound::IsMuted() const
{
    if (_channel == nullptr) return false;
    bool isMute;
    _channel->getMute(&isMute);
    return isMute;
}

void Audio::Sound::FadeIn(float fadeTime)
{
    if (!IsPlaying()) return;
    if (fadeTime <= 0.f) return;
    const unsigned long long start = GetDspClock();
    const unsigned long long end = start + GetSampleRateTime(fadeTime);
    _channel->removeFadePoints(start, end);
    _channel->addFadePoint(start, 0.f);
    _channel->addFadePoint(end, 1.f);
}

void Audio::Sound::FadeOut(float fadeTime)
{
    if (!IsPlaying()) return;
    if (fadeTime <= 0.f) return;
    const unsigned long long start = GetDspClock();
    const unsigned long long end = start + GetSampleRateTime(fadeTime);
    _channel->removeFadePoints(start, end);
    _channel->addFadePoint(start, 1.f);
    _channel->addFadePoint(end, 0.f);
}

void Audio::Sound::SetDelay(float delayTime)
{
    if (_channel == nullptr) return;
    _channel->setDelay(GetDspClock() + GetSampleRateTime(delayTime), 0, false);
}

float Audio::Sound::GetLength() const
{
    if (_channel == nullptr) return 0.f;
    unsigned int length;
    _sound->getLength(&length, FMOD_TIMEUNIT_MS);
    return static_cast<float>(length) / 1000.f;
}

unsigned long long Audio::Sound::GetDspClock() const
{
    unsigned long long dspClock;
    _channel->getDSPClock(nullptr, &dspClock);
    return dspClock;
}

unsigned long long Audio::Sound::GetSampleRateTime(const float time) const
{
    return static_cast<unsigned long long>(time * static_cast<double>(_rate));
}

unsigned int Audio::Sound::GetPosition() const
{
    unsigned int position;
    _channel->getPosition(&position, FMOD_TIMEUNIT_PCM);
    return position;
}
