#!/usr/bin/env sh
# Makro hattını ekran çıkışı olmadan çalıştırır. ROOT ortamınız farklıysa ROOT_CMD değişkenini ayarlayın.

set -eu

ROOT_CMD=${ROOT_CMD:-root}
CONFIG=${1:-config.json}

${ROOT_CMD} -l -b -q "run_all.C(\"${CONFIG}\")"
