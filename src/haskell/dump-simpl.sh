#!/bin/bash

SCRIPT_DIR=$(dirname $0)

ghc -ddump-inlinings \
    -ddump-simpl \
    -dsuppress-module-prefixes \
    -dsuppress-idinfo \
    -dsuppress-coercions \
    -dsuppress-type-applications \
    -fforce-recomp \
    -O0 \
    $SCRIPT_DIR/main.hs \
    $SCRIPT_DIR/StringableM.hs