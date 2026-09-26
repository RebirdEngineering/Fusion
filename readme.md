# Fusion

A WIP decompilation of Rovio Mobile's internal successor of their internal version of the KA3D engine.

While the "engine" is technically a bunch of standalone libraries that are still used in Unity and RCS/Beacon/SkyNest itself, this only covers the multiplatform game engine's libraries.
No tools will be included as they would heavily increase the size of the engine.

The main branch (this one) is heavily based off the revision found in Angry Birds Seasons v4.1.0 for iPhone, due to containing a lot of leftover debugging information that can pretty much fully re-symbolize the stripped executable. Other known revisions of the engine will likely be decompiled later.

Please do not confuse this for private KA3D. Fusion is exclusively for modern day platforms.

### Differencies / accuracy notes
- To reduce legal risk, we do not aim to reverse engineer anything handling DRM or IAPs, the resulting code is DRM-free, at worst dummy implementations of them will be allowed, just so games would be able to reference them.
- Certain variable/parameter names, asserts and missing methods have been reconstructed by referencing the originally semi-open-source release of the KA3D engine, reverse engineering KA3D-era and Silverlight ports of games. For more information, check the Hidden Birds Fusion documentation spreadsheet.
- Any functions vastly similar to public KA3D in the grand scale will use the original namespace macros.

### Compiling

Simply open the repo in CMake and you will be able to build the most of the libraries for targeting to a project. At the moment, the repo is not quite completed and other build types than Windows or dummy implementations are unimplemented.

### The executables used for comparison/reference (BLAKE3)

- `ea7f3ad2e21b743d1d87eb1c18e7f4f6302b7be76159b935b8a98cd9da1b21d3 (executable) + 1bc6a6c63908a8ea71f72e7bf53a535828b3791917d7a74a2994970f9af63cbd (.dSYM) AngryBirdsSeasonsFull`
	Angry Birds Seasons v4.1.0 for iPhone
- ` 950beefdcdcb45101543cf707de8919740af3d98fe7d5f9edc68c7d68e7e6d24 angrybirdsfreemagic`
	Angry Birds Free with Magic v1.1.3 for Meego + leftover debug information.
- ` 16da89de8ce40a7e2a84b7a2d894cbd60a80267ed920e44a3dfc43fb4e6127d9 angrybirdsfreemagic`
	Angry Birds Free with Magic v1.1.5 for Meego + leftover debug information.

### Miscellaneous notes

Legal notes:
- The source code of engine itself (everything in `source` and `include`) are provided as-is.
- Any modifications are licensed under MIT.
- The main focus of the project is to allow modern-day development and is done in a good faith - we don't condone 
  piracy, we just essentially want to give it a "second life".
- The decompilation project does not include any assets - you need to get them from your own copy of a game using it.
- For development on Apple platforms, a local copy of their SDKs must be manually included.

Project initially started by LolHacksRule. No AI is used for the decompiled code. Any PRs entirely using AI will be denied.

The original semi-open-source KA3D engine can be found at https://sourceforge.net/projects/ka3d/. Original engine belongs to Rovio.