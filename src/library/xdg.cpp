// SPDX-License-Identifier: GPL-3.0
// SPDX-FileCopyrightText: 2026 silver_gray
#include <filesystem>

std::filesystem::path xdgConfigDir()
{
    std::filesystem::path config_path;

    const char *xdg_config = getenv("XDG_CONFIG_HOME");
    if (xdg_config && xdg_config[0] != '\0')
        config_path = std::filesystem::path(xdg_config);

    const char *home = std::getenv("HOME");
    if (home && home[0] != '\0')
        config_path = std::filesystem::path(home) / ".config";

    return config_path;
}