Param(
  [string]$CfCommit = "a56389f4efb2fb1c531e17ef8a2fde382a32c9a0",
  [string]$ClockwiseRef = "v1.4.2"
)
Set-StrictMode -Version Latest; $ErrorActionPreference="Stop"
Set-Location (Join-Path $PSScriptRoot "..")

$TP = "components/clockwise_mario_ext/third_party"
$CF = Join-Path $TP "cw-cf-0x-01"; $CF_GFX = Join-Path $CF "gfx"
$GFX = Join-Path $TP "cw-gfx-engine"; $COM = Join-Path $TP "cw-commons"
New-Item -ItemType Directory -Force -Path $CF_GFX,$GFX,$COM | Out-Null

function Grab($u,$dst){ Invoke-WebRequest -UseBasicParsing -Uri $u -OutFile $dst }

Write-Host ">> Mario (cw-cf-0x-01 @ $CfCommit)"
Grab "https://raw.githubusercontent.com/jnthas/cw-cf-0x-01/$CfCommit/Clockface.h"     (Join-Path $CF "Clockface.h")
Grab "https://raw.githubusercontent.com/jnthas/cw-cf-0x-01/$CfCommit/Clockface.cpp"   (Join-Path $CF "Clockface.cpp")
foreach($f in "assets.h","mario.h","block.h","Super_Mario_Bros__24pt7b.h"){
  Grab "https://raw.githubusercontent.com/jnthas/cw-cf-0x-01/$CfCommit/gfx/$f" (Join-Path $CF_GFX $f)
}

Write-Host ">> cw-gfx-engine (clockwise @ $ClockwiseRef)"
foreach($f in "Locator","Tile","Game","Object","ImageUtils"){
  Grab "https://raw.githubusercontent.com/jnthas/clockwise/$ClockwiseRef/firmware/lib/cw-gfx-engine/$f.h"   (Join-Path $GFX "$f.h")
  Grab "https://raw.githubusercontent.com/jnthas/clockwise/$ClockwiseRef/firmware/lib/cw-gfx-engine/$f.cpp" (Join-Path $GFX "$f.cpp")
}

Write-Host ">> cw-commons (clockwise @ $ClockwiseRef)"
foreach($f in "IClockface.h","picopixel.h","CWDateTime.h"){
  Grab "https://raw.githubusercontent.com/jnthas/clockwise/$ClockwiseRef/firmware/lib/cw-commons/$f" (Join-Path $COM $f)
}

Write-Host "Done."