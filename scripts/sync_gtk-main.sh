# SPDX-License-Identifier: GPL-3.0
# SPDX-FileCopyrightText: 2026 silver_gray
#!/bin/bash

git switch gtk-main &&
git fetch origin &&
git rebase origin/gtk-development &&
git push --force-with-lease origin gtk-main &&
git switch gtk-development
