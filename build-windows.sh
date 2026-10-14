#!/usr/bin/env bash
# Cross-compiles the Windows version from Linux (same as build-windows.cmd).
set -euo pipefail

IMAGE=f3rkanoid-builder
OUTPUT=dist/windows

cd "$(dirname "$0")"

if ! command -v docker >/dev/null 2>&1; then
    echo "ERROR: Docker not found. Install Docker and make sure the daemon is running." >&2
    exit 1
fi

echo "==> Building Docker image..."
echo "    (First run compiles SFML from source — takes ~5 min. Subsequent runs use the cache.)"
docker build -f Dockerfile.build -t "$IMAGE" .

echo "==> Extracting artifacts from container..."
CONTAINER=$(docker create "$IMAGE")
trap 'docker rm "$CONTAINER" >/dev/null' EXIT

rm -rf "$OUTPUT"
mkdir -p "$OUTPUT"
docker cp "$CONTAINER:/workspace/dist/." "$OUTPUT"

echo ""
echo "==> Done!  Distribution folder: $OUTPUT"
printf '%s\n' '    Run the game on Windows:  dist\windows\f3rkanoid.exe'
