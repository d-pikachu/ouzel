// Copyright (C) 2018 Elviss Strazdins
// This file is part of the Ouzel engine.

#pragma once

#include <vector>
#include "animators/Animator.hpp"

namespace ouzel
{
    namespace scene
    {
        class Parallel: public Animator
        {
        public:
            Parallel(const std::vector<Animator*>& initAnimators);
            Parallel(const std::vector<std::unique_ptr<Animator>>& initAnimators);

        protected:
            virtual void updateProgress() override;
        };
    } // namespace scene
} // namespace ouzel
