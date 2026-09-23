# SPDX-License-Identifier: GPL-3.0
# SPDX-FileCopyrightText: 2026 silver_gray
#!/bin/bash

clang-format -i $(find src -name '*.cpp') $(find src -name '*.h') &&
clang-tidy --quiet --fix -p . $(find src -name '*.cpp') $(find src -name '*.h')
