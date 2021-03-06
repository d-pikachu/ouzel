// Copyright (C) 2018 Elviss Strazdins
// This file is part of the Ouzel engine.

#pragma once

#include <list>
#include "scene/Component.hpp"
#include "math/Size2.hpp"
#include "math/Vector2.hpp"
#include "scene/SpriteData.hpp"
#include "core/UpdateCallback.hpp"
#include "graphics/Material.hpp"

namespace ouzel
{
    namespace scene
    {
        class SceneManager;

        class Sprite: public Component
        {
        public:
            static const uint32_t TYPE = Component::SPRITE;

            Sprite();
            Sprite(const SpriteData& spriteData);
            Sprite(const std::string& filename, bool mipmaps = true,
                   uint32_t spritesX = 1, uint32_t spritesY = 1,
                   const Vector2& pivot = Vector2(0.5f, 0.5f));
            Sprite(std::shared_ptr<graphics::Texture> texture,
                   uint32_t spritesX = 1, uint32_t spritesY = 1,
                   const Vector2& pivot = Vector2(0.5f, 0.5f));

            bool init(const SpriteData& spriteData);
            bool init(const std::string& filename, bool mipmaps = true,
                      uint32_t spritesX = 1, uint32_t spritesY = 1,
                      const Vector2& pivot = Vector2(0.5f, 0.5f));
            bool init(std::shared_ptr<graphics::Texture> newTexture,
                      uint32_t spritesX = 1, uint32_t spritesY = 1,
                      const Vector2& pivot = Vector2(0.5f, 0.5f));

            void update(float delta);

            virtual void draw(const Matrix4& transformMatrix,
                              float opacity,
                              const Matrix4& renderViewProjection,
                              const std::shared_ptr<graphics::Texture>& renderTarget,
                              const Rect& renderViewport,
                              bool depthWrite,
                              bool depthTest,
                              bool wireframe,
                              bool scissorTest,
                              const Rect& scissorRectangle) override;

            inline const std::shared_ptr<graphics::Material>& getMaterial() const { return material; }
            inline void setMaterial(const std::shared_ptr<graphics::Material>& newMaterial) { material = newMaterial; }

            inline const Vector2& getOffset() const { return offset; }
            void setOffset(const Vector2& newOffset);

            void play();
            void stop(bool resetAnimation = true);
            void reset();
            inline bool isPlaying() const { return playing; }

            inline const std::map<std::string, SpriteData::Animation>& getAnimations() const { return animations; }
            inline const SpriteData::Animation* getAnimation() const { return currentAnimation->animation; }
            inline std::string getAnimationName() const { return currentAnimation->animation->name; }
            bool hasAnimation(const std::string& animation) const;
            void setAnimation(const std::string& newAnimation, bool repeat = true);
            void addAnimation(const std::string& newAnimation, bool repeat = true);
            void setAnimationProgress(float progress);
            void setAnimationTime(float time);

        protected:
            void updateBoundingBox();

            std::shared_ptr<graphics::Material> material;
            std::map<std::string, SpriteData::Animation> animations;

            struct QueuedAnimation
            {
                const SpriteData::Animation* animation;
                bool repeat;
            };

            std::list<QueuedAnimation> animationQueue;
            std::list<QueuedAnimation>::iterator currentAnimation;

            std::shared_ptr<graphics::Texture> whitePixelTexture;

            Vector2 offset;
            Matrix4 offsetMatrix = Matrix4::IDENTITY;

            bool playing = false;
            bool running = false;
            float currentTime = 0.0f;

            UpdateCallback updateCallback;
        };
    } // namespace scene
} // namespace ouzel
