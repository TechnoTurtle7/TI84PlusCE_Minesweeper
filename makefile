# ----------------------------
# Makefile Options
# ----------------------------

NAME = MSWPR
ICON = icon.png
DESCRIPTION = "It's minesweeper"
COMPRESSED = YES
COMPRESSED_MODE = zx0
OUTPUT_MAP = NO

CFLAGS = -Wall -Wextra -Oz
CXXFLAGS = -Wall -Wextra -Oz

# ----------------------------

include $(shell cedev-config --makefile)
