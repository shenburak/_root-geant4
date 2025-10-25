#!/usr/bin/env sh
# Execute the macro pipeline in headless mode. Adjust ROOTSYS before calling if needed.

set -eu

ROOT_CMD=${ROOT_CMD:-root}
CONFIG=${1:-config.json}

${ROOT_CMD} -l -b -q "run_all.C(\"${CONFIG}\")"
