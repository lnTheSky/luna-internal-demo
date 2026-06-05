# luna_internal

Visual Studio C++ solution for a DX11 internal overlay/hooking project built around MinHook and Dear ImGui.

## Overview

The repo is organized as a traditional Visual Studio solution rather than a manifest-driven project. The main binary is a DLL in `Internal Base/`, with `minhook/` built as a bundled static library.

The checked-in code currently implements a Present-hooked ImGui overlay, entity-driven ESP, an aimbot/legitbot path, and a small menu layer for runtime toggles and color settings.

## Highlights

| Area | Status | Notes |
| --- | --- | --- |
| DX11 Present hook | Implemented | Set up in `src/core/Hooks.cpp` via MinHook |
| ImGui overlay | Implemented | Initialized from `hkPresent()` |
| ESP box | Implemented | Configurable in menu |
| ESP skeleton | Implemented | Uses bone connections from SDK helpers |
| ESP health bar | Implemented | Drawn per visible target |
| ESP name | Partial | Present in code, but marked unstable in comments |
| Enemy counter | Implemented | Simple text overlay |
| Aimbot / legitbot | Implemented | FOV ring, smoothing, recoil compensation |
| Misc features | Placeholder | `Misc::Render()` exists but is empty |
| Bhop | Placeholder | File exists, no implementation in checked-in source |
| Chams | Not compiled | Files exist on disk but are not in `.vcxproj` |

## Repository Layout

| Path | Purpose |
| --- | --- |
| `Internal Base.sln` | Top-level Visual Studio solution |
| `Internal Base/` | Main DLL project |
| `minhook/` | MinHook static library project |
| `Internal Base/src/core/` | DLL entrypoint and hook setup |
| `Internal Base/src/feature/` | Visual/combat/misc features |
| `Internal Base/src/menu/` | ImGui menu rendering |
| `Internal Base/src/sdk/` | Entity access, offsets, math, memory helpers |
| `Internal Base/dumper/` | Checked-in generated offset/schema headers |

## Runtime Flow

1. `DllMain` in `Internal Base/src/core/Main.cpp` starts `MainThread`.
2. `MainThread` calls `Hooks::Setup()` and waits until `VK_END` is pressed.
3. `Hooks::Setup()` creates a temporary DX11 swapchain to grab the `Present` vtable slot and installs the hook.
4. `Hooks::hkPresent()` initializes ImGui/DX11 once, updates `EntityManager`, copies the view matrix from `client.dll + Offsets::dwViewMatrix`, and renders the menu plus enabled features every frame.
5. `Hooks::Destroy()` removes hooks and shuts ImGui down on unload.

## Controls

| Key | Action |
| --- | --- |
| `Insert` | Open or close the menu |
| `End` | Unload the DLL |
| `F1` | Default ESP toggle bind |
| `F2` | Default aim toggle bind |

ESP and aim binds can also be reassigned from the menu.

## Build

This repo does not use CMake, Meson, or a package manager manifest. The source of truth for builds is the checked-in Visual Studio solution and project files.

Recommended target:

| Setting | Value |
| --- | --- |
| Solution | `Internal Base.sln` |
| Configuration | `Debug|x64` |
| Main output | DLL from `Internal Base` |
| Dependency | `minhook` static library |

Build notes:

- `Debug|x64` is the safest configuration to work from.
- New `.cpp` and `.h` files are not auto-discovered.
- If you add a source file, also add it to `Internal Base/Internal Base.vcxproj` and usually `Internal Base/Internal Base.vcxproj.filters`.
- Files present on disk are not necessarily part of the build.

## Build Matrix Notes

| Config | State | Notes |
| --- | --- | --- |
| `Debug|x64` | Recommended | Least machine-specific checked-in target |
| `Release|x64` | Fragile | Uses checked-in absolute paths in the main project |
| `OLLVM|x64` | Fragile | Uses LLVM-specific settings and local path assumptions |
| `Win32` variants | Present | Available in project files, but less useful than x64 |

## Toolchain Quirks

- `Internal Base/Internal Base.vcxproj` uses `v143` and mixes language standard settings by configuration.
- `minhook/minhook.vcxproj` uses `ClangCL` for `Release|x64`.
- Some non-debug configurations contain checked-in absolute paths under include/library settings.
- `msbuild` is not available in the current OpenCode CLI environment here, so real build verification may require Visual Studio or a Developer Command Prompt.

## Offsets

Offsets are mostly exposed through checked-in generated headers under `Internal Base/dumper/`.

When offsets change:

1. Refresh `Internal Base/dumper/` from `a2x/cs2-dumper` output.
2. Prefer replacing generated files rather than hand-editing schema headers.
3. Keep manual offsets documented when no generated source exists.

Known manual offset still present in source:

- `Internal Base/src/sdk/memory/Offsets.h`: `m_aimPunchCache = 0x16F0`

## Known Limitations

| Area | Limitation |
| --- | --- |
| Testing | No repo-local automated tests, lint, or CI |
| `Misc` | Placeholder only |
| `bhop` | Placeholder only |
| Name ESP | Code comment notes instability under OLLVM/SEH-related conditions |
| Chams | Not wired into the Visual Studio project |
