#pragma once
#include <string>

class LoaderParams {
public:
    LoaderParams(float x, float y, float width, float height, std::string textureID, 
                 int numFrames, int callbackID = 0, int animSpeed = 0)
        : m_x(x), m_y(y), m_width(width), m_height(height), 
          m_textureID(textureID), m_numFrames(numFrames), 
          m_callbackID(callbackID), m_animSpeed(animSpeed) 
    {}

    float getX() const { return m_x; }
    float getY() const { return m_y; }
    float getWidth() const { return m_width; }
    float getHeight() const { return m_height; }
    std::string getTextureID() const { return m_textureID; }
    int getNumFrames() const { return m_numFrames; }
    int getCallbackID() const { return m_callbackID; }
    int getAnimSpeed() const { return m_animSpeed; }

private:
    float m_x, m_y;
    float m_width, m_height;
    int m_numFrames;
    int m_callbackID;
    int m_animSpeed;
    std::string m_textureID;
};