#pragma once

#include <memory>
#include <unordered_map>

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>

namespace sen {

template <typename T>
using CacheMap = std::unordered_map<std::string, std::weak_ptr<T>>;

/**
  * @brief  Loads an sfml type from file and 
  * returns a shared_ptr to it
  * @param  pathFile: path to file 
  */
template <typename T>
inline std::shared_ptr<T> loadFromFile(const std::string& pathFile) {
  static_assert(true);
}

template <>
inline std::shared_ptr<sf::Font> loadFromFile<sf::Font>(const std::string& pathFile) {
  auto font = std::make_shared<sf::Font>();
  if (!font->loadFromFile(pathFile))
    return nullptr;
  return font;
}

template <>
inline std::shared_ptr<sf::Music> loadFromFile<sf::Music>(const std::string& pathFile) {
  auto mus = std::make_shared<sf::Music>();
  if (!mus->openFromFile(pathFile))
    return nullptr;
  return mus;
}

template <>
inline std::shared_ptr<sf::SoundBuffer> loadFromFile<sf::SoundBuffer>(const std::string& pathFile) {
  auto sb = std::make_shared<sf::SoundBuffer>();
  if (!sb->loadFromFile(pathFile))
    return nullptr;
  return sb;
}

template <>
inline std::shared_ptr<sf::Texture> loadFromFile<sf::Texture>(const std::string& pathFile) {
  auto tex = std::make_shared<sf::Texture>();
  if (!tex->loadFromFile(pathFile))
    return nullptr;
  return tex;
}

class CacheSystem {
  static CacheMap<sf::Font> m_fonts;
  static CacheMap<sf::Music> m_musics;
  static CacheMap<sf::SoundBuffer> m_soundBuffers;
  static CacheMap<sf::Texture> m_textures;

  static float s_time;
  static float s_updateTime;

 public:
  /**
		* @brief  Returns an instance of sf::Font.
		* @note   if the object cannot be loaded from file * it returns nullptr.
		* @param  pathFile: a path to file
		* @retval 
		*/
  static std::shared_ptr<sf::Font> getFont(const std::string& pathFile) {
    auto& map = getFontMap();
    return getResource(map, pathFile);
  }

  /**
		* @brief  Returns an instance of sf::Music.
		* @note   if the object cannot be loaded from file * it returns nullptr.
		* @param  pathFile: a path to file
		* @retval 
		*/
  static std::shared_ptr<sf::Music> getMusic(const std::string& pathFile) {
    auto& map = getMusicMap();
    return getResource(map, pathFile);
  }

  /**
		* @brief  Returns an instance of sf::Font.
		* @note   if the object cannot be loaded from file * it returns nullptr.
		* @param  pathFile: a path to file
		* @retval 
		*/
  static std::shared_ptr<sf::SoundBuffer> getSoundBuffer(const std::string& pathFile) {
    auto& map = getSoundBufferMap();
    return getResource(map, pathFile);
  }

  /**
		* @brief  Returns an instance of sf::Texture.
		* @note   if the object cannot be loaded from file * it returns nullptr.
		* @param  pathFile: a path to file
		* @retval 
		*/
  static std::shared_ptr<sf::Texture> getTexture(const std::string& pathFile) {
    auto& map = getTextureMap();
    return getResource(map, pathFile);
  }

  /**
		* @brief  Removes all weak_ptrs to the object that
		* are not longer used and frees the memory they were
		* holding
		*/
  static void update(float deltaTime);

 private:
  /**
		* @brief  Helper method that updates the map 
		* and removes all weak_ptrs
		*/
  template <typename T>
  static void updateMap(CacheMap<T>& map) {
    for (auto weak = map.cbegin(); weak != map.cend();) {
      if (weak->second.expired()) {
        weak = map.erase(weak);
      } else {
        ++weak;
      }
    }
  }

  template <typename T>
  static std::shared_ptr<T> getResource(CacheMap<T>& map, const std::string pathFile) {
    auto ptr = map[pathFile].lock();

    if (!ptr) {
      ptr = loadFromFile<T>(pathFile);
      map[pathFile] = ptr;
    }

    return ptr;
  }

  static CacheMap<sf::Font>& getFontMap() {
    return m_fonts;
  }

  static CacheMap<sf::Music>& getMusicMap() {
    return m_musics;
  }

  static CacheMap<sf::SoundBuffer>& getSoundBufferMap() {
    return m_soundBuffers;
  }

  static CacheMap<sf::Texture>& getTextureMap() {
    return m_textures;
  }
};

}  // namespace sen