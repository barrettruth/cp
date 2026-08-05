{
  description = "competitive programming toolchain";

  inputs.nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";

  outputs =
    { nixpkgs, ... }:
    let
      systems = [
        "aarch64-darwin"
        "aarch64-linux"
        "x86_64-darwin"
        "x86_64-linux"
      ];
      forAllSystems = f: nixpkgs.lib.genAttrs systems (system: f nixpkgs.legacyPackages.${system});
    in
    {
      devShells = forAllSystems (pkgs: {
        default = (pkgs.mkShell.override { stdenv = pkgs.gcc14Stdenv; }) {
          packages = [
            pkgs.just
            pkgs.clang-tools
            pkgs.coreutils
          ]
          ++ pkgs.lib.optional pkgs.stdenv.hostPlatform.isLinux pkgs.gdb;
        };
      });
    };
}
