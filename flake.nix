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
      devShells = forAllSystems (
        pkgs:
        let
          isLinux = pkgs.stdenv.hostPlatform.isLinux;
          clangTools = pkgs.llvmPackages.clang-tools;
          gcc = pkgs.gcc14Stdenv.cc;
          clangd = pkgs.writeShellScriptBin "clangd" ''
            exec ${clangTools}/bin/clangd '--query-driver=${gcc}/bin/g++' "$@"
          '';
          packages = [
            pkgs.just
            pkgs.coreutils
            pkgs.python313
            clangd
            clangTools
          ]
          ++ pkgs.lib.optional isLinux pkgs.gdb;
        in
        {
          default = (pkgs.mkShell.override { stdenv = pkgs.gcc14Stdenv; }) {
            name = "cp-gcc";
            inherit packages;
            CXX_STD = "c++17";
            CXX_HARDENING_FLAGS = "-D_GLIBCXX_DEBUG -D_GLIBCXX_ASSERTIONS";
            CXX_SANITIZER_FLAGS = pkgs.lib.optionalString isLinux "-fsanitize=address,undefined";
          };
        }
      );
    };
}
