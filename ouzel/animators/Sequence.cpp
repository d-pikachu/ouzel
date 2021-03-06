// Copyright (C) 2018 Elviss Strazdins
// This file is part of the Ouzel engine.

#include <algorithm>
#include <numeric>
#include "Sequence.hpp"

namespace ouzel
{
    namespace scene
    {
        Sequence::Sequence(const std::vector<Animator*>& initAnimators):
            Animator(std::accumulate(initAnimators.begin(), initAnimators.end(), 0.0f, [](float a, Animator* b) { return a + b->getLength(); }))
        {
            for (Animator* animator : initAnimators)
            {
                addAnimator(animator);
            }
        }

        Sequence::Sequence(const std::vector<std::unique_ptr<Animator>>& initAnimators):
            Animator(std::accumulate(initAnimators.begin(), initAnimators.end(), 0.0f, [](float a, const std::unique_ptr<Animator>& b) { return a + b->getLength(); }))
        {
            for (const std::unique_ptr<Animator>& animator : initAnimators)
            {
                addAnimator(animator.get());
            }
        }

        void Sequence::play()
        {
            setProgress(0.0f);
            done = false;
            running = true;

            targetActor = actor;

            if (!targetActor)
            {
                if (parent)
                {
                    targetActor = parent->getTargetActor();
                }
            }

            if (!animators.empty())
            {
                currentAnimator = animators.front();
                currentAnimator->play();
            }
            else
            {
                currentAnimator = nullptr;
            }
        }

        void Sequence::updateProgress()
        {
            Animator::updateProgress();

            float time = 0.0f;

            for (Animator* animator : animators)
            {
                if (animator->getLength() <= 0.0f || currentTime > time + animator->getLength())
                {
                    if (animator == currentAnimator) animator->setProgress(1.0f);
                }
                else if (currentTime <= time)
                {
                    if (animator == currentAnimator) animator->setProgress(0.0f);
                }
                else
                {
                    if (currentAnimator != animator)
                    {
                        currentAnimator = animator;
                        animator->play();
                    }

                    animator->setProgress((currentTime - time) / animator->getLength());
                }

                time += animator->getLength();
            }
        }
    } // namespace scene
} // namespace ouzel
