$ErrorActionPreference = "Stop"

$image  = "f3rkanoid-builder"
$output = "dist\windows"

# Verify Docker is available
if (-not (Get-Command docker -ErrorAction SilentlyContinue)) {
    Write-Error "Docker not found. Make sure Docker Desktop is running."
    exit 1
}

Write-Host "==> Building Docker image..."
Write-Host "    (First run compiles SFML from source — takes ~5 min. Subsequent runs use the cache.)"
docker build -f Dockerfile.build -t $image .
if ($LASTEXITCODE -ne 0) { Write-Error "Docker build failed."; exit 1 }

Write-Host "==> Extracting artifacts from container..."
$container = docker create $image
if ($LASTEXITCODE -ne 0) { Write-Error "docker create failed."; exit 1 }

New-Item -ItemType Directory -Force -Path $output | Out-Null
docker cp "${container}:/workspace/dist/." $output
docker rm $container | Out-Null

Write-Host ""
Write-Host "==> Done!  Distribution folder: $output"
Write-Host "    Run the game:  .\$output\f3rkanoid.exe"
