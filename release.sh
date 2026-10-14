#!/usr/bin/env bash
# Creates a new F3rkanoid release.
#
# Reads the current version from VERSION, lets you pick the next one
# (patch / minor / major), commits the bump, tags it as vX.Y.Z and pushes.
# The tag push triggers .github/workflows/release.yml, which builds the
# Windows and Linux binaries and publishes them as a GitHub Release.
#
# Usage: ./release.sh [--dry-run]
set -euo pipefail

BRANCH=master
REMOTE=origin

DRY_RUN=false
case "${1:-}" in
    "") ;;
    --dry-run) DRY_RUN=true ;;
    -h|--help)
        echo "Usage: ./release.sh [--dry-run]"
        echo "  --dry-run   show what would happen without changing anything"
        exit 0 ;;
    *) echo "Unknown option: $1 (try --help)" >&2; exit 1 ;;
esac

cd "$(dirname "$0")"

die() { echo "ERROR: $*" >&2; exit 1; }

# Runs a command, or only prints it in dry-run mode.
run() {
    if $DRY_RUN; then
        echo "   [dry-run] $*"
    else
        "$@"
    fi
}

tag_exists() {
    git rev-parse -q --verify "refs/tags/$1" >/dev/null \
        || git ls-remote --exit-code --tags "$REMOTE" "refs/tags/$1" >/dev/null 2>&1
}

# ---------------------------------------------------------------------------
# Safety checks
# ---------------------------------------------------------------------------
[ "$(git branch --show-current)" = "$BRANCH" ] \
    || die "you must be on '$BRANCH' to release (current: $(git branch --show-current))."

[ -z "$(git status --porcelain)" ] \
    || die "you have uncommitted changes. Commit or stash them first."

echo "==> Checking that $BRANCH is up to date with $REMOTE..."
git fetch -q "$REMOTE" "$BRANCH" --tags
[ "$(git rev-parse HEAD)" = "$(git rev-parse "$REMOTE/$BRANCH")" ] \
    || die "local $BRANCH differs from $REMOTE/$BRANCH. Pull (or push) first."

[ -f VERSION ] || die "VERSION file not found."
CURRENT=$(tr -d '[:space:]' < VERSION)
[[ "$CURRENT" =~ ^([0-9]+)\.([0-9]+)\.([0-9]+)$ ]] \
    || die "VERSION must look like 1.2.3 (found '$CURRENT')."
MAJOR=${BASH_REMATCH[1]} MINOR=${BASH_REMATCH[2]} PATCH=${BASH_REMATCH[3]}

# ---------------------------------------------------------------------------
# Menu, built from the current version
# ---------------------------------------------------------------------------
LABELS=() VERSIONS=()
if ! tag_exists "v$CURRENT"; then
    # VERSION was never released (e.g. the very first release): offer it as is.
    LABELS+=("release current  → $CURRENT   (not released yet)")
    VERSIONS+=("$CURRENT")
fi
LABELS+=("patch  → $MAJOR.$MINOR.$((PATCH + 1))   (bug fixes, small changes)")
VERSIONS+=("$MAJOR.$MINOR.$((PATCH + 1))")
LABELS+=("minor  → $MAJOR.$((MINOR + 1)).0   (new features)")
VERSIONS+=("$MAJOR.$((MINOR + 1)).0")
LABELS+=("major  → $((MAJOR + 1)).0.0   (big or incompatible changes)")
VERSIONS+=("$((MAJOR + 1)).0.0")
LABELS+=("cancel")

echo ""
echo "Current version: $CURRENT"
echo ""
PS3=$'\nChoose the release type: '
select _ in "${LABELS[@]}"; do
    [[ "$REPLY" =~ ^[0-9]+$ ]] && (( REPLY >= 1 && REPLY <= ${#LABELS[@]} )) && break
    echo "Invalid choice, type a number from the list."
done
# Ctrl+D ends the menu without a valid choice.
[[ "${REPLY:-}" =~ ^[0-9]+$ ]] || { echo ""; echo "Cancelled."; exit 0; }
(( REPLY == ${#LABELS[@]} )) && { echo "Cancelled."; exit 0; }

NEW=${VERSIONS[REPLY - 1]}
TAG="v$NEW"
tag_exists "$TAG" && die "tag $TAG already exists."

# ---------------------------------------------------------------------------
# Summary and confirmation
# ---------------------------------------------------------------------------
LAST_TAG=$(git describe --tags --abbrev=0 2>/dev/null || true)
echo ""
echo "==> About to release $TAG"
if [ -n "$LAST_TAG" ]; then
    echo "    Changes since $LAST_TAG:"
    git log --oneline --no-merges "$LAST_TAG..HEAD" | sed 's/^/      /'
else
    echo "    (first release)"
fi
echo ""
if [ "$NEW" != "$CURRENT" ]; then
    echo "    1. Update VERSION: $CURRENT → $NEW and commit \"Release $TAG\""
else
    echo "    1. VERSION is already $NEW, nothing to commit"
fi
echo "    2. Create tag $TAG"
echo "    3. Push to $REMOTE (this starts the GitHub build and publishes the release)"
echo ""

if ! $DRY_RUN; then
    read -r -p "Proceed? [y/N] " ANSWER || ANSWER=""
    [[ "$ANSWER" =~ ^[yY]$ ]] || { echo "Cancelled."; exit 0; }
fi

# ---------------------------------------------------------------------------
# Release
# ---------------------------------------------------------------------------
if [ "$NEW" != "$CURRENT" ]; then
    if $DRY_RUN; then
        echo "   [dry-run] echo $NEW > VERSION"
    else
        echo "$NEW" > VERSION
    fi
    run git add VERSION
    run git commit -q -m "Release $TAG"
fi
run git tag -a "$TAG" -m "F3rkanoid $NEW"
# --atomic: the commit and the tag are pushed together, or neither is.
run git push --atomic "$REMOTE" "$BRANCH" "$TAG"

REPO_URL=$(git remote get-url "$REMOTE" | sed -E 's#^git@github.com:#https://github.com/#; s#\.git$##')
echo ""
echo "==> Released $TAG$($DRY_RUN && echo ' (dry run, nothing was changed)')"
echo "    Build progress: $REPO_URL/actions"
echo "    Release page:   $REPO_URL/releases/tag/$TAG   (ready in ~10-15 min)"
