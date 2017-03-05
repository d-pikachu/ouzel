// Copyright (C) 2017 Elviss Strazdins
// This file is part of the Ouzel engine.

#include "ImageDataSTB.h"
#include "utils/Log.h"
#include "core/Application.h"
#include "files/FileSystem.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

namespace ouzel
{
    namespace graphics
    {
        bool ImageDataSTB::initFromFile(const std::string& newFilename)
        {
            filename = newFilename;

            std::vector<uint8_t> newData;
            if (!sharedApplication->getFileSystem()->readFile(newFilename, newData))
            {
                return false;
            }

            return initFromBuffer(newData);
        }

        bool ImageDataSTB::initFromBuffer(const std::vector<uint8_t>& newData)
        {
            int width;
            int height;
            int comp;

            stbi_uc* tempData = stbi_load_from_memory(newData.data(), static_cast<int>(newData.size()), &width, &height, &comp, STBI_rgb_alpha);

            if (!tempData)
            {
                Log(Log::Level::ERR) << "Failed to open texture file " << filename << ", reason: " << stbi_failure_reason();
                return false;
            }

            data.assign(tempData, tempData + (width * height * 4));

            stbi_image_free(tempData);

            size.v[0] = static_cast<float>(width);
            size.v[1] = static_cast<float>(height);

            return true;
        }
    } // namespace graphics
} // namespace ouzel