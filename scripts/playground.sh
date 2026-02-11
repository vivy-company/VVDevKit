#!/usr/bin/env bash
set -euo pipefail

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
SCHEME="VVDevKitPlayground"
CONFIG="${1:-Debug}"
DERIVED_DATA="${ROOT_DIR}/build"
DESTINATION="platform=macOS"

echo "Building ${SCHEME} (${CONFIG})..."
xcodebuild \
  -scheme "${SCHEME}" \
  -configuration "${CONFIG}" \
  -destination "${DESTINATION}" \
  -derivedDataPath "${DERIVED_DATA}" \
  build

APP_PATH="${DERIVED_DATA}/Build/Products/${CONFIG}/${SCHEME}.app"
EXE_PATH="${DERIVED_DATA}/Build/Products/${CONFIG}/${SCHEME}"
if [[ ! -x "${EXE_PATH}" ]]; then
  echo "Build succeeded but .app not found at ${APP_PATH}" >&2
  echo "Executable not found at ${EXE_PATH}" >&2
  exit 1
fi

APP_ROOT="${APP_PATH}/Contents"
MACOS_DIR="${APP_ROOT}/MacOS"
RES_DIR="${APP_ROOT}/Resources"
mkdir -p "${MACOS_DIR}" "${RES_DIR}"

if [[ ! -d "${APP_PATH}" ]]; then
  echo "No .app produced by xcodebuild; bundling executable..."
  cat > "${APP_ROOT}/Info.plist" <<EOF
<?xml version="1.0" encoding="UTF-8"?>
<!DOCTYPE plist PUBLIC "-//Apple//DTD PLIST 1.0//EN" "http://www.apple.com/DTDs/PropertyList-1.0.dtd">
<plist version="1.0">
<dict>
  <key>CFBundleName</key>
  <string>${SCHEME}</string>
  <key>CFBundleIdentifier</key>
  <string>com.vvdevkit.${SCHEME}</string>
  <key>CFBundleExecutable</key>
  <string>${SCHEME}</string>
  <key>CFBundlePackageType</key>
  <string>APPL</string>
  <key>CFBundleVersion</key>
  <string>1</string>
  <key>CFBundleShortVersionString</key>
  <string>1.0</string>
  <key>LSMinimumSystemVersion</key>
  <string>13.0</string>
</dict>
</plist>
EOF
fi

cp "${EXE_PATH}" "${MACOS_DIR}/${SCHEME}"

for bundle in "${DERIVED_DATA}/Build/Products/${CONFIG}"/*.bundle; do
  if [[ -d "${bundle}" ]]; then
    cp -R "${bundle}" "${RES_DIR}/"
  fi
done

echo "Built app: ${APP_PATH}"
open "${APP_PATH}"
